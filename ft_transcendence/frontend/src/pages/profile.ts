import { api, getToken, ValidationError, ConflictError, AuthError, ServerError } from '../api.js';
import { TwoFAManager } from '../twofa.js';
import { navigate } from '../router.js';
import { removeAuthToken } from '../api.js';
import { loadAvatar } from '../imageUtils.js';

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
		id: string;
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

interface UserProfileData {
	id: string;
	username: string;
	display_name: string | null;
	avatar: string | null;
	email: string;
	twoFactorEnabled: boolean;
	stats?: PlayerStats;
	match_history?: MatchHistoryItem[];
}

export function renderProfile(): string {
	const token = getToken();

	if (!token) {
		return `
      <div class="max-w-2xl mx-auto space-y-6">
        <div class="card text-center">
          <div class="text-6xl mb-6">🔒</div>
          <h2 class="text-3xl font-bold mb-4" data-i18n="profile.title">Profile</h2>
          <p class="text-red-400 text-xl mb-6" data-i18n="auth.authenticationRequired">Authentication required</p>
          <button onclick="navigate('auth')" class="btn btn-blue" data-i18n="auth.login">Login</button>
        </div>
      </div>
    `;
	}

	setTimeout(initTwoFA, 100);
	setTimeout(loadProfile, 100);
	return `
    <div class="max-w-2xl mx-auto space-y-6">
      <div class="card">
        <h3 class="text-2xl font-bold mb-4" data-i18n="profile.title">Profile</h3>
        <div id="profileInfo" class="space-y-2">
          <div class="animate-pulse">
            <div class="h-4 bg-gray-700 rounded w-3/4 mb-2"></div>
            <div class="h-4 bg-gray-700 rounded w-1/2"></div>
          </div>
        </div>
        <div class="grid grid-cols-2 gap-4 mt-4">
          <input id="displayName" placeholder="Display Name (Nickname)" class="input" data-i18n-placeholder="profile.displayName" />
          <input id="newEmail" type="email" placeholder="New Email" class="input" data-i18n-placeholder="profile.newEmail" />
        </div>

        <div class="col-span-2 mt-4">
          <label class="block text-sm text-gray-400 mb-2" data-i18n="profile.uploadAvatar">Upload Avatar (JPG only, max 2MB)</label>
          <input type="file" id="avatarFile" accept=".jpg,.jpeg,image/jpeg" class="w-full p-2 rounded bg-gray-700 text-white">
        </div>

        <button onclick="uploadAvatar()" class="btn btn-blue mt-4" data-i18n="profile.uploadAvatar2">Upload Avatar</button>
        <button onclick="deleteAvatar()" class="btn btn-red mt-4" data-i18n="profile.deleteAvatar">🗑️ Remove Avatar</button>
        <button onclick="updateProfile()" class="btn btn-blue mt-4" data-i18n="profile.updatePersonalInfo">Update Personal Info</button>

        <button onclick="navigate('gdpr')" class="btn btn-gray mt-2" data-i18n="profile.privacyData">🔒 Privacy & Data</button>
        <button id="enable2FABtn" class="btn btn-blue" data-i18n="2fa.setup2FA">
        </button>
        <div id="profileResult" class="hidden"></div>
      </div>

      <div id="disableSection" class="card" style="display: none;">
        <div class="flex gap-4">
          <button id="disable2FABtn" class="btn btn-red" data-i18n="2fa.disable2FA">
          </button>
          <button id="generateBackupCodesBtn" class="btn btn-yellow" data-i18n="2fa.generateBackupCodes">
          </button>
        </div>
      </div>

      <!-- Match History Button & Section -->
      <div class="card">
        <button id="toggleMatchHistoryBtn" onclick="toggleMatchHistory()" class="btn btn-blue w-full" data-i18n="profile.showMatchHistory">
          📊 View Match History & Stats
        </button>
      </div>

      <div id="matchHistorySection" class="card hidden">
        <div id="matchHistoryContent"></div>
      </div>

      <div id="setupModal" class="modal hidden">
        <div class="modal-content card max-w-lg">
          <h3 class="text-2xl font-bold mb-4" data-i18n="2fa.setupTitle">Setup 2FA</h3>
          <div class="mb-6 text-center">
            <p class="mb-4" data-i18n="2fa.scanQR">Scan this QR code with your authenticator app:</p>
            <img id="qrCodeImage" src="" alt="QR Code" class="mx-auto mb-4 bg-white p-4 rounded">
            <button id="refreshQRBtn" class="btn btn-gray mt-2" data-i18n="2fa.refreshQR">🔄 Refresh QR</button>
          </div>
          <div class="mb-4">
            <label class="block mb-2" data-i18n="2fa.enterCode">Enter 6-digit code:</label>
            <input type="text" id="verificationCode" maxlength="6" placeholder="000000"
                   class="input text-center text-2xl font-mono tracking-widest">
          </div>
          <div class="flex gap-4">
            <button id="verifyCodeBtn" class="btn btn-blue flex-1" data-i18n="2fa.verifyActivate">
              ✓ Verify & Activate
            </button>
            <button id="cancelSetupBtn" class="btn btn-gray flex-1" data-i18n="common.cancel">
              Cancel
            </button>
          </div>
        </div>
      </div>

      <div id="disableModal" class="modal hidden">
        <div class="modal-content card max-w-lg">
          <h3 class="text-2xl font-bold mb-4 text-red-400" data-i18n="2fa.disableTitle">Disable 2FA</h3>
          <p class="mb-4" data-i18n="2fa.enterCodeToDisable">Enter your 6-digit code to disable 2FA:</p>
          <input type="text" id="disableVerificationCode" maxlength="6" placeholder="000000"
                 class="input text-center text-2xl font-mono tracking-widest mb-4">
          <div class="flex gap-4">
            <button id="confirmDisableBtn" class="btn btn-red flex-1" data-i18n="2fa.disableButton">
              Disable 2FA
            </button>
            <button id="cancelDisableBtn" class="btn btn-gray flex-1" data-i18n="common.cancel">
              Cancel
            </button>
          </div>
        </div>
      </div>

      <div id="backupCodesModal" class="modal hidden">
        <div class="modal-content card max-w-2xl">
          <h3 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="2fa.backupCodesAlert">⚠️ Save Your Backup Codes</h3>
          <p class="mb-4" data-i18n="2fa.newBackupCodes">Store these codes safely. Each can be used only once:</p>
          <div id="backupCodesList" class="grid grid-cols-2 gap-3 mb-6"></div>
          <div class="flex gap-4">
            <button id="copyAllCodesBtn" class="btn btn-blue flex-1">
              Copy all
            </button>
            <button id="downloadCodesBtn" class="btn btn-yellow flex-1">
              Download
            </button>
            <button id="closeBackupCodesBtn" class="btn btn-gray flex-1" data-i18n="common.confirm">
              I've Saved Them
            </button>
          </div>
        </div>
      </div>
    </div>
  `;
}

