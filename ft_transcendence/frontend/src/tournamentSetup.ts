import { navigate } from './router.js';

import {
	getCurrentUser,
	verifyPlayerByName,
	createRegisteredPlayer,
	createGuestPlayer,
	loginPlayer,
	type Player,
	type UserProfile
} from './gameService.js';

import {
	createTournament,
	saveTournament,
	createTournamentInDB,
	startTournamentInDB
} from "./tournamentEngine.js";

const USERS_TOUR_NUM = 8;

// ===== PLAYER TYPE MANAGEMENT =====

interface PlayerSlot {
	type: 'registered' | 'guest';
	value: string;
}

// Store player slot configurations
const playerSlots: Map<number, PlayerSlot> = new Map();

// Store verified registered players (slot index -> UserProfile)
// Populated when the user clicks "Verify" on a registered slot,
// or pre-populated from the current session for slot 0.
const verifiedPlayers: Map<number, UserProfile> = new Map();

// Toggle player type between registered and guest
function togglePlayerType(index: number, type: 'registered' | 'guest'): void {
	const guestInput = document.getElementById(`guest-input-${index}`);
	const registeredInput = document.getElementById(`registered-input-${index}`);
	const guestRadio = document.getElementById(`radio-guest-${index}`) as HTMLInputElement;
	const registeredRadio = document.getElementById(`radio-registered-${index}`) as HTMLInputElement;

	if (type === 'guest') {
		guestInput?.classList.remove('hidden');
		registeredInput?.classList.add('hidden');
		if (guestRadio) guestRadio.checked = true;
	} else {
		guestInput?.classList.add('hidden');
		registeredInput?.classList.remove('hidden');
		if (registeredRadio) registeredRadio.checked = true;
	}

	// Clear any previous verification when the type changes
	verifiedPlayers.delete(index);
	updateVerificationStatus(index, null);

	playerSlots.set(index, { type, value: '' });
}

// ===== VERIFICATION HELPERS =====

/**
 * Updates the verification badge displayed below a registered input.
 * status: null = clear, 'pending' = loading, 'ok' = verified, 'error' = not found
 */
function updateVerificationStatus(
	index: number,
	status: null | 'pending' | 'ok' | 'error',
	message?: string
): void {
	const statusEl = document.getElementById(`verify-status-${index}`);
	const verifyBtn = document.getElementById(`verify-btn-${index}`) as HTMLButtonElement | null;
	if (!statusEl) return;

	if (status === null) {
		statusEl.innerHTML = '';
		if (verifyBtn) { verifyBtn.textContent = 'Verify'; verifyBtn.disabled = false; }
	} else if (status === 'pending') {
		statusEl.innerHTML = '<span class="text-yellow-400 text-xs">⏳ Verifying...</span>';
		if (verifyBtn) verifyBtn.disabled = true;
	} else if (status === 'ok') {
		statusEl.innerHTML = `<span class="text-green-400 text-xs">✓ ${message || 'Verified'}</span>`;
		if (verifyBtn) { verifyBtn.textContent = '✓ Change'; verifyBtn.disabled = false; }
	} else if (status === 'error') {
		statusEl.innerHTML = `<span class="text-red-400 text-xs">✗ ${message || 'User not found'}</span>`;
		if (verifyBtn) { verifyBtn.textContent = 'Verify'; verifyBtn.disabled = false; }
	}
}

/**
 * Verifies a registered player slot by username.
 * Called from the "Verify" button in each registered slot.
 * Uses verifyPlayerByName from gameService — the same API endpoint
 * that games.ts uses to look up players.
 */
