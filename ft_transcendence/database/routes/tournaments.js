import db from '../config/sqlite.js';

export default async function tournamentsRoutes(fastify, options) {

	// Create a new tournament
	fastify.post('/tournaments', async (request, reply) => {
		const {
			name,
			creator_id = null,
			max_players = 8,
			tournament_type
		} = request.body;

		if (!name) {
			return reply.status(422).send({
				error: 'Tournament name is required',
				success: false,
				code: 'MISSING_NAME'
			});
		}

		try {
			const result = await db.run(
				`INSERT INTO tournaments (name, creator_id, max_players, tournament_type, status, current_round, created_at)
				VALUES (?, ?, ?, ?,'pending', 0, CURRENT_TIMESTAMP)`,
				[name, creator_id, max_players, tournament_type]
			);
			return { success: true, tournamentId: result.id };
		} catch (error) {
			console.error('Error creating tournament:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Get tournament by ID
	fastify.get('/tournaments/:id', async (request, reply) => {
		const { id } = request.params;

		try {
			const tournament = await db.get('SELECT * FROM tournaments WHERE id = ?', [id]);
			if (!tournament) {
				return reply.status(404).send({
					error: 'Tournament not found',
					success: false,
					code: 'TOURNAMENT_NOT_FOUND'
				});
			}

			// Get participants
			const participants = await db.all(
				`SELECT * FROM tournament_participants 
				WHERE tournament_id = ? 
				ORDER BY seed ASC`,
				[id]
			);

			// Get matches
			const matches = await db.all(
				`SELECT * FROM matches 
				WHERE tournament_id = ? 
				ORDER BY played_at ASC`,
				[id]
			);

			return {
				success: true,
				tournament: {
					...tournament,
					participants,
					matches
				}
			};
		} catch (error) {
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// List all tournaments
	fastify.get('/tournaments', async (request, reply) => {
		const { status, limit = 50, offset = 0 } = request.query;

		try {
			let sql = 'SELECT * FROM tournaments';
			const params = [];

			if (status) {
				sql += ' WHERE status = ?';
				params.push(status);
			}

			sql += ' ORDER BY created_at DESC LIMIT ? OFFSET ?';
			params.push(parseInt(limit), parseInt(offset));

			const tournaments = await db.all(sql, params);
			return { success: true, tournaments };
		} catch (error) {
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Update tournament
	fastify.put('/tournaments/:id', async (request, reply) => {
		const { id } = request.params;
		const updates = request.body;

		const allowedFields = ['name', 'status', 'current_round', 'winner_id', 'winner_name', 'started_at', 'completed_at'];
		const fields = Object.keys(updates).filter(f => allowedFields.includes(f));

		if (fields.length === 0) {
			return reply.status(422).send({
				error: 'No valid fields to update',
				success: false,
				code: 'NO_UPDATES'
			});
		}

		const updateFields = fields.map(field => `${field} = ?`).join(', ');
		const values = fields.map(field => updates[field]);
		values.push(id);

		try {
			await db.run(`UPDATE tournaments SET ${updateFields} WHERE id = ?`, values);
			return { success: true };
		} catch (error) {
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Delete tournament
	fastify.delete('/tournaments/:id', async (request, reply) => {
		const { id } = request.params;

		try {
			await db.run('DELETE FROM tournaments WHERE id = ?', [id]);
			return { success: true };
		} catch (error) {
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Add participant to tournament
	fastify.post('/tournaments/:id/participants', async (request, reply) => {
		const { id } = request.params;
		const { user_id = null, display_name } = request.body;

		if (!display_name) {
			return reply.status(422).send({
				error: 'Display name is required',
				success: false,
				code: 'MISSING_DISPLAY_NAME'
			});
		}

		try {
			// Check tournament exists and is pending
			const tournament = await db.get('SELECT * FROM tournaments WHERE id = ?', [id]);
			if (!tournament) {
				return reply.status(404).send({
					error: 'Tournament not found',
					success: false,
					code: 'TOURNAMENT_NOT_FOUND'
				});
			}

			if (tournament.status !== 'pending') {
				return reply.status(422).send({
					error: 'Tournament already started',
					success: false,
					code: 'TOURNAMENT_STARTED'
				});
			}

			// Check max players
			const currentCount = await db.get(
				'SELECT COUNT(*) as count FROM tournament_participants WHERE tournament_id = ?',
				[id]
			);

			if (currentCount.count >= tournament.max_players) {
				return reply.status(422).send({
					error: 'Tournament is full',
					success: false,
					code: 'TOURNAMENT_FULL'
				});
			}

			// Check if user already joined (if registered user)
			if (user_id) {
				const existing = await db.get(
					'SELECT * FROM tournament_participants WHERE tournament_id = ? AND user_id = ?',
					[id, user_id]
				);
				if (existing) {
					return reply.status(409).send({
						error: 'User already in tournament',
						success: false,
						code: 'ALREADY_JOINED'
					});
				}
			}

			// Check display name uniqueness in this tournament
			const nameExists = await db.get(
				'SELECT * FROM tournament_participants WHERE tournament_id = ? AND display_name = ?',
				[id, display_name]
			);
			if (nameExists) {
				return reply.status(409).send({
					error: 'Display name already taken in this tournament',
					success: false,
					code: 'NAME_TAKEN'
				});
			}

			const result = await db.run(
				`INSERT INTO tournament_participants (tournament_id, user_id, display_name, joined_at)
				VALUES (?, ?, ?, CURRENT_TIMESTAMP)`,
				[id, user_id, display_name]
			);

			return { success: true, participantId: result.id };
		} catch (error) {
			console.error('Error adding participant:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Batch add participants (for tournament setup)
	fastify.post('/tournament-participants', async (request, reply) => {
		const { participants } = request.body;

		// Validate body fields
		const allowedFields = ['participants'];
		const receivedFields = Object.keys(request.body || {});
		const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
		if (unexpectedFields.length > 0) {
			return reply.status(422).send({
				success: false,
				error: 'validation.unexpectedFields',
				code: 'UNEXPECTED_FIELDS'
			});
		}

		if (!participants || !Array.isArray(participants) || participants.length === 0) {
			return reply.status(422).send({
				error: 'Participants array is required',
				success: false,
				code: 'MISSING_PARTICIPANTS'
			});
		}

		// Prevent DoS: limit array size
		if (participants.length > 100) {
			return reply.status(422).send({
				error: 'Too many participants (max 100)',
				success: false,
				code: 'TOO_MANY_PARTICIPANTS'
			});
		}

		// Validate each participant object
		for (let i = 0; i < participants.length; i++) {
			const participant = participants[i];

			// Validate participant is an object
			if (!participant || typeof participant !== 'object' || Array.isArray(participant)) {
				return reply.status(422).send({
					error: `Participant at index ${i} must be an object`,
					success: false,
					code: 'INVALID_PARTICIPANT'
				});
			}

			// Validate participant fields
			const allowedParticipantFields = ['tournament_id', 'user_id', 'display_name', 'seed'];
			const receivedParticipantFields = Object.keys(participant);
			const unexpectedParticipantFields = receivedParticipantFields.filter(f => !allowedParticipantFields.includes(f));
			if (unexpectedParticipantFields.length > 0) {
				return reply.status(422).send({
					success: false,
					error: `Participant at index ${i} has unexpected fields`,
					code: 'UNEXPECTED_FIELDS'
				});
			}

			// Required fields
			if (!participant.tournament_id) {
				return reply.status(422).send({
					error: `Participant at index ${i} missing tournament_id`,
					success: false,
					code: 'MISSING_FIELDS'
				});
			}

			if (!participant.display_name) {
				return reply.status(422).send({
					error: `Participant at index ${i} missing display_name`,
					success: false,
					code: 'MISSING_FIELDS'
				});
			}

			// Type validation
			if (typeof participant.tournament_id !== 'number' && typeof participant.tournament_id !== 'string') {
				return reply.status(422).send({
					error: `Participant at index ${i} has invalid tournament_id type`,
					success: false,
					code: 'INVALID_TYPE'
				});
			}

			if (participant.user_id !== null && participant.user_id !== undefined && 
				typeof participant.user_id !== 'number' && typeof participant.user_id !== 'string') {
				return reply.status(422).send({
					error: `Participant at index ${i} has invalid user_id type`,
					success: false,
					code: 'INVALID_TYPE'
				});
			}

			if (typeof participant.display_name !== 'string' || participant.display_name.length === 0 || participant.display_name.length > 255) {
				return reply.status(422).send({
					error: `Participant at index ${i} has invalid display_name`,
					success: false,
					code: 'INVALID_DISPLAY_NAME'
				});
			}

			if (participant.seed !== null && participant.seed !== undefined && typeof participant.seed !== 'number') {
				return reply.status(422).send({
					error: `Participant at index ${i} has invalid seed type`,
					success: false,
					code: 'INVALID_TYPE'
				});
			}
		}

		try {
			// Insert all participants
			for (const participant of participants) {
				const { tournament_id, user_id, display_name, seed } = participant;
				
				await db.run(
					`INSERT INTO tournament_participants (tournament_id, user_id, display_name, seed, joined_at)
					VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)`,
					[tournament_id, user_id || null, display_name, seed || null]
				);
			}

			return { success: true, count: participants.length };
		} catch (error) {
			console.error('Error adding participants:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Get tournament participants
	fastify.get('/tournaments/:id/participants', async (request, reply) => {
		const { id } = request.params;

		try {
			const participants = await db.all(
				`SELECT * FROM tournament_participants 
				WHERE tournament_id = ? 
				ORDER BY seed ASC, joined_at ASC`,
				[id]
			);
			return { success: true, participants };
		} catch (error) {
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Update participant (seed, eliminate)
	fastify.put('/tournaments/:id/participants/:participantId', async (request, reply) => {
		const { id, participantId } = request.params;
		const { seed, eliminated, eliminated_round } = request.body;

		try {
			const updates = [];
			const values = [];

			if (seed !== undefined) {
				updates.push('seed = ?');
				values.push(seed);
			}
			if (eliminated !== undefined) {
				updates.push('eliminated = ?');
				values.push(eliminated ? 1 : 0);
			}
			if (eliminated_round !== undefined) {
				updates.push('eliminated_round = ?');
				values.push(eliminated_round);
			}

			if (updates.length === 0) {
				return reply.status(422).send({
					error: 'No fields to update',
					success: false,
					code: 'NO_UPDATES'
				});
			}

			values.push(participantId, id);

			await db.run(
				`UPDATE tournament_participants SET ${updates.join(', ')} 
				WHERE id = ? AND tournament_id = ?`,
				values
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

	// Remove participant from tournament
	fastify.delete('/tournaments/:id/participants/:participantId', async (request, reply) => {
		const { id, participantId } = request.params;

		try {
			await db.run(
				'DELETE FROM tournament_participants WHERE id = ? AND tournament_id = ?',
				[participantId, id]
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

	// Start tournament (set seeds randomly and change status)
	fastify.post('/tournaments/:id/start', async (request, reply) => {
		const { id } = request.params;

		try {
			const tournament = await db.get('SELECT * FROM tournaments WHERE id = ?', [id]);
			if (!tournament) {
				return reply.status(404).send({
					error: 'Tournament not found',
					success: false,
					code: 'TOURNAMENT_NOT_FOUND'
				});
			}

			if (tournament.status !== 'pending') {
				return reply.status(422).send({
					error: 'Tournament already started',
					success: false,
					code: 'ALREADY_STARTED'
				});
			}

			const participants = await db.all(
				'SELECT * FROM tournament_participants WHERE tournament_id = ?',
				[id]
			);

			if (participants.length < 2) {
				return reply.status(422).send({
					error: 'Need at least 2 participants',
					success: false,
					code: 'NOT_ENOUGH_PLAYERS'
				});
			}

			// Shuffle and assign seeds
			const shuffled = participants.sort(() => Math.random() - 0.5);
			for (let i = 0; i < shuffled.length; i++) {
				await db.run(
					'UPDATE tournament_participants SET seed = ? WHERE id = ?',
					[i + 1, shuffled[i].id]
				);
			}

			// Update tournament status
			await db.run(
				`UPDATE tournaments SET status = 'in_progress', current_round = 1, started_at = CURRENT_TIMESTAMP WHERE id = ?`,
				[id]
			);

			return { success: true, message: 'Tournament started' };
		} catch (error) {
			console.error('Error starting tournament:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Start tournament (PATCH version - usado por frontend)
	fastify.patch('/tournaments/:id/start', async (request, reply) => {
		const { id } = request.params;
		const { status, started_at } = request.body;

		// Validate body fields
		const allowedFields = ['status', 'started_at'];
		const receivedFields = Object.keys(request.body || {});
		const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
		if (unexpectedFields.length > 0) {
			return reply.status(422).send({
				success: false,
				error: 'validation.unexpectedFields',
				code: 'UNEXPECTED_FIELDS'
			});
		}

		// Validate status field
		if (status !== undefined) {
			const allowedStatuses = ['pending', 'active', 'in_progress', 'completed'];
			if (!allowedStatuses.includes(status)) {
				return reply.status(422).send({
					success: false,
					error: 'validation.invalidStatus',
					code: 'INVALID_STATUS'
				});
			}
		}

		// Validate started_at field
		if (started_at !== undefined && typeof started_at !== 'string') {
			return reply.status(422).send({
				success: false,
				error: 'validation.invalidType',
				code: 'INVALID_TYPE'
			});
		}

		try {
			await db.run(
				`UPDATE tournaments SET status = ?, started_at = ? WHERE id = ?`,
				[status || 'active', started_at || new Date().toISOString(), id]
			);

			return { success: true };
		} catch (error) {
			console.error('Error starting tournament:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Update tournament round
	fastify.patch('/tournaments/:id/round', async (request, reply) => {
		const { id } = request.params;
		const { current_round } = request.body;

		// Validate body fields
		const allowedFields = ['current_round'];
		const receivedFields = Object.keys(request.body || {});
		const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
		if (unexpectedFields.length > 0) {
			return reply.status(422).send({
				success: false,
				error: 'validation.unexpectedFields',
				code: 'UNEXPECTED_FIELDS'
			});
		}

		if (current_round === undefined) {
			return reply.status(422).send({
				error: 'current_round is required',
				success: false,
				code: 'MISSING_ROUND'
			});
		}

		// Validate current_round type and range
		if (typeof current_round !== 'number' || current_round < 1 || current_round > 100) {
			return reply.status(422).send({
				error: 'current_round must be a number between 1 and 100',
				success: false,
				code: 'INVALID_ROUND'
			});
		}

		try {
			await db.run(
				`UPDATE tournaments SET current_round = ? WHERE id = ?`,
				[current_round, id]
			);

			return { success: true };
		} catch (error) {
			console.error('Error updating tournament round:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

	// Complete tournament
	fastify.patch('/tournaments/:id/complete', async (request, reply) => {
		const { id } = request.params;
		const { status, winner_id, winner_name, current_round, completed_at } = request.body;

		try {
			// Check if tournament exists and is not already completed
			const tournament = await db.get('SELECT * FROM tournaments WHERE id = ?', [id]);
			
			if (!tournament) {
				return reply.status(404).send({
					success: false,
					error: 'Tournament not found',
					code: 'TOURNAMENT_NOT_FOUND'
				});
			}

			if (tournament.status === 'completed') {
				return reply.status(409).send({
					success: false,
					error: 'Tournament already completed',
					code: 'ALREADY_COMPLETED'
				});
			}
		} catch (error) {
			console.error('Error checking tournament:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}

		// Validate body fields
		const allowedFields = ['status', 'winner_id', 'winner_name', 'current_round', 'completed_at'];
		const receivedFields = Object.keys(request.body || {});
		const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
		if (unexpectedFields.length > 0) {
			return reply.status(422).send({
				success: false,
				error: 'validation.unexpectedFields',
				code: 'UNEXPECTED_FIELDS'
			});
		}

		// Validate status field
		if (status !== undefined) {
			const allowedStatuses = ['pending', 'active', 'in_progress', 'completed'];
			if (!allowedStatuses.includes(status)) {
				return reply.status(422).send({
					success: false,
					error: 'validation.invalidStatus',
					code: 'INVALID_STATUS'
				});
			}
		}

		// Validate winner_id type
		if (winner_id !== undefined && winner_id !== null && 
			typeof winner_id !== 'number' && typeof winner_id !== 'string') {
			return reply.status(422).send({
				success: false,
				error: 'validation.invalidType',
				code: 'INVALID_TYPE'
			});
		}

		// Validate winner_name type
		if (winner_name !== undefined && winner_name !== null && 
			(typeof winner_name !== 'string' || winner_name.length === 0 || winner_name.length > 255)) {
			return reply.status(422).send({
				success: false,
				error: 'validation.invalidWinnerName',
				code: 'INVALID_WINNER_NAME'
			});
		}

		// Validate current_round type
		if (current_round !== undefined && current_round !== null && 
			(typeof current_round !== 'number' || current_round < 1 || current_round > 100)) {
			return reply.status(422).send({
				success: false,
				error: 'validation.invalidRound',
				code: 'INVALID_ROUND'
			});
		}

		// Validate completed_at type
		if (completed_at !== undefined && typeof completed_at !== 'string') {
			return reply.status(422).send({
				success: false,
				error: 'validation.invalidType',
				code: 'INVALID_TYPE'
			});
		}

		try {
			await db.run(
				`UPDATE tournaments 
				SET status = ?, winner_id = ?, winner_name = ?, current_round = ?, completed_at = ?
				WHERE id = ?`,
				[
					status || 'completed',
					winner_id || null,
					winner_name,
					current_round,
					completed_at || new Date().toISOString(),
					id
				]
			);

			return { success: true };
		} catch (error) {
			console.error('Error completing tournament:', error);
			return reply.status(503).send({
				error: 'Database error',
				success: false,
				code: 'DB_ERROR'
			});
		}
	});

}