async function initTwoFA(): Promise<void> {
	const manager = new TwoFAManager();
	await manager.init();
	window.languageManager?.applyTranslations();
	(window as any).twoFAManager = manager;
}

async function loadProfile(): Promise<void> {
	const token = getToken();
	if (!token) {
		const infoDiv = document.getElementById('profileInfo');
		if (infoDiv) {
			infoDiv.innerHTML = '<p class="text-red-400" data-i18n="auth.authenticationRequired">Please login</p>';
			window.languageManager?.applyTranslations();
		}
		return;
	}

	try {
		const response = await api<any>('/api/auth/profile-data');

		const infoDiv = document.getElementById('profileInfo');
		if (infoDiv) {
			if (response.success && response.user) {
				// Fetch avatar with authentication if it exists
				const avatarUrl = await loadAvatar(response.user.avatar);

				infoDiv.innerHTML = `
          <div class="mb-4">
            <img 
              width="200" 
              height="200" 
              class="rounded-full mx-auto border-4 border-gray-700"
              src="${avatarUrl}" 
              onerror="this.src='/default-avatar.png'"
              alt="User avatar"
            />
          </div>
          <p><strong data-i18n="profile.displayName">Nickname:</strong> ${response.user.display_name || 'N/A'}</p>
          <p><strong data-i18n="profile.username">Full Name:</strong> ${response.user.username || 'N/A'}</p>
          <p><strong data-i18n="profile.email">Email:</strong> ${response.user.email || 'N/A'}</p>
          <p><strong data-i18n="profile.id">ID:</strong> ${response.user.id || 'N/A'}</p>
          <p><strong data-i18n="profile.2fa">2FA:</strong> <span class="${response.user.twoFactorEnabled ? 'text-green-400' : 'text-yellow-400'}">${response.user.twoFactorEnabled ? 'Enabled' : 'Disabled'}</span></p>
        `;
			} else {
				infoDiv.innerHTML = '<p class="text-red-400" data-i18n="profile.failedToLoad">Failed to load profile</p>';
			}
			window.languageManager?.applyTranslations();
		}
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error loading profile:', error);
		}
		const infoDiv = document.getElementById('profileInfo');
		if (infoDiv) {
			infoDiv.innerHTML = '<p class="text-red-400" data-i18n="profile.failedToLoad">Failed to load profile</p>';
			window.languageManager?.applyTranslations();
		}
	}
}