async function verifyTournamentPlayer(index: number): Promise<void> {
	const input = document.getElementById(`player-registered-${index}`) as HTMLInputElement;
	const username = input?.value.trim();

	if (!username) {
		updateVerificationStatus(index, 'error', 'Enter a username first');
		return;
	}

	// Remove any previous verification for this slot
	verifiedPlayers.delete(index);
	updateVerificationStatus(index, 'pending');

	try {
		const user = await verifyPlayerByName(username);

		if (user) {
			// Prevent the same user appearing twice in the tournament
			for (const [otherIndex, otherUser] of verifiedPlayers.entries()) {
				if (otherIndex !== index && otherUser.id === user.id) {
					updateVerificationStatus(index, 'error', 'Player already in tournament');
					return;
				}
			}

			verifiedPlayers.set(index, user);
			playerSlots.set(index, { type: 'registered', value: user.username });

			// Show the canonical display name in the input
			input.value = user.display_name || user.username;
			updateVerificationStatus(index, 'ok', `${user.display_name || user.username} verified`);
		} else {
			updateVerificationStatus(index, 'error', 'User not found');
		}
	} catch (_error) {
		updateVerificationStatus(index, 'error', 'Verification failed');
	}
}

/**
 * Opens a login modal for a registered slot.
 * Equivalent to showPlayer2VerifyModal in games.ts, adapted for
 * multi-player tournament setup.
 */
function showPlayerVerifyModal(index: number): void {
	const wrapper = document.getElementById('modal');
	if (!wrapper) return;

	// Sync current DOM values into HTML attributes before saving,
	// so that typed names and radio selections survive the round-trip.
	wrapper.querySelectorAll<HTMLInputElement>('input[type="text"], input[type="email"], input[type="password"]')
		.forEach(el => el.setAttribute('value', el.value));
	wrapper.querySelectorAll<HTMLInputElement>('input[type="radio"]')
		.forEach(el => el.checked ? el.setAttribute('checked', '') : el.removeAttribute('checked'));

	// Save setup HTML so we can restore it on "Back"
	(window as any)._tournamentSetupHTML = wrapper.innerHTML;

	const t = (key: string, fallback: string) =>
		(window as any).languageManager?.t(key) ?? fallback;

	wrapper.innerHTML = `
    <div class="card text-center space-y-4 max-w-md mx-auto">
      <h2 class="text-xl font-bold text-yellow-400">
        <span data-i18n="tournament.verifyPlayer">${t('tournament.verifyPlayer', 'Verify Player')}</span> ${index + 1}
      </h2>
      <p class="text-gray-400 text-sm" data-i18n="tournament.verifyPlayerHint">
        ${t('tournament.verifyPlayerHint', 'The player must log in to confirm their identity')}
      </p>

      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="admin.email">Email</label>
        <input
          type="email"
          id="tour-player-email-${index}"
          placeholder="email@example.com"
          class="w-full p-2 rounded bg-gray-700 text-white"
        />
      </div>

      <div class="text-left">
        <label class="block text-sm text-gray-400 mb-1" data-i18n="admin.password">Password</label>
        <input
          type="password"
          id="tour-player-password-${index}"
          placeholder="Password"
          class="w-full p-2 rounded bg-gray-700 text-white"
        />
      </div>

      <div id="tour-login-status-${index}" class="text-sm min-h-5"></div>

      <div class="flex gap-4 mt-4">
        <button
          onclick="window.tournamentUI.closePlayerVerifyModal(${index})"
          class="btn btn-gray flex-1"
          data-i18n="game.back"
        >${t('game.back', 'Back')}</button>
        <button
          onclick="window.tournamentUI.loginTournamentPlayer(${index})"
          class="btn btn-green flex-1"
          data-i18n="game.login"
        >${t('game.login', 'Login')}</button>
      </div>
    </div>
  `;

	setTimeout(() => {
		(document.getElementById(`tour-player-email-${index}`) as HTMLInputElement)?.focus();
	}, 50);
}

/** Restores the setup modal after closing the login sub-modal. */
function closePlayerVerifyModal(_index: number): void {
	const wrapper = document.getElementById('modal');
	if (!wrapper) return;
	const saved = (window as any)._tournamentSetupHTML;
	if (saved) {
		wrapper.innerHTML = saved;
		applyTranslations();
	}
}

