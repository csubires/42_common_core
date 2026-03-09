import { navigate } from '../router.js';
import { getCurrentUser, createRegisteredPlayer, createGuestPlayer, createAIPlayer, startGameSession, endGameSession, loginPlayer } from '../gameService.js';
import { initPongGame, setOnGameEnd, showWinnerOverlay } from '../pong.js';
import { setupTicTacToe } from '../tictactoe.js';
import { ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError } from '../api.js';
// ===== PLAYER SETUP STATE =====
let verifiedPlayer2: any = null;

// ===== GAME OPTIONS STATE =====
let pendingGamePlayers: any = null;
let pendingTicTacToeMode: { isAI: boolean, difficulty?: number } | null = null;
let gameContext: 'pong' | 'tictactoe' = 'pong';
let gameOptions = {
  background: 'default',
  difficulty: 'medium'
};
let ticTacToeOptions = {
  theme: 'classic',
  boardSize: 3,
  specialMode: 'none' as 'none' | 'timed' | 'gravity'
};
// ===== GAME SELECTION PAGE =====
export function renderGames() {
	return `
    <h2 class="text-4xl font-bold text-center text-yellow-400 mb-8" data-i18n="game.select">Select Game</h2>
    <div class="grid grid-cols-1 sm:grid-cols-3 gap-4 sm:gap-6 max-w-4xl mx-auto">
      <div class="card text-center cursor-pointer hover:ring-2 hover:ring-yellow-400" onclick="window.gameUI.startPongPvP()">
        <div class="text-6xl mb-4">🏓</div>
        <h3 class="text-xl font-bold" data-i18n="game.pongPvP">Pong - PvP</h3>
        <p class="text-gray-400" data-i18n="game.playerVSplayer">Player vs Player</p>
      </div>
      <div class="card text-center cursor-pointer hover:ring-2 hover:ring-yellow-400" onclick="window.gameUI.showDifficultySelect()">
        <div class="text-6xl mb-4">🤖</div>
        <h3 class="text-xl font-bold" data-i18n="game.pongAI">Pong - AI</h3>
        <p class="text-gray-400"data-i18n="game.playerVScomputer">Player vs Computer</p>
      </div>
      <div class="card text-center cursor-pointer hover:ring-2 hover:ring-yellow-400" onclick="window.gameUI.startTicTacToe()">
        <div class="text-6xl mb-4">⭕</div>
        <h3 class="text-xl font-bold" data-i18n="game.ttt">Tic-Tac-Toe</h3>
        <p class="text-gray-400" data-i18n="game.twoplayers">2 Players</p>
      </div>
    </div>
  `;
}
// ===== MODAL HELPERS =====
function showModal(html: string) {
	const modal = document.getElementById('modal');
	if (!modal)
		return;
	modal.classList.remove('hidden');
	modal.innerHTML = html;
}
function hideModal() {
	const modal = document.getElementById('modal');
	if (!modal)
		return;
	modal.classList.add('hidden');
	verifiedPlayer2 = null;
}
function clearPlayer2Verification() {
	verifiedPlayer2 = null;
	getCurrentUser().then(currentUser => {
		if (currentUser) {
			showPlayer2Setup(currentUser);
		}
	});
}
// ===== PONG GAME FLOWS =====
async function startPongPvP() {
	gameContext = 'pong';
	const currentUser = await getCurrentUser();
	if (!currentUser) {
		// No user logged in - both players must be guests
		showGuestVsGuestSetup();
	}
	else {
		// User logged in - show player 2 setup
		showPlayer2Setup(currentUser);
	}
}
async function startPongAI(difficulty: number) {
	hideModal(); // Close difficulty modal
	const currentUser = await getCurrentUser();
	let player1;
	if (currentUser) {
		player1 = createRegisteredPlayer(currentUser);
	}
	else {
		// Guest player
		player1 = createGuestPlayer('Guest');
	}
	const player2 = createAIPlayer(difficulty);
	// Start session
	startGameSession({
		player1,
		player2,
		gameType: 'pong',
		isAI: true,
		difficulty,
		startTime: Date.now()
	});
	// Setup game end handler
	setupPongGameEndHandler();
	// Navigate and init game
	navigate('game');
	initPongGame({
		player1,
		player2,
		isAI: true,
		difficulty
	});
}
// ===== PLAYER SETUP MODALS =====
function showGuestVsGuestSetup() {
	showModal(`
    <div class="card text-center space-y-4 max-w-md mx-auto">
      <h2 class="text-2xl font-bold text-yellow-400" data-i18n="game.guestVSguest">Guest vs Guest</h2>
      <p class="text-sm text-gray-400" data-i18n="game.noPlayersLogged">No players logged in - both will play as guests</p>
      
      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="game.player1">Player 1 (W/S keys)</label>
        <input
          type="text"
          value="Guest"
          disabled
          class="w-full p-3 rounded bg-gray-600 cursor-not-allowed text-white"
        />
        <p class="text-xs text-gray-400 mt-1" data-i18n="game.playingAsGuest">Playing as guest</p>
      </div>
      
      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="game.player2">Player 2 (↑/↓ keys)</label>
        <input
          type="text"
          value="Guest"
          disabled
          class="w-full p-3 rounded bg-gray-600 cursor-not-allowed text-white"
        />
        <p class="text-xs text-gray-400 mt-1" data-i18n="game.playingAsGuest">Playing as guest</p>
      </div>
      
      <div class="flex gap-4 mt-6">
        <button onclick="window.gameUI.hideModal()" class="btn btn-gray flex-1" data-i18n="game.cancel">Cancel</button>
        <button onclick="window.gameUI.confirmGuestVsGuest()" class="btn btn-green flex-1" data-i18n="game.startGame">Start Game</button>
      </div>
    </div>
  `);
	applyTranslations();
}
function showPlayer2Setup(currentUser: any) {
	const player1Name = currentUser.display_name || currentUser.username;
	const player2DisplayName = verifiedPlayer2
		? (verifiedPlayer2.display_name || verifiedPlayer2.username)
		: 'Guest';
	const verifiedStatus = verifiedPlayer2
		? `<p class="text-xs text-green-400 mt-1" data-i18n="game.verifiedPlayer">✓ Verified player</p>`
		: `<p class="text-xs text-gray-400 mt-1" data-i18n="game.playingAsGuest">Playing as guest</p>`;
	const verifyButtonHtml = verifiedPlayer2
		? '<button onclick="window.gameUI.clearPlayer2Verification()" class="btn btn-yellow mt-2" type="button" data-i18n="game.changePlayer">Change Player 2</button>'
		: '<button onclick="window.gameUI.showPlayer2VerifyModal()" class="btn btn-blue mt-2" type="button" data-i18n="game.verifyPlayer2">Verify Player 2</button>';
	showModal(`
    <div class="card text-center space-y-4 max-w-md mx-auto">
      <h2 class="text-2xl font-bold text-yellow-400" data-i18n="game.player2setup">Player 2 Setup</h2>
      
      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="game.player1">Player 1 (W/S keys)</label>
        <input
          type="text"
          value="${player1Name}"
          disabled
          class="w-full p-3 rounded bg-gray-600 cursor-not-allowed text-white"
        />
        <p class="text-xs text-green-400 mt-1" data-i18n="game.logged">✓ Logged in as ${player1Name}</p>
      </div>
      
      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="game.player2">Player 2 (↑/↓ keys)</label>
        <input
          type="text"
          value="${player2DisplayName}"
          disabled
          class="w-full p-3 rounded bg-gray-600 cursor-not-allowed text-white"
        />
        ${verifiedStatus}
        ${verifyButtonHtml}
      </div>
      
      <div class="flex gap-4 mt-6">
        <button onclick="window.gameUI.hideModal()" class="btn btn-gray flex-1" data-i18n="game.cancel">Cancel</button>
        <button onclick="window.gameUI.confirmPlayer2Setup()" class="btn btn-green flex-1" data-i18n="game.startGame">Start Game</button>
      </div>
    </div>
  `);
	applyTranslations();
}
function showPlayer2VerifyModal() {
	showModal(`
    <div class="card text-center space-y-4 max-w-md mx-auto">
      <h2 class="text-2xl font-bold text-yellow-400" data-i18n="game.verifyPlayer2">Verify Player 2</h2>
      <p class="text-gray-400" data-i18n="game.player2mustLog">Player 2 must log in to verify their identity</p>
      
      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="admin.email">Email</label>
        <input
          type="email"
          id="player2Email"
          placeholder="email@example.com"
          class="w-full p-3 rounded bg-gray-700 text-white"
        />
      </div>
      
      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="admin.password">Password</label>
        <input
          type="password"
          id="player2Password"
          placeholder="Password"
          class="w-full p-3 rounded bg-gray-700 text-white"
        />
      </div>
      
      <div id="loginStatus" class="text-sm"></div>
      
      <div class="flex gap-4 mt-6">
        <button onclick="window.gameUI.backToPlayer2Setup()" class="btn btn-gray flex-1" data-i18n="game.back">Back</button>
        <button onclick="window.gameUI.loginPlayer2Direct()" class="btn btn-green flex-1" data-i18n="game.login">Login</button>
      </div>
    </div>
  `);
	focusInput('player2Email');
	applyTranslations();
}
async function loginPlayer2Direct() {
	const emailInput = document.getElementById('player2Email') as HTMLInputElement;
	const passwordInput = document.getElementById('player2Password') as HTMLInputElement;
	const statusDiv = document.getElementById('loginStatus');
	if (!emailInput || !passwordInput || !statusDiv)
		return;
	const email = emailInput.value.trim();
	const password = passwordInput.value;
	if (!email || !password) {
		statusDiv.innerHTML = '<span class="text-red-400" data-i18n="game.enterEmailAndPassword">Please enter email and password</span>';
		applyTranslations();
		return;
	}
	statusDiv.innerHTML = '<span class="text-yellow-400" data-i18n="game.logginIn">Logging in...</span>';
	applyTranslations();
	
	try {
		const user = await loginPlayer(email, password);
		
		if (user) {
			// Check if player 2 is the same as player 1
			const currentUser = await getCurrentUser();
			if (currentUser && user.id === currentUser.id) {
				statusDiv.innerHTML = '<span class="text-red-400" data-i18n="game.samePlayerError">✗ Player 2 cannot be the same as Player 1</span>';
				applyTranslations();
				return;
			}
			
			verifiedPlayer2 = user;
			statusDiv.innerHTML = '<span class="text-green-400" data-i18n="game.player2Verified">✓ Player 2 verified!</span>';
			applyTranslations();
			setTimeout(() => {
				backToPlayer2Setup();
			}, 1000);
		} else {
			statusDiv.innerHTML = '<span class="text-red-400" data-i18n="game.invalidCredentials">✗ Invalid credentials</span>';
			applyTranslations();
		}
	} catch (error: any) {
		// Handle different error types using instanceof
		let errorMessage = '<span class="text-red-400" data-i18n="game.loginFailed">✗ Login failed. Please try again</span>';
		
		if (error instanceof AuthError) {
			errorMessage = '<span class="text-red-400" data-i18n="game.invalidCredentials">✗ Invalid credentials</span>';
		} else if (error instanceof ServerError) {
			console.error('Server error during player 2 login:', error);
		}
		
		statusDiv.innerHTML = errorMessage;
		applyTranslations();
	}
}
async function backToPlayer2Setup() {
	const currentUser = await getCurrentUser();
	if (currentUser) {
		showPlayer2Setup(currentUser);
	}
}
// ===== GAME START CONFIRMATION =====
async function confirmGuestVsGuest() {
	const player1 = createGuestPlayer('Guest');
	const player2 = createGuestPlayer('Guest');
	if (gameContext === 'tictactoe') {
		pendingGamePlayers = { player1, player2 };
		hideModal();
		showTicTacToeOptions(false);
	} else {
		startPongWithPlayers(player1, player2);
	}
}
async function confirmPlayer2Setup() {
	const currentUser = await getCurrentUser();
	if (!currentUser)
		return;
	const player1 = createRegisteredPlayer(currentUser);
	let player2;
	if (verifiedPlayer2) {
		// Additional safety check: prevent same player
		if (verifiedPlayer2.id === currentUser.id) {
			const errorMsg = window.languageManager?.t('game.samePlayerError') || 
				'Player 2 cannot be the same as Player 1';
			alert(errorMsg);
			return;
		}
		// Verified registered player
		player2 = createRegisteredPlayer(verifiedPlayer2);
	}
	else {
		// Not verified - always use Guest
		player2 = createGuestPlayer('Guest');
	}
	if (gameContext === 'tictactoe') {
		pendingGamePlayers = { player1, player2 };
		hideModal();
		showTicTacToeOptions(false);
	} else {
		startPongWithPlayers(player1, player2);
	}
}
function startPongWithPlayers(player1: any, player2: any) {
	// Store players and show game options modal
	pendingGamePlayers = { player1, player2 };
	showGameOptionsModal();
}

