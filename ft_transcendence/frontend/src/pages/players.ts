import { api, ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError } from '../api.js';
import { loadAvatar } from '../imageUtils.js';

interface PlayerListItem {
	id: string;
	username: string;
	display_name: string | null;
	avatar: string | null;
	online_status: string;
}

interface PlayerStats {
	games_played: number;
	wins: number;
	losses: number;
	win_rate: number;
	tournament_wins: number;
}

interface MatchHistoryItem {
	id: number;
	opponent: {
		name: string;
	};
	playerScore: number;
	opponentScore: number;
	won: boolean;
	gameType: string;
	duration: number | null;
	playedAt: string;
	tournamentId: number | null;
}

interface PlayerProfile {
	username: string;
	display_name: string | null;
	avatar: string | null;
	online_status: string;
	last_seen: string | null;
	created_at: string;
	stats: PlayerStats;
	match_history: MatchHistoryItem[];
}

interface LeaderboardEntry {
	id: string;
	username: string;
	display_name: string | null;
	avatar: string | null;
	online_status: string;
	stats: PlayerStats;
}

export function renderPlayers(): string {
	setTimeout(() => {
		loadPlayers();
		setupPlayerCardClickHandlers();
	}, 100);

	return `
    <div class="max-w-4xl mx-auto">
      <h2 class="text-3xl font-bold text-center text-cyan-400 mb-8" data-i18n="players.title">👥 Players</h2>

      <div class="card mb-6">
        <div class="flex gap-4">
          <input id="playerSearch" type="text" placeholder="Search players..."
                 class="input flex-1" data-i18n-placeholder="players.searchPlaceholder" />
          <button id="searchPlayersBtn" class="btn btn-blue" data-i18n="players.search">🔍 Search</button>
          <button id="leaderboardBtn" class="btn btn-yellow" data-i18n="players.leaderboard">🏆 Leaderboard</button>
        </div>
      </div>

      <div id="playersList" class="grid grid-cols-1 md:grid-cols-2 gap-4">
        <div class="card animate-pulse">
          <div class="h-16 bg-gray-700 rounded"></div>
        </div>
      </div>

      <!-- Player Profile Modal -->
      <div id="playerModal" class="modal hidden">
        <div class="modal-content card max-w-3xl max-h-[90vh] overflow-y-auto">
          <div id="playerModalContent"></div>
          <div class="flex gap-4 mt-6">
            <button id="addFriendBtn" class="btn btn-green flex-1" data-i18n="players.addFriend">
              ➕ Add Friend
            </button>
            <button id="closeModalBtn" class="btn btn-gray flex-1" data-i18n="common.close">
              Close
            </button>
          </div>
        </div>
      </div>

      <!-- Leaderboard Modal -->
      <div id="leaderboardModal" class="modal hidden">
        <div class="modal-content card max-w-4xl max-h-[90vh] overflow-y-auto">
          <h3 class="text-2xl font-bold text-yellow-400 mb-6 text-center" data-i18n="players.leaderboardTitle">🏆 Top Players Leaderboard</h3>
          <div id="leaderboardContent"></div>
          <div class="flex gap-4 mt-6">
            <button id="closeLeaderboardBtn" class="btn btn-gray flex-1" data-i18n="common.close">
              Close
            </button>
          </div>
        </div>
      </div>
    </div>
  `;
}

