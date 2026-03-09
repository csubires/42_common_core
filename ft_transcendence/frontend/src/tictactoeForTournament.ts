import { navigate } from './router.js';
import {
	getGameSession,
	type Player,
} from './gameService.js';

// ===== CALLBACK (mirrors pong.ts) =====

export interface MatchResult {
	player1: Player;
	player2: Player;
	player1Score: number;
	player2Score: number;
	winner: Player;
}

let onGameEndCallback: ((result: MatchResult) => void) | null = null;

export function setOnTicTacToeGameEnd(callback: (result: MatchResult) => void): void {
	onGameEndCallback = callback;
}

// ===== GAME STATE =====

const BOARD_SIZE = 3;
const BACKGROUND_COLOR = '#000';
const GRID_COLOR = '#fff';
const X_COLOR = '#3b82f6';
const O_COLOR = '#ef4444';

let canvas: HTMLCanvasElement | null = null;
let ctx: CanvasRenderingContext2D | null = null;
let board: string[][] = [];
let currentPlayer: 'X' | 'O' = 'X';
let over = false;

let winnerTimeoutId: ReturnType<typeof setTimeout> | null = null;
let initTimeoutId: ReturnType<typeof setTimeout> | null = null;

let player1: Player;
let player2: Player;

// ===== PUBLIC API =====

export function initTicTacToeForTournament(config: {
	player1: Player;
	player2: Player;
}): void {
	const session = getGameSession();
	if (!session) {
		console.error('No game session found for TicTacToe tournament match');
		navigate('games');
		return;
	}

	player1 = config.player1;
	player2 = config.player2;

	navigate('game');

	initTimeoutId = setTimeout(() => {
		initTimeoutId = null;

		canvas = document.getElementById('gameCanvas') as HTMLCanvasElement;
		if (!canvas) return;
		ctx = canvas.getContext('2d')!;

		canvas.width = 600;
		canvas.height = 600;
		resizeCanvas();
		window.addEventListener('resize', resizeCanvas);

		board = Array(BOARD_SIZE).fill(null).map(() =>
			Array(BOARD_SIZE).fill('')
		);
		currentPlayer = 'X';
		over = false;

		document.getElementById('exitGameContainer')?.classList.remove('hidden');

		canvas.removeEventListener('click', handleClick);
		canvas.addEventListener('click', handleClick);

		showPlayerLabels();
		draw();
	}, 50);
}

export function stopTicTacToeForTournament(): void {
	over = true;

	if (initTimeoutId)    { clearTimeout(initTimeoutId);    initTimeoutId = null; }
	if (winnerTimeoutId)  { clearTimeout(winnerTimeoutId);  winnerTimeoutId = null; }

	window.removeEventListener('resize', resizeCanvas);

	if (canvas) {
		canvas.removeEventListener('click', handleClick);
		canvas = null;
	}

	document.getElementById('exitGameBtn')?.classList.add('hidden');
	hidePlayerLabels();
}

// ===== PLAYER LABELS ======

function showPlayerLabels(): void {
	const container = document.getElementById('playerLabels');
	const labelX = document.getElementById('labelPlayerX');
	const labelO = document.getElementById('labelPlayerO');
	if (container && labelX && labelO) {
		labelX.textContent = `✕ ${player1.name}`;
		labelO.textContent = `◯ ${player2.name}`;
		labelX.style.color = X_COLOR;
		labelO.style.color = O_COLOR;
		container.classList.remove('hidden');
	}
}

function hidePlayerLabels(): void {
	const container = document.getElementById('playerLabels');
	if (container) container.classList.add('hidden');
}

// ===== DRAWING =====

function draw(): void {
	if (!ctx) return;
	const cellSize = 600 / BOARD_SIZE;

	ctx.fillStyle = BACKGROUND_COLOR;
	ctx.fillRect(0, 0, 600, 600);

	ctx.strokeStyle = GRID_COLOR;
	ctx.lineWidth = 4;

	for (let i = 1; i < BOARD_SIZE; i++) {
		ctx.beginPath(); ctx.moveTo(i * cellSize, 0);   ctx.lineTo(i * cellSize, 600); ctx.stroke();
		ctx.beginPath(); ctx.moveTo(0, i * cellSize);   ctx.lineTo(600, i * cellSize); ctx.stroke();
	}

	ctx.font = `${Math.floor(cellSize * 0.6)}px sans-serif`;
	ctx.textAlign = 'center';
	ctx.textBaseline = 'middle';

	for (let r = 0; r < BOARD_SIZE; r++) {
		for (let c = 0; c < BOARD_SIZE; c++) {
			if (board[r][c]) {
				ctx.fillStyle = board[r][c] === 'X' ? X_COLOR : O_COLOR;
				ctx.fillText(board[r][c], c * cellSize + cellSize / 2, r * cellSize + cellSize / 2);
			}
		}
	}
}

