import { navigate } from './router.js';
import {
	type Player
} from './gameService.js';

let onGameEndCallback: ((result: MatchResult) => void) | null = null;

export function setOnGameEnd(callback: (result: MatchResult) => void): void {
	onGameEndCallback = callback;
}

interface MatchResult {
	player1: Player;
	player2: Player;
	player1Score: number;
	player2Score: number;
	winner: Player;
}

interface Paddle {
	x: number;
	y: number;
	w: number;
	h: number;
	dy: number;
}

interface Ball {
	x: number;
	y: number;
	r: number;
	dx: number;
	dy: number;
}

let canvas: HTMLCanvasElement;
let ctx: CanvasRenderingContext2D;
let animationId: number;
let countdownTimer: ReturnType<typeof setInterval> | null = null;
let initTimeoutId: ReturnType<typeof setTimeout> | null = null;
let gameOn = false;
let isAI = false;
let difficulty = 3;
let paddleHeight = 100;
let backgroundType = 'default';

let player1: Player;
let player2: Player;

const paddle1: Paddle = { x: 10, y: 250, w: 10, h: 100, dy: 0 };
const paddle2: Paddle = { x: 780, y: 250, w: 10, h: 100, dy: 0 };
const ball: Ball = { x: 400, y: 300, r: 10, dx: 5, dy: 5 };
let score1 = 0, score2 = 0;
const keys: Record<string, boolean> = {};

const INITIAL_BALL_SPEED = 3;
const MAX_BALL_SPEED = 15;
const SPEED_INCREMENT = 0.01;
const PADDLE_SPEED = 5;
const COLLISION_MARGIN = 6;
const IMPACT_ANGLE_FACTOR = 8;

let aiLastUpdate = 0;
let aiDecision: 'up' | 'down' | '' = '';
let aiTargetY: number = 250;

export function initPongGame(config: {
	player1: Player;
	player2: Player;
	isAI: boolean;
	difficulty?: number;
	gameOptions?: {
		background: string;
		difficulty: string;
	};
}): void {
	player1 = config.player1;
	player2 = config.player2;
	isAI = config.isAI;
	difficulty = config.difficulty || 3;

	navigate('game');

	// Set options AFTER navigate, because navigate triggers stopPongGame which resets them
	if (config.gameOptions) {
		switch (config.gameOptions.difficulty) {
			case 'easy':
				paddleHeight = 150;
				break;
			case 'medium':
				paddleHeight = 100;
				break;
			case 'hard':
				paddleHeight = 60;
				break;
			default:
				paddleHeight = 100;
		}
		backgroundType = config.gameOptions.background || 'default';
	}

	initTimeoutId = setTimeout(() => {
		initTimeoutId = null;
		canvas = document.getElementById('gameCanvas') as HTMLCanvasElement;
		ctx = canvas.getContext('2d')!;
		canvas.width = 800;
		canvas.height = 600;
		resizePong();
		window.addEventListener('resize', resizePong);

		// Reset game state
		gameOn = false;
		score1 = score2 = 0;
		paddle1.y = 250;
		paddle1.h = paddleHeight;
		paddle2.y = 250;
		paddle2.h = paddleHeight;
		paddle1.dy = paddle2.dy = 0;
		resetBall();

		aiLastUpdate = 0;
		aiDecision = '';
		aiTargetY = 250;
		Object.keys(keys).forEach(key => keys[key] = false);

		const exitContainer = document.getElementById('exitGameContainer');
		if (exitContainer) exitContainer.classList.remove('hidden');

		countdown(() => { gameOn = true; loop(); });
	}, 50);
}

function resetBall(direction?: 'left' | 'right'): void {
	ball.x = 400;
	ball.y = 300;

	if (direction === 'left') {
		ball.dx = -INITIAL_BALL_SPEED;
	} else if (direction === 'right') {
		ball.dx = INITIAL_BALL_SPEED;
	} else {
		ball.dx = (Math.random() > 0.5 ? 1 : -1) * INITIAL_BALL_SPEED;
	}

	ball.dy = (Math.random() > 0.5 ? 1 : -1) * INITIAL_BALL_SPEED;

	if (isAI) {
		updateAITarget();
	}
}