function setupPlayerCardClickHandlers(): void {
	// Event delegation for player cards
	const playersList = document.getElementById('playersList');
	if (playersList) {
		playersList.addEventListener('click', (e) => {
			const card = (e.target as HTMLElement).closest('[data-player-id]');
			if (card) {
				const playerId = card.getAttribute('data-player-id');
				if (playerId) {
					viewPlayer(playerId);
				}
			}
		});
	}
	
	// Search button
	const searchBtn = document.getElementById('searchPlayersBtn');
	if (searchBtn) {
		searchBtn.addEventListener('click', searchPlayers);
	}
	
	// Search on Enter key
	const searchInput = document.getElementById('playerSearch') as HTMLInputElement;
	if (searchInput) {
		searchInput.addEventListener('keypress', (e) => {
			if (e.key === 'Enter') {
				searchPlayers();
			}
		});
	}
	
	// Leaderboard button
	const leaderboardBtn = document.getElementById('leaderboardBtn');
	if (leaderboardBtn) {
		leaderboardBtn.addEventListener('click', showLeaderboard);
	}
	
	// Close modal button
	const closeBtn = document.getElementById('closeModalBtn');
	if (closeBtn) {
		closeBtn.addEventListener('click', closePlayerModal);
	}
	
	// Close leaderboard button
	const closeLeaderboardBtn = document.getElementById('closeLeaderboardBtn');
	if (closeLeaderboardBtn) {
		closeLeaderboardBtn.addEventListener('click', closeLeaderboardModal);
	}
}

async function loadPlayers(search: string = ''): Promise<void> {
	const container = document.getElementById('playersList');
	if (!container) {
		return;
	}

	try {
		const response = await api<{ success: boolean; users: PlayerListItem[] }>(
			`/api/database/players?search=${encodeURIComponent(search)}&limit=50`
		);

		if (response.success && response.users.length > 0) {
			// Render immediately with default avatars for speed
			container.innerHTML = response.users.map(player => renderPlayerCard(player)).join('');
			window.languageManager?.applyTranslations();
			
			// Load avatars progressively in background
			response.users.forEach(async (player, index) => {
				try {
					const avatarUrl = await loadAvatar(player.avatar);
					const imgElement = container.querySelector(`[data-player-id="${player.id}"] img`);
					if (imgElement && avatarUrl) {
						(imgElement as HTMLImageElement).src = avatarUrl;
					}
				} catch (error) {
					// Avatar loading failed - will remain as default
				}
			});
		} else {
			container.innerHTML = `
        <div class="card col-span-2 text-center text-gray-400">
          <p data-i18n="players.noPlayersFound">No players found</p>
        </div>
      `;
			window.languageManager?.applyTranslations();
		}
	} catch (error: any) {
		if (error instanceof ServerError) {
			console.error('Server error loading players:', error);
		}
		let message = error instanceof AuthError
			? '<p class="text-red-400" data-i18n="players.authRequired">Authentication required</p>'
			: '<p data-i18n="players.loadError">Failed to load players</p>';
		container.innerHTML = `
			<div class="card col-span-2 text-center text-red-400">
				${message}
			</div>
		`;
		window.languageManager?.applyTranslations();
	}
}

function renderPlayerCard(player: PlayerListItem): string {
	const statusColor = player.online_status === 'online' ? 'text-green-400' : 'text-gray-400';
	const statusDot = player.online_status === 'online' ? 'bg-green-400' : 'bg-gray-400';

	// REMOVED inline onclick - using event delegation instead
	return `
		<div class="card hover:border-yellow-400 cursor-pointer transition-all" data-player-id="${player.id}">
			<div class="flex items-center gap-4">
				<div class="relative">
					<img class="w-16 h-16 rounded-full border-2 border-gray-600 object-cover"
							 src="/default-avatar.png"
							 alt="${player.username}"
							 onerror="this.src='/default-avatar.png'" />
					<span class="absolute bottom-0 right-0 w-4 h-4 ${statusDot} rounded-full border-2 border-gray-800"></span>
				</div>
				<div class="flex-1">
					<h3 class="text-lg font-bold text-yellow-400">${player.display_name || player.username}</h3>
					<p class="text-sm text-gray-400">@${player.username}</p>
					<p class="text-xs ${statusColor} mt-1">● <span data-i18n="players.status.${player.online_status}">${player.online_status || 'offline'}</span></p>
				</div>
			</div>
		</div>
	`;
}

