import fs from 'fs/promises';
import path from 'path';
import { fileURLToPath } from 'url';
import sharp from 'sharp';
import db from '../config/sqlite.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Path to media volume
const AVATARS_DIR = path.join(__dirname, '../../media/avatars');

export default async function avatarRoutes(fastify, options) {
	// Ensure avatars directory exists
	await fs.mkdir(AVATARS_DIR, { recursive: true });

	// POST /database/avatar/upload - Upload avatar
	fastify.post('/avatar/upload', async (request, reply) => {
		
		try {
			// Get user ID from JWT (set by gateway)
			const userId = request.headers['x-user-id'];
			
			if (!userId) {
				return reply.status(401).send({
					success: false,
					error: 'auth.authenticationRequired',
					code: 'AUTH_REQUIRED'
				});
			}

			
			// Get the uploaded file
			const data = await request.file();
			
			if (!data) {
				return reply.status(422).send({
					success: false,
					error: 'No file uploaded',
					code: 'NO_FILE'
				});
			}

			// Validate file type
			const mimeType = data.mimetype;
			
			if (mimeType !== 'image/jpeg' && mimeType !== 'image/jpg') {
				return reply.status(422).send({
					success: false,
					error: 'Only JPG/JPEG files are allowed',
					code: 'INVALID_FILE_TYPE'
				});
			}

			// Path where we'll save the avatar
			const avatarPath = path.join(AVATARS_DIR, `${userId}.jpg`);

			const buffer = await data.toBuffer();

			// Process image with sharp: resize to 200x200 and save as JPG
			await sharp(buffer)
				.resize(200, 200, {
					fit: 'cover',
					position: 'center'
				})
				.jpeg({ quality: 90 })
				.toFile(avatarPath);


			// Update database with avatar path
			const avatarUrl = `/api/database/avatar/${userId}`;
			
			await db.run(
				'UPDATE users SET avatar = ? WHERE id = ?',
				[avatarUrl, userId]
			);

			return reply.send({
				success: true,
				message: 'Avatar uploaded successfully',
				avatar: avatarUrl
			});

		} catch (error) {
			console.error('❌ Database: Avatar upload error:', error);
			console.error('❌ Database: Error stack:', error.stack);
			fastify.log.error('Avatar upload error:', error);
			return reply.status(503).send({
				success: false,
				error: 'Failed to upload avatar: ' + error.message,
				code: 'DB_ERROR'
			});
		}
	});

	// GET /database/avatar/:userId - Retrieve avatar
	fastify.get('/avatar/:userId', async (request, reply) => {
		try {
			const { userId } = request.params;

			// Path to user's avatar
			const avatarPath = path.join(AVATARS_DIR, `${userId}.jpg`);

			// Check if avatar exists
			try {
				await fs.access(avatarPath);
				// Avatar exists, send it
				const fileStream = await fs.readFile(avatarPath);
				return reply
					.type('image/jpeg')
					.send(fileStream);
			} catch (err) {
				// Avatar doesn't exist, return 404
				// Frontend will fallback to default avatar
				return reply.status(404).send({
					success: false,
					error: 'Avatar not found'
				});
			}

		} catch (error) {
			fastify.log.error('Avatar retrieval error:', error);
			return reply.status(503).send({
				success: false,
				error: 'Failed to retrieve avatar'
			});
		}
	});

	// DELETE /database/avatar/:userId - Delete avatar
	fastify.delete('/avatar/:userId', async (request, reply) => {
		try {
			const userId = request.headers['x-user-id'];
			const { userId: targetUserId } = request.params;

			// Only allow users to delete their own avatar
			if (userId !== targetUserId) {
				return reply.status(403).send({
					success: false,
					error: 'Forbidden'
				});
			}

			const avatarPath = path.join(AVATARS_DIR, `${userId}.jpg`);

			try {
				// Try to delete the physical file (may not exist for OAuth users)
				await fs.unlink(avatarPath);
			} catch (err) {
				// File doesn't exist - that's okay (GitHub OAuth avatar URLs)
			}

			// Always update database to remove avatar reference
			await db.run(
				'UPDATE users SET avatar = NULL WHERE id = ?',
				[userId]
			);

			return reply.send({
				success: true,
				message: 'Avatar deleted successfully'
			});

		} catch (error) {
			fastify.log.error('Avatar deletion error:', error);
			return reply.status(503).send({
				success: false,
				error: 'Failed to delete avatar'
			});
		}
	});
}