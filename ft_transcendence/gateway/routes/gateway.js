import jwt from 'jsonwebtoken';

export default async function gatewayRoutes(fastify, options) {
	fastify.get('/health', async () => ({
		service: 'api-gateway',
		status: 'OK',
		url: 'http://gateway:3000',
		database: 'connected',
		timestamp: new Date().toISOString(),
		endpoints: [
			'/api/auth',
			'/api/2fa',
			'/api/i18n',
			'/api/database',
			'/api/gdpr'
		]
	}));
}