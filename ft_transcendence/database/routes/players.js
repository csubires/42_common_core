import db from '../config/sqlite.js';

/**
 * Helper function to get player profile with stats and match history
 * @param {string} userId - The user ID to fetch profile for
 * @returns {Promise<object|null>} Player profile or null if not found
 */
async function getPlayerProfile(userId) {
    // Get user basic info
    const user = await db.get(
        `SELECT id, username, display_name, avatar, online_status, 
                last_seen, created_at
         FROM users
         WHERE id = ? AND is_active = 1 AND is_anonymized = 0`,
        [userId]
    );

    if (!user) {
        return null;
    }

    // Calculate stats from matches table
    const statsQuery = `
        SELECT 
            COUNT(*) as games_played,
            SUM(CASE WHEN winner_id = ? THEN 1 ELSE 0 END) as wins,
            SUM(CASE WHEN winner_id != ? AND winner_id IS NOT NULL THEN 1 ELSE 0 END) as losses
        FROM matches
        WHERE (player1_id = ? OR player2_id = ?)
    `;
    
    const stats = await db.get(statsQuery, [userId, userId, userId, userId]);

    // Get tournament wins count
    const tournamentWinsQuery = `
        SELECT COUNT(*) as tournament_wins
        FROM tournaments
        WHERE winner_id = ? AND status = 'completed'
    `;
    
    const tournamentWins = await db.get(tournamentWinsQuery, [userId]);

    // Get recent match history (last 10 matches)
    const matchHistoryQuery = `
        SELECT 
            m.id,
            m.player1_id,
            m.player1_name,
            m.player2_id,
            m.player2_name,
            m.player1_score,
            m.player2_score,
            m.winner_id,
            m.winner_name,
            m.game_type,
            m.match_duration,
            m.played_at,
            m.tournament_id
        FROM matches m
        WHERE m.player1_id = ? OR m.player2_id = ?
        ORDER BY m.played_at DESC
        LIMIT 10
    `;

    const matchHistory = await db.all(matchHistoryQuery, [userId, userId]);

    // Format match history for frontend
    const formattedMatches = matchHistory.map(match => {
        const isPlayer1 = match.player1_id === userId;
        const opponent = {
            name: isPlayer1 ? match.player2_name : match.player1_name
        };
        const playerScore = isPlayer1 ? match.player1_score : match.player2_score;
        const opponentScore = isPlayer1 ? match.player2_score : match.player1_score;
        const won = match.winner_id === userId;

        return {
            id: match.id,
            opponent,
            playerScore,
            opponentScore,
            won,
            gameType: match.game_type,
            duration: match.match_duration,
            playedAt: match.played_at,
            tournamentId: match.tournament_id
        };
    });

    // Build complete profile response
    return {
        username: user.username,
        display_name: user.display_name,
        avatar: user.avatar || '/avatars/default-avatar.png',
        online_status: user.online_status || 'offline',
        last_seen: user.last_seen,
        created_at: user.created_at,
        stats: {
            games_played: stats.games_played || 0,
            wins: stats.wins || 0,
            losses: stats.losses || 0,
            win_rate: stats.games_played > 0 
                ? Math.round((stats.wins / stats.games_played) * 100) 
                : 0,
            tournament_wins: tournamentWins.tournament_wins || 0
        },
        match_history: formattedMatches
    };
}

