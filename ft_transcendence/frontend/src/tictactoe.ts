import { navigate } from './router.js';
import {
	getCurrentUser,
	createRegisteredPlayer,
	createGuestPlayer,
	createAIPlayer,
	startGameSession,
	endGameSession,
	getGameSession,
	type Player,
	type GameSession
} from './gameService.js';

let canvas: HTMLCanvasElement | null = null;
let ctx: CanvasRenderingContext2D | null = null;
let board: string[][] = [['', '', ''], ['', '', ''], ['', '', '']];
let currentPlayer: 'X' | 'O' = 'X';
let over = false;
let animationFrame: number | null = null;
let aiMoveTimeoutId: ReturnType<typeof setTimeout> | null = null;
let winnerTimeoutId: ReturnType<typeof setTimeout> | null = null;
let initTimeoutId: ReturnType<typeof setTimeout> | null = null;

const TURN_TIME_SECONDS = 10;
let timerSecondsLeft = TURN_TIME_SECONDS;
let timerIntervalId: ReturnType<typeof setInterval> | null = null;

let player1: Player;  // X
let player2: Player;  // O
let isAI = false;

interface CustomSettings {
	boardSize: number;
	theme: 'classic' | 'neon' | 'minimal';
	specialMode: 'none' | 'timed';
}

let settings: CustomSettings = {
	boardSize: 3,
	theme: 'classic',
	specialMode: 'none'
};

const themes = {
	classic: {
		backgroundColor: '#000',
		gridColor: '#fff',
		xColor: '#3b82f6',
		oColor: '#ef4444'
	},
	neon: {
		backgroundColor: '#0a0a1a',
		gridColor: '#00ff00',
		xColor: '#ff00ff',
		oColor: '#00ffff'
	},
	minimal: {
		backgroundColor: '#f5f5f5',
		gridColor: '#333',
		xColor: '#666',
		oColor: '#999'
	}
};

export async function setupTicTacToe(ai: boolean = false, difficulty: number = 3, p1?: Player, p2?: Player): Promise<void> {
	const currentUser = await getCurrentUser();

	loadCustomization();

	if (p1) {
		player1 = p1;
	} else if (currentUser) {
		player1 = createRegisteredPlayer(currentUser);
	} else {
		player1 = createGuestPlayer('Player 1');
	}

	if (ai) {
		player2 = createAIPlayer(difficulty);
		isAI = true;
	} else if (p2) {
		player2 = p2;
		isAI = false;
	} else {
		player2 = createGuestPlayer('Player 2');
		isAI = false;
	}

	startGameSession({
		player1,
		player2,
		gameType: 'tictactoe',
		isAI: ai,
		difficulty: ai ? difficulty : undefined,
		startTime: Date.now()
	});

	startTicTacToe();
}

export function startTicTacToe(): void {
	const session = getGameSession();
	if (!session) {
		// No game session - redirect to games page
		navigate('games');
		return;
	}

	player1 = session.player1;
	player2 = session.player2;
	isAI = session.isAI;

	navigate('game');

	initTimeoutId = setTimeout(() => {
		initTimeoutId = null;
		canvas = document.getElementById('gameCanvas') as HTMLCanvasElement;
		if (!canvas) return;
		ctx = canvas.getContext('2d')!;

		const canvasSize = 600;
		canvas.width = canvasSize;
		canvas.height = canvasSize;
		resizeTicTacToe();
		window.addEventListener('resize', resizeTicTacToe);

		board = Array(settings.boardSize).fill(null).map(() =>
			Array(settings.boardSize).fill('')
		);
		currentPlayer = 'X';
		over = false;

		const exitBtn = document.getElementById('exitGameBtn');
		if (exitBtn) {
			exitBtn.classList.remove('hidden');
		}

		const settingsMenu = document.getElementById('tictactoeSettings');
		if (settingsMenu) {
			settingsMenu.classList.remove('hidden');
		}

		canvas.onclick = null;

		canvas.addEventListener('click', handleClick);
		showPlayerLabels();
		draw();
		startTurnTimer();
	}, 50);
}

