import jwtService from '../services/jwt.js';
import User, {
	saveUser,
	findUserById,
	findUserByEmail,
	getAllUsers,
	incrementLoginAttempts,
	resetLoginAttempts,
	updateUser,
	findOrCreateOAuthUser
} from '../services/user.js';
import { validateLogin, validateRegistration, validateProfileUpdate } from '../middleware/validation.js';
import fastifyPassport from '@fastify/passport';
import { configurePassport } from '../config/oauth.js';
import { authenticateJWT } from '../middleware/auth.js';
import validationService from '../services/validation.js';

export default async function userRoutes(fastify, options) {

	fastify.get('/list', {
		preHandler: [authenticateJWT]
	}, async (request, reply) => {
		try {
			const users = await getAllUsers();
			const safeUsers = users.map(user => ({
				id: user.id,
				username: user.username || 'N/A',
				displayName: user.display_name || 'N/A',
				email: user.email || 'N/A',
				twoFactorEnabled: user.twoFactorEnabled || false,
				isActive: user.isActive !== false,
				createdAt: user.createdAt,
				updatedAt: user.updatedAt,
				oauthProvider: user.oauth_provider,
				isAnonymized: user.isAnonymized || false
			}));
			return { success: true, users: safeUsers };
		} catch (error) {
			return reply.status(503).send({
				error: 'admin.errorLoading',
				code: 'USERS_LOAD_ERROR'
			});
		}
	});

	fastify.get('/profile-data', async (request, reply) => {
		const userId = request.headers['x-user-id'] ||
			(request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);

		if (!userId) {
			return reply.status(401).send({
				success: false,
				error: 'messages.authError'
			});
		}

		try {
			const user = await findUserById(userId);
			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}
			return {
				success: true,
				user: user.toSafeJSON()
			};
		} catch (error) {
			return reply.status(503).send({
				success: false,
				error: 'common.internalError'
			});
		}
	});

	fastify.put('/profile-data', {
		preHandler: [validateProfileUpdate]
	}, async (request, reply) => {
		const userId = request.headers['x-user-id'] ||
			(request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);

		if (!userId) {
			return reply.status(401).send({
				success: false,
				error: 'messages.authError'
			});
		}

		try {
			const { display_name, avatar, email } = request.body;

			const user = await findUserById(userId);
			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}

			// Check if email is already in use by another user
			if (email !== undefined) {
				const existingUser = await findUserByEmail(email);
				if (existingUser && existingUser.id !== userId) {
					return reply.status(409).send({
						success: false,
						error: 'profile.emailInUse',
						code: 'EMAIL_IN_USE'
					});
				}
			}

			const updateData = {};
			if (display_name !== undefined) updateData.display_name = display_name;
			if (avatar !== undefined) updateData.avatar = avatar;
			if (email !== undefined) updateData.email = email;

			if (Object.keys(updateData).length > 0) {
				try {
					await updateUser(user.id, updateData);
				} catch (updateError) {
					// Handle SQLite UNIQUE constraint error
					if (updateError.message && updateError.message.includes('UNIQUE constraint')) {
						return reply.status(409).send({
							success: false,
							error: 'profile.emailInUse',
							code: 'EMAIL_IN_USE'
						});
					}
					throw updateError;
				}
			}

			const updatedUser = await findUserById(userId);
			return {
				success: true,
				user: updatedUser.toSafeJSON()
			};
		} catch (error) {
			console.error('Profile update error:', error);
			return reply.status(503).send({
				success: false,
				error: 'common.internalError',
				code: 'INTERNAL_ERROR'
			});
		}
	});

	fastify.get('/profile', {
		preHandler: async (req, reply) => {
			const authHeader = req.headers.authorization;
			if (!authHeader?.startsWith('Bearer ')) {
				return reply.status(401).send({
					success: false,
					error: 'messages.authError'
				});
			}

			const token = authHeader.substring(7);
			const decoded = await jwtService.verifyToken(token);
			if (!decoded) {
				return reply.status(401).send({
					success: false,
					error: 'auth.invalidToken'
				});
			}

			req.user = decoded;
		}
	}, async (request, reply) => {
		try {
			const user = await findUserById(request.user.id);
			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}

			return {
				success: true,
				user: user.toSafeJSON()
			};
		} catch (error) {
			return reply.status(503).send({
				success: false,
				error: 'common.internalError'
			});
		}
	});

}
