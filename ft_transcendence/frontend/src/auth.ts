import { api, setToken, clearToken, getToken, ValidationError, ConflictError, AuthError, ServerError } from './api.js';
import { navigate } from './router.js';
import { clearUserCache } from './gameService.js';

// Heartbeat interval (in milliseconds) - 60 seconds
const HEARTBEAT_INTERVAL = 60000;
let heartbeatTimer: number | null = null;

export function initAuth(): void {
	updateAuthBtn();
	checkOAuthError();
	handleOAuthRedirect();
	startHeartbeat();
}

function handleOAuthRedirect() {
  const params = new URLSearchParams(window.location.search);
  const token = params.get('token');
  if (token) {
    setToken(token);
    window.history.replaceState({}, document.title, window.location.pathname);
    window.location.href = '/';
  }
}

export function checkOAuthError(): void {
	const urlParams = new URLSearchParams(window.location.search);
	const error = urlParams.get('error');
	const message = urlParams.get('message');
	if (error === 'oauth_not_configured') {
		showResult('loginResult', 'auth.oauthNotConfigured', true);
	}
}

export function updateAuthBtn(): void {
	const btn = document.getElementById('authBtn');
	if (!btn) return;

	const token = getToken();
	if (token) {
		btn.setAttribute('data-i18n', 'common.logout');
		btn.textContent = window.languageManager?.t('common.logout') || 'Logout';
		btn.onclick = logout;
	} else {
		btn.setAttribute('data-i18n', 'navBar.login');
		btn.textContent = window.languageManager?.t('navBar.login') || 'Login';
		btn.onclick = () => navigate('auth');
	}
}

export async function login(): Promise<void> {
	const email = (document.getElementById('loginEmail') as HTMLInputElement).value;
	const password = (document.getElementById('loginPassword') as HTMLInputElement).value;

	try {
		const data = await api<any>('/api/auth/login', {
			method: 'POST',
			body: JSON.stringify({ email, password })
		});

		if (data.requires2FA) {
			localStorage.setItem('temp_2fa_token', data.tempToken);
			navigate('twofaverify');
			return;
		}

		setToken(data.token);
		updateAuthBtn();
		startHeartbeat(); // Start heartbeat after successful login
		navigate('profile');
	} catch (error: any) {
		// Validation errors (422) and auth errors (401) should show user message
		// No console.error since these are expected user input errors
		if (error instanceof ValidationError || error instanceof AuthError) {
			showResult('loginResult', error.message, true);
		} else if (error instanceof ServerError) {
			console.error('Login server error:', error);
			showResult('loginResult', 'common.internalError', true);
		} else {
			showResult('loginResult', error.message, true);
		}
	}
}

export async function register(): Promise<void> {
	const username = (document.getElementById('regUsername') as HTMLInputElement).value;
	const display_name = (document.getElementById('regUsername') as HTMLInputElement).value;
	const email = (document.getElementById('regEmail') as HTMLInputElement).value;
	const password = (document.getElementById('regPassword') as HTMLInputElement).value;
	const termsAccepted = (document.getElementById('termsAccepted') as HTMLInputElement)?.checked;

	// Validate terms acceptance
	if (!termsAccepted) {
		showResult('registerResult', 'auth.termsAcceptanceRequired', true);
		return;
	}

	try {
		const data = await api<any>('/api/auth/register', {
			method: 'POST',
			body: JSON.stringify({ username, display_name, email, password })
		});

		setToken(data.token);
		updateAuthBtn();
		startHeartbeat(); // Start heartbeat after successful registration
		navigate('profile');
		showResult('registerResult', 'messages.registrationSuccess', false);
	} catch (error: any) {
		// Validation errors (422) and conflicts (409) should show user message
		// No console.error for validation/conflict errors
		if (error instanceof ValidationError) {
			showResult('registerResult', error.message, true);
		} else if (error instanceof ConflictError) {
			// Email/username already exists
			showResult('registerResult', error.message, true);
		} else if (error instanceof ServerError) {
			console.error('Registration server error:', error);
			showResult('registerResult', 'common.internalError', true);
		} else {
			showResult('registerResult', error.message, true);
		}
	}
}

export async function logout(): Promise<void> {
	// Call backend logout endpoint to set user offline
	await api('/api/database/logout', {
		method: 'POST',
		body: JSON.stringify({})
	}).catch(() => {
		// Ignore errors, we're logging out anyway
	});

	stopHeartbeat(); // Stop heartbeat
	clearToken();
	clearUserCache();
	updateAuthBtn();
	navigate('home');
}

// Heartbeat function to keep user online
async function sendHeartbeat(): Promise<void> {
	const token = getToken();
	if (!token) {
		stopHeartbeat();
		return;
	}

	try {
		await api('/api/database/heartbeat', {
			method: 'POST',
			body: JSON.stringify({}) // <-- send an empty object
		});
	} catch (error) {
		// Don't log validation/auth errors to console - heartbeat failures are expected
		if (error instanceof AuthError) {
			// Token invalid - stop heartbeat and logout
			stopHeartbeat();
			clearToken();
			updateAuthBtn();
		} else if (error instanceof ServerError) {
			console.error('Heartbeat server error:', error);
		}
		// Silently ignore other errors (network issues, etc.)
	}
}

// Start periodic heartbeat
function startHeartbeat(): void {
	const token = getToken();
	if (!token) return;

	// Clear any existing heartbeat
	stopHeartbeat();

	// Send initial heartbeat
	sendHeartbeat();

	// Set up periodic heartbeat
	heartbeatTimer = window.setInterval(() => {
		sendHeartbeat();
	}, HEARTBEAT_INTERVAL);
}

// Stop heartbeat
function stopHeartbeat(): void {
	if (heartbeatTimer !== null) {
		clearInterval(heartbeatTimer);
		heartbeatTimer = null;
	}
}


export function showGlobalMessage(
	message: string,
	type: 'success' | 'error' = 'error',
	duration = 2500
): void {
	let container = document.getElementById('globalMessage');

	if (!container) {
		container = document.createElement('div');
		container.id = 'globalMessage';
		container.className =
			'fixed top-5 left-1/2 -translate-x-1/2 z-50 px-4 py-3 rounded text-sm shadow-lg transition-opacity';

		document.body.appendChild(container);
	}

	container.className =
		`fixed top-50 left-1/2 -translate-x-1/2 z-50 px-4 py-3 rounded text-sm shadow-lg ${type === 'error'
			? 'bg-red-900 text-red-200'
			: 'bg-green-900 text-green-200'
		}`;

	container.textContent = message;
	container.style.opacity = '1';

	setTimeout(() => {
		container!.style.opacity = '0';
		container!.style.display = 'none';
	}, duration);
}



function showResult(id: string, message: string, isError: boolean): void {
	const el = document.getElementById(id);
	if (!el) return;
	el.classList.remove('hidden', 'success', 'error');
	el.classList.add('result', isError ? 'error' : 'success');
	el.innerHTML = `<span data-i18n="${message}"></span>`;
	window.languageManager?.applyTranslations();

	if (isError) {
		setTimeout(() => {
			el.classList.add('hidden');
		}, 5000);
	}
}



(window as any).login = login;
(window as any).register = register;
(window as any).logout = logout;
(window as any).updateAuthBtn = updateAuthBtn;
(window as any).showGlobalMessage = showGlobalMessage;