import { navigate } from "./router.js";
import type { Player } from "./gameService.js";
import {
	loadTournament,
	saveTournament,
	getCurrentMatch,
	setMatchWinner,
	advanceTournament,
	getChampion,
	saveTournamentMatch,
	updateTournamentRound,
	completeTournamentInDB
} from "./tournamentEngine.js";
import { startGameSession } from "./gameService.js";
import { initPongGame, setOnGameEnd, showWinnerOverlay } from "./pong.js";
import {
	initTicTacToeForTournament,
	setOnTicTacToeGameEnd,
	//stopTicTacToeForTournament,
	type MatchResult as TicTacToeMatchResult
} from "./tictactoeForTournament.js";

export function startCurrentMatch(type: string): void {
	const tournament = loadTournament();
	if (!tournament) return;

	const match = getCurrentMatch(tournament);
	if (!match) return;

	const isPong = type === "P";
	const gType  = isPong ? 'pong' : 'tictactoe';

	startGameSession({
		player1:      match.player1,
		player2:      match.player2,
		gameType:     gType,
		isAI:         match.player2.id === "AI",
		difficulty:   match.player2.id === "AI" ? 3 : undefined,
		startTime:    Date.now(),
		tournamentId: tournament.tournamentId || null
	});

	if (isPong) {
		setOnGameEnd((result) => {
			showWinnerOverlay(result.winner.name, () => {
				finishMatch(result.winner, result.player1Score, result.player2Score);
			});
		});

		navigate("game");
		setTimeout(() => {
			initPongGame({
				player1:   match.player1,
				player2:   match.player2,
				isAI:      match.player2.id === "AI",
				difficulty: match.player2.id === "AI" ? 3 : undefined
			});
		}, 100);

	} else {
		// TicTacToe tournament match
		setOnTicTacToeGameEnd((result: TicTacToeMatchResult) => {
			// Reuse the same winner overlay from pong for consistency
			showWinnerOverlay(result.winner.name, () => {
				finishMatch(result.winner, result.player1Score, result.player2Score);
			});
		});

		// initTicTacToeForTournament calls navigate('game') internally
		initTicTacToeForTournament({
			player1:   match.player1,
			player2:   match.player2,
		});
	}
}

export async function finishMatch(
	winner: Player,
	player1Score: number,
	player2Score: number
): Promise<void> {
	const tournament = loadTournament();
	if (!tournament) return;

	const match = getCurrentMatch(tournament);
	if (!match) return;

	if (tournament.tournamentId) {
		const session = await import('./gameService.js').then(m => m.getGameSession());
		const matchDuration = session
			? Math.floor((Date.now() - session.startTime) / 1000)
			: null;

		await saveTournamentMatch(
			tournament.tournamentId,
			match.player1,
			match.player2,
			player1Score,
			player2Score,
			winner,
			matchDuration || undefined,
			tournament.gameType ?? 'pong'      // ← propagar el tipo de juego del torneo
		);
	}

	setMatchWinner(tournament, winner);
	const previousRound = tournament.currentRoundIndex;
	advanceTournament(tournament);
	saveTournament(tournament);

	if (tournament.tournamentId && tournament.currentRoundIndex !== previousRound) {
		await updateTournamentRound(tournament.tournamentId, tournament.currentRoundIndex);
	}

	const champion = getChampion(tournament);
	if (champion) {
		if (tournament.tournamentId) {
			await completeTournamentInDB(
				tournament.tournamentId,
				champion,
				tournament.currentRoundIndex
			);
		}
		showChampion(champion);
	} else {
		navigate("tournament_game");
	}
}

function showChampionOverlay(championName: string, onComplete: () => void): void {
	const el  = document.getElementById('countdown');
	const txt = document.getElementById('countdownText');

	if (!el || !txt) { onComplete(); return; }

	el.classList.remove('hidden');
	txt.innerHTML = `<div class="text-6xl font-bold text-yellow-400 mb-4">🏆 ${championName}</div><div class="text-4xl font-semibold text-yellow-300">Tournament Champion!</div>`;

	setTimeout(() => {
		el.classList.add('hidden');
		txt.className = 'text-9xl font-extrabold text-yellow-300';
		txt.innerHTML = '';
		onComplete();
	}, 4000);
}

function showChampion(player: Player): void {
	showChampionOverlay(player.name, () => {
		sessionStorage.removeItem("Tournament");
		navigate("home");
	});
}