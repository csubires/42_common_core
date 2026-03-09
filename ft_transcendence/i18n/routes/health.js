export default async function healthRoutes(fastify, options) {
	const locales = global.__I18N_LOCALES__ || {};

	fastify.get('/health', async () => {
		return {
			service: 'i18n-service',
			status: 'OK',
			url: process.env.I18N_SERVICE_PORT,
			timestamp: new Date().toISOString(),
			languages: Object.keys(locales || {}),
			loaded: Object.keys(locales || {}).length > 0,
			endpoints: [
				'/locales/:language.json',
				'/languages'
			]
		};
	});


	fastify.get('/i18n/health', async () => {
		return {
			service: 'i18n-service',
			status: 'OK',
			url: process.env.I18N_SERVICE_PORT,
			timestamp: new Date().toISOString(),
			languages: Object.keys(locales || {}),
			loaded: Object.keys(locales || {}).length > 0,
			endpoints: [
				'/locales/:language.json',
				'/languages'
			]
		};
	});

	fastify.get('/languages', async () => {
		return {
			success: true,
			languages: Object.keys(locales || {}).map(lang => ({
				code: lang,
				name: lang === 'en' ? 'English' : 'Español',
				native: lang === 'en' ? 'English' : 'Español',
				lol: lang === 'en' ? 'Japanese' : '日本語'
			}))
		};
	});

	fastify.get('/locales/:language.json', async (request, reply) => {
		const { language } = request.params;
		const all = global.__I18N_LOCALES__ || {};
		const available = Object.keys(all);
		if (!all[language]) {
			return reply.status(404).send({
				error: 'Language not found',
				available
			});
		}
		return all[language];
	});
}
