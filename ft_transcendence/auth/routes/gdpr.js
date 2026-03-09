import gdprService from '../services/gdpr.js';
import { findUserById } from '../services/user.js';
import jwtService from '../services/jwt.js';

export default async function gdprRoutes(fastify, options) {

	async function authenticateUser(request, reply) {
		const authHeader = request.headers.authorization;

		if (!authHeader?.startsWith('Bearer ')) {
			return reply.status(401).send({
				success: false,
				error: 'messages.authError'
			});
		}

		const token = authHeader.substring(7);
		const decoded = await jwtService.verifyToken(token);

		if (!decoded?.id) {
			return reply.status(401).send({
				success: false,
				error: 'auth.invalidToken'
			});
		}

		request.user = decoded;
	}

	fastify.get('/user-data', {
		preHandler: authenticateUser
	}, async (request, reply) => {
		try {
			const user = await findUserById(request.user.id);
			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}

			const dataSummary = await gdprService.getUserDataSummary(user.id);

			return {
				success: true,
				data: {
					profile: user.toSafeJSON(),
					dataSummary
				}
			};
		} catch (error) {
			fastify.log.error('GDPR user-data error:', error);
			return reply.status(503).send({
				success: false,
				error: 'common.internalError'
			});
		}
	});

	fastify.get('/user-consent', {
		preHandler: authenticateUser
	}, async (request, reply) => {
		try {
			const user = await findUserById(request.user.id);
			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}

			return {
				success: true,
				consent: {
					dataProcessing: user.consent_data_processing === 1,
					marketingEmails: user.consent_marketing === 1,
					analytics: user.consent_analytics === 1
				}
			};
		} catch (error) {
			return reply.status(503).send({
				success: false,
				error: 'common.internalError'
			});
		}
	});

	fastify.post('/anonymize', {
		preHandler: authenticateUser
	}, async (request, reply) => {
		try {
			// Validate body - only _dummy field allowed (workaround for empty POST)
			if (request.body) {
				const allowedFields = ['_dummy'];
				const receivedFields = Object.keys(request.body);
				const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
				if (unexpectedFields.length > 0) {
					return reply.status(422).send({
						success: false,
						error: 'validation.unexpectedFields',
						code: 'UNEXPECTED_FIELDS'
					});
				}
				delete request.body._dummy;
			}

			const user = await findUserById(request.user.id);
			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}
			const success = await gdprService.anonymizeUserData(user.id);
			if (!success) {
				return reply.status(503).send({
					success: false,
					error: 'gdpr.anonymizationError',
					code: 'ANONYMIZATION_FAILED'
				});
			}

			return {
				success: true,
				message: 'messages.dataAnonymized'
			};
		} catch (error) {
			return reply.status(503).send({
				success: false,
				error: `gdpr.anonymizationError ${request.user.id}`,
				code: 'INTERNAL_ERROR'
			});
		}
	});

	fastify.post('/export-data', {
		preHandler: authenticateUser
	}, async (request, reply) => {
		try {
			// Validate body - only _dummy field allowed (workaround for empty POST)
			if (request.body) {
				const allowedFields = ['_dummy'];
				const receivedFields = Object.keys(request.body);
				const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
				if (unexpectedFields.length > 0) {
					return reply.status(422).send({
						success: false,
						error: 'validation.unexpectedFields',
						code: 'UNEXPECTED_FIELDS'
					});
				}
				delete request.body._dummy;
			}

			const user = await findUserById(request.user.id);
			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}

			const exportData = await gdprService.exportUserData(user.id);
			if (!exportData) {
				return reply.status(503).send({
					success: false,
					error: 'gdpr.exportError',
					code: 'EXPORT_FAILED'
				});
			}

			return {
				success: true,
				data: exportData,
				format: 'json',
				generatedAt: new Date().toISOString()
			};
		} catch (error) {
			return reply.status(503).send({
				success: false,
				error: 'gdpr.exportError',
				code: 'INTERNAL_ERROR'
			});
		}
	});

	fastify.post('/delete-account', {
		preHandler: authenticateUser
	}, async (request, reply) => {
		try {
			const { confirmation } = request.body;

			// Validate body fields
			const allowedFields = ['confirmation'];
			const receivedFields = Object.keys(request.body || {});
			const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
			if (unexpectedFields.length > 0) {
				return reply.status(422).send({
					success: false,
					error: 'validation.unexpectedFields',
					code: 'UNEXPECTED_FIELDS'
				});
			}

			// Validate confirmation field
			if (!confirmation) {
				return reply.status(422).send({
					success: false,
					error: 'gdpr.confirmationRequired',
					code: 'MISSING_CONFIRMATION'
				});
			}

			if (typeof confirmation !== 'string') {
				return reply.status(422).send({
					success: false,
					error: 'validation.invalidInput',
					code: 'INVALID_TYPE'
				});
			}

			const user = await findUserById(request.user.id);

			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound'
				});
			}

			// Accept confirmation in English, Spanish, or Japanese
			const validConfirmations = [
				'DELETE MY ACCOUNT',      // English
				'ELIMINAR MI CUENTA',     // Spanish
				'アカウントを削除'         // Japanese
			];
			if (!validConfirmations.includes(confirmation)) {
				return reply.status(422).send({
					success: false,
					error: 'gdpr.invalidConfirmation',
					code: 'INVALID_CONFIRMATION'
				});
			}

			const success = await gdprService.deleteUserAccount(user.id);
			if (!success) {
				return reply.status(503).send({
					success: false,
					error: 'gdpr.deletionError',
					code: 'DELETION_FAILED'
				});
			}

			return {
				success: true,
				message: 'messages.accountDeleted'
			};
		} catch (error) {
			return reply.status(503).send({
				success: false,
				error: 'gdpr.deletionError',
				code: 'INTERNAL_ERROR'
			});
		}
	});

	fastify.post('/update-consent', {
		preHandler: authenticateUser
	}, async (request, reply) => {
		try {
			const { marketingEmails, analytics, dataProcessing } = request.body;

			// Validate body fields
			const allowedFields = ['marketingEmails', 'analytics', 'dataProcessing'];
			const receivedFields = Object.keys(request.body || {});
			const unexpectedFields = receivedFields.filter(f => !allowedFields.includes(f));
			if (unexpectedFields.length > 0) {
				return reply.status(422).send({
					success: false,
					error: 'validation.unexpectedFields',
					code: 'UNEXPECTED_FIELDS'
				});
			}

			// Validate types (should be boolean or convertible to boolean)
			const validateBooleanField = (field, value) => {
				if (value !== undefined && typeof value !== 'boolean' && typeof value !== 'number' && typeof value !== 'string') {
					return false;
				}
				return true;
			};

			if (!validateBooleanField('marketingEmails', marketingEmails)) {
				return reply.status(422).send({
					success: false,
					error: 'validation.invalidInput',
					code: 'INVALID_TYPE'
				});
			}

			if (!validateBooleanField('analytics', analytics)) {
				return reply.status(422).send({
					success: false,
					error: 'validation.invalidInput',
					code: 'INVALID_TYPE'
				});
			}

			if (!validateBooleanField('dataProcessing', dataProcessing)) {
				return reply.status(422).send({
					success: false,
					error: 'validation.invalidInput',
					code: 'INVALID_TYPE'
				});
			}

			const user = await findUserById(request.user.id);

			if (!user) {
				return reply.status(404).send({
					success: false,
					error: 'messages.userNotFound',
					code: 'USER_NOT_FOUND'
				});
			}

			const success = await gdprService.updateUserConsent(user.id, {
				marketingEmails: Boolean(marketingEmails),
				analytics: Boolean(analytics),
				dataProcessing: Boolean(dataProcessing),
				consentUpdatedAt: new Date().toISOString()
			});

			if (!success) {
				return reply.status(503).send({
					success: false,
					error: 'gdpr.consentUpdateError',
					code: 'CONSENT_UPDATE_ERROR'
				});
			}

			return {
				success: true,
				message: 'messages.preferencesUpdated'
			};
		} catch (error) {
			return reply.status(503).send({
				success: false,
				error: 'gdpr.consentUpdateError',
				code: 'INTERNAL_ERROR'
			});
		}
	});
}
