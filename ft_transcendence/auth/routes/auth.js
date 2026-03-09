import jwtService from '../services/jwt.js';
import User, {
	saveUser,
	findUserById,
	findUserByEmail,
	incrementLoginAttempts,
	resetLoginAttempts,
	findOrCreateOAuthUser
} from '../services/user.js';
import { validateLogin, validateRegistration } from '../middleware/validation.js';
import fastifyPassport from '@fastify/passport';
import { configurePassport } from '../config/oauth.js';

export default async function authRoutes(fastify, options) {

	fastify.post('/login', { preHandler: validateLogin }, async (request, reply) => {
		const { email, password } = request.body;

		try {
			const user = await findUserByEmail(email);
			if (!user) {
				return reply.status(401).send({
					success: false,
					error: 'messages.invalidCredentials'
				});
			}

			if (user.isAccountLocked()) {
				return reply.status(423).send({
					success: false,
					error: 'auth.accountLocked'
				});
			}

			const isValidPassword = await user.verifyPassword(password);
			if (!isValidPassword) {
				await incrementLoginAttempts(user.id);
				return reply.status(401).send({
					success: false,
					error: 'messages.invalidCredentials'
				});
			}

			await resetLoginAttempts(user.id);

			if (user.two_factor_enabled) {
				const tempToken = await jwtService.generateToken({
					id: user.id,
					temp2FA: true
				}, { expiresIn: '5m' });

				return {
					success: true,
					requires2FA: true,
					tempToken
				};
			}

			const token = await jwtService.generateToken({
				id: user.id,
				username: user.username,
				email: user.email
			});

			return {
				success: true,
				token,
				user: user.toSafeJSON()
			};
		} catch (error) {
			console.error('Login error:', error);
			return reply.status(503).send({
				success: false,
				error: 'common.internalError'
			});
		}
	});

	fastify.post('/register', { preHandler: validateRegistration }, async (request, reply) => {
		const { username, email, password } = request.body;

		const existingUser = await findUserByEmail(email);
		if (existingUser) {
			return reply.status(409).send({
				success: false,
				error: 'auth.userExists'
			});
		}

		const newUser = {
			id: 'user_' + Math.random().toString(36).substr(2, 9) + Date.now().toString(36),
			username,
			username,
			email,
			password,
			two_factor_enabled: false
		};

		const savedUser = await saveUser(newUser);
		if (!savedUser) {
			return reply.status(503).send({
				success: false,
				error: 'auth.creationError'
			});
		}

		const token = await jwtService.generateToken({
			id: savedUser.id,
			username: savedUser.username,
			email: savedUser.email
		});

		return {
			success: true,
			token,
			user: savedUser.toSafeJSON()
		};
	});




	fastify.get('/health', async () => ({
		service: 'auth-service',
		status: 'OK',
		url: 'http://auth:3000',
		timestamp: new Date().toISOString(),
		version: '1.0.0',
		endpoints: ['/auth', '/2fa']
	}));


}