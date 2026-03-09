const API_BASE = '';

// Custom error classes for different HTTP status codes
export class ValidationError extends Error {
	status: number = 422;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'ValidationError';
		this.code = code;
	}
}

export class ConflictError extends Error {
	status: number = 409;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'ConflictError';
		this.code = code;
	}
}

export class AuthError extends Error {
	status: number = 401;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'AuthError';
		this.code = code;
	}
}

export class ForbiddenError extends Error {
	status: number = 403;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'ForbiddenError';
		this.code = code;
	}
}

export class NotFoundError extends Error {
	status: number = 404;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'NotFoundError';
		this.code = code;
	}
}

export class ServerError extends Error {
	status: number = 500;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'ServerError';
		this.code = code;
	}
}

export class BadGatewayError extends Error {
	status: number = 502;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'BadGatewayError';
		this.code = code;
	}
}

export class ServiceUnavailableError extends Error {
	status: number = 503;
	code?: string;

	constructor(message: string, code?: string) {
		super(message);
		this.name = 'ServiceUnavailableError';
		this.code = code;
	}
}

// Fallback in-memory storage for private browsing mode
let memoryStorage: { [key: string]: string } = {};

// Check if storage is available
function isStorageAvailable(type: 'localStorage' | 'sessionStorage'): boolean {
	try {
		const storage = window[type];
		const test = '__storage_test__';
		storage.setItem(test, test);
		storage.removeItem(test);
		return true;
	} catch (e) {
		return false;
	}
}

// Use sessionStorage if available, fallback to memory
const useSessionStorage = isStorageAvailable('sessionStorage');

function getToken(): string | null {
	if (useSessionStorage) {
		return sessionStorage.getItem('auth_token');
	}
	return memoryStorage['auth_token'] || null;
}

function setToken(token: string): void {
	if (useSessionStorage) {
		sessionStorage.setItem('auth_token', token);
	} else {
		memoryStorage['auth_token'] = token;
	}
}

function clearToken(): void {
	if (useSessionStorage) {
		sessionStorage.removeItem('auth_token');
	} else {
		delete memoryStorage['auth_token'];
	}
}

function removeAuthToken(): void {
	clearToken();
}

function getHeaders(): HeadersInit {
	const headers: Record<string, string> = {};

	const token = getToken();
	if (token) {
		headers['Authorization'] = `Bearer ${token}`;
	}

	return headers;
}

async function api<T>(url: string, options: RequestInit = {}): Promise<T> {
	const isFormData = options.body instanceof FormData;

	const response = await fetch(`${API_BASE}${url}`, {
		...options,
		headers: {
			...(isFormData ? {} : { 'Content-Type': 'application/json' }),
			...getHeaders(),
			...options.headers
		}
	});

	let data: any = null;
	try {
		data = await response.json();
	} catch {
		data = {};
	}

	// Handle authentication errors (token expired/invalid)
	if (response.status === 401 && data?.error === 'auth.invalidToken') {
		removeAuthToken();

		window.dispatchEvent(
			new CustomEvent('auth-expired', {
				detail: 'Your session has expired. Please login again.'
			})
		);

		throw new AuthError(data?.error || 'auth.invalidToken', data?.code);
	}

	// Throw specific error types based on status code
	if (!response.ok) {
		const errorMessage = data?.error || 'common.requestFailed';
		const errorCode = data?.code;

		switch (response.status) {
			case 422:
				throw new ValidationError(errorMessage, errorCode);
			case 409:
				throw new ConflictError(errorMessage, errorCode);
			case 401:
				throw new AuthError(errorMessage, errorCode);
			case 403:
				throw new ForbiddenError(errorMessage, errorCode);
			case 404:
				throw new NotFoundError(errorMessage, errorCode);
			case 500:
			case 502:
			case 503:
				throw new ServerError(errorMessage, errorCode);
			default:
				throw new Error(errorMessage);
		}
	}

	return data as T;
}

export { api, getToken, setToken, clearToken, removeAuthToken };