/**
 * Handles login submit inside the tournament player login sub-modal.
 * Reuses loginPlayer from gameService — identical to loginPlayer2Direct in games.ts.
 */
async function loginTournamentPlayer(index: number): Promise<void> {
	const emailInput = document.getElementById(`tour-player-email-${index}`) as HTMLInputElement;
	const passwordInput = document.getElementById(`tour-player-password-${index}`) as HTMLInputElement;
	const statusDiv = document.getElementById(`tour-login-status-${index}`);

	if (!emailInput || !passwordInput || !statusDiv) return;

	const email = emailInput.value.trim();
	const password = passwordInput.value;

	const t = (key: string, fallback: string) =>
		(window as any).languageManager?.t(key) ?? fallback;

	if (!email || !password) {
		statusDiv.innerHTML = `<span class="text-red-400 text-xs" data-i18n="game.enterEmailAndPassword">${t('game.enterEmailAndPassword', 'Please enter email and password')}</span>`;
		return;
	}

	statusDiv.innerHTML = `<span class="text-yellow-400 text-xs" data-i18n="game.logginIn">${t('game.logginIn', 'Logging in...')}</span>`;

	try {
		const user = await loginPlayer(email, password);

		if (user) {
			// Prevent the same user appearing twice
			for (const [otherIndex, otherUser] of verifiedPlayers.entries()) {
				if (otherIndex !== index && otherUser.id === user.id) {
					statusDiv.innerHTML = `<span class="text-red-400 text-xs" data-i18n="tournament.playerAlreadyInTournament">${t('tournament.playerAlreadyInTournament', '✗ This player is already in the tournament')}</span>`;
					return;
				}
			}

			verifiedPlayers.set(index, user);
			playerSlots.set(index, { type: 'registered', value: user.username });

			const verifiedMsg = `✓ ${user.display_name || user.username} ${t('tournament.playerVerifiedSuffix', 'verified!')}`;
			statusDiv.innerHTML = `<span class="text-green-400 text-xs">${verifiedMsg}</span>`;

			setTimeout(() => {
				closePlayerVerifyModal(index);
				// Update the visible input with the canonical display name
				const input = document.getElementById(`player-registered-${index}`) as HTMLInputElement;
				if (input) input.value = user.display_name || user.username;
				updateVerificationStatus(index, 'ok', `${user.display_name || user.username} ${t('tournament.playerVerifiedSuffix', 'verified!')}`);
			}, 800);
		} else {
			statusDiv.innerHTML = `<span class="text-red-400 text-xs" data-i18n="game.invalidCredentials">${t('game.invalidCredentials', '✗ Invalid credentials')}</span>`;
		}
	} catch (error: any) {
		let msgKey = 'game.loginFailed';
		let msgFallback = '✗ Login failed';
		if (
			error?.message === 'messages.invalidCredentials' ||
			error?.message === 'auth.authenticationRequired'
		) {
			msgKey = 'game.invalidCredentials';
			msgFallback = '✗ Invalid credentials';
		} else if (error?.message === 'auth.invalidToken') {
			msgKey = 'game.sessionExpired';
			msgFallback = '✗ Session expired';
		}
		statusDiv.innerHTML = `<span class="text-red-400 text-xs" data-i18n="${msgKey}">${t(msgKey, msgFallback)}</span>`;
	}
}

// ===== SLOT HTML GENERATION =====