function showGameOptionsModal() {
	showModal(`
    <div class="card text-center space-y-4 max-w-sm mx-auto">
      <h2 class="text-xl font-bold text-yellow-400" data-i18n="game.options">Game Options</h2>
      
      <div class="text-left">
        <label class="block text-xs text-gray-400 mb-1 font-bold" data-i18n="game.background">Background</label>
        <div class="grid grid-cols-4 gap-2">
          <label class="flex flex-col items-center cursor-pointer group">
            <input type="radio" name="background" value="default" checked data-background="default" class="hidden">
            <div class="w-full h-16 rounded border-2 border-gray-600 group-has-[:checked]:border-yellow-400 group-has-[:checked]:border-4 bg-black flex items-center justify-center text-white text-xs font-bold mb-1 transition-all duration-200 pointer-events-none"></div>
            <span class="text-white text-xs" data-i18n="game.background1">Default</span>
          </label>
          
          <label class="flex flex-col items-center cursor-pointer group">
            <input type="radio" name="background" value="space" data-background="space" class="hidden">
            <div class="w-full h-16 rounded border-2 border-gray-600 group-has-[:checked]:border-yellow-400 group-has-[:checked]:border-4 bg-gradient-to-b from-gray-900 to-black flex items-center justify-center relative overflow-hidden mb-1 transition-all duration-200 pointer-events-none">
              <div class="absolute w-1 h-1 bg-white rounded-full pointer-events-none" style="top: 20%; left: 20%;"></div>
              <div class="absolute w-0.5 h-0.5 bg-white rounded-full pointer-events-none" style="top: 40%; right: 30%;"></div>
            </div>
            <span class="text-white text-xs" data-i18n="game.background2">Space</span>
          </label>
          
          <label class="flex flex-col items-center cursor-pointer group">
            <input type="radio" name="background" value="ocean" data-background="ocean" class="hidden">
            <div class="w-full h-16 rounded border-2 border-gray-600 group-has-[:checked]:border-yellow-400 group-has-[:checked]:border-4 bg-gradient-to-b from-blue-900 to-blue-950 flex items-center justify-center relative overflow-hidden mb-1 transition-all duration-200 pointer-events-none">
              <div class="absolute inset-0 opacity-30 pointer-events-none" style="background: repeating-linear-gradient(90deg, transparent, transparent 10px, rgba(255,255,255,0.1) 10px, rgba(255,255,255,0.1) 20px);"></div>
            </div>
            <span class="text-white text-xs" data-i18n="game.background3">Ocean</span>
          </label>
          
          <label class="flex flex-col items-center cursor-pointer group">
            <input type="radio" name="background" value="neon" data-background="neon" class="hidden">
            <div class="w-full h-16 rounded border-2 border-gray-600 group-has-[:checked]:border-yellow-400 group-has-[:checked]:border-4 bg-gradient-to-br from-purple-900 via-gray-900 to-cyan-900 flex items-center justify-center relative overflow-hidden mb-1 transition-all duration-200 pointer-events-none">
              <div class="absolute inset-0 opacity-50 pointer-events-none" style="background: repeating-linear-gradient(45deg, transparent, transparent 5px, rgba(0,255,255,0.1) 5px, rgba(0,255,255,0.1) 10px);"></div>
            </div>
            <span class="text-white text-xs" data-i18n="game.background4">Neon</span>
          </label>
        </div>
      </div>

      <div class="text-left">
        <label class="block text-xs text-gray-400 mb-1 font-bold" data-i18n="game.dificulty">Difficulty</label>
        <div class="grid grid-cols-3 gap-2" id="difficultyOptions">
          <label class="flex flex-col items-center cursor-pointer group p-3 rounded-lg border-2 border-gray-600 transition-all duration-200 bg-gradient-to-b from-green-900 to-green-700 difficulty-label">
            <input type="radio" name="difficulty" value="easy" data-difficulty="easy" class="hidden">
            <div class="text-2xl mb-1">👶</div>
            <span class="text-green-200 font-bold text-sm">Easy</span>
            <span class="text-xs text-green-100" data-i18n="game.dificulty1">Relaxed</span>
          </label>
          <label class="flex flex-col items-center cursor-pointer group p-3 rounded-lg border-2 border-gray-600 transition-all duration-200 bg-gradient-to-b from-yellow-900 to-yellow-700 difficulty-label">
            <input type="radio" name="difficulty" value="medium" checked data-difficulty="medium" class="hidden">
            <div class="text-2xl mb-1">😎</div>
            <span class="text-yellow-200 font-bold text-sm">Medium</span>
            <span class="text-xs text-yellow-100" data-i18n="game.dificulty2">Balanced</span>
          </label>
          <label class="flex flex-col items-center cursor-pointer group p-3 rounded-lg border-2 border-gray-600 transition-all duration-200 bg-gradient-to-b from-red-900 to-red-700 difficulty-label">
            <input type="radio" name="difficulty" value="hard" data-difficulty="hard" class="hidden">
            <div class="text-2xl mb-1">😈</div>
            <span class="text-red-200 font-bold text-sm">Hard</span>
            <span class="text-xs text-red-100" data-i18n="game.dificulty3">Challenging</span>
          </label>
        </div>
      </div>

      <div class="flex gap-3 mt-4">
        <button onclick="window.gameUI.cancelGameOptions()" class="btn btn-gray flex-1" data-i18n="game.cancel">Cancel</button>
        <button onclick="window.gameUI.confirmGameOptions()" class="btn btn-green flex-1" data-i18n="game.accept">Accept</button>
      </div>
    </div>
  `);

	// Apply translations immediately
	applyTranslations();

	// Attach event listeners after modal is created
	setTimeout(() => {
		const backgroundLabels = document.querySelectorAll('input[name="background"]');
		const difficultyInputs = document.querySelectorAll('input[name="difficulty"]');
		const difficultyLabels = document.querySelectorAll('.difficulty-label');

		// Visual feedback for selected background
		function updateBackgroundSelection() {
			backgroundLabels.forEach((input) => {
				const label = input.closest('label');
				const preview = label?.querySelector('div');
				const radio = input as HTMLInputElement;
				if (radio.checked && preview) {
					preview.classList.add('ring-4', 'ring-yellow-400', 'border-yellow-400');
				} else if (preview) {
					preview.classList.remove('ring-4', 'ring-yellow-400', 'border-yellow-400');
				}
			});
		}

		// Visual feedback for selected difficulty
		function updateDifficultySelection() {
			difficultyLabels.forEach((label) => {
				const input = label.querySelector('input[name="difficulty"]') as HTMLInputElement;
				if (input && input.checked) {
					label.classList.add('ring-4', 'ring-yellow-400', 'border-yellow-400');
				} else {
					label.classList.remove('ring-4', 'ring-yellow-400', 'border-yellow-400');
				}
			});
		}

		// Add click listeners to background labels
		backgroundLabels.forEach((input) => {
			const label = input.closest('label');
			if (label) {
				label.addEventListener('click', () => {
					const radio = input as HTMLInputElement;
					backgroundLabels.forEach(r => (r as HTMLInputElement).checked = false);
					radio.checked = true;
					gameOptions.background = radio.value;
					updateBackgroundSelection();
					console.log('Background changed to:', radio.value);
				});
			}
		});

		// Add click listeners to difficulty labels
		difficultyLabels.forEach((label) => {
			label.addEventListener('click', () => {
				const input = label.querySelector('input[name="difficulty"]') as HTMLInputElement;
				if (input) {
					input.checked = true;
					gameOptions.difficulty = input.value;
					updateDifficultySelection();
					console.log('Difficulty changed to:', input.value);
				}
			});
		});

		difficultyInputs.forEach(input => {
			input.addEventListener('change', (e: any) => {
				gameOptions.difficulty = e.target.value;
				updateDifficultySelection();
				console.log('Difficulty changed to:', e.target.value);
			});
		});

		// Initial highlights
		updateBackgroundSelection();
		updateDifficultySelection();
	}, 0);
}

