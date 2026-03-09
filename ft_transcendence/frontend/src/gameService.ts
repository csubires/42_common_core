import { api, getToken, ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError } from './api.js';

// ===== TYPES =====

export interface Player {
	id: string | null;      // null for guests
	name: string;           // display name or alias
	isGuest: boolean;
}

export interface MatchResult {
	player1: Player;
	player2: Player;
	player1Score: number;
	player2Score: number;
	winner: Player;
	gameType: 'pong' | 'tictactoe';
	tournamentId?: number | null;
	matchDuration?: number | null;  // seconds
}

export interface UserProfile {
	id: string;
	username: string;
	email: string;
	avatar: string;
	display_name: string;
}

export interface GameSession {
	player1: Player;
	player2: Player;
	gameType: 'pong' | 'tictactoe';
	isAI: boolean;
	difficulty?: number;
	startTime: number;
	tournamentId?: number | null;
}

// ===== USER CACHE =====

let cachedUser: UserProfile | null = null;

export async function getCurrentUser(): Promise<UserProfile | null> {
	const token = getToken();
	if (!token) {
		cachedUser = null;
		return null;
	}

	if (cachedUser) {
		return cachedUser;
	}

	try {
		const response = await api<{ success: boolean; user: UserProfile }>('/api/auth/profile-data');
		if (response.success && response.user) {
			cachedUser = response.user;
			return cachedUser;
		}
		return null;
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error getting user profile:', error);
		}
		return null;
	}
}

export function clearUserCache(): void {
	cachedUser = null;
}

export function isLoggedIn(): boolean {
	return getToken() !== null;
}

// ===== PLAYER FACTORY FUNCTIONS =====

export function createRegisteredPlayer(user: UserProfile): Player {
	return {
		id: user.id,
		name: user.display_name,
		isGuest: false
	};
}

export function createGuestPlayer(alias: string): Player {
	return {
		id: null,
		name: alias || 'Guest',
		isGuest: true
	};
}

export function createAIPlayer(difficulty: number): Player {
	const difficultyNames: Record<number, string> = {
		2: 'AI (Easy)',
		3: 'AI (Medium)',
		4: 'AI (Hard)'
	};
	return {
		id: null,
		name: difficultyNames[difficulty] || 'AI',
		isGuest: true
	};
}

// ===== PLAYER VERIFICATION =====

export async function verifyPlayerByName(playerName: string): Promise<UserProfile | null> {
	try {
		const response = await api<{ success: boolean; users: UserProfile[] }>(
			`/api/database/players?search=${encodeURIComponent(playerName)}&limit=10`
		);

		if (response.success && response.users) {
			const player = response.users.find((u: UserProfile) =>
				u.username === playerName || u.display_name === playerName
			);
			return player || null;
		}
		return null;
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error verifying player:', error);
		}
		return null;
	}
}

export async function loginPlayer(email: string, password: string): Promise<UserProfile | null> {
	const response = await api<{ success: boolean; user: UserProfile }>('/api/auth/login', {
		method: 'POST',
		body: JSON.stringify({ email, password })
	});

	if (response.success && response.user) {
		return response.user;
	}
	return null;
}

// ===== MATCH SAVING =====

export async function saveMatch(result: MatchResult): Promise<{
	success: boolean;
	matchId?: number;
	error?: string;
	skipped?: boolean
}> {
	// Only save matches where at least one player is logged in
	const hasLoggedInPlayer = result.player1.id !== null || result.player2.id !== null;
	if (!hasLoggedInPlayer) {
		//console.log('Match not saved: no logged-in players (guest vs guest)');
		return { success: true, skipped: true };
	}

	// Determine user vs opponent based on who's logged in
	let userScore, opponentScore, opponentName, opponentId;
	if (result.player1.id !== null) {
		userScore = result.player1Score;
		opponentScore = result.player2Score;
		opponentName = result.player2.name;
		opponentId = result.player2.id;
	} else {
		userScore = result.player2Score;
		opponentScore = result.player1Score;
		opponentName = result.player1.name;
		opponentId = result.player1.id;
	}

	try {
		const payload = {
			opponent_id: opponentId || null,
			opponent_name: opponentName,
			user_score: userScore,
			opponent_score: opponentScore,
			winner: result.winner.name,
			game_type: result.gameType,
			tournament_id: result.tournamentId || null,
			match_duration: result.matchDuration || null
		};

		// Call to register the match
		const response = await api<{ success: boolean; matchId: number }>('/api/database/matches', {
			method: 'POST',
			body: JSON.stringify(payload)
		});

		return { success: true, matchId: response.matchId };
	} catch (error: any) {
		if (error instanceof ServerError) {
			console.error('Server error saving match:', error);
		}
		return { success: false, error: error.message };
	}
}

// ===== USER STATS =====

export async function getUserStats(userId: string): Promise<{
	wins: number;
	losses: number;
	games_played: number;
	win_rate: number;
	recentMatches: any[];
} | null> {
	try {
		const response = await api<{
			success: boolean;
			stats: { wins: number; losses: number; games_played: number; win_rate: number };
			recentMatches: any[];
		}>(`/api/database/stats/user/${userId}`);

		if (response.success) {
			return {
				...response.stats,
				recentMatches: response.recentMatches
			};
		}
		return null;
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error getting user stats:', error);
		}
		return null;
	}
}

export async function getMatchHistory(userId: string, limit = 20): Promise<any[]> {
	try {
		const response = await api<{ success: boolean; matches: any[] }>(
			`/api/database/matches/user/${userId}?limit=${limit}`
		);
		return response.success ? response.matches : [];
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error getting match history:', error);
		}
		return [];
	}
}

// ===== GAME SESSION MANAGEMENT =====

let currentSession: GameSession | null = null;

export function startGameSession(session: GameSession): void {
	currentSession = {
		...session,
		startTime: Date.now()
	};
}

export function getGameSession(): GameSession | null {
	return currentSession;
}

export async function endGameSession(
	player1Score: number,
	player2Score: number
): Promise<{ success: boolean; matchId?: number; skipped?: boolean }> {
	if (!currentSession) {
		// No active game session - cannot end
		return { success: false };
	}

	const winner = player1Score > player2Score
		? currentSession.player1
		: currentSession.player2;

	const matchDuration = Math.floor((Date.now() - currentSession.startTime) / 1000);

	const result = await saveMatch({
		player1: currentSession.player1,
		player2: currentSession.player2,
		player1Score,
		player2Score,
		winner,
		gameType: currentSession.gameType,
		tournamentId: currentSession.tournamentId,
		matchDuration
	});

	currentSession = null;
	return result;
}

export function cancelGameSession(): void {
	currentSession = null;
}