async function uploadAvatar(): Promise<void> {
	const fileInput = document.getElementById('avatarFile') as HTMLInputElement;
	const avatarFile = fileInput?.files?.[0];

	if (!avatarFile) {
		const msg = window.languageManager?.t('profile.selectFile');
		showProfileMessage(
			msg !== null ? msg : 'Please select a file',
			'error'
		);
		return;
	}

	// Validate file type - check both MIME type and extension
	const validTypes = ['image/jpeg', 'image/jpg'];
	const validExtensions = ['.jpg', '.jpeg'];
	const fileName = avatarFile.name.toLowerCase();
	const hasValidExtension = validExtensions.some(ext => fileName.endsWith(ext));

	if (!validTypes.includes(avatarFile.type) && !hasValidExtension) {
		const msg = window.languageManager?.t('profile.onlyJpgAllowed');
		showProfileMessage(
			msg !== null ? msg : 'Only JPG/JPEG files are allowed',
			'error'
		);
		return;
	}

	// Validate file size (2MB)
	if (avatarFile.size > 2 * 1024 * 1024) {
		const msg = window.languageManager?.t('profile.fileSizeLimit');
		showProfileMessage(
			msg !== null ? msg : 'File size must be less than 2MB',
			'error'
		);
		return;
	}

	// Create FormData and append file
	const formData = new FormData();
	formData.append('avatar', avatarFile);

	try {
		const uploadingMsg = window.languageManager?.t('profile.uploading');
		showProfileMessage(
			uploadingMsg !== null ? uploadingMsg : 'Uploading...',
			'success'
		);

		// Call the upload endpoint
		const data = await api<any>('/api/database/avatar/upload', {
			method: 'POST',
			body: formData
		});

		if (!data.success) {
			throw new Error(data.error || 'Upload failed');
		}

		const successMsg = window.languageManager?.t('profile.avatarUploaded');
		showProfileMessage(
			successMsg !== null ? successMsg : (data.message || 'Avatar uploaded successfully'),
			'success'
		);

		// Clear the file input
		if (fileInput) {
			fileInput.value = '';
		}

		// Reload profile to show new avatar
		setTimeout(() => {
			loadProfile();
		}, 500);
	} catch (error: any) {
		if (error instanceof ServerError) {
			console.error('Server error uploading avatar:', error);
		}
		const errorMsg = window.languageManager?.t('profile.uploadFailed');
		showProfileMessage(
			errorMsg !== null ? errorMsg : (error.message || 'Failed to upload avatar'),
			'error'
		);
	}
}

