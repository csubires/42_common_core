import {
	findUserById,
	updateUser,
	deleteUser
 } from './user.js';

import TwoFactorService from './twoFactor.js';

class GdprService {
	async getUserDataSummary(userId) {
		try {
			const user = await findUserById(userId);
			if (!user) return null;
			return {
				profileInfo: {
					hasUsername: !!user.username,
					hasEmail: !!user.email,
					hasAvatar: !!user.avatar,
					twoFactorEnabled: Boolean(user.two_factor_enabled)
				},
				activity: {
					accountCreated: user.created_at || new Date().toISOString(),
					lastUpdated: user.updated_at || new Date().toISOString()
				},
				consent: {
					marketingEmails: user.consent_marketing === 1,
					analytics: user.consent_analytics === 1,
					dataProcessing: user.consent_data_processing === 1,
					updatedAt: user.consent_updated_at
				}
			};
		} catch (error) {
			console.error('Error in getUserDataSummary:', error);
			return null;
		}
	}

	async anonymizeUserData(userId) {
		try {
			const anonymizedData = {
				username: `anonymous_${this.generateRandomId()}`,
				avatar: null,
				is_anonymized: 1,
				two_factor_enabled: 0,
				two_factor_secret: null
			};
			const response = await updateUser(userId, anonymizedData);
			return response !== undefined;
		} catch (error) {
			console.error('Error in anonymizeUserData:', error);
			throw error;
		}
	}

	async exportUserData(userId) {
		try {
			const user = await findUserById(userId);
			if (!user) return null;
			return {
				exportInfo: {
					generatedAt: new Date().toISOString(),
					format: 'GDPR-COMPLIANT'
				},
				profile: user.toSafeJSON()
			};
		} catch (error) {
			console.error('Error in exportUserData:', error);
			throw error;
		}
	}

	async updateUserConsent(userId, consentData) {
		try {
			const response = await updateUser(userId, {
				consent_marketing: consentData.marketingEmails ? 1 : 0,
				consent_analytics: consentData.analytics ? 1 : 0,
				consent_data_processing: consentData.dataProcessing ? 1 : 0,
				consent_updated_at: consentData.consentUpdatedAt
			});
			return response !== undefined;
		} catch (error) {
			console.error('Error in updateUserConsent:', error);
			throw error;
		}
	}

	async deleteUserAccount(userId) {
		try {
			await TwoFactorService.saveBackupCodes(userId, []);
			const response = await deleteUser(userId);
			return response !== undefined;
		} catch (error) {
			console.error('Error in deleteUserAccount:', error);
			throw error;
		}
	}

	generateRandomId() {
		return Math.random().toString(36).substr(2, 9);
	}
}

const gdprServiceInstance = new GdprService();

export const anonymizeUserData = (userId) => gdprServiceInstance.anonymizeUserData(userId);
export const deleteUserAccount = (userId) => gdprServiceInstance.deleteUserAccount(userId);
export const updateUserConsent = (userId, consentData) => gdprServiceInstance.updateUserConsent(userId, consentData);
export const exportUserData = (userId) => gdprServiceInstance.exportUserData(userId);
export const getUserDataSummary = (userId) => gdprServiceInstance.getUserDataSummary(userId);

export default gdprServiceInstance;
