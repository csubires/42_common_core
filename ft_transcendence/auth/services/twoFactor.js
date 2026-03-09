import speakeasy from 'speakeasy';
import QRCode from 'qrcode';
import bcrypt from 'bcrypt';

class TwoFactorService {
	generateSecret(user) {
		const issuer = 'SecureApp';
		const accountName = (user.email || user.username).replace(/[^a-zA-Z0-9@.]/g, '');
		const secret = speakeasy.generateSecret({
			name: `${issuer}:${accountName}`,
			issuer: issuer,
			length: 20
		});
		return {
			secret: secret.base32,
			otpauth_url: secret.otpauth_url
		};
	}

	async generateQRCode(otpauthUrl) {
		try {
			return await QRCode.toDataURL(otpauthUrl);
		} catch (error) {
			throw new Error('QR code generation failed');
		}
	}

	verifyToken(secret, token, window = 2) {
		try {
			if (!secret || !token) {
				return false;
			}
			return speakeasy.totp.verify({
				secret: secret,
				encoding: 'base32',
				token: token,
				window: window,
				step: 30
			});
		} catch (error) {
			return false;
		}
	}

	generateBackupCodes(count = 8) {
		const codes = [];
		for (let i = 0; i < count; i++) {
			const part1 = Math.floor(10000 + Math.random() * 90000).toString();
			const part2 = Math.floor(100 + Math.random() * 900).toString();
			codes.push(`${part1}-${part2}`);
		}
		return codes;
	}

	async saveBackupCodes(userId, codes) {
		try {
			const hashedCodes = await Promise.all(
				codes.map(async (code) => {
					return await bcrypt.hash(code, 10);
				})
			);

			const response = await fetch(
				`http://database:3003/database/backup-codes`, {
				method: 'POST',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify({ user_id: userId, codes: hashedCodes })
			});

			const data = await response.json();
			if (response.status === 404) {
				return null;
			}

			return data.success;
		} catch (error) {
			return false;
		}
	}

	async verifyBackupCode(userId, code) {
		try {

			const response = await fetch(
				`http://database:3003/database/backup-codes/user/${userId}`,
				{ method: 'GET' }
			);

			const data = await response.json();
			if (response.status === 404) {
				return null;
			}


			if (!data.success || !data.codes) {
				return false;
			}

			const codes = data.codes;

			for (const codeRecord of codes) {
				if (codeRecord.used === 0) {
					const isValid = await bcrypt.compare(code, codeRecord.code_hash);
					if (isValid) {

						const response = await fetch(
							`http://database:3003/database/backup-codes/${codeRecord.id}/use`, {
							method: 'PUT'
						});


						if (response.status === 404) {
							return null;
						}
						return true;
					}
				}
			}
			return false;
		} catch (error) {
			return false;
		}
	}

	async getRemainingBackupCodes(userId) {
		try {
			const response = await fetch(
				`http://database:3003/database/backup-codes/user/${userId}`,
				{ method: 'GET' }
			);

			const data = await response.json();
			if (response.status === 404) {
				return null;
			}
			if (data.success && data.codes) {
				return data.codes.filter(code => code.used === 0).length;
			}
			return 0;
		} catch (error) {
			return 0;
		}
	}

	async clearBackupCodes(userId) {
		try {
			const response = await saveBackupCodes(userId, []);
			return response.data.success;
		} catch (error) {
			return false;
		}
	}
}



export default new TwoFactorService();