function updateGameOption(option: string, value: string) {
	gameOptions = {
		...gameOptions,
		[option]: value
	};
}

function confirmGameOptions() {
	if (!pendingGamePlayers) return;

	const { player1, player2 } = pendingGamePlayers;

	// Start session
	startGameSession({
		player1,
		player2,
		gameType: 'pong',
		isAI: false,
		startTime: Date.now()
	});

	// Setup game end handler
	setupPongGameEndHandler();

	// Hide modal and start game
	hideModal();
	initPongGame({
		player1,
		player2,
		isAI: false,
		gameOptions: gameOptions
	});
}

function cancelGameOptions() {
	pendingGamePlayers = null;
	gameOptions = {
		background: 'default',
		difficulty: 'medium'
	};
	hideModal();
	navigate('games');
}
// ===== GAME END HANDLING =====
function setupPongGameEndHandler() {
	setOnGameEnd(async (result) => {
		// Show winner overlay
		showWinnerOverlay(result.winner.name, async () => {
			// Save match after overlay
			const saveResult = await endGameSession(result.player1Score, result.player2Score);
			if (saveResult.success && !saveResult.skipped) {
				console.log('Match saved with ID:', saveResult.matchId);
			}
			else if (saveResult.skipped) {
				console.log('Match not saved: guest vs guest');
			}
			else {
				console.warn('Failed to save match');
			}
			// Navigate back to games
			navigate('games');
		});
	});
}
// ===== DIFFICULTY SELECTION =====
function showDifficultySelect() {
	showModal(`
    <div class="card text-center space-y-4">
      <h2 class="text-2xl font-bold text-yellow-400" data-i18n="game.selectDifficulty">Select Difficulty</h2>
      <button onclick="window.gameUI.startPongAI(2)" class="btn btn-green w-full" data-i18n="game.easy">Easy</button>
      <button onclick="window.gameUI.startPongAI(3)" class="btn btn-yellow w-full" data-i18n="game.medium">Medium</button>
      <button onclick="window.gameUI.startPongAI(4)" class="btn btn-red w-full" data-i18n="game.hard">Hard</button>
      <button onclick="window.gameUI.hideModal()" class="btn btn-gray w-full" data-i18n="game.cancel">Cancel</button>
    </div>
  `);
  applyTranslations();
}
// ===== TIC-TAC-TOE =====
function startTicTacToe() {
	showModal(`
		<div class="card text-center space-y-4">
			<h2 class="text-2xl font-bold text-yellow-400" data-i18n="game.ttt">Tic-Tac-Toe</h2>
			<p class="text-gray-400" data-i18n="game.gameMode">Choose game mode</p>
			
			<div class="space-y-2">
				<button onclick="window.gameUI.startTicTacToePvP()" class="btn btn-green w-full" data-i18n="game.playerVSplayer">👥 Player vs Player</button>
				<button onclick="window.gameUI.showTicTacToeOptions(true)" class="btn btn-yellow w-full" data-i18n="game.playerVSAI">🤖 Player vs AI</button>
			</div>
			
			<button onclick="window.gameUI.hideModal()" class="btn btn-gray w-full" data-i18n="game.cancel">Cancel</button>
		</div>
	`);
	applyTranslations();
}

