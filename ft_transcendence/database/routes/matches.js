import db from '../config/sqlite.js';

export default async function matchesRoutes(fastify, options) {

	// Record a new match (secure)
	fastify.post('/matches', async (request, reply) => {
		// Check if this is a tournament match (has explicit player IDs) or user match
		const {
			player1_id,
			player1_name,
			player2_id,
			player2_name,
			player1_score,
			player2_score,
			winner_id,
			winner_name,
			opponent_id,
			opponent_name,
			user_score,
			opponent_score,
			winner,
			game_type = 'pong',
			tournament_id = null,
			match_duration = null
		} = request.body;

		// Tournament match format (explicit player IDs)
		if (player1_id !== undefined && player2_id !== undefined) {
			// This is a tournament match with explicit players
			if (!player1_name || !player2_name || player1_score === undefined || player2_score === undefined || !winner_name) {
				return reply.status(422).send({
					error: 'Missing required fields for tournament match',
					success: false,
					code: 'MISSING_FIELDS'
				});
			}

			try {
				const result = await db.run(
					`INSERT INTO matches (
						player1_id, player1_name, player2_id, player2_name,
						player1_score, player2_score, winner_id, winner_name,
						game_type, tournament_id, match_duration, played_at
					) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP)`,
					[
						player1_id || null,
						player1_name,
						player2_id || null,
						player2_name,
						player1_score,
						player2_score,
						winner_id || null,
						winner_name,
						game_type,
						tournament_id,
						match_duration
					]
				);

				return { success: true, matchId: result.id };
			} catch (error) {
				console.error('Error creating tournament match:', error);
				return reply.status(503).send({
					error: 'database.writeError',
					success: false,
					code: 'DB_WRITE_ERROR'
				});
			}
		}

		// Regular user match format (authenticated user vs opponent)
		const userId = request.headers['x-user-id'];
		if (!userId) {
			return reply.status(401).send({ success: false, error: 'auth.required' });
		}

		if (!opponent_name || user_score === undefined || opponent_score === undefined || !winner) {
			return reply.status(422).send({
				error: 'Missing required fields',
				success: false,
				code: 'MISSING_FIELDS'
			});
		}

		// Use authenticated user as player1, opponent as player2
		const resolvedPlayer1Id = userId;
		const player1_name_temp = winner === opponent_name ? undefined : 'You';
		const resolvedPlayer2Id = opponent_id || null;
		const resolvedPlayer2Name = opponent_name;
		const resolvedPlayer1Score = user_score;
		const resolvedPlayer2Score = opponent_score;
		const resolvedWinnerName = winner;
		let resolvedWinnerId = null;
		if (resolvedPlayer1Score > resolvedPlayer2Score) {
			resolvedWinnerId = resolvedPlayer1Id;
		} else if (resolvedPlayer2Score > resolvedPlayer1Score && resolvedPlayer2Id) {
			resolvedWinnerId = resolvedPlayer2Id;
		}

		// Fetch the user's display name from DB for player1_name
		let resolvedPlayer1Name = player1_name_temp;
		try {
			const userRow = await db.get('SELECT display_name, username FROM users WHERE id = ?', [userId]);
			if (userRow) {
				resolvedPlayer1Name = userRow.display_name || userRow.username || 'You';
			}
		} catch (e) {
			// fallback to 'You'
		}

		try {
			const result = await db.run(
				`INSERT INTO matches (
					player1_id, player1_name, player2_id, player2_name,
					player1_score, player2_score, winner_id, winner_name,
					game_type, tournament_id, match_duration, played_at
				) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP)`,
				[
					resolvedPlayer1Id, resolvedPlayer1Name, resolvedPlayer2Id, resolvedPlayer2Name,
					resolvedPlayer1Score, resolvedPlayer2Score, resolvedWinnerId, resolvedWinnerName,
					game_type, tournament_id, match_duration
				]
			);

			return { success: true, matchId: result.id };
		} catch (error) {
			console.error('Error creating match:', error);
			return reply.status(503).send({
				error: 'database.writeError',
				success: false,
				code: 'DB_WRITE_ERROR'
			});
		}
	});

	// Get match by ID // not called right now
	fastify.get('/matches/:id', async (request, reply) => {
		const { id } = request.params;

		try {
			const match = await db.get('SELECT * FROM matches WHERE id = ?', [id]);
			if (!match) {
				return reply.status(404).send({
					error: 'Match not found',
					success: false,
					code: 'MATCH_NOT_FOUND'
				});
			}
			return { success: true, match };
		} catch (error) {
			return reply.status(503).send({
				error: 'database.queryError',
				success: false,
				code: 'DB_QUERY_ERROR'
			});
		}
	});

	// Get user's match history // Called by getMatchHistory but that is neve rused
	fastify.get('/matches/user/:userId', async (request, reply) => {
		const { userId } = request.params;
		const { limit = 50, offset = 0 } = request.query;

		try {
			const matches = await db.all(
				`SELECT * FROM matches 
				WHERE player1_id = ? OR player2_id = ?
				ORDER BY played_at DESC
				LIMIT ? OFFSET ?`,
				[userId, userId, parseInt(limit), parseInt(offset)]
			);
			return { success: true, matches };
		} catch (error) {
			return reply.status(503).send({
				error: 'database.queryError',
				success: false,
				code: 'DB_QUERY_ERROR'
			});
		}
	});

	// Get matches by tournament // Not used
	fastify.get('/matches/tournament/:tournamentId', async (request, reply) => {
		const { tournamentId } = request.params;

		try {
			const matches = await db.all(
				`SELECT * FROM matches 
				WHERE tournament_id = ?
				ORDER BY played_at ASC`,
				[tournamentId]
			);
			return { success: true, matches };
		} catch (error) {
			return reply.status(503).send({
				error: 'database.queryError',
				success: false,
				code: 'DB_QUERY_ERROR'
			});
		}
	});

	// Get all matches (with optional filters) // not called
	fastify.get('/matches', async (request, reply) => {
		const { game_type, limit = 100, offset = 0 } = request.query;

		try {
			let sql = 'SELECT * FROM matches';
			const params = [];

			if (game_type) {
				sql += ' WHERE game_type = ?';
				params.push(game_type);
			}

			sql += ' ORDER BY played_at DESC LIMIT ? OFFSET ?';
			params.push(parseInt(limit), parseInt(offset));

			const matches = await db.all(sql, params);
			return { success: true, matches };
		} catch (error) {
			return reply.status(503).send({
				error: 'database.queryError',
				success: false,
				code: 'DB_QUERY_ERROR'
			});
		}
	});

	// Get user stats // not called
	fastify.get('/stats/user/:userId', async (request, reply) => {
		const { userId } = request.params;

		try {
			const user = await db.get(
				'SELECT wins, losses, games_played FROM users WHERE id = ?',
				[userId]
			);

			if (!user) {
				return reply.status(404).send({
					error: 'User not found',
					success: false,
					code: 'USER_NOT_FOUND'
				});
			}

			const recentMatches = await db.all(
				`SELECT * FROM matches 
				WHERE player1_id = ? OR player2_id = ?
				ORDER BY played_at DESC LIMIT 10`,
				[userId, userId]
			);

			return {
				success: true,
				stats: {
					wins: user.wins || 0,
					losses: user.losses || 0,
					games_played: user.games_played || 0,
					win_rate: user.games_played > 0
						? ((user.wins / user.games_played) * 100).toFixed(1)
						: 0
				},
				recentMatches
			};
		} catch (error) {
			return reply.status(503).send({
				error: 'database.queryError',
				success: false,
				code: 'DB_QUERY_ERROR'
			});
		}
	});

}