function showProfileMessage(message: string, type: 'success' | 'error'): void {
	const resultDiv = document.getElementById('profileResult');
	if (resultDiv) {
		resultDiv.classList.remove('hidden');
		resultDiv.className = `mt-4 p-3 rounded ${type === 'success' ? 'bg-green-900 text-green-200' : 'bg-red-900 text-red-200'}`;
		resultDiv.textContent = message;

		setTimeout(() => {
			resultDiv.classList.add('hidden');
		}, 5000);
	}
}

async function updateProfile(): Promise<void> {
	const display_name = (document.getElementById('displayName') as HTMLInputElement).value;
	const email = (document.getElementById('newEmail') as HTMLInputElement).value;

	// Validate display name (required)
	if (!display_name || display_name.trim() === '') {
		const msg = window.languageManager?.t('validation.displayNameRequired');
		showProfileMessage(
			msg !== null ? msg : 'Display name is required',
			'error'
		);
		return;
	}

	const trimmed = display_name.trim();
	if (trimmed.length < 3 || trimmed.length > 30) {
		const msg = window.languageManager?.t('validation.displayNameLength');
		showProfileMessage(
			msg !== null ? msg : 'Display name must be 3-30 characters',
			'error'
		);
		return;
	}

	// Only allow letters, numbers, and underscores
	const displayNameRegex = /^[a-zA-Z0-9_]+$/;
	if (!displayNameRegex.test(trimmed)) {
		const msg = window.languageManager?.t('validation.displayNameInvalidChars');
		showProfileMessage(
			msg !== null ? msg : 'Display name can only contain letters, numbers, and underscores',
			'error'
		);
		return;
	}

	// Validate email if provided
	if (email && email.trim() !== '') {
		// Same validation as backend
		const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
		if (!emailRegex.test(email)) {
			const msg = window.languageManager?.t('validation.invalidEmailFormat');
			showProfileMessage(
				msg !== null ? msg : 'Invalid email format',
				'error'
			);
			return;
		}

		// Check for temporary email domains
		const tempEmailDomains = [
			'tempmail.com', 'guerrillamail.com', 'mailinator.com',
			'10minutemail.com', 'yopmail.com', 'throwaway.com'
		];
		const domain = email.split('@')[1].toLowerCase();
		if (tempEmailDomains.some(temp => domain.includes(temp))) {
			const msg = window.languageManager?.t('validation.temporaryEmailNotAllowed');
			showProfileMessage(
				msg !== null ? msg : 'Temporary email addresses are not allowed',
				'error'
			);
			return;
		}
	}

	try {
		const data = await api<any>('/api/auth/profile-data', {
			method: 'PUT',
			body: JSON.stringify({ display_name, email: email || undefined })
		});

		if (!data.success) {
			const translated = data.error ? window.languageManager?.t(data.error) : null;
			const errorMsg = translated !== null ? translated : (data.error || 'Failed to update profile');
			showProfileMessage(errorMsg, 'error');
			return;
		}

		const successMsg = window.languageManager?.t('profile.emailUpdated');
		showProfileMessage(
			successMsg !== null ? successMsg : 'Email updated successfully',
			'success'
		);

		// Clear the email input after successful update
		const emailInput = document.getElementById('newEmail') as HTMLInputElement;
		if (emailInput) {
			emailInput.value = '';
		}

		loadProfile();
	} catch (error: any) {
		if (error instanceof ServerError) {
			console.error('Server error updating email:', error);
		}
		let errorMsg: string;
		// Error message comes from error.message (standard Error property)
		if (error.message) {
			const translated = window.languageManager?.t(error.message);
			errorMsg = translated !== null ? translated : error.message;
		} else {
			const translated = window.languageManager?.t('profile.failedToUpdateEmail');
			errorMsg = translated !== null ? translated : 'Failed to update email';
		}
		showProfileMessage(errorMsg, 'error');
	}
}

