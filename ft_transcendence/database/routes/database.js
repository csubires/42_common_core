import db from '../config/sqlite.js';

export default async function databaseRoutes(fastify, options) {

		fastify.get('/health', async () => {
		try {
			await db.get('SELECT 1 as test');
			return {
				service: 'database-service',
				status: 'OK',
				url: 'http://database:3003',
				database: 'connected',
				timestamp: new Date().toISOString(),
				endpoints: [
					'/users/:id',
					'/users/email/:email',
					'/users',
					'/users/all',
					'/backup-codes',
					'/query'
				]
			};
		} catch (error) {
			return {
				service: 'database-service',
				status: 'ERROR',
				database: 'disconnected',
				success: false,
				error: error.message,
				timestamp: new Date().toISOString()
			};
		}
	});

}