async function viewPlayer(playerId: string): Promise<void> {
	const modal = document.getElementById('playerModal');
	const content = document.getElementById('playerModalContent');
	const addFriendBtn = document.getElementById('addFriendBtn');

	if (!modal || !content) {
		return;
	}

	// Show loading state
	content.innerHTML = `
		<div class="animate-pulse">
			<div class="h-32 bg-gray-700 rounded mb-4"></div>
			<div class="h-4 bg-gray-700 rounded w-3/4 mb-2"></div>
			<div class="h-4 bg-gray-700 rounded w-1/2"></div>
		</div>
	`;
	modal.classList.remove('hidden');

	try {
		const response = await api<{ success: boolean; user: PlayerProfile }>(`/api/database/players/${encodeURIComponent(playerId)}`);

		if (response.success && response.user) {
			const player = response.user;
			const avatarUrl = await loadAvatar(player.avatar);

			content.innerHTML = `
				<!-- Player Header -->
				<div class="text-center mb-6">
					<img class="w-24 h-24 rounded-full border-4 border-yellow-400 mx-auto object-cover"
							 src="${avatarUrl}"
							 alt="${player.username}"
							 onerror="this.src='/default-avatar.png'" />
					<h3 class="text-2xl font-bold text-yellow-400 mt-4">${player.display_name || player.username}</h3>
					<p class="text-gray-400">@${player.username}</p>
					<p class="text-sm ${player.online_status === 'online' ? 'text-green-400' : 'text-gray-400'} mt-1">
						● <span data-i18n="players.status.${player.online_status}">${player.online_status || 'offline'}</span>
					</p>
				</div>

				<!-- Stats Grid -->
				<div class="grid grid-cols-5 gap-3 mb-6">
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-yellow-400">${player.stats.games_played}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.gamesPlayed">Games</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-green-400">${player.stats.wins}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.wins">Wins</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-red-400">${player.stats.losses}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.losses">Losses</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-blue-400">${player.stats.win_rate}%</p>
						<p class="text-xs text-gray-400" data-i18n="profile.winRate">Win%</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-purple-400">${player.stats.tournament_wins || 0}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.tournamentWins">🏆 Tours</p>
					</div>
				</div>

				<!-- Match History -->
				<div class="mt-6">
					<h4 class="text-lg font-bold text-cyan-400 mb-3" data-i18n="profile.matchHistory">📜 Match History</h4>
					${renderMatchHistory(player.match_history)}
				</div>
			`;

			// Apply translations and set up Add Friend button
			window.languageManager?.applyTranslations();
			setupAddFriendButton(playerId);
		}
	} catch (error: any) {
		let isAuthError = false;
		if (error && error.message === 'auth.authenticationRequired') {
			isAuthError = true;
		}
		let message = isAuthError
			? '<p class="text-red-400 text-center" data-i18n="players.authRequired">Authentication required</p>'
			: '<p class="text-red-400 text-center" data-i18n="players.loadError">Failed to load player profile</p>';
		content.innerHTML = message;
		window.languageManager?.applyTranslations();
	}
}