function resizeCanvas(): void {
	if (!canvas) return;
	const maxW = Math.min(window.innerWidth - 32, 600);
	canvas.style.width  = `${maxW}px`;
	canvas.style.height = `${maxW}px`;
}

// ===== INPUT =====

function handleClick(e: MouseEvent): void {
	if (over || !canvas) return;

	const rect = canvas.getBoundingClientRect();
	const scaleX = canvas.width / rect.width;
	const scaleY = canvas.height / rect.height;
	const cellSize = canvas.width / BOARD_SIZE;
	const c = Math.floor((e.clientX - rect.left) * scaleX / cellSize);
	const r = Math.floor((e.clientY - rect.top) * scaleY / cellSize);

	if (c < 0 || c >= BOARD_SIZE) return;
	if (r < 0 || r >= BOARD_SIZE) return;
	if (board[r][c]) return;

	makeMove(r, c);
}

// ===== GAME LOGIC =====

function makeMove(r: number, c: number): void {
	board[r][c] = currentPlayer;
	draw();

	const result = checkWin();
	if (result) {
		over = true;

		let score1 = 0, score2 = 0;
		if      (result === 'X') { score1 = 1; }
		else if (result === 'O') { score2 = 1; }
		else                     { score1 = 0.5; score2 = 0.5; }  // Tie

		winnerTimeoutId = setTimeout(() => {
			winnerTimeoutId = null;
			fireGameEnd(result, score1, score2);
		}, 300);
	} else {
		currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
	}
}

function fireGameEnd(result: string, score1: number, score2: number): void {
	// In a tie there is no real winner; we pass player1 only as a placeholder
	// but score1 === score2 === 0.5, so saveMatch / saveTournamentMatch will
	// record it correctly (both IDs present, scores equal).
	// The tournament bracket always needs a winner to advance, so in a tie
	// we pick the player who is registered (or player1 as last resort).
	const winner = result === 'Tie'
		? (!player1.isGuest ? player1 : !player2.isGuest ? player2 : player1)
		: result === 'X' ? player1 : player2;

	const matchResult: MatchResult = {
		player1,
		player2,
		player1Score: score1,
		player2Score: score2,
		winner,
	};

	if (onGameEndCallback) {
		onGameEndCallback(matchResult);
	} else {
		// Standalone fallback (should not normally happen in tournament context)
		showWinnerAndExit(result);
	}
}

function showWinnerAndExit(w: string): void {
	const el  = document.getElementById('countdown')!;
	const txt = document.getElementById('countdownText')!;
	el.classList.remove('hidden');

	document.getElementById('exitGameBtn')?.classList.add('hidden');

	txt.textContent = w === 'Tie'
		? "It's a Tie!"
		: `${(w === 'X' ? player1 : player2).name} Wins!`;
	txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';

	setTimeout(() => {
		el.classList.add('hidden');
		txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';
		navigate('games');
	}, 2000);
}

function checkWin(): string | null {
	const size = BOARD_SIZE;

	// Rows
	for (let r = 0; r < size; r++)
		for (let c = 0; c <= size - size; c++) {
			const first = board[r][c];
			if (first && board[r].slice(c, c + size).every(cell => cell === first)) return first;
		}

	// Columns
	for (let c = 0; c < size; c++)
		for (let r = 0; r <= size - size; r++) {
			const first = board[r][c];
			if (first) {
				let match = true;
				for (let i = 1; i < size; i++) if (board[r + i][c] !== first) { match = false; break; }
				if (match) return first;
			}
		}

	// Diagonals ↘
	for (let r = 0; r <= size - size; r++)
		for (let c = 0; c <= size - size; c++) {
			const first = board[r][c];
			if (first) {
				let match = true;
				for (let i = 1; i < size; i++) if (board[r + i][c + i] !== first) { match = false; break; }
				if (match) return first;
			}
		}

	// Diagonals ↙
	for (let r = 0; r <= size - size; r++)
		for (let c = size - 1; c < size; c++) {
			const first = board[r][c];
			if (first) {
				let match = true;
				for (let i = 1; i < size; i++) if (board[r + i][c - i] !== first) { match = false; break; }
				if (match) return first;
			}
		}

	return board.some(row => row.some(cell => cell === '')) ? null : 'Tie';
}

// ===== CLEANUP ON PAGE CHANGE =====

window.addEventListener('beforepagechange', () => {
	stopTicTacToeForTournament();
});