async function anonymize(): Promise<void> {
	if (!confirm('Are you sure you want to anonymize your account?')) return;

	const confirmPassword = (document.getElementById('confirmPwd') as HTMLInputElement).value;

	try {
		const data = await api<any>('/api/users/gdpr/anonymize', {
			method: 'POST',
			body: JSON.stringify({ confirmPassword })
		});

		const resultDiv = document.getElementById('dangerResult');
		if (resultDiv) {
			resultDiv.classList.remove('hidden');
			resultDiv.className = 'mt-4 p-3 rounded bg-green-900 text-green-200';
			resultDiv.textContent = 'Account anonymized successfully';
		}
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error anonymizing account:', error);
		}
		const resultDiv = document.getElementById('dangerResult');
		if (resultDiv) {
			resultDiv.classList.remove('hidden');
			resultDiv.className = 'mt-4 p-3 rounded bg-red-900 text-red-200';
			resultDiv.textContent = 'Failed to anonymize account';
		}
	}
}

async function deleteAcc(): Promise<void> {
	if (!confirm('DELETE account permanently? This cannot be undone!')) return;

	const confirmPassword = (document.getElementById('confirmPwd') as HTMLInputElement).value;

	try {
		const data = await api<any>('/api/users/gdpr/delete', {
			method: 'DELETE',
			body: JSON.stringify({ confirmPassword })
		});

		const resultDiv = document.getElementById('dangerResult');
		if (resultDiv) {
			resultDiv.classList.remove('hidden');
			resultDiv.className = 'mt-4 p-3 rounded bg-green-900 text-green-200';
			resultDiv.textContent = 'Account deleted successfully';
		}

		setTimeout(() => {
			removeAuthToken();
			window.location.href = '/';
		}, 2000);
	} catch (error) {
		if (error instanceof ServerError) {
			console.error('Server error deleting account:', error);
		}
		const resultDiv = document.getElementById('dangerResult');
		if (resultDiv) {
			resultDiv.classList.remove('hidden');
			resultDiv.className = 'mt-4 p-3 rounded bg-red-900 text-red-200';
			resultDiv.textContent = 'Failed to delete account';
		}
	}
}