function generatePlayerSlotHTML(
	index: number,
	defaultType: 'registered' | 'guest' = 'guest',
	defaultName: string = '',
	isPreFilled = false   // true only for slot 0 (logged-in user)
): string {
	const isGuest = defaultType === 'guest';

	// Pre-filled slot already verified; no button needed
	const verifiedBadge = (!isGuest && isPreFilled)
		? `<span class="text-green-400 text-xs" id="verify-status-${index}">✓ ${defaultName} (you)</span>`
		: `<span class="text-xs" id="verify-status-${index}"></span>`;

	const verifyButtonHtml = (!isGuest && isPreFilled)
		? ''
		: `<button
        id="verify-btn-${index}"
        onclick="window.tournamentUI.showPlayerVerifyModal(${index})"
        class="btn btn-blue btn-sm mt-1 text-xs px-2 py-1"
        type="button"
      >Verify</button>`;

	return `
    <div class="border border-gray-600 rounded-lg p-3">
      <label class="block text-sm text-gray-400 mb-2"><span data-i18n="tournament.player">Player</span> ${index + 1}</label>
      
      <!-- Type selector -->
      <div class="flex gap-4 mb-2">
        <label class="flex items-center cursor-pointer">
          <input 
            type="radio" 
            name="type-${index}" 
            id="radio-guest-${index}"
            value="guest" 
            ${isGuest ? 'checked' : ''}
            onchange="window.tournamentUI.togglePlayerType(${index}, 'guest')"
            class="mr-1"
          />
          <span class="text-sm" data-i18n="tournament.guest">🎮 Invitado</span>
        </label>
        <label class="flex items-center cursor-pointer">
          <input 
            type="radio" 
            name="type-${index}" 
            id="radio-registered-${index}"
            value="registered"
            ${!isGuest ? 'checked' : ''}
            onchange="window.tournamentUI.togglePlayerType(${index}, 'registered')"
            class="mr-1"
          />
          <span class="text-sm" data-i18n="tournament.registered">👤 Registrado</span>
        </label>
      </div>
      
      <!-- Guest input -->
      <div id="guest-input-${index}" ${!isGuest ? 'class="hidden"' : ''}>
        <input
          type="text"
          id="player-guest-${index}"
          placeholder="Nombre del invitado"
          data-i18n-placeholder="tournament.guestNamePlaceholder"
          value="${isGuest ? defaultName : ''}"
          class="w-full p-2 rounded bg-gray-700 text-white"
        />
      </div>
      
      <!-- Registered input -->
      <div id="registered-input-${index}" ${isGuest ? 'class="hidden"' : ''}>
        <input
          type="text"
          id="player-registered-${index}"
          placeholder="Nombre de usuario registrado"
          data-i18n-placeholder="tournament.registeredNamePlaceholder"
          value="${!isGuest ? defaultName : ''}"
          ${isPreFilled ? 'readonly' : ''}
          class="w-full p-2 rounded bg-gray-700 text-white ${isPreFilled ? 'opacity-70 cursor-not-allowed' : ''}"
        />
        <div class="flex items-center justify-between mt-1">
          ${verifiedBadge}
          ${verifyButtonHtml}
        </div>
        <p class="text-xs text-gray-500 mt-1" data-i18n="tournament.registeredNameHint">
          Ingresa el nombre de usuario exacto y pulsa Verify
        </p>
      </div>
    </div>
  `;
}

// ===== MODAL HELPERS =====

function showModal(html: string): void {
	const modal = document.getElementById('modal');
	if (!modal) return;
	modal.classList.remove('hidden');
	modal.innerHTML = html;
}

function hideModal(): void {
	const modal = document.getElementById('modal');
	if (!modal) return;
	modal.classList.add('hidden');
}

// ===== UTILITY FUNCTIONS =====

function applyTranslations(): void {
	if ((window as any).languageManager?.isReady()) {
		(window as any).languageManager.applyTranslations();
	}
}

// ===== TOURNAMENT SETUP =====

export async function setupPongTournament(ai: boolean, diff = 3): Promise<void> {
	const currentUser = await getCurrentUser();
	showTournamentSetupModal(currentUser, ai, diff, "P");
}

export async function setupTicTacToeTournament(ai: boolean, diff = 3): Promise<void> {
	const currentUser = await getCurrentUser();
	showTournamentSetupModal(currentUser, ai, diff, "T");
}