function renderMatchHistory(matches: MatchHistoryItem[]): string {
	if (matches.length === 0) {
		return `
			<div class="bg-gray-800 rounded-lg p-4 text-center text-gray-400">
				<p data-i18n="profile.noMatchHistory">No matches played yet</p>
			</div>
		`;
	}

	return `
		<div class="space-y-2 max-h-96 overflow-y-auto">
			${matches.map(match => {
		const resultColor = match.won ? 'bg-green-900/30 border-green-600' : 'bg-red-900/30 border-red-600';
		const resultIcon = match.won ? '🏆' : '💔';
		const resultKey = match.won ? 'players.victory' : 'players.defeat';
		const resultDefault = match.won ? 'Victory' : 'Defeat';
		const date = new Date(match.playedAt).toLocaleDateString('en-US', {
			month: 'short',
			day: 'numeric',
			year: 'numeric'
		});
		const gameTypeLower = (match.gameType || 'pong').toLowerCase();
		const gameTypeLabel = gameTypeLower === 'tictactoe' ? '❌⭕ TicTacToe' : '🏓 Pong';
		const gameTypeBg = gameTypeLower === 'tictactoe' ? 'bg-blue-700' : 'bg-cyan-700';

		return `
					<div class="border ${resultColor} rounded-lg p-3 hover:shadow-lg transition-shadow">
						<div class="flex items-center justify-between">
							<div class="flex-1">
								<div class="flex items-center gap-2 mb-1">
									<span class="text-lg">${resultIcon}</span>
									<span class="font-bold ${match.won ? 'text-green-400' : 'text-red-400'}" data-i18n="${resultKey}">${resultDefault}</span>
									<span class="text-xs ${gameTypeBg} px-2 py-0.5 rounded">${gameTypeLabel}</span>
									${match.tournamentId ? `<span class="text-xs bg-purple-600 px-2 py-0.5 rounded" data-i18n="players.tournament">Tournament</span>` : ''}
								</div>
								<div class="text-sm text-gray-400">
									<span data-i18n="players.vs">vs</span> <span>${match.opponent.name ? match.opponent.name : '<span data-i18n="players.unknown">Unknown</span>'}</span>
									<span class="mx-2">•</span>
									<span>${date}</span>
								</div>
							</div>
							<div class="text-right">
								<div class="text-2xl font-bold ${match.won ? 'text-green-400' : 'text-red-400'}">
									${match.playerScore} - ${match.opponentScore}
								</div>
								${match.duration ? `<div class="text-xs text-gray-500">${formatDuration(match.duration)}</div>` : ''}
							</div>
						</div>
					</div>
				`;
	}).join('')}
		</div>
	`;
}

function formatDuration(seconds: number): string {
	const minutes = Math.floor(seconds / 60);
	const secs = seconds % 60;
	return `${minutes}m ${secs}s`;
}

async function setupAddFriendButton(playerId: string): Promise<void> {
	const btn = document.getElementById('addFriendBtn') as HTMLButtonElement;
	if (!btn) return;

	// Check friendship status
	try {
		const checkResponse = await api<{ success: boolean; status: string }>(
			`/api/database/friends/me/check/${encodeURIComponent(playerId)}`
		);

		const status = checkResponse.success ? checkResponse.status : 'none';
		updateButtonState(btn, status);
	} catch (error) {
		console.error('Failed to check friendship status:', error);
		updateButtonState(btn, 'none');
	}

	// Set up click handler
	btn.onclick = () => addFriend(playerId);
}

function updateButtonState(btn: HTMLButtonElement, status: string): void {
	btn.disabled = false;
	btn.className = 'btn btn-green flex-1';
	
	if (status === 'pending') {
		btn.disabled = true;
		btn.className = 'btn btn-gray flex-1';
		btn.setAttribute('data-i18n', 'players.requestPending');
		btn.innerHTML = '⏳ Request Pending';
	} else if (status === 'accepted') {
		btn.disabled = true;
		btn.className = 'btn btn-gray flex-1';
		btn.setAttribute('data-i18n', 'players.alreadyFriends');
		btn.innerHTML = '✓ Already Friends';
	} else {
		btn.setAttribute('data-i18n', 'players.addFriend');
		btn.innerHTML = '➕ Add Friend';
	}
	
	window.languageManager?.applyTranslations();
}

function closePlayerModal(): void {
	const modal = document.getElementById('playerModal');
	if (modal) {
		modal.classList.add('hidden');
	}
}