function draw(): void {
	if (!ctx) return;
	const theme = themes[settings.theme];
	const cellSize = 600 / settings.boardSize;

	ctx.fillStyle = theme.backgroundColor;
	ctx.fillRect(0, 0, 600, 600);

	ctx.strokeStyle = theme.gridColor;
	ctx.lineWidth = 4;

	for (let i = 1; i < settings.boardSize; i++) {
		ctx.beginPath();
		ctx.moveTo(i * cellSize, 0);
		ctx.lineTo(i * cellSize, 600);
		ctx.stroke();

		ctx.beginPath();
		ctx.moveTo(0, i * cellSize);
		ctx.lineTo(600, i * cellSize);
		ctx.stroke();
	}

	ctx.font = `${Math.floor(cellSize * 0.6)}px sans-serif`;
	ctx.textAlign = 'center';
	ctx.textBaseline = 'middle';

	for (let r = 0; r < settings.boardSize; r++) {
		for (let c = 0; c < settings.boardSize; c++) {
			if (board[r][c]) {
				ctx.fillStyle = board[r][c] === 'X' ? theme.xColor : theme.oColor;
				ctx.fillText(board[r][c], c * cellSize + cellSize / 2, r * cellSize + cellSize / 2);
			}
		}
	}

	if (settings.specialMode === 'timed' && !over) {
		const ratio = timerSecondsLeft / TURN_TIME_SECONDS;
		const barH = 10;
		const barY = 600 - barH;

		ctx.fillStyle = 'rgba(255,255,255,0.15)';
		ctx.fillRect(0, barY, 600, barH);

		const r2 = Math.min(1, 2 * (1 - ratio));
		const g2 = Math.min(1, 2 * ratio);
		ctx.fillStyle = `rgb(${Math.round(r2 * 220)},${Math.round(g2 * 180)},0)`;
		ctx.fillRect(0, barY, 600 * ratio, barH);

		ctx.font = 'bold 18px monospace';
		ctx.fillStyle = timerSecondsLeft <= 3 ? '#ff4444' : '#ffffff';
		ctx.textAlign = 'right';
		ctx.textBaseline = 'bottom';
		ctx.fillText(`${timerSecondsLeft}s`, 596, barY - 2);
		ctx.textAlign = 'center';
		ctx.textBaseline = 'middle';
	}
}

function resizeTicTacToe(): void {
	if (!canvas) return;
	const maxW = Math.min(window.innerWidth - 32, 600);
	canvas.style.width = `${maxW}px`;
	canvas.style.height = `${maxW}px`;
}

function handleClick(e: MouseEvent): void {
	if (over) return;
	if (!canvas) return;
	if (currentPlayer === 'O' && isAI) return;

	const rect = canvas.getBoundingClientRect();
	const scaleX = canvas.width / rect.width;
	const scaleY = canvas.height / rect.height;
	const cellSize = canvas.width / settings.boardSize;
	const c = Math.floor((e.clientX - rect.left) * scaleX / cellSize);

	if (c < 0 || c >= settings.boardSize) return;

	const r = Math.floor((e.clientY - rect.top) * scaleY / cellSize);
	if (r < 0 || r >= settings.boardSize) return;
	if (board[r][c]) return;
	makeMove(r, c);
}

function makeMove(r: number, c: number): void {
	stopTurnTimer();
	board[r][c] = currentPlayer;
	draw();

	const result = checkWin();
	if (result) {
		over = true;

		let score1 = 0, score2 = 0;
		if (result === 'X') score1 = 1;
		else if (result === 'O') score2 = 1;
		else { score1 = 0.5; score2 = 0.5; }

		endGameSession(score1, score2).then(() => {
			winnerTimeoutId = setTimeout(() => { winnerTimeoutId = null; showWinner(result); }, 300);
		});
	} else {
		currentPlayer = currentPlayer === 'X' ? 'O' : 'X';

		if (isAI && currentPlayer === 'O' && !over) {
			aiMoveTimeoutId = setTimeout(() => { aiMoveTimeoutId = null; makeAIMove(); }, 500); // Small delay for better UX
		} else {
			startTurnTimer();
		}
	}
}

function startTurnTimer(): void {
	stopTurnTimer();
	if (settings.specialMode !== 'timed' || over) return;
	timerSecondsLeft = TURN_TIME_SECONDS;
	draw();
	timerIntervalId = setInterval(() => {
		timerSecondsLeft--;
		draw();
		if (timerSecondsLeft <= 0) {
			stopTurnTimer();
			if (over) return;

			currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
			if (isAI && currentPlayer === 'O' && !over) {
				aiMoveTimeoutId = setTimeout(() => { aiMoveTimeoutId = null; makeAIMove(); }, 300);
			} else {
				startTurnTimer();
			}
		}
	}, 1000);
}

