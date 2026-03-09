
import createFastifyApp from '../shared/fastify-config.js';
import authRoutes from './routes/auth.js';
import oauthRoutes from './routes/oauth.js';
import twoFARoutes from './routes/2fa.js';
import userRoutes from './routes/user.js';
import gdprRoutes from './routes/gdpr.js';
import jwtRoutes from './routes/jwt.js';
import vaultRoutes from './routes/vault.js';
import fastifyPassport from '@fastify/passport';
import { configurePassport } from './config/oauth.js';
import VaultService from './services/vault.js';

async function startAuthService() {

	const fastify = await createFastifyApp({
		serviceName: 'auth-service',
		enableSessions: true,
		corsOrigin: true,
		getSessionSecret: () => VaultService.getSessionSecret(),
	});

	await fastify.register(fastifyPassport.initialize());
	await fastify.register(fastifyPassport.secureSession());
	configurePassport(fastifyPassport);

	await fastify.register(userRoutes, { prefix: '/auth' });
	await fastify.register(authRoutes, { prefix: '/auth' });
	await fastify.register(jwtRoutes, { prefix: '/auth' });
	await fastify.register(vaultRoutes, { prefix: '/vault' });
	await fastify.register(oauthRoutes, { prefix: '/oauth' });
	await fastify.register(twoFARoutes, { prefix: '/2fa' });
	await fastify.register(gdprRoutes, { prefix: '/gdpr' });
	await fastify.listen({ host: '0.0.0.0', port: 3001 });
}

startAuthService().catch(error => {
	console.error(error);
	process.exit(1);
});