async function showTournamentSetupModal(
	currentUser: any,
	ai: boolean,
	diff: number,
	type: string
): Promise<void> {

	// Clear all previous state
	playerSlots.clear();
	verifiedPlayers.clear();

	const modeLabel = ai ? 'tournament.humanAI' : 'tournament.humanOnly';
	const modeFallback = ai ? 'Human players + AI' : 'Human players only';

	let html = `
    <div class="card text-center space-y-4 max-w-4xl mx-auto">
      <h2 class="text-2xl font-bold text-yellow-400" data-i18n="tournament.setup">🏆 Tournament Setup</h2>
      <p class="text-sm text-gray-400" data-i18n="${modeLabel}">${modeFallback}</p>
      
      <div class="grid grid-cols-2 gap-4 text-left">
  `;

	const endIndex = ai ? USERS_TOUR_NUM - 1 : USERS_TOUR_NUM;

	for (let i = 0; i < endIndex; i++) {
		if (i === 0 && currentUser) {
			// First slot: pre-fill + pre-verify with the current session user
			html += generatePlayerSlotHTML(i, 'registered', currentUser.display_name || currentUser.username, true);
			playerSlots.set(i, { type: 'registered', value: currentUser.username });
			verifiedPlayers.set(i, currentUser);  // already verified via session
		} else {
			html += generatePlayerSlotHTML(i, 'guest', '');
			playerSlots.set(i, { type: 'guest', value: '' });
		}
	}

	if (ai) {
		html += `
      <div class="border border-gray-600 rounded-lg p-3">
        <label class="block text-sm text-gray-400 mb-2"><span data-i18n="tournament.player">Player</span> ${USERS_TOUR_NUM}</label>
        <input
          type="text"
          id="ai-player-input"
          value="AI (Difficulty ${diff})"
          disabled
          class="w-full p-2 rounded bg-gray-600 cursor-not-allowed text-white"
        />
        <p class="text-xs text-yellow-400 mt-1" data-i18n="tournament.aiPlayerLabel">🤖 AI Player</p>
      </div>
    `;
	}

	html += `
      </div>
      
      <div id="tournamentSetupStatus" class="text-sm min-h-5"></div>
      
      <div class="flex gap-4 mt-6">
        <button onclick="window.tournamentUI.hideTournamentModal()" class="btn btn-gray flex-1" data-i18n="game.cancel">Cancel</button>
        <button onclick="window.tournamentUI.confirmTournamentSetup(${ai}, ${diff}, '${type}')" class="btn btn-green flex-1" data-i18n="tournament.start">Start Tournament</button>
      </div>
    </div>
  `;

	showModal(html);
	applyTranslations();

	if (ai) {
		const aiInput = document.getElementById('ai-player-input') as HTMLInputElement;
		if (aiInput) {
			const aiLabel = (window as any).languageManager?.t('tournament.ai') ?? 'AI';
			const diffLabel = (window as any).languageManager?.t('tournament.difficulty') ?? 'Difficulty';
			aiInput.value = `${aiLabel} (${diffLabel} ${diff})`;
		}
	}

	setTimeout(() => {
		const firstInputId = currentUser ? 'player-guest-1' : 'player-guest-0';
		const firstInput = document.getElementById(firstInputId) as HTMLInputElement;
		firstInput?.focus();
	}, 100);
}

