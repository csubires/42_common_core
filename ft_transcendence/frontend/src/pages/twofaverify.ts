import { verify2FALogin } from '../twofa.js';
import { navigate } from '../router.js';
import { setToken, ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError, api } from '../api.js';
import { updateAuthBtn } from '../auth.js';

export function renderTwoFAVerify(): string {
  setTimeout(initVerify, 100);
  return `
    <div class="max-w-md mx-auto">
      <div class="card text-center">
        <div class="text-6xl mb-6">🔐</div>
        <h2 class="text-3xl font-bold mb-4" data-i18n="2fa.verificationRequired">Two-Factor Authentication</h2>
        
        <!-- TOTP Mode -->
        <div id="totpMode">
          <p class="text-gray-400 mb-6" data-i18n="2fa.enterCodePrompt">Enter the 6-digit code from your authenticator app</p>

          <form id="verify2FAForm">
            <input type="text" id="tokenInput" maxlength="6" placeholder="000000"
                   class="input text-center text-3xl font-mono tracking-widest mb-4"
                   data-i18n-placeholder="2fa.sixDigitCode" autocomplete="off">
            <button type="submit" class="btn btn-blue w-full mb-4" data-i18n="2fa.verify">
              Verify
            </button>
          </form>

          <button id="useBackupCodeBtn" class="text-sm text-yellow-400 hover:text-yellow-300 underline" data-i18n="2fa.lostDevice">
            Lost your device? Use a backup code
          </button>
        </div>

        <!-- Backup Code Mode -->
        <div id="backupMode" class="hidden">
          <p class="text-gray-400 mb-6" data-i18n="2fa.enterBackupCodePrompt">Enter one of your backup recovery codes</p>

          <form id="verifyBackupForm">
            <input type="text" id="backupCodeInput" placeholder="12345-678"
                   class="input text-center text-xl font-mono tracking-wide mb-4"
                   data-i18n-placeholder="2fa.backupCodePlaceholder" autocomplete="off">
            <button type="submit" class="btn btn-yellow w-full mb-4" data-i18n="2fa.verifyBackupCodeBtn">
              Verify Backup Code
            </button>
          </form>

          <button id="useTOTPBtn" class="text-sm text-blue-400 hover:text-blue-300 underline" data-i18n="2fa.backToAuthenticator">
            ← Back to authenticator code
          </button>
        </div>

        <div id="verifyMessage" class="hidden mt-4"></div>
      </div>
    </div>
  `;
}

function initVerify(): void {
  const form = document.getElementById('verify2FAForm');
  const backupForm = document.getElementById('verifyBackupForm');
  const tokenInput = document.getElementById('tokenInput') as HTMLInputElement;
  const backupCodeInput = document.getElementById('backupCodeInput') as HTMLInputElement;
  const useBackupBtn = document.getElementById('useBackupCodeBtn');
  const useTOTPBtn = document.getElementById('useTOTPBtn');
  const totpMode = document.getElementById('totpMode');
  const backupMode = document.getElementById('backupMode');

  // TOTP form submission
  if (form) {
    form.addEventListener('submit', async (e) => {
      e.preventDefault();
      await verifyToken();
    });
  }

  // Backup code form submission
  if (backupForm) {
    backupForm.addEventListener('submit', async (e) => {
      e.preventDefault();
      await verifyBackupCode();
    });
  }

  // Switch to backup code mode
  if (useBackupBtn && totpMode && backupMode) {
    useBackupBtn.addEventListener('click', () => {
      totpMode.classList.add('hidden');
      backupMode.classList.remove('hidden');
      backupCodeInput?.focus();
    });
  }

  // Switch back to TOTP mode
  if (useTOTPBtn && totpMode && backupMode) {
    useTOTPBtn.addEventListener('click', () => {
      backupMode.classList.add('hidden');
      totpMode.classList.remove('hidden');
      tokenInput?.focus();
    });
  }

  // Only allow digits in TOTP input
  if (tokenInput) {
    tokenInput.focus();
    tokenInput.addEventListener('input', (e) => {
      const input = e.target as HTMLInputElement;
      input.value = input.value.replace(/\D/g, '');
    });
  }

  window.languageManager?.applyTranslations();
}

