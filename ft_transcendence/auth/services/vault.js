const VAULT_BASE = 'http://vault:8200/v1';

function sleep(ms) {
	return new Promise((r) => setTimeout(r, ms));
}

async function fetchWithTimeout(url, options = {}, timeout = 5000) {
	const controller = new AbortController();
	const id = setTimeout(() => controller.abort(), timeout);

	try {
		const res = await fetch(url, {
			...options,
			signal: controller.signal,
		});

		if (!res.ok) {
			const text = await res.text();
			throw new Error(`Vault HTTP ${res.status}: ${text}`);
		}

		return res.json();
	} finally {
		clearTimeout(id);
	}
}

async function waitForVault(retries = 10, delay = 500) {
	for (let i = 0; i < retries; i++) {
		try {
			await fetchWithTimeout(`${VAULT_BASE}/sys/health`);
			return true;
		} catch {
			await sleep(delay);
		}
	}
	throw new Error('Vault not reachable');
}

class VaultService {
	constructor() {
		this.baseURL = VAULT_BASE;
		this.headers = {
			'X-Vault-Token': 'root',
			'Content-Type': 'application/json',
		};
	}

	async init() {
		await waitForVault();
	}

	async _request(path, options = {}) {
		return fetchWithTimeout(`${this.baseURL}/${path}`, {
			method: options.method || 'GET',
			headers: this.headers,
			body: options.body ? JSON.stringify(options.body) : undefined,
		});
	}

	async getSecret(path) {
		const data = await this._request(`secret/data/${path}`);
		return data?.data?.data ?? null;
	}

	async getJWTSecret() {
		const app = await this.getSecret('jwt/config');
		return app?.jwt_secret ?? null;
	}

	async getSessionSecret() {
		const session = await this.getSecret('session/config');
		return session?.secret ?? null;
	}

	async getOAuthSecret(service) {
		return this.getSecret(`oauth/${service}`);
	}
}

const vaultService = new VaultService();
await vaultService.init();

export default vaultService;