function stopTurnTimer(): void {
	if (timerIntervalId !== null) {
		clearInterval(timerIntervalId);
		timerIntervalId = null;
	}
}

function makeAIMove(): void {
	if (over) return;

	const session = getGameSession();
	const difficulty = session?.difficulty || 3;

	let move: { r: number; c: number } | null = null;

	// Difficulty levels:
	// 2 (Easy): Random moves
	// 3 (Medium): Mix of optimal and random
	// 4 (Hard): Always optimal (minimax)

	if (difficulty === 2) {
		move = getRandomMove();
	} else if (difficulty === 3) {
		move = Math.random() < 0.6 ? getBestMove() : getRandomMove();
	} else {
		move = getBestMove();
	}

	if (move) {
		makeMove(move.r, move.c);
	}
}

function getRandomMove(): { r: number; c: number } | null {
	const empty: { r: number; c: number }[] = [];

	for (let r = 0; r < settings.boardSize; r++) {
		for (let c = 0; c < settings.boardSize; c++) {
			if (!board[r][c]) {
				empty.push({ r, c });
			}
		}
	}

	if (empty.length === 0) return null;
	return empty[Math.floor(Math.random() * empty.length)];
}

function getBestMove(): { r: number; c: number } | null {
	let bestScore = -Infinity;
	let bestMove: { r: number; c: number } | null = null;

	for (let r = 0; r < settings.boardSize; r++) {
		for (let c = 0; c < settings.boardSize; c++) {
			if (!board[r][c]) {
				board[r][c] = 'O';
				const score = minimax(board, 0, false);
				board[r][c] = '';

				if (score > bestScore) {
					bestScore = score;
					bestMove = { r, c };
				}
			}
		}
	}

	return bestMove;
}

function minimax(board: string[][], depth: number, isMaximizing: boolean): number {
	const result = checkWin();

	if (result === 'O') return 10 - depth;
	if (result === 'X') return depth - 10;
	if (result === 'Tie') return 0;

	if (depth > 6 && settings.boardSize > 3) {
		return 0;
	}

	if (isMaximizing) {
		let bestScore = -Infinity;
		for (let r = 0; r < settings.boardSize; r++) {
			for (let c = 0; c < settings.boardSize; c++) {
				if (!board[r][c]) {
					board[r][c] = 'O';
					const score = minimax(board, depth + 1, false);
					board[r][c] = '';
					bestScore = Math.max(score, bestScore);
				}
			}
		}
		return bestScore;
	} else {
		let bestScore = Infinity;
		for (let r = 0; r < settings.boardSize; r++) {
			for (let c = 0; c < settings.boardSize; c++) {
				if (!board[r][c]) {
					board[r][c] = 'X';
					const score = minimax(board, depth + 1, true);
					board[r][c] = '';
					bestScore = Math.min(score, bestScore);
				}
			}
		}
		return bestScore;
	}
}

function checkWin(): string | null {
	const size = settings.boardSize;
	const winLength = size === 3 ? 3 : size;

	for (let r = 0; r < size; r++) {
		for (let c = 0; c <= size - winLength; c++) {
			const first = board[r][c];
			if (first && board[r].slice(c, c + winLength).every(cell => cell === first)) {
				return first;
			}
		}
	}

	for (let c = 0; c < size; c++) {
		for (let r = 0; r <= size - winLength; r++) {
			const first = board[r][c];
			if (first) {
				let match = true;
				for (let i = 1; i < winLength; i++) {
					if (board[r + i][c] !== first) {
						match = false;
						break;
					}
				}
				if (match) return first;
			}
		}
	}

	for (let r = 0; r <= size - winLength; r++) {
		for (let c = 0; c <= size - winLength; c++) {
			const first = board[r][c];
			if (first) {
				let match = true;
				for (let i = 1; i < winLength; i++) {
					if (board[r + i][c + i] !== first) {
						match = false;
						break;
					}
				}
				if (match) return first;
			}
		}
	}

	for (let r = 0; r <= size - winLength; r++) {
		for (let c = winLength - 1; c < size; c++) {
			const first = board[r][c];
			if (first) {
				let match = true;
				for (let i = 1; i < winLength; i++) {
					if (board[r + i][c - i] !== first) {
						match = false;
						break;
					}
				}
				if (match) return first;
			}
		}
	}

	const hasEmpty = board.some(row => row.some(cell => cell === ''));
	return hasEmpty ? null : 'Tie';
}