async function startTicTacToePvP() {
	gameContext = 'tictactoe';
	const currentUser = await getCurrentUser();
	if (!currentUser) {
		// No user logged in - both players must be guests
		showGuestVsGuestSetup();
	}
	else {
		// User logged in - show player 2 setup
		showPlayer2Setup(currentUser);
	}
}

function showTicTacToeOptions(isAI: boolean) {
	// Reset options so nothing is pre-selected
	ticTacToeOptions = { theme: '', boardSize: 3, specialMode: '' as any };

	const difficultySection = isAI ? `
		<div class="text-left">
			<label class="block text-xs text-gray-400 mb-1 font-bold" data-i18n="game.AIdifficulty">AI Difficulty</label>
			<div class="grid grid-cols-3 gap-2" id="tictactoe-difficulty">
				<label class="flex flex-col items-center cursor-pointer group p-3 rounded-lg border-2 border-gray-600 transition-all duration-200 bg-gradient-to-b from-green-900 to-green-700 ttt-difficulty-label">
					<input type="radio" name="ttt-difficulty" value="2" data-difficulty="2" class="hidden">
					<div class="text-2xl mb-1">😊</div>
					<span class="text-green-200 font-bold text-sm">Easy</span>
					<span class="text-xs text-green-100" data-i18n="game.casual">Casual</span>
				</label>
				<label class="flex flex-col items-center cursor-pointer group p-3 rounded-lg border-2 border-gray-600 transition-all duration-200 bg-gradient-to-b from-yellow-900 to-yellow-700 ttt-difficulty-label">
					<input type="radio" name="ttt-difficulty" value="3" data-difficulty="3" class="hidden">
					<div class="text-2xl mb-1">😐</div>
					<span class="text-yellow-200 font-bold text-sm">Medium</span>
					<span class="text-xs text-yellow-100" data-i18n="game.normal">Normal</span>
				</label>
				<label class="flex flex-col items-center cursor-pointer group p-3 rounded-lg border-2 border-gray-600 transition-all duration-200 bg-gradient-to-b from-red-900 to-red-700 ttt-difficulty-label">
					<input type="radio" name="ttt-difficulty" value="4" data-difficulty="4" class="hidden">
					<div class="text-2xl mb-1">😈</div>
					<span class="text-red-200 font-bold text-sm">Hard</span>
					<span class="text-xs text-red-100" data-i18n="game.expert">Expert</span>
				</label>
			</div>
		</div>
	` : '';
	
	showModal(`
		<div class="card text-center space-y-4 max-w-sm mx-auto">
			<h2 class="text-xl font-bold text-yellow-400" data-i18n="game.tttOptions">Tic-Tac-Toe Options</h2>
			
			${difficultySection}
			
			<div class="text-left">
				<label class="block text-xs text-gray-400 mb-1 font-bold" data-i18n="game.theme">Theme</label>
				<div class="grid grid-cols-3 gap-2" id="tictactoe-themes">
					<label class="flex flex-col items-center cursor-pointer group ttt-theme-label">
						<input type="radio" name="ttt-theme" value="classic" data-theme="classic" class="hidden">
						<div class="w-full h-20 rounded border-2 border-gray-600 transition-all duration-200 bg-black flex items-center justify-center relative overflow-hidden mb-1">
							<svg viewBox="0 0 100 100" class="w-10 h-10">
								<line x1="33" y1="0" x2="33" y2="100" stroke="#fff" stroke-width="3"/>
								<line x1="67" y1="0" x2="67" y2="100" stroke="#fff" stroke-width="3"/>
								<line x1="0" y1="33" x2="100" y2="33" stroke="#fff" stroke-width="3"/>
								<line x1="0" y1="67" x2="100" y2="67" stroke="#fff" stroke-width="3"/>
								<text x="16" y="22" fill="#3b82f6" font-size="18" font-weight="bold">X</text>
								<text x="83" y="88" fill="#ef4444" font-size="18" font-weight="bold">O</text>
							</svg>
						</div>
						<span class="text-white text-xs" data-i18n="game.classic">Classic</span>
					</label>
					
					<label class="flex flex-col items-center cursor-pointer group ttt-theme-label">
						<input type="radio" name="ttt-theme" value="neon" data-theme="neon" class="hidden">
						<div class="w-full h-20 rounded border-2 border-gray-600 transition-all duration-200 bg-gradient-to-br from-purple-950 via-gray-900 to-cyan-950 flex items-center justify-center relative overflow-hidden mb-1">
							<svg viewBox="0 0 100 100" class="w-10 h-10">
								<line x1="33" y1="0" x2="33" y2="100" stroke="#00ff00" stroke-width="3"/>
								<line x1="67" y1="0" x2="67" y2="100" stroke="#00ff00" stroke-width="3"/>
								<line x1="0" y1="33" x2="100" y2="33" stroke="#00ff00" stroke-width="3"/>
								<line x1="0" y1="67" x2="100" y2="67" stroke="#00ff00" stroke-width="3"/>
								<text x="16" y="22" fill="#ff00ff" font-size="18" font-weight="bold">X</text>
								<text x="83" y="88" fill="#00ffff" font-size="18" font-weight="bold">O</text>
							</svg>
						</div>
						<span class="text-white text-xs" data-i18n="game.neon">Neon</span>
					</label>
					
					<label class="flex flex-col items-center cursor-pointer group ttt-theme-label">
						<input type="radio" name="ttt-theme" value="minimal" data-theme="minimal" class="hidden">
						<div class="w-full h-20 rounded border-2 border-gray-600 transition-all duration-200 bg-gray-100 flex items-center justify-center relative overflow-hidden mb-1">
							<svg viewBox="0 0 100 100" class="w-10 h-10">
								<line x1="33" y1="0" x2="33" y2="100" stroke="#333" stroke-width="2"/>
								<line x1="67" y1="0" x2="67" y2="100" stroke="#333" stroke-width="2"/>
								<line x1="0" y1="33" x2="100" y2="33" stroke="#333" stroke-width="2"/>
								<line x1="0" y1="67" x2="100" y2="67" stroke="#333" stroke-width="2"/>
								<text x="16" y="22" fill="#666" font-size="18" font-weight="bold">X</text>
								<text x="83" y="88" fill="#999" font-size="18" font-weight="bold">O</text>
							</svg>
						</div>
						<span class="text-white text-xs" data-i18n="game.minimal">Minimal</span>
					</label>
				</div>
			</div>
			
			<div class="text-left">
				<label class="block text-xs text-gray-400 mb-1 font-bold" data-i18n="game.mode">Mode</label>
				<div class="grid grid-cols-3 gap-2" id="tictactoe-modes">
					<label class="flex flex-col items-center cursor-pointer group ttt-mode-label">
						<input type="radio" name="ttt-mode" value="none" data-mode="none" class="hidden">
					<div class="w-full h-14 rounded border-2 border-gray-600 transition-all duration-200 bg-gray-700 flex items-center justify-center mb-1">
						<span class="text-2xl">🎮</span>
						</div>
						<span class="text-white text-xs" data-i18n="game.normal">Normal</span>
					</label>
					<label class="flex flex-col items-center cursor-pointer group ttt-mode-label">
						<input type="radio" name="ttt-mode" value="timed" data-mode="timed" class="hidden">
					<div class="w-full h-14 rounded border-2 border-gray-600 transition-all duration-200 bg-orange-900 flex items-center justify-center mb-1">
						<span class="text-2xl">⏱</span>
						</div>
						<span class="text-white text-xs" data-i18n="game.timed">Timed</span>
					</label>
				</div>
			</div>
			
			<div class="flex gap-3 mt-4">
				<button onclick="window.gameUI.cancelTicTacToeOptions()" class="btn btn-gray flex-1" data-i18n="game.cancel">Cancel</button>
				<button id="ttt-start-btn" onclick="window.gameUI.confirmTicTacToeOptions(${isAI})" class="btn btn-green flex-1 opacity-50 cursor-not-allowed" disabled data-i18n="game.startGame">Start Game</button>
			</div>
		</div>
	`);
	
	applyTranslations();
	setTimeout(() => setupTicTacToeOptionsListeners(isAI), 0);
}