function predictBallYAtPaddle(ballState: Ball, paddleX: number): number {
	let x = ballState.x;
	let y = ballState.y;
	let dx = ballState.dx;
	let dy = ballState.dy;

	if (dx <= 0) return y;

	while (x < paddleX - ballState.r) {
		x += dx;
		y += dy;

		if (y - ballState.r < 0) {
			y = ballState.r;
			dy = -dy;
		} else if (y + ballState.r > canvas.height) {
			y = canvas.height - ballState.r;
			dy = -dy;
		}
	}

	return y;
}

function updateAITarget(): void {
	const predictedY = predictBallYAtPaddle(ball, paddle2.x);

	const errorMargin = difficulty === 2 ? 50 : difficulty === 3 ? 30 : 4;
	const randomOffset = (Math.random() - 0.5) * errorMargin;

	aiTargetY = predictedY - paddle2.h / 2 + randomOffset;

	if (aiTargetY < 0) aiTargetY = 0;
	if (aiTargetY > canvas.height - paddle2.h) {
		aiTargetY = canvas.height - paddle2.h;
	}
}

function loop(): void {
	if (!gameOn) return;
	update();
	draw();
	animationId = requestAnimationFrame(loop);
}

function update(): void {
	paddle1.dy = 0;
	if (keys['w'] && paddle1.y > 0) paddle1.dy = -PADDLE_SPEED;
	if (keys['s'] && paddle1.y < canvas.height - paddle1.h) paddle1.dy = PADDLE_SPEED;
	paddle1.y += paddle1.dy;

	// Clamp
	if (paddle1.y < 0) paddle1.y = 0;
	if (paddle1.y > canvas.height - paddle1.h) paddle1.y = canvas.height - paddle1.h;

	if (isAI) {
		const now = Date.now();
		const ballComingToAI = ball.dx > 0;
		const isHard = difficulty !== 2 && difficulty !== 3;
		const updateInterval = isHard
			? (ballComingToAI ? 50 : 200)
			: (ballComingToAI ? 800 : 1000);

		if (now - aiLastUpdate >= updateInterval) {
			aiLastUpdate = now;

			if (ballComingToAI) {
				updateAITarget();
			} else {
				aiTargetY = canvas.height / 2 - paddle2.h / 2;
			}

			const paddleCenter = paddle2.y + paddle2.h / 2;
			const targetCenter = aiTargetY + paddle2.h / 2;
			const threshold = isHard ? 0 : (ballComingToAI ? 4 : 30);

			if (paddleCenter < targetCenter - threshold) {
				aiDecision = 'down';
			} else if (paddleCenter > targetCenter + threshold) {
				aiDecision = 'up';
			} else {
				aiDecision = '';
			}
		}


		const currentCenter = paddle2.y + paddle2.h / 2;
		const targetCenterNow = aiTargetY + paddle2.h / 2;
		const stopThreshold = 3;
		if (Math.abs(currentCenter - targetCenterNow) <= stopThreshold) {
			aiDecision = '';
		}

		keys['o'] = aiDecision === 'up';
		keys['l'] = aiDecision === 'down';
	}

	paddle2.dy = 0;
	if (keys['o'] && paddle2.y > 0) paddle2.dy = -PADDLE_SPEED;
	if (keys['l'] && paddle2.y < canvas.height - paddle2.h) paddle2.dy = PADDLE_SPEED;
	paddle2.y += paddle2.dy;

	// Clamp 
	if (paddle2.y < 0) paddle2.y = 0;
	if (paddle2.y > canvas.height - paddle2.h) paddle2.y = canvas.height - paddle2.h;

	if (Math.abs(ball.dx) < MAX_BALL_SPEED) {
		ball.dx += ball.dx > 0 ? SPEED_INCREMENT : -SPEED_INCREMENT;
	}

	const prevX = ball.x;
	const prevY = ball.y;

	ball.x += ball.dx;
	ball.y += ball.dy;

	if (ball.y - ball.r <= 0) {
		ball.y = ball.r;
		ball.dy = Math.abs(ball.dy);
	} else if (ball.y + ball.r >= canvas.height) {
		ball.y = canvas.height - ball.r;
		ball.dy = -Math.abs(ball.dy);
	}

	const leftPaddleRight = paddle1.x + paddle1.w;
	if (ball.dx < 0 &&
		ball.x - ball.r <= leftPaddleRight &&
		prevX - ball.r > leftPaddleRight &&
		ball.y + ball.r > paddle1.y &&
		ball.y - ball.r < paddle1.y + paddle1.h) {

		ball.dx = Math.abs(ball.dx);

		const impactPosition = (ball.y - paddle1.y) / paddle1.h;
		ball.dy = IMPACT_ANGLE_FACTOR * (impactPosition - 0.5);

		ball.x = leftPaddleRight + ball.r;

		if (isAI) updateAITarget();
	}

	const rightPaddleLeft = paddle2.x;
	if (ball.dx > 0 &&
		ball.x + ball.r >= rightPaddleLeft &&
		prevX + ball.r < rightPaddleLeft &&
		ball.y + ball.r > paddle2.y &&
		ball.y - ball.r < paddle2.y + paddle2.h) {

		ball.dx = -Math.abs(ball.dx);

		const impactPosition = (ball.y - paddle2.y) / paddle2.h;
		ball.dy = IMPACT_ANGLE_FACTOR * (impactPosition - 0.5);

		ball.x = rightPaddleLeft - ball.r;
	}

	if (ball.x < 0) { score2++; checkWin(); resetBall('right'); }
	if (ball.x > 800) { score1++; checkWin(); resetBall('left'); }
}