async function addFriend(playerId: string): Promise<void> {
	const btn = document.getElementById('addFriendBtn') as HTMLButtonElement;
	if (!btn || btn.disabled) return;

	// Show sending state
	btn.disabled = true;
	btn.setAttribute('data-i18n', 'players.sendingRequest');
	btn.innerHTML = '⏳ Sending...';
	window.languageManager?.applyTranslations();

	try {
		const response = await api<{ success: boolean; error?: string; code?: string }>('/api/database/friends/me/add', {
			method: 'POST',
			body: JSON.stringify({ friend_id: playerId })
		});

		if (response.success) {
			updateButtonState(btn, 'pending');
			showToast('Friend request sent!', 'success');
		} else {
			updateButtonState(btn, 'none');
			if (response.code === 'SELF_FRIEND') {
				showToast('You cannot add yourself as a friend', 'error');
			} else {
				showToast(response.error || 'Failed to send request', 'error');
			}
		}
	} catch (error) {
		updateButtonState(btn, 'none');
		
		if (error instanceof ForbiddenError && (error as any).code === 'SELF_FRIEND') {
			showToast('You cannot add yourself as a friend', 'error');
		} else if (error instanceof ServerError) {
			console.error('Server error sending friend request:', error);
			showToast('Failed to send friend request', 'error');
		} else {
			showToast('Failed to send friend request', 'error');
		}
	}
}

function showToast(message: string, type: 'success' | 'error'): void {
	// Use i18n for known messages if possible
	let translated = message;
	if (window.languageManager?.t) {
		if (message === 'Friend request sent!') {
			const t = window.languageManager.t('players.friendRequestSent');
			translated = t !== null ? t : message;
		}
		if (message === 'Failed to send request') {
			const t = window.languageManager.t('players.failedToSendRequest');
			translated = t !== null ? t : message;
		}
		if (message === 'Failed to send friend request') {
			const t = window.languageManager.t('players.failedToSendFriendRequest');
			translated = t !== null ? t : message;
		}
		if (message === 'You cannot add yourself as a friend') {
			const t = window.languageManager.t('players.cannotAddSelf');
			translated = t !== null ? t : message;
		}
	}
	const toast = document.createElement('div');
	toast.className = `fixed bottom-4 right-4 px-6 py-3 rounded-lg shadow-lg z-50 ${type === 'success' ? 'bg-green-600' : 'bg-red-600'} text-white`;
	toast.textContent = translated;
	document.body.appendChild(toast);

	setTimeout(() => {
		toast.remove();
	}, 3000);
}

function searchPlayers(): void {
	const searchInput = document.getElementById('playerSearch') as HTMLInputElement;
	if (searchInput) {
		loadPlayers(searchInput.value);
	}
}

async function showLeaderboard(): Promise<void> {
	const modal = document.getElementById('leaderboardModal');
	const content = document.getElementById('leaderboardContent');
	
	if (!modal || !content) {
		return;
	}

	// Show loading state
	content.innerHTML = `
		<div class="animate-pulse space-y-4">
			<div class="h-20 bg-gray-700 rounded"></div>
			<div class="h-20 bg-gray-700 rounded"></div>
			<div class="h-20 bg-gray-700 rounded"></div>
		</div>
	`;
	modal.classList.remove('hidden');

	try {
		const response = await api<{ success: boolean; leaderboard: LeaderboardEntry[] }>('/api/database/players/leaderboard?limit=5');

		if (response.success && response.leaderboard.length > 0) {
			// Load avatars for all players
			const leaderboardWithAvatars = await Promise.all(
				response.leaderboard.map(async (player, index) => {
					const avatarUrl = await loadAvatar(player.avatar);
					return { ...player, avatarUrl, rank: index + 1 };
				})
			);

			content.innerHTML = `
				<div class="space-y-4">
					${leaderboardWithAvatars.map(player => renderLeaderboardCard(player)).join('')}
				</div>
			`;
			window.languageManager?.applyTranslations();
		} else {
			content.innerHTML = `
				<div class="card text-center text-gray-400">
					<p data-i18n="players.noLeaderboardData">No leaderboard data available yet</p>
				</div>
			`;
			window.languageManager?.applyTranslations();
		}
	} catch (error: any) {
		let message = error instanceof AuthError
			? '<p class="text-red-400" data-i18n="players.authRequired">Authentication required</p>'
			: '<p data-i18n="players.leaderboardError">Failed to load leaderboard</p>';
		content.innerHTML = `
			<div class="card text-center text-red-400">
				${message}
			</div>
		`;
		window.languageManager?.applyTranslations();
	}
}

