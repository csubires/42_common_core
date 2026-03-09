import db from '../config/sqlite.js';

export default async function friendsRoutes(fastify, options) {


    fastify.get('/friends/me/requests', async (request, reply) => {
        try {
            const userId = request.headers['x-user-id'] ||
                (request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);

            if (!userId) {
                return reply.status(401).send({
                    success: false,
                    error: 'Authentication required',
                    code: 'AUTH_REQUIRED'
                });
            }

            const requests = await db.all(
                `SELECT f.*, u.username, u.avatar
             FROM friendships f
             LEFT JOIN users u ON f.user_id = u.id
             WHERE f.friend_id = ? AND f.status = 'pending'
             ORDER BY f.created_at DESC`,
                [userId]
            );
            return { success: true, requests };
        } catch (error) {
            console.error('Error loading friend requests:', error);
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    fastify.get('/friends/me', async (request, reply) => {
        try {
            const userId = request.headers['x-user-id'] ||
                (request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);

            if (!userId) {
                return reply.status(401).send({
                    success: false,
                    error: 'Authentication required',
                    code: 'AUTH_REQUIRED'
                });
            }

            const friends = await db.all(
                `SELECT f.*,
                CASE
                    WHEN f.user_id = ? THEN f.friend_id
                    ELSE f.user_id
                END as friend_user_id,
                u.username, u.avatar, u.online_status, u.last_seen
             FROM friendships f
             LEFT JOIN users u ON (
                CASE
                    WHEN f.user_id = ? THEN f.friend_id
                    ELSE f.user_id
                END = u.id
             )
             WHERE (f.user_id = ? OR f.friend_id = ?) AND f.status = 'accepted'
             ORDER BY f.created_at DESC`,
                [userId, userId, userId, userId]
            );
            return { success: true, friends };
        } catch (error) {
            console.error('Error loading friends:', error);
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    fastify.get('/friends/me/sent', async (request, reply) => {
        try {
            const userId = request.headers['x-user-id'] ||
                (request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);

            if (!userId) {
                return reply.status(401).send({
                    success: false,
                    error: 'Authentication required',
                    code: 'AUTH_REQUIRED'
                });
            }

            const requests = await db.all(
                `SELECT f.*, u.username, u.avatar
             FROM friendships f
             LEFT JOIN users u ON f.friend_id = u.id
             WHERE f.user_id = ? AND f.status = 'pending'
             ORDER BY f.created_at DESC`,
                [userId]
            );
            return { success: true, requests };
        } catch (error) {
            console.error('Error loading sent requests:', error);
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    fastify.get('/friends/me/check/:friendId', async (request, reply) => {
        try {
            const userId = request.headers['x-user-id'] ||
                (request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);
            const { friendId } = request.params;

            if (!userId) {
                return reply.status(401).send({
                    success: false,
                    error: 'Authentication required',
                    code: 'AUTH_REQUIRED'
                });
            }

            if (!friendId) {
                return reply.status(422).send({
                    success: false,
                    error: 'Friend ID is required',
                    code: 'MISSING_FRIEND_ID'
                });
            }

            const friendship = await db.get(
                `SELECT * FROM friendships
             WHERE (user_id = ? AND friend_id = ?) OR (user_id = ? AND friend_id = ?)`,
                [userId, friendId, friendId, userId]
            );

            if (!friendship) {
                return { success: true, status: 'none', friendship: null };
            }
            return { success: true, status: friendship.status, friendship };
        } catch (error) {
            console.error('Error checking friendship:', error);
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    fastify.post('/friends/me/add', async (request, reply) => {
        try {
            const userId = request.headers['x-user-id'] ||
                (request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);
            const { friend_id } = request.body;

            if (!userId) {
                return reply.status(401).send({
                    success: false,
                    error: 'Authentication required',
                    code: 'AUTH_REQUIRED'
                });
            }

            // Validate body fields
            const allowedFields = ['friend_id'];
            const receivedFields = Object.keys(request.body || {});
            const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
            if (unexpectedFields.length > 0) {
                return reply.status(422).send({
                    success: false,
                    error: 'validation.unexpectedFields',
                    code: 'UNEXPECTED_FIELDS'
                });
            }

            if (!friend_id) {
				return reply.status(422).send({
                    success: false,
                    error: 'validation.missingFields',
                    code: 'MISSING_FIELDS'
                });
            }

            // Validate friend_id format
            if (typeof friend_id !== 'string' || friend_id.length === 0) {
                return reply.status(422).send({
                    success: false,
                    error: 'validation.invalidUserId',
                    code: 'INVALID_USER_ID'
                });
            }

            if (userId === friend_id) {
				return reply.status(403).send({
                    success: false,
                    error: 'validation.cannotAddSelf',
                    code: 'SELF_FRIEND'
                });
            }

            const existing = await db.get(
                `SELECT * FROM friendships
             WHERE (user_id = ? AND friend_id = ?) OR (user_id = ? AND friend_id = ?)`,
                [userId, friend_id, friend_id, userId]
            );

            if (existing) {
                return reply.status(409).send({
                    error: 'Friendship already exists',
                    success: false,
                    code: 'ALREADY_EXISTS',
                    status: existing.status
                });
            }

            const result = await db.run(
                `INSERT INTO friendships (user_id, friend_id, status, created_at)
             VALUES (?, ?, 'pending', CURRENT_TIMESTAMP)`,
                [userId, friend_id]
            );

            return { success: true, friendshipId: result.id };
        } catch (error) {
            console.error('Error adding friend:', error);
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });


    // Send friend request
    fastify.post('/friends', async (request, reply) => {
        const { user_id, friend_id } = request.body;

        if (!user_id || !friend_id) {
            return reply.status(422).send({
                error: 'Both user_id and friend_id are required',
                success: false,
                code: 'MISSING_FIELDS'
            });
        }

        if (user_id === friend_id) {
			return reply.status(403).send({
                error: 'Cannot add yourself as friend',
                success: false,
                code: 'SELF_FRIEND'
            });
        }

        try {
            // Check if friendship already exists (in either direction)
            const existing = await db.get(
                `SELECT * FROM friendships
				WHERE (user_id = ? AND friend_id = ?) OR (user_id = ? AND friend_id = ?)`,
                [user_id, friend_id, friend_id, user_id]
            );

            if (existing) {
                return reply.status(409).send({
                    error: 'Friendship already exists',
                    success: false,
                    code: 'ALREADY_EXISTS',
                    status: existing.status
                });
            }

            const result = await db.run(
                `INSERT INTO friendships (user_id, friend_id, status, created_at)
				VALUES (?, ?, 'pending', CURRENT_TIMESTAMP)`,
                [user_id, friend_id]
            );

            return { success: true, friendshipId: result.id };
        } catch (error) {
            console.error('Error creating friendship:', error);
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    // Get user's friends (accepted only)
    fastify.get('/friends/user/:userId', async (request, reply) => {
        const { userId } = request.params;
        const { status = 'accepted' } = request.query;

        try {
            const friends = await db.all(
                `SELECT f.*,
					CASE
						WHEN f.user_id = ? THEN f.friend_id
						ELSE f.user_id
					END as friend_user_id,
					u.username, u.avatar, u.online_status, u.last_seen
				FROM friendships f
				LEFT JOIN users u ON (
					CASE
						WHEN f.user_id = ? THEN f.friend_id
						ELSE f.user_id
					END = u.id
				)
				WHERE (f.user_id = ? OR f.friend_id = ?) AND f.status = ?
				ORDER BY f.created_at DESC`,
                [userId, userId, userId, userId, status]
            );

            return { success: true, friends };
        } catch (error) {
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    // Get pending friend requests (received)
    fastify.get('/friends/requests/:userId', async (request, reply) => {
        const { userId } = request.params;

        try {
            const requests = await db.all(
                `SELECT f.*, u.username, u.avatar
				FROM friendships f
				LEFT JOIN users u ON f.user_id = u.id
				WHERE f.friend_id = ? AND f.status = 'pending'
				ORDER BY f.created_at DESC`,
                [userId]
            );

            return { success: true, requests };
        } catch (error) {
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    // Get sent friend requests
    fastify.get('/friends/sent/:userId', async (request, reply) => {
        const { userId } = request.params;

        try {
            const requests = await db.all(
                `SELECT f.*, u.username, u.avatar
				FROM friendships f
				LEFT JOIN users u ON f.friend_id = u.id
				WHERE f.user_id = ? AND f.status = 'pending'
				ORDER BY f.created_at DESC`,
                [userId]
            );

            return { success: true, requests };
        } catch (error) {
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    // Update friendship status (accept, reject, block)
    fastify.put('/friends/:id', async (request, reply) => {
        const authenticatedUserId = request.headers['x-user-id'] ||
            (request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);
        const { id } = request.params;
        const { status } = request.body;

        // Validate body fields
        const allowedFields = ['status'];
        const receivedFields = Object.keys(request.body || {});
        const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
        if (unexpectedFields.length > 0) {
            return reply.status(422).send({
                success: false,
                error: 'validation.unexpectedFields',
                code: 'UNEXPECTED_FIELDS'
            });
        }

        const allowedStatuses = ['accepted', 'rejected', 'blocked'];
        if (!status || !allowedStatuses.includes(status)) {
			return reply.status(422).send({
                error: 'Invalid status. Must be: accepted, rejected, or blocked',
                success: false,
                code: 'INVALID_STATUS'
            });
        }

        try {
            const friendship = await db.get('SELECT * FROM friendships WHERE id = ?', [id]);
            if (!friendship) {
                return reply.status(404).send({
                    error: 'Friendship not found',
                    success: false,
                    code: 'NOT_FOUND'
                });
            }

            // Authorization: Verify the authenticated user is the RECIPIENT of this friend request
            if (friendship.friend_id !== authenticatedUserId) {
                return reply.status(403).send({
                    success: false,
                    error: 'Forbidden: You can only respond to your own friend requests',
                    code: 'FORBIDDEN'
                });
            }

            await db.run(
                'UPDATE friendships SET status = ? WHERE id = ?',
                [status, id]
            );

            return { success: true };
        } catch (error) {
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    // Delete friendship
    fastify.delete('/friends/:id', async (request, reply) => {
        const authenticatedUserId = request.headers['x-user-id'] ||
            (request.headers['x-user'] ? JSON.parse(request.headers['x-user']).id : null);
        const { id } = request.params;

        try {
            const friendship = await db.get('SELECT * FROM friendships WHERE id = ?', [id]);
            
            if (!friendship) {
                return reply.status(404).send({
                    success: false,
                    error: 'Friendship not found',
                    code: 'NOT_FOUND'
                });
            }

            // Authorization: Verify the authenticated user is part of this friendship
            if (friendship.user_id !== authenticatedUserId && 
                friendship.friend_id !== authenticatedUserId) {
                return reply.status(403).send({
                    success: false,
                    error: 'Forbidden: You can only delete your own friendships',
                    code: 'FORBIDDEN'
                });
            }

            await db.run('DELETE FROM friendships WHERE id = ?', [id]);
            return { success: true };
        } catch (error) {
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    // Check friendship status between two users
    fastify.get('/friends/check/:userId/:friendId', async (request, reply) => {
        const { userId, friendId } = request.params;

        try {
            const friendship = await db.get(
                `SELECT * FROM friendships
				WHERE (user_id = ? AND friend_id = ?) OR (user_id = ? AND friend_id = ?)`,
                [userId, friendId, friendId, userId]
            );

            if (!friendship) {
                return { success: true, status: 'none', friendship: null };
            }

            return { success: true, status: friendship.status, friendship };
        } catch (error) {
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });

    // Update user online status
    fastify.put('/users/:id/status', async (request, reply) => {
        const { id } = request.params;
        const { online_status } = request.body;

        const allowedStatuses = ['online', 'offline', 'in_game'];
        if (!online_status || !allowedStatuses.includes(online_status)) {
			return reply.status(422).send({
                error: 'Invalid status. Must be: online, offline, or in_game',
                success: false,
                code: 'INVALID_STATUS'
            });
        }

        try {
            await db.run(
                `UPDATE users SET online_status = ?, last_seen = CURRENT_TIMESTAMP WHERE id = ?`,
                [online_status, id]
            );
            return { success: true };
        } catch (error) {
            return reply.status(503).send({
                error: 'Database error',
                success: false,
                code: 'DB_ERROR'
            });
        }
    });





}