function checkWin(): void {
	if (score1 >= 5 || score2 >= 5) {
		gameOn = false;
		const winner = score1 >= 5 ? player1 : player2;

		const result: MatchResult = {
			player1,
			player2,
			player1Score: score1,
			player2Score: score2,
			winner
		};

		if (onGameEndCallback) {
			onGameEndCallback(result);
		} else {
			showWinner(winner.name);
		}
	}
}

function drawBackground(): void {
	switch (backgroundType) {
		case 'space': {
			ctx.fillStyle = '#0a0a1a';
			ctx.fillRect(0, 0, 800, 600);
			ctx.fillStyle = '#fff';
			for (let i = 0; i < 50; i++) {
				const x = (i * 137) % 800;
				const y = (i * 71) % 600;
				const size = (i % 3) * 0.5 + 0.5;
				ctx.fillRect(x, y, size, size);
			}
			break;
		}
		case 'ocean': {
			const oceanGradient = ctx.createLinearGradient(0, 0, 0, 600);
			oceanGradient.addColorStop(0, '#1a3a4a');
			oceanGradient.addColorStop(1, '#0a1a2a');
			ctx.fillStyle = oceanGradient;
			ctx.fillRect(0, 0, 800, 600);
			ctx.strokeStyle = 'rgba(255, 255, 255, 0.1)';
			ctx.lineWidth = 1;
			for (let i = 0; i < 6; i++) {
				ctx.beginPath();
				for (let x = 0; x < 800; x += 10) {
					const y = i * 100 + Math.sin(x * 0.05) * 10;
					if (x === 0) ctx.moveTo(x, y);
					else ctx.lineTo(x, y);
				}
				ctx.stroke();
			}
			break;
		}
		case 'neon': {
			const neonGradient = ctx.createLinearGradient(0, 0, 800, 600);
			neonGradient.addColorStop(0, '#1a0033');
			neonGradient.addColorStop(0.5, '#0a0a1a');
			neonGradient.addColorStop(1, '#001a33');
			ctx.fillStyle = neonGradient;
			ctx.fillRect(0, 0, 800, 600);
			ctx.strokeStyle = 'rgba(0, 255, 255, 0.1)';
			ctx.lineWidth = 1;
			for (let x = 0; x < 800; x += 50) {
				ctx.beginPath();
				ctx.moveTo(x, 0);
				ctx.lineTo(x, 600);
				ctx.stroke();
			}
			for (let y = 0; y < 600; y += 50) {
				ctx.beginPath();
				ctx.moveTo(0, y);
				ctx.lineTo(800, y);
				ctx.stroke();
			}
			break;
		}
		default:
			ctx.fillStyle = '#000';
			ctx.fillRect(0, 0, 800, 600);
	}
}