function renderLeaderboardCard(player: LeaderboardEntry & { avatarUrl: string; rank: number }): string {
	const rankColors = ['text-yellow-400', 'text-gray-300', 'text-orange-400'];
	const rankColor = player.rank <= 3 ? rankColors[player.rank - 1] : 'text-cyan-400';
	const rankEmojis = ['🥇', '🥈', '🥉'];
	const rankEmoji = player.rank <= 3 ? rankEmojis[player.rank - 1] : `#${player.rank}`;
	const statusColor = player.online_status === 'online' ? 'text-green-400' : 'text-gray-400';

	return `
		<div class="card border-2 ${player.rank === 1 ? 'border-yellow-400 bg-yellow-900/10' : player.rank === 2 ? 'border-gray-300 bg-gray-700/10' : player.rank === 3 ? 'border-orange-400 bg-orange-900/10' : 'border-gray-700'} cursor-pointer hover:border-cyan-400 transition-all" 
		     data-player-id="${player.id}"
		     onclick="window.viewPlayer('${player.id}')">
			<div class="flex items-center gap-4">
				<!-- Rank -->
				<div class="text-4xl font-bold ${rankColor} w-16 text-center">
					${rankEmoji}
				</div>
				
				<!-- Avatar -->
				<div class="relative">
					<img class="w-16 h-16 rounded-full border-2 border-gray-600 object-cover"
					     src="${player.avatarUrl}"
					     alt="${player.username}"
					     onerror="this.src='/default-avatar.png'" />
				</div>
				
				<!-- Player Info -->
				<div class="flex-1">
					<h3 class="text-lg font-bold text-yellow-400">${player.display_name || player.username}</h3>
					<p class="text-sm text-gray-400">@${player.username}</p>
					<p class="text-xs ${statusColor} mt-1">● <span data-i18n="players.status.${player.online_status}">${player.online_status || 'offline'}</span></p>
				</div>
				
				<!-- Stats -->
				<div class="grid grid-cols-5 gap-3">
					<div class="text-center">
						<p class="text-lg font-bold text-yellow-400">${player.stats.games_played}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.gamesPlayed">Games</p>
					</div>
					<div class="text-center">
						<p class="text-lg font-bold text-green-400">${player.stats.wins}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.wins">Wins</p>
					</div>
					<div class="text-center">
						<p class="text-lg font-bold text-red-400">${player.stats.losses}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.losses">Losses</p>
					</div>
					<div class="text-center">
						<p class="text-lg font-bold text-blue-400">${player.stats.win_rate}%</p>
						<p class="text-xs text-gray-400" data-i18n="profile.winRate">Win%</p>
					</div>
					<div class="text-center">
						<p class="text-lg font-bold text-purple-400">${player.stats.tournament_wins || 0}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.tournamentWins">🏆 Tours</p>
					</div>
				</div>
			</div>
		</div>
	`;
}

function closeLeaderboardModal(): void {
	const modal = document.getElementById('leaderboardModal');
	if (modal) {
		modal.classList.add('hidden');
	}
}

// Expose functions globally (for backward compatibility)
declare global {
	interface Window {
		viewPlayer: (id: string) => void;
		closePlayerModal: () => void;
		searchPlayers: () => void;
		showLeaderboard: () => void;
		closeLeaderboardModal: () => void;
	}
}

window.viewPlayer = viewPlayer;
window.closePlayerModal = closePlayerModal;
window.searchPlayers = searchPlayers;
window.showLeaderboard = showLeaderboard;
window.closeLeaderboardModal = closeLeaderboardModal;