import Fastify from 'fastify';
import i18nRoutes from './routes/i18n.js';

import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));

async function startI18nService() {
	const fastify = Fastify({
		serviceName: 'i18n-service',
		logger: { level: 'warn' },
		trustProxy: true
	});

	const corsOrigin = true;
	const fastifyCors = await import('@fastify/cors');
	await fastify.register(fastifyCors.default, {
		origin: corsOrigin === 'true' ? true : corsOrigin,
		credentials: true,
		methods: ['GET', 'POST', 'PUT', 'DELETE', 'PATCH', 'OPTIONS'],
		allowedHeaders: ['Content-Type', 'Authorization', 'x-service-token'],
		exposedHeaders: ['Set-Cookie']
	});

	const locales = {};
	const localesPath = path.join(__dirname, 'locales');
	try {
		const files = fs.readdirSync(localesPath);
		files.forEach(file => {
			if (file.endsWith('.json')) {
				const language = file.replace('.json', '');
				const filePath = path.join(localesPath, file);
				const content = fs.readFileSync(filePath, 'utf8');
				locales[language] = JSON.parse(content);
			}
		});
		Object.defineProperty(global, '__I18N_LOCALES__', { value: locales, configurable: true });
	} catch (error) { }

	await fastify.register(i18nRoutes, { prefix: '/i18n' });
	await fastify.listen({ host: '0.0.0.0', port: 3002 });
}

startI18nService().catch(error => {
	console.error(error);
	process.exit(1);
});
