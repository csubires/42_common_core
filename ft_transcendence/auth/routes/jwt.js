import jwtService from '../services/jwt.js';

export default async function jwtRoutes(fastify, options) {
	fastify.post('/jwt/verify', async (request, reply) => {
		const { token } = request.body;
		const decoded = await jwtService.verifyToken(token);
		if (!decoded?.id) {
			return reply.status(401).send({ success: false, error: 'auth.invalidToken' });
		}
		return { success: true, decoded };
	});
}