function setupTicTacToeOptionsListeners(isAI: boolean) {
	const themeLabels = document.querySelectorAll('.ttt-theme-label');
	const themeInputs = document.querySelectorAll('input[name="ttt-theme"]');

	function updateStartButton() {
		const btn = document.getElementById('ttt-start-btn') as HTMLButtonElement;
		if (!btn) return;
		const hasTheme = !!ticTacToeOptions.theme;
		const hasMode = !!ticTacToeOptions.specialMode;
		const hasDifficulty = !isAI || !!document.querySelector('input[name="ttt-difficulty"]:checked');
		const allSelected = hasTheme && hasMode && hasDifficulty;
		btn.disabled = !allSelected;
		if (allSelected) {
			btn.classList.remove('opacity-50', 'cursor-not-allowed');
		} else {
			btn.classList.add('opacity-50', 'cursor-not-allowed');
		}
	}
	
	function updateThemeSelection() {
		themeLabels.forEach((label) => {
			const input = label.querySelector('input[name="ttt-theme"]') as HTMLInputElement;
			const preview = label.querySelector('div');
			if (input && input.checked && preview) {
				preview.classList.add('ring-4', 'ring-yellow-400', 'border-yellow-400');
			} else if (preview) {
				preview.classList.remove('ring-4', 'ring-yellow-400', 'border-yellow-400');
			}
		});
	}
	
	themeLabels.forEach((label) => {
		label.addEventListener('click', () => {
			const input = label.querySelector('input[name="ttt-theme"]') as HTMLInputElement;
			if (input) {
				input.checked = true;
				ticTacToeOptions.theme = input.value as 'classic' | 'neon' | 'minimal';
				updateThemeSelection();
				updateStartButton();
			}
		});
	});
	
	themeInputs.forEach(input => {
		input.addEventListener('change', (e: any) => {
			ticTacToeOptions.theme = e.target.value;
			updateThemeSelection();
			updateStartButton();
		});
	});

	const modeLabels = document.querySelectorAll('.ttt-mode-label');
	const modeInputs = document.querySelectorAll('input[name="ttt-mode"]');

	function updateModeSelection() {
		modeLabels.forEach((label) => {
			const input = label.querySelector('input[name="ttt-mode"]') as HTMLInputElement;
			const preview = label.querySelector('div');
			if (input && input.checked && preview) {
				preview.classList.add('ring-4', 'ring-yellow-400', 'border-yellow-400');
			} else if (preview) {
				preview.classList.remove('ring-4', 'ring-yellow-400', 'border-yellow-400');
			}
		});
	}

	modeLabels.forEach((label) => {
		label.addEventListener('click', () => {
			const input = label.querySelector('input[name="ttt-mode"]') as HTMLInputElement;
			if (input) {
				input.checked = true;
				ticTacToeOptions.specialMode = input.value as 'none' | 'timed' | 'gravity';
				updateModeSelection();
				updateStartButton();
			}
		});
	});

	modeInputs.forEach(input => {
		input.addEventListener('change', (e: any) => {
			ticTacToeOptions.specialMode = e.target.value;
			updateModeSelection();
			updateStartButton();
		});
	});

	updateModeSelection();

	if (isAI) {
		const difficultyLabels = document.querySelectorAll('.ttt-difficulty-label');
		const difficultyInputs = document.querySelectorAll('input[name="ttt-difficulty"]');
		
		function updateDifficultySelection() {
			difficultyLabels.forEach((label) => {
				const input = label.querySelector('input[name="ttt-difficulty"]') as HTMLInputElement;
				if (input && input.checked) {
					label.classList.add('ring-4', 'ring-yellow-400', 'border-yellow-400');
				} else {
					label.classList.remove('ring-4', 'ring-yellow-400', 'border-yellow-400');
				}
			});
		}
		
		difficultyLabels.forEach((label) => {
			label.addEventListener('click', () => {
				const input = label.querySelector('input[name="ttt-difficulty"]') as HTMLInputElement;
				if (input) {
					input.checked = true;
					updateDifficultySelection();
					updateStartButton();
				}
			});
		});
		
		difficultyInputs.forEach(input => {
			input.addEventListener('change', () => {
				updateDifficultySelection();
				updateStartButton();
			});
		});
		
		updateDifficultySelection();
	}
	
	updateThemeSelection();
	updateStartButton();
}