async function verifyToken(): Promise<void> {
  const tokenInput = document.getElementById('tokenInput') as HTMLInputElement;
  const token = tokenInput?.value.trim();

  if (!token || !/^\d{6}$/.test(token)) {
    showMessage(window.languageManager?.t('2fa.pleaseEnterValidCode') || 'Please enter a valid 6-digit code', 'error');
    return;
  }

  const tempToken = localStorage.getItem('temp_2fa_token');
  if (!tempToken) {
    showMessage(window.languageManager?.t('2fa.sessionExpired') || 'Session expired. Please login again.', 'error');
    setTimeout(() => navigate('auth'), 2000);
    return;
  }

  try {
    showMessage(window.languageManager?.t('2fa.verifying') || 'Verifying...', 'info');
    const result = await verify2FALogin(token, tempToken);

    if (result.success && result.token) {
      localStorage.removeItem('temp_2fa_token');
      setToken(result.token);
      showMessage(window.languageManager?.t('2fa.verificationSuccess') || 'Verification successful! Redirecting...', 'success');
      updateAuthBtn();
      setTimeout(() => {
        navigate('profile');
      }, 1000);
    } else {
      showMessage(window.languageManager?.t('2fa.invalidCode') || 'Invalid code. Please try again.', 'error');
      tokenInput.value = '';
      tokenInput.focus();
    }
  } catch (error) {
    if (error instanceof ServerError) {
      console.error('Server error during 2FA verification:', error);
    }
    showMessage(window.languageManager?.t('2fa.connectionError') || 'Connection error. Please try again.', 'error');
  }
}

async function verifyBackupCode(): Promise<void> {
  const backupCodeInput = document.getElementById('backupCodeInput') as HTMLInputElement;
  const backupCode = backupCodeInput?.value.trim();

  if (!backupCode || backupCode.length < 5) {
    showMessage(window.languageManager?.t('2fa.pleaseEnterValidBackupCode') || 'Please enter a valid backup code', 'error');
    return;
  }

  const tempToken = localStorage.getItem('temp_2fa_token');
  if (!tempToken) {
    showMessage(window.languageManager?.t('2fa.sessionExpired') || 'Session expired. Please login again.', 'error');
    setTimeout(() => navigate('auth'), 2000);
    return;
  }

  try {
    showMessage(window.languageManager?.t('2fa.verifyingBackupCode') || 'Verifying backup code...', 'info');
    const result = await api<any>('/api/2fa/verify-backup-code', {
      method: 'POST',
      body: JSON.stringify({ backupCode, tempToken })
    });

    if (result.success && result.token) {
      localStorage.removeItem('temp_2fa_token');
      setToken(result.token);
      showMessage(window.languageManager?.t('2fa.backupCodeVerified') || 'Backup code verified! This code has been used. Redirecting...', 'success');
      updateAuthBtn();
      setTimeout(() => {
        navigate('profile');
      }, 1000);
    } else {
      showMessage(result.error || window.languageManager?.t('2fa.invalidBackupCode') || 'Invalid backup code. Please try again.', 'error');
      backupCodeInput.value = '';
      backupCodeInput.focus();
    }
  } catch (error) {
    if (error instanceof ServerError) {
      console.error('Server error during backup code verification:', error);
    }
    showMessage(window.languageManager?.t('2fa.invalidBackupCodeOrConnection') || 'Invalid backup code or connection error. Please try again.', 'error');
  }
}

function showMessage(message: string, type: 'success' | 'error' | 'info'): void {
  const messageDiv = document.getElementById('verifyMessage');
  if (!messageDiv) return;

  const colors = {
    success: 'bg-green-900 text-green-200 border-green-600',
    error: 'bg-red-900 text-red-200 border-red-600',
    info: 'bg-blue-900 text-blue-200 border-blue-600'
  };

  messageDiv.className = `p-3 rounded border ${colors[type]}`;
  messageDiv.textContent = message;
  messageDiv.classList.remove('hidden');
}