export default async function playersRoutes(fastify, options) {
    /**
     * GET /players
     * Returns a list of players with minimal information (for the player list)
     * Query params:
     *   - search: optional search term for username/display_name
     *   - limit: max number of results (default 50)
     *   - offset: pagination offset (default 0)
     */
    fastify.get('/players', async (request, reply) => {
        const search = request.query.search || '';
        const limit = request.query.limit || 50;
        const offset = request.query.offset || 0;

        try {
            let sql = `
                SELECT id, username, display_name, avatar, online_status
                FROM users
                WHERE is_active = 1 AND is_anonymized = 0
            `;
            const params = [];

            if (search) {
                sql += ' AND (username LIKE ? OR display_name LIKE ?)';
                const searchTerm = `%${search}%`;
                params.push(searchTerm, searchTerm);
            }

            sql += ' ORDER BY online_status DESC, username ASC LIMIT ? OFFSET ?';
            params.push(parseInt(limit), parseInt(offset));

            const users = await db.all(sql, params);

            return {
                success: true,
                users: users.map(user => ({
                    id: user.id,
                    username: user.username,
                    display_name: user.display_name,
                    avatar: user.avatar || '/avatars/default-avatar.png',
                    online_status: user.online_status || 'offline'
                }))
            };
        } catch (error) {
            console.error('Error loading players:', error);
            return reply.status(503).send({
                success: false,
                error: 'common.internalError',
                code: 'DB_ERROR'
            });
        }
    });

    /**
     * GET /players/leaderboard
     * Returns top players by wins, including tournament wins
     */
    fastify.get('/players/leaderboard', async (request, reply) => {
        const limit = request.query.limit || 5;

        try {
            // Get top players by wins with stats and tournament wins
            const leaderboardQuery = `
                SELECT 
                    u.id,
                    u.username,
                    u.display_name,
                    u.avatar,
                    u.online_status,
                    COUNT(DISTINCT m.id) as games_played,
                    SUM(CASE WHEN m.winner_id = u.id THEN 1 ELSE 0 END) as wins,
                    SUM(CASE WHEN m.winner_id != u.id AND m.winner_id IS NOT NULL THEN 1 ELSE 0 END) as losses,
                    COUNT(DISTINCT t.id) as tournament_wins
                FROM users u
                LEFT JOIN matches m ON (m.player1_id = u.id OR m.player2_id = u.id)
                LEFT JOIN tournaments t ON (t.winner_id = u.id AND t.status = 'completed')
                WHERE u.is_active = 1 AND u.is_anonymized = 0
                GROUP BY u.id, u.username, u.display_name, u.avatar, u.online_status
                HAVING games_played > 0
                ORDER BY wins DESC, games_played DESC
                LIMIT ?
            `;

            const players = await db.all(leaderboardQuery, [parseInt(limit)]);

            // Format the response with IDs
            const leaderboard = players.map(player => ({
                id: player.id,
                username: player.username,
                display_name: player.display_name,
                avatar: player.avatar || '/avatars/default-avatar.png',
                online_status: player.online_status || 'offline',
                stats: {
                    games_played: player.games_played || 0,
                    wins: player.wins || 0,
                    losses: player.losses || 0,
                    win_rate: player.games_played > 0 
                        ? Math.round((player.wins / player.games_played) * 100) 
                        : 0,
                    tournament_wins: player.tournament_wins || 0
                }
            }));

            return {
                success: true,
                leaderboard
            };
        } catch (error) {
            console.error('Error loading leaderboard:', error);
            return reply.status(503).send({
                success: false,
                error: 'common.internalError',
                code: 'DB_ERROR'
            });
        }
    });

    /**
     * GET /players/me
     * Returns detailed player profile for the authenticated user
     * Requires authentication via x-user-id header
     */
    fastify.get('/players/me', async (request, reply) => {
        const userId = request.headers['x-user-id'];

        if (!userId) {
            return reply.status(401).send({
                success: false,
                error: 'Authentication required',
                code: 'AUTH_REQUIRED'
            });
        }

        try {
            const profile = await getPlayerProfile(userId);

            if (!profile) {
                return reply.status(404).send({
                    success: false,
                    error: 'Player not found',
                    code: 'PLAYER_NOT_FOUND'
                });
            }

            return { success: true, user: profile };
        } catch (error) {
            console.error('Error loading player profile:', error);
            return reply.status(503).send({
                success: false,
                error: 'common.internalError',
                code: 'DB_ERROR'
            });
        }
    });

    /**
     * GET /players/:id
     * Returns detailed player profile for any user by ID
     * Used by friends page and players page
     * Requires authentication
     */
    fastify.get('/players/:id', async (request, reply) => {
        const { id } = request.params;

        // Require authentication
        const requestingUserId = request.headers['x-user-id'];
        if (!requestingUserId) {
            return reply.status(401).send({
                success: false,
                error: 'Authentication required',
                code: 'AUTH_REQUIRED'
            });
        }

        try {
            const profile = await getPlayerProfile(id);

            if (!profile) {
                return reply.status(404).send({
                    success: false,
                    error: 'Player not found',
                    code: 'PLAYER_NOT_FOUND'
                });
            }

            return { success: true, user: profile };
        } catch (error) {
            console.error('Error loading player profile:', error);
            return reply.status(503).send({
                success: false,
                error: 'common.internalError',
                code: 'DB_ERROR'
            });
        }
    });
}