async function deleteAvatar(): Promise<void> {
	const msg = window.languageManager?.t('profile.confirmDeleteAvatar');
	const confirmMsg = msg !== null ? msg : 'Are you sure you want to remove your avatar?';
	if (!confirm(confirmMsg)) return;

	try {
		const token = getToken();
		if (!token) {
			const msg = window.languageManager?.t('profile.loginFirst');
			showProfileMessage(
				msg !== null ? msg : 'Please login first',
				'error'
			);
			return;
		}

		// Get current user ID from profile data
		const profileResponse = await api<any>('/api/auth/profile-data');
		if (!profileResponse.success || !profileResponse.user) {
			throw new Error('Failed to get user ID');
		}

		const userId = profileResponse.user.id;

		// Call DELETE endpoint with empty JSON body
		const data = await api<any>(`/api/database/avatar/${userId}`, {
			method: 'DELETE',
			body: JSON.stringify({})
		});

		if (!data.success) {
			throw new Error(data.error || 'Delete failed');
		}

		const msg = window.languageManager?.t('profile.avatarDeleted');
		showProfileMessage(
			msg !== null ? msg : (data.message || 'Avatar removed successfully'),
			'success'
		);

		// Reload profile to show default avatar
		setTimeout(() => {
			loadProfile();
		}, 500);
	} catch (error: any) {
		if (error instanceof ServerError) {
			console.error('Server error deleting avatar:', error);
		}
		const msg = window.languageManager?.t('profile.deleteFailed');
		showProfileMessage(
			msg !== null ? msg : (error.message || 'Failed to remove avatar'),
			'error'
		);
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

async function toggleMatchHistory(): Promise<void> {
	const matchHistorySection = document.getElementById('matchHistorySection');
	const toggleBtn = document.getElementById('toggleMatchHistoryBtn');
	
	if (!matchHistorySection || !toggleBtn) return;

	if (matchHistorySection.classList.contains('hidden')) {
		// Show match history - load it if not already loaded
		const content = matchHistorySection.querySelector('#matchHistoryContent');
		if (content && content.innerHTML.trim() === '') {
			await loadMatchHistory();
		}
		matchHistorySection.classList.remove('hidden');
		toggleBtn.setAttribute('data-i18n', 'profile.hideMatchHistory');
		toggleBtn.textContent = 'Hide Match History';
		window.languageManager?.applyTranslations();
	} else {
		// Hide match history
		matchHistorySection.classList.add('hidden');
		toggleBtn.setAttribute('data-i18n', 'profile.showMatchHistory');
		toggleBtn.textContent = '📊 View Match History & Stats';
		window.languageManager?.applyTranslations();
	}
}

async function loadMatchHistory(): Promise<void> {
	const content = document.getElementById('matchHistoryContent');
	if (!content) return;

	// Show loading state
	content.innerHTML = `
		<div class="animate-pulse">
			<div class="h-32 bg-gray-700 rounded mb-4"></div>
			<div class="h-4 bg-gray-700 rounded w-3/4 mb-2"></div>
			<div class="h-4 bg-gray-700 rounded w-1/2"></div>
		</div>
	`;

	try {
		const token = getToken();
		if (!token) {
			content.innerHTML = '<p class="text-red-400 text-center" data-i18n="auth.authenticationRequired">Authentication required</p>';
			window.languageManager?.applyTranslations();
			return;
		}

		// Fetch player profile with stats and match history using authenticated endpoint
		const response = await api<{ success: boolean; user: UserProfileData }>(`/api/database/players/me`);

		if (response.success && response.user) {
			const stats = response.user.stats;
			const matchHistory = response.user.match_history || [];

			content.innerHTML = `
				<!-- Stats Grid -->
				<div class="grid grid-cols-5 gap-3 mb-6">
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-yellow-400">${stats?.games_played || 0}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.gamesPlayed">Games</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-green-400">${stats?.wins || 0}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.wins">Wins</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-red-400">${stats?.losses || 0}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.losses">Losses</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-blue-400">${stats?.win_rate || 0}%</p>
						<p class="text-xs text-gray-400" data-i18n="profile.winRate">Win%</p>
					</div>
					<div class="bg-gray-800 rounded-lg p-3 text-center">
						<p class="text-2xl font-bold text-purple-400">${stats?.tournament_wins || 0}</p>
						<p class="text-xs text-gray-400" data-i18n="profile.tournamentWins">🏆 Tours</p>
					</div>
				</div>

				<!-- Match History -->
				<div class="mt-6">
					<h4 class="text-lg font-bold text-cyan-400 mb-3" data-i18n="profile.matchHistory">📜 Match History</h4>
					${renderMatchHistory(matchHistory)}
				</div>
			`;

			window.languageManager?.applyTranslations();
		}
	} catch (error: any) {
		if (error instanceof ServerError) {
			console.error('Server error loading match history:', error);
		}
		let isAuthError = error instanceof AuthError;
		let message = isAuthError
			? '<p class="text-red-400 text-center" data-i18n="auth.authenticationRequired">Authentication required</p>'
			: '<p class="text-red-400 text-center" data-i18n="profile.failedToLoad">Failed to load match history</p>';
		content.innerHTML = message;
		window.languageManager?.applyTranslations();
	}
}

(window as any).updateProfile = updateProfile;
(window as any).anonymize = anonymize;
(window as any).deleteAcc = deleteAcc;
(window as any).uploadAvatar = uploadAvatar;
(window as any).deleteAvatar = deleteAvatar;
(window as any).toggleMatchHistory = toggleMatchHistory;