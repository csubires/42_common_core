import db from '../config/sqlite.js';

// Helper function to update user online status
export async function updateUserOnlineStatus(userId, status) {
	try {
		await db.run(
			`UPDATE users SET online_status = ?, last_seen = CURRENT_TIMESTAMP WHERE id = ?`,
			[status, userId]
		);
	} catch (error) {
		console.error('Error updating online status:', error);
		throw error;
	}
}

// Mark users as offline if they haven't sent a heartbeat in 2 minutes
export async function markInactiveUsersOffline() {
	try {
		await db.run(
			`UPDATE users 
			 SET online_status = 'offline' 
			 WHERE online_status = 'online' 
			 AND datetime(last_seen) < datetime('now', '-2 minutes')`
		);
	} catch (error) {
		console.error('Error marking inactive users offline:', error);
	}
}

export default async function heartbeatRoutes(fastify, options) {
	
	// Heartbeat endpoint - updates user's last_seen and online_status
	fastify.post('/heartbeat', async (request, reply) => {
		const userId = request.headers['x-user-id'];
		if (!userId) {
			return reply.status(401).send({ success: false, error: 'auth.required' });
		}

		try {
			await updateUserOnlineStatus(userId, 'online');
			return {
				success: true,
				timestamp: new Date().toISOString()
			};
		} catch (error) {
			console.error('Heartbeat error:', error);
			return reply.status(503).send({
				success: false,
				error: 'database.writeError',
				code: 'DB_WRITE_ERROR'
			});
		}
	});

	// Optional: Logout endpoint to explicitly set offline
	fastify.post('/logout', async (request, reply) => {
		const userId = request.headers['x-user-id'];
		
		if (!userId) {
			return reply.status(401).send({
				success: false,
				error: 'auth.userIdMissing',
				code: 'AUTH_REQUIRED'
			});
		}

		try {
			await updateUserOnlineStatus(userId, 'offline');
			
			return reply.status(200).send({
				success: true
			});
		} catch (error) {
			console.error('Logout error:', error);
			
			// Check if it's a database error
			if (error.code === 'SQLITE_ERROR' || error.code === 'SQLITE_CONSTRAINT') {
				return reply.status(422).send({
					success: false,
					error: 'database.updateFailed',
					code: 'DB_UPDATE_ERROR',
					details: error.message
				});
			}
			
			// Database connection or other critical errors
			return reply.status(503).send({
				success: false,
				error: 'database.writeError',
				code: 'DB_WRITE_ERROR',
				details: error.message
			});
		}
	});
}