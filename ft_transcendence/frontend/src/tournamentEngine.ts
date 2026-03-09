import type { Player } from "./gameService";
import { api, ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError } from './api.js';

export type Match = {
	player1: Player;
	player2: Player;
	winner?: Player;
};

export type Round = {
	matches: Match[];
};

export type Tournament = {
	players: Player[];
	rounds: Round[];
	currentRoundIndex: number;
	currentMatchIndex: number;
	tournamentId?: number | null;
	creatorId?: string | null;
	gameType?: 'pong' | 'tictactoe';
};

// Utils
function shufflePlayers(players: Player[]): Player[] {
	return [...players].sort(() => Math.random() - 0.5);
}

function createMatches(players: Player[]): Match[] {
	const matches: Match[] = [];

	for (let i = 0; i < players.length; i += 2) {
		let p1 = players[i];
		let p2 = players[i + 1];

		if (p1.id === "AI") {
			[p1, p2] = [p2, p1];
		}

		matches.push({ player1: p1, player2: p2 });
	}
	return matches;
}

export function createTournament(players: Player[]): Tournament {
	const shuffled = shufflePlayers(players);

	return {
		players: shuffled,
		rounds: [{ matches: createMatches(shuffled) }],
		currentRoundIndex: 0,
		currentMatchIndex: 0
	};
}

export function getCurrentMatch(t: Tournament): Match | null {
	return t.rounds[t.currentRoundIndex]?.matches[t.currentMatchIndex] ?? null;
}

export function setMatchWinner(t: Tournament, winner: Player): void {
	const match = getCurrentMatch(t);
	if (match) match.winner = winner;
}

export function advanceTournament(t: Tournament): void {
	const round = t.rounds[t.currentRoundIndex];
	t.currentMatchIndex++;

	if (t.currentMatchIndex < round.matches.length) return;

	const winners = round.matches
		.map(m => m.winner)
		.filter(Boolean) as Player[];

	if (winners.length <= 1) return;

	t.rounds.push({ matches: createMatches(winners) });
	t.currentRoundIndex++;
	t.currentMatchIndex = 0;
}

// TournamentWinner
export function getChampion(t: Tournament): Player | null {
	const lastRound = t.rounds[t.rounds.length - 1];
	return lastRound?.matches.length === 1
		? lastRound.matches[0].winner ?? null
		: null;
}

// Storage
export function saveTournament(t: Tournament): void {
	sessionStorage.setItem("Tournament", JSON.stringify(t));
}

export function loadTournament(): Tournament | null {
	const data = sessionStorage.getItem("Tournament");
	return data ? JSON.parse(data) : null;
}

// ===== DATABASE FUNCTIONS =====

/**
 * Creates a tournament in the DB
 * @returns tournament ID or null if it fails
 */
export async function createTournamentInDB(
	players: Player[],
	type: string,
	creatorId?: string | null
): Promise<number | null> {
	try {
		// Determine tournament creator (first registered player by default)
		const actualCreatorId = creatorId || players.find(p => !p.isGuest)?.id || null;

		// Determine type of tournament (P -> Pong; T -> TicTacToe)
		const tournamentName = type == 'P' ? 'Pong' : 'TicTacToe';

		const response = await api<{ success: boolean; tournamentId: number }>(
			'/api/database/tournaments',
			{
				method: 'POST',
				body: JSON.stringify({
					name: `${tournamentName} Tournament ${new Date().toLocaleDateString()}`,
					creator_id: actualCreatorId,
					max_players: players.length,
					tournament_type: tournamentName
				})
			}
		);

		if (response.success && response.tournamentId) {
			// Save tournament players
			await saveTournamentParticipants(response.tournamentId, players);
			return response.tournamentId;
		}
		return null;
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error creating tournament:', error);
		}
		return null;
	}
}

/**
 * Store the tournament players in the DB
 */
async function saveTournamentParticipants(
	tournamentId: number,
	players: Player[]
): Promise<void> {
	try {
		const participants = players.map((player, index) => ({
			tournament_id: tournamentId,
			user_id: player.isGuest ? null : player.id,
			display_name: player.name,
			seed: index + 1
		}));

		await api('/api/database/tournament-participants', {
			method: 'POST',
			body: JSON.stringify({ participants })
		});
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error saving tournament participants:', error);
		}
	}
}

/**
 * Starts a tournament in the DB
 */
export async function startTournamentInDB(tournamentId: number): Promise<void> {
	try {
		await api(`/api/database/tournaments/${tournamentId}/start`, {
			method: 'PATCH',
			body: JSON.stringify({
				status: 'active',
				started_at: new Date().toISOString()
			})
		});
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error starting tournament:', error);
		}
	}
}

/**
 * Store a tournament's match in the DB
 * Only if there is a registered player in the match
 */
export async function saveTournamentMatch(
	tournamentId: number,
	player1: Player,
	player2: Player,
	player1Score: number,
	player2Score: number,
	winner: Player,
	matchDuration?: number,
	gameType: 'pong' | 'tictactoe' = 'pong'   // ← nuevo parámetro con default para no romper llamadas existentes
): Promise<{ success: boolean; matchId?: number }> {
	const hasRegisteredPlayer = !player1.isGuest || !player2.isGuest;
	if (!hasRegisteredPlayer) {
		return { success: true };
	}

	try {
		const payload = {
			player1_id:    player1.isGuest ? null : player1.id,
			player1_name:  player1.name,
			player2_id:    player2.isGuest ? null : player2.id,
			player2_name:  player2.name,
			player1_score: player1Score,
			player2_score: player2Score,
			winner_id:     winner.isGuest ? null : winner.id,
			winner_name:   winner.name,
			game_type:     gameType,                               // ← ya no hardcodeado
			tournament_id: tournamentId,
			match_duration: matchDuration || null
		};

		const response = await api<{ success: boolean; matchId: number }>(
			'/api/database/matches',
			{ method: 'POST', body: JSON.stringify(payload) }
		);

		return { success: true, matchId: response.matchId };
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error saving tournament match:', error);
		}
		return { success: false };
	}
}

/**
 * Completes a tournament in DB
 */
export async function completeTournamentInDB(
	tournamentId: number,
	winner: Player,
	currentRound: number
): Promise<void> {
	try {
		await api(`/api/database/tournaments/${tournamentId}/complete`, {
			method: 'PATCH',
			body: JSON.stringify({
				status: 'completed',
				winner_id: winner.isGuest ? null : winner.id,
				winner_name: winner.name,
				current_round: currentRound,
				completed_at: new Date().toISOString()
			})
		});
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error completing tournament:', error);
		}
	}
}

/**
 * Updates round
 */
export async function updateTournamentRound(
	tournamentId: number,
	currentRound: number
): Promise<void> {
	try {
		await api(`/api/database/tournaments/${tournamentId}/round`, {
			method: 'PATCH',
			body: JSON.stringify({
				current_round: currentRound
			})
		});
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error updating tournament round:', error);
		}
	}
}