import fastifyPassport from '@fastify/passport';
import jwtService from '../services/jwt.js';

export default async function oauthRoutes(fastify) {
	fastify.get('/github', {
		preValidation: fastifyPassport.authenticate('github', {
			scope: ['user:email'],
			failWithError: true
		})
	}, async () => {
	});

	fastify.get('/github/callback', {
		preValidation: fastifyPassport.authenticate('github', {
			failureRedirect: '/?error=auth_failed',
			failWithError: true
		})
	}, async (request, reply) => {
		const user = request.user;
		if (!user) {
			return reply.redirect('/?error=user_not_found');
		}

		const jwtToken = await jwtService.generateToken({
			id: user.id,
			username: user.username,
			email: user.email,
			avatar: user.avatar,
			twoFactorEnabled: user.two_factor_enabled === true
		});

		return reply.redirect(`/?token=${jwtToken}`);
	});

	fastify.setErrorHandler(function (error, request, reply) {
		if (error.message && error.message.includes('oauth_not_configured')) {
			return reply.redirect('/?error=oauth_not_configured&message=GitHub+OAuth+is+not+configured');
		}

		fastify.log.error({
			err: error,
			url: request.url,
			method: request.method
		}, 'Request error');

		const statusCode = error.statusCode || 500;
		const response = {
			error: 'common.internalError',
			code: 'INTERNAL_ERROR'
		};

		if (process.env.NODE_ENV === 'development') {
			response.message = error.message;
		}

		reply.status(statusCode).send(response);
	});
}