function confirmTicTacToeOptions(isAI: boolean) {
	// Save theme and mode to localStorage
	localStorage.setItem('tictactoeCustomization', JSON.stringify({
		theme: ticTacToeOptions.theme,
		boardSize: ticTacToeOptions.boardSize,
		specialMode: ticTacToeOptions.specialMode
	}));
	
	hideModal();
	
	if (isAI) {
		const difficultyInput = document.querySelector('input[name="ttt-difficulty"]:checked') as HTMLInputElement;
		const difficulty = difficultyInput ? parseInt(difficultyInput.value) : 3;
		setupTicTacToe(true, difficulty);
	} else {
		const players = pendingGamePlayers;
		pendingGamePlayers = null;
		setupTicTacToe(false, 3, players?.player1, players?.player2);
	}
}

function cancelTicTacToeOptions() {
	hideModal();
	startTicTacToe();
}
// ===== UTILITY FUNCTIONS =====
function applyTranslations() {
	if (window.languageManager?.isReady()) {
		window.languageManager.applyTranslations();
	}
}
function focusInput(id: string) {
	setTimeout(() => {
		const input = document.getElementById(id) as HTMLInputElement;
		input?.focus();
	}, 100);
}
function focusFirstInput() {
	setTimeout(() => {
		const input = document.querySelector('input:not([disabled])') as HTMLInputElement;
		input?.focus();
	}, 100);
}
// ===== GLOBAL EXPORTS =====
(window as any).gameUI = {
	// Main flows
	startPongPvP,
	startPongAI,
	showDifficultySelect,
	startTicTacToe,
	showTicTacToeOptions,
	// Modal controls
	hideModal,
	// Player setup
	showPlayer2VerifyModal,
	loginPlayer2Direct,
	clearPlayer2Verification,
	confirmGuestVsGuest,
	confirmPlayer2Setup,
	backToPlayer2Setup,
	// Game options
	updateGameOption,
	confirmGameOptions,
	cancelGameOptions,
	// Tic Tac Toe options
	startTicTacToePvP,
	confirmTicTacToeOptions,
	cancelTicTacToeOptions
};