async function confirmTournamentSetup(ai: boolean, diff: number, type: string): Promise<void> {
	const players: Player[] = [];
	const statusDiv = document.getElementById('tournamentSetupStatus');

	const endIndex = ai ? USERS_TOUR_NUM - 1 : USERS_TOUR_NUM;

	for (let i = 0; i < endIndex; i++) {
		const slotConfig = playerSlots.get(i);

		if (!slotConfig) {
			if (statusDiv) statusDiv.innerHTML = `<span class="text-red-400">⚠️ Error: slot ${i + 1} not configured</span>`;
			return;
		}

		let player: Player;

		if (slotConfig.type === 'guest') {
			// ── Guest: only needs a name ─────────────────────────────────────────
			const input = document.getElementById(`player-guest-${i}`) as HTMLInputElement;
			const name = input?.value.trim() || '';

			if (!name) {
				if (statusDiv) statusDiv.innerHTML = `<span class="text-red-400">⚠️ Please enter a name for Player ${i + 1}</span>`;
				return;
			}

			player = createGuestPlayer(name);

		} else {
			// ── Registered: must have been verified ──────────────────────────────
			let verifiedUser = verifiedPlayers.get(i);

			if (!verifiedUser) {
				// Fallback: try verifying by username now (user skipped the Verify button)
				const input = document.getElementById(`player-registered-${i}`) as HTMLInputElement;
				const username = input?.value.trim() || '';

				if (!username) {
					if (statusDiv) statusDiv.innerHTML = `<span class="text-red-400">⚠️ Please enter a username for Player ${i + 1}</span>`;
					return;
				}

				if (statusDiv) statusDiv.innerHTML = `<span class="text-yellow-400">⏳ Verifying Player ${i + 1}...</span>`;

				const found = await verifyPlayerByName(username);

				if (!found) {
					if (statusDiv) statusDiv.innerHTML = `<span class="text-red-400">⚠️ Player ${i + 1}: user "${username}" not found. Click Verify first.</span>`;
					updateVerificationStatus(i, 'error', 'User not found');
					return;
				}

				// Duplicate check
				for (const existing of verifiedPlayers.values()) {
					if (existing.id === found.id) {
						if (statusDiv) statusDiv.innerHTML = `<span class="text-red-400">⚠️ Player ${i + 1}: "${found.display_name || found.username}" is already in the tournament.</span>`;
						return;
					}
				}

				verifiedPlayers.set(i, found);
				updateVerificationStatus(i, 'ok', `${found.display_name || found.username} verified`);
				verifiedUser = found;
			}

			player = createRegisteredPlayer(verifiedUser);
		}

		// Duplicate name check
		if (players.some(p => p.name.toLowerCase() === player.name.toLowerCase())) {
			if (statusDiv) statusDiv.innerHTML = `<span class="text-red-400">⚠️ "${player.name}" is already used. Please use unique names.</span>`;
			return;
		}

		players.push(player);
	}

	if (ai) {
		players.push({ name: `AI (Difficulty ${diff})`, id: "AI", isGuest: false });
	}

	if (players.length !== USERS_TOUR_NUM) {
		if (statusDiv) statusDiv.innerHTML = `<span class="text-red-400">⚠️ Need exactly ${USERS_TOUR_NUM} players. Got ${players.length}.</span>`;
		return;
	}

	if (statusDiv) statusDiv.innerHTML = '<span class="text-yellow-400">⏳ Creating tournament...</span>';

	const tournament = createTournament(players);
	tournament.gameType = type === 'P' ? 'pong' : 'tictactoe';
	const currentUser = await getCurrentUser();
	const tournamentId = await createTournamentInDB(players, type, currentUser?.id || null);

	if (tournamentId) {
		tournament.tournamentId = tournamentId;
		tournament.creatorId = currentUser?.id || null;
		await startTournamentInDB(tournamentId);
	}

	saveTournament(tournament);
	hideModal();
	navigate("tournament_game");
}

function hideTournamentModal(): void {
	hideModal();
}

// ===== GLOBAL EXPORTS =====

(window as any).tournamentUI = {
	setupPongTournament,
	setupTicTacToeTournament,
	confirmTournamentSetup,
	hideTournamentModal,
	togglePlayerType,
	verifyTournamentPlayer,     // used internally by confirmTournamentSetup as fallback
	showPlayerVerifyModal,      // opens email+password modal (mirrors showPlayer2VerifyModal)
	closePlayerVerifyModal,
	loginTournamentPlayer       // handles login submit (mirrors loginPlayer2Direct)
};