function showPlayerLabels(): void {
	const container = document.getElementById('playerLabels');
	const labelX = document.getElementById('labelPlayerX');
	const labelO = document.getElementById('labelPlayerO');
	if (container && labelX && labelO) {
		const theme = themes[settings.theme];
		labelX.textContent = `✕ ${player1.name}`;
		labelO.textContent = `◯ ${player2.name}`;
		labelX.style.color = theme.xColor;
		labelO.style.color = theme.oColor;
		container.classList.remove('hidden');
	}
}

function hidePlayerLabels(): void {
	const container = document.getElementById('playerLabels');
	if (container) container.classList.add('hidden');
}

function showWinner(w: string): void {
	const el = document.getElementById('countdown')!;
	const txt = document.getElementById('countdownText')!;
	el.classList.remove('hidden');

	const exitBtn = document.getElementById('exitGameBtn');
	if (exitBtn) {
		exitBtn.classList.add('hidden');
	}

	const settingsMenu = document.getElementById('tictactoeSettings');
	if (settingsMenu) {
		settingsMenu.classList.add('hidden');
	}

	let message = '';
	if (w === 'Tie') {
		message = "It's a Tie!";
	} else {
		const winner = w === 'X' ? player1 : player2;
		message = `${winner.name} Wins!`;
	}

	txt.textContent = message;
	txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';

	setTimeout(() => {
		el.classList.add('hidden');
		txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';
		navigate('games');
	}, 2000);
}

export function stopTicTacToe(): void {
	over = true;

	if (initTimeoutId !== null) { clearTimeout(initTimeoutId); initTimeoutId = null; }
	if (aiMoveTimeoutId !== null) { clearTimeout(aiMoveTimeoutId); aiMoveTimeoutId = null; }
	if (winnerTimeoutId !== null) { clearTimeout(winnerTimeoutId); winnerTimeoutId = null; }
	if (animationFrame !== null) { cancelAnimationFrame(animationFrame); animationFrame = null; }
	stopTurnTimer();

	window.removeEventListener('resize', resizeTicTacToe);
	if (canvas) {
		canvas.removeEventListener('click', handleClick);
		canvas = null;
	}

	document.getElementById('exitGameBtn')?.classList.add('hidden');
	document.getElementById('tictactoeSettings')?.classList.add('hidden');
	hidePlayerLabels();
}

export function exitGame(): void {
	stopTicTacToe();
	navigate('games');
}

function loadCustomization(): void {
	const stored = localStorage.getItem('tictactoeCustomization');
	if (stored) {
		try {
			const parsed = JSON.parse(stored);
			settings = {
				boardSize: parsed.boardSize || 3,
				theme: parsed.theme || 'classic',
				specialMode: parsed.specialMode || 'none'
			};
		} catch (e) {
			
		}
	}
}

export function saveCustomization(newSettings: Partial<CustomSettings>): void {
	settings = { ...settings, ...newSettings };
	localStorage.setItem('tictactoeCustomization', JSON.stringify(settings));
}

export function getCustomization(): CustomSettings {
	return { ...settings };
}

export function changeTheme(theme: 'classic' | 'neon' | 'minimal'): void {
	settings.theme = theme;
	saveCustomization({ theme });
	draw();
}

export function changeSpecialMode(mode: 'none' | 'timed'): void {
	settings.specialMode = mode;
	saveCustomization({ specialMode: mode });

	if (!over) {
		if (mode === 'timed') {
			startTurnTimer();
		} else {
			stopTurnTimer();
			draw();
		}
	}
}

window.addEventListener('beforepagechange', () => {
	stopTicTacToe();
});

(window as any).setupTicTacToe = setupTicTacToe;
(window as any).startTicTacToe = startTicTacToe;
(window as any).exitGame = exitGame;
(window as any).changeTicTacToeTheme = changeTheme;
(window as any).changeTicTacToeMode = changeSpecialMode;