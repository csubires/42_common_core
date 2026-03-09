import vaultService from '../services/vault.js';

export default async function vaultRoutes(fastify, options) {
	// Service token
	fastify.get('/secret/service-token', async (request, reply) => {
		const token = await vaultService.getSecret('service-token/config');
		if (!token) {
			return reply.status(404).send({ success: false, error: 'vault.serviceTokenNotFound' });
		}
		return { token };
	});

	// JWT secret
	fastify.get('/secret/jwt', async (request, reply) => {
		const secret = await vaultService.getJWTSecret();
		if (!secret) {
			return reply.status(404).send({ success: false, error: 'vault.jwtSecretNotFound' });
		}
		return { secret };
	});

	// Session secret
	fastify.get('/secret/session', async (request, reply) => {
		const secret = await vaultService.getSessionSecret();
		if (!secret) {
			return reply.status(404).send({ success: false, error: 'vault.sessionSecretNotFound' });
		}
		return { secret };
	});
}