function draw(): void {
	drawBackground();

	ctx.fillStyle = '#fff';
	ctx.fillRect(paddle1.x, paddle1.y, paddle1.w, paddle1.h);
	ctx.fillRect(paddle2.x, paddle2.y, paddle2.w, paddle2.h);

	ctx.beginPath();
	ctx.arc(ball.x, ball.y, 10, 0, Math.PI * 2);
	ctx.fill();

	// Scores
	ctx.font = '48px monospace';
	ctx.fillText(score1.toString(), 200, 60);
	ctx.fillText(score2.toString(), 580, 60);

	// Player names
	ctx.font = '16px monospace';
	ctx.fillStyle = '#888';
	const p1Name = player1?.name || 'Player 1';
	const p2Name = player2?.name || 'Player 2';
	ctx.fillText(p1Name, 200 - ctx.measureText(p1Name).width / 2, 85);
	ctx.fillText(p2Name, 580 - ctx.measureText(p2Name).width / 2, 85);
}

function countdown(cb: () => void): void {
	const el = document.getElementById('countdown')!;
	const txt = document.getElementById('countdownText')!;
	el.classList.remove('hidden');

	let n = 3;
	txt.textContent = n.toString();

	countdownTimer = setInterval(() => {
		n--;
		if (n > 0) txt.textContent = n.toString();
		else if (n === 0) txt.textContent = 'GO!';
		else {
			clearInterval(countdownTimer!);
			countdownTimer = null;
			el.classList.add('hidden');
			cb();
		}
	}, 1000);
}

export function showWinnerOverlay(winnerName: string, onContinue: () => void): void {
	const el = document.getElementById('countdown')!;
	const txt = document.getElementById('countdownText')!;
	el.classList.remove('hidden');
	txt.textContent = `🎉 ${winnerName} Wins!`;
	txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';

	// Hide exit button when game ends
	const exitContainer = document.getElementById('exitGameContainer');
	if (exitContainer) exitContainer.classList.add('hidden');

	setTimeout(() => {
		el.classList.add('hidden');
		txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';
		onContinue();
	}, 3000);
}

function resizePong(): void {
	if (!canvas) return;
	const maxW = Math.min(window.innerWidth - 32, 800);
	const scale = maxW / 800;
	canvas.style.width = `${Math.round(800 * scale)}px`;
	canvas.style.height = `${Math.round(600 * scale)}px`;
}

export function stopPongGame(): void {
	gameOn = false;
	window.removeEventListener('resize', resizePong);

	if (animationId) {
		cancelAnimationFrame(animationId);
	}

	if (countdownTimer !== null) {
		clearInterval(countdownTimer);
		countdownTimer = null;
	}
	if (initTimeoutId !== null) {
		clearTimeout(initTimeoutId);
		initTimeoutId = null;
	}

	Object.keys(keys).forEach(key => keys[key] = false);

	aiLastUpdate = 0;
	aiDecision = '';
	aiTargetY = 250;

	ball.x = 400;
	ball.y = 300;
	ball.dx = INITIAL_BALL_SPEED;
	ball.dy = INITIAL_BALL_SPEED;
	paddle1.y = paddle2.y = 250;
	paddle1.h = paddle2.h = 100;
	paddle1.dy = paddle2.dy = 0;
	paddleHeight = 100;
	backgroundType = 'default';
	score1 = score2 = 0;

	const exitContainer = document.getElementById('exitGameContainer');
	if (exitContainer) exitContainer.classList.add('hidden');
}

function showWinner(winner: string): void {
	const el = document.getElementById('countdown')!;
	const txt = document.getElementById('countdownText')!;
	el.classList.remove('hidden');
	txt.textContent = `🎉 ${winner} Wins!`;
	txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';

	const exitContainer = document.getElementById('exitGameContainer');
	if (exitContainer) exitContainer.classList.add('hidden');

	setTimeout(() => {
		el.classList.add('hidden');
		txt.className = 'text-2xl sm:text-3xl md:text-4xl lg:text-5xl font-bold text-yellow-300';
		navigate('games');
	}, 3000);
}

export function exitGame(): void {
	stopPongGame();

	navigate('games');
}

window.addEventListener('keydown', e => keys[e.key] = true);
window.addEventListener('keyup', e => keys[e.key] = false);

window.addEventListener('beforepagechange', () => {
	stopPongGame();
});

(window as any).exitGame = exitGame;
