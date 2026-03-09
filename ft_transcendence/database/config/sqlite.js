import sqlite3 from 'sqlite3';
import path from 'path';
import { fileURLToPath } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));

class Database {
	constructor() {
		this.db = null;
		this.init();
	}

	init() {
		const dbPath = path.join(__dirname, '../../data/app.db');
		this.db = new sqlite3.Database(dbPath, (err) => {
			if (err) {
				console.error('Error connecting to SQLite:', err.message);
			} else {
				this.createTables();
			}
		});
	}

	createTables() {
		const usersTable = `
            CREATE TABLE IF NOT EXISTS users (
                id TEXT PRIMARY KEY,
                username TEXT NOT NULL,
                display_name TEXT,
                email TEXT UNIQUE,
                password_hash TEXT,
                oauth_provider TEXT,
                oauth_id TEXT,
                avatar TEXT,
                two_factor_enabled BOOLEAN DEFAULT 0,
                two_factor_secret TEXT,
                is_active BOOLEAN DEFAULT 1,
                is_anonymized BOOLEAN DEFAULT 0,
                login_attempts INTEGER DEFAULT 0,
                locked_until DATETIME,
                consent_marketing BOOLEAN DEFAULT 0,
                consent_analytics BOOLEAN DEFAULT 0,
                consent_data_processing BOOLEAN DEFAULT 1,
                consent_updated_at DATETIME,
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                online_status TEXT DEFAULT 'offline',
                last_seen DATETIME,
                UNIQUE(oauth_provider, oauth_id)
            )
        `;

		const backupCodesTable = `
            CREATE TABLE IF NOT EXISTS backup_codes (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id TEXT NOT NULL,
                code_hash TEXT NOT NULL,
                used BOOLEAN DEFAULT 0,
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
            )
        `;

		const friendshipsTable = `
            CREATE TABLE IF NOT EXISTS friendships (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id TEXT NOT NULL,
                friend_id TEXT NOT NULL,
                status TEXT DEFAULT 'pending',
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
                FOREIGN KEY (friend_id) REFERENCES users(id) ON DELETE CASCADE,
                UNIQUE(user_id, friend_id)
            )
        `;

		const tournamentsTable = `
            CREATE TABLE IF NOT EXISTS tournaments (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                creator_id TEXT,
				tournament_type TEXT DEFAULT 'Pong',
                status TEXT DEFAULT 'pending',
                max_players INTEGER DEFAULT 8,
                current_round INTEGER DEFAULT 0,
                winner_id TEXT,
                winner_name TEXT,
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                started_at DATETIME,
                completed_at DATETIME,
                FOREIGN KEY (creator_id) REFERENCES users(id) ON DELETE SET NULL,
                FOREIGN KEY (winner_id) REFERENCES users(id) ON DELETE SET NULL
            )
        `;

		const tournamentParticipantsTable = `
            CREATE TABLE IF NOT EXISTS tournament_participants (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                tournament_id INTEGER NOT NULL,
                user_id TEXT,
                display_name TEXT NOT NULL,
                seed INTEGER,
                eliminated BOOLEAN DEFAULT 0,
                eliminated_round INTEGER,
                joined_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY (tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE,
                FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE SET NULL
            )
        `;

		const matchesTable = `
			CREATE TABLE IF NOT EXISTS matches (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				player1_id TEXT,
                player1_name TEXT,
				player2_id TEXT,
                player2_name TEXT,
				player1_score INTEGER NOT NULL,
				player2_score INTEGER NOT NULL,
				winner_id TEXT,
                winner_name TEXT,
				game_type TEXT DEFAULT 'pong',
				tournament_id INTEGER DEFAULT NULL,
				match_duration INTEGER,
				played_at DATETIME DEFAULT CURRENT_TIMESTAMP,
				FOREIGN KEY (player1_id) REFERENCES users(id) ON DELETE SET NULL,
				FOREIGN KEY (player2_id) REFERENCES users(id) ON DELETE SET NULL,
				FOREIGN KEY (winner_id) REFERENCES users(id) ON DELETE SET NULL,
				FOREIGN KEY (tournament_id) REFERENCES tournaments(id) ON DELETE SET NULL
    )
`;

		this.run(usersTable).catch(err => {
			console.error('Error creating users table:', err);
		});

		this.run(backupCodesTable).catch(err => {
			console.error('Error creating backup_codes table:', err);
		});

		this.run(friendshipsTable).catch(err => {
			console.error('Error creating friendships table:', err);
		});

		this.run(tournamentsTable).catch(err => {
			console.error('Error creating tournaments table:', err);
		});

		this.run(tournamentParticipantsTable).catch(err => {
			console.error('Error creating tournament_participants table:', err);
		});

		this.run(matchesTable).catch(err => {
			console.error('Error creating matches table:', err);
		});

		// // Add new columns to existing users table (for existing databases)
		// const newUserColumns = [
		// 	'ALTER TABLE users ADD COLUMN display_name TEXT',
		// 	'ALTER TABLE users ADD COLUMN wins INTEGER DEFAULT 0',
		// 	'ALTER TABLE users ADD COLUMN losses INTEGER DEFAULT 0',
		// 	'ALTER TABLE users ADD COLUMN games_played INTEGER DEFAULT 0',
		// 	'ALTER TABLE users ADD COLUMN online_status TEXT DEFAULT \'offline\'',
		// 	'ALTER TABLE users ADD COLUMN last_seen DATETIME'
		// ];

		// newUserColumns.forEach(sql => {
		// 	this.run(sql).catch(() => {
		// 		// Column already exists, ignore error
		// 	});
		// });
	}

	async run(sql, params = []) {
		const self = this; // Save reference to Database instance
		return new Promise(async (resolve, reject) => {
			this.db.run(sql, params, async function (err) {
				if (err) {
					console.error('SQL Error:', err);
					console.error('SQL Statement:', sql);
					console.error('Parameters:', params);
					
					// Auto-recovery for readonly database
					if (err.code === 'SQLITE_READONLY' || err.code === 'SQLITE_CANTOPEN') {
						const recovered = await self.reinitialize();
						if (recovered) {
							// Retry the operation once after recovery
							self.db.run(sql, params, function (retryErr) {
								if (retryErr) {
									console.error('❌ Retry after recovery failed:', retryErr);
									reject(retryErr);
								} else {
									resolve({ id: this.lastID, changes: this.changes });
								}
							});
							return;
						}
					}
					
					reject(err);
				} else {
					resolve({ id: this.lastID, changes: this.changes });
				}
			});
		});
	}

	get(sql, params = []) {
		return new Promise((resolve, reject) => {
			this.db.get(sql, params, (err, row) => {
				if (err) {
					console.error('SQL Error:', err);
					console.error('SQL Statement:', sql);
					console.error('Parameters:', params);
					reject(err);
				} else {
					resolve(row);
				}
			});
		});
	}

	all(sql, params = []) {
		return new Promise((resolve, reject) => {
			this.db.all(sql, params, (err, rows) => {
				if (err) {
					console.error('SQL Error:', err);
					console.error('SQL Statement:', sql);
					console.error('Parameters:', params);
					reject(err);
				} else {
					resolve(rows);
				}
			});
		});
	}

	close() {
		return new Promise((resolve, reject) => {
			this.db.close((err) => {
				if (err) reject(err);
				else resolve();
			});
		});
	}

	// Health check: verify database can write
	async healthCheck() {
		try {
			await this.run(
				`CREATE TABLE IF NOT EXISTS _health_check (id INTEGER PRIMARY KEY, checked_at DATETIME)`
			);
			await this.run(
				`INSERT OR REPLACE INTO _health_check (id, checked_at) VALUES (1, CURRENT_TIMESTAMP)`
			);
			const result = await this.get(`SELECT * FROM _health_check WHERE id = 1`);
			return { healthy: true, canWrite: true, lastCheck: result?.checked_at };
		} catch (error) {
			console.error('Database health check failed:', error);
			return { 
				healthy: false, 
				canWrite: false, 
				error: error.message,
				errorCode: error.code 
			};
		}
	}

	// Reinitialize database connection
	async reinitialize() {
		return new Promise((resolve) => {
			// Close existing connection
			if (this.db) {
				this.db.close((err) => {
					if (err) console.error('Error closing database:', err);
					
					// Wait a moment before reopening
					setTimeout(() => {
						this.init();
						// Give init time to complete
						setTimeout(() => {
							resolve(true);
						}, 1000);
					}, 500);
				});
			} else {
				// No existing connection, just initialize
				this.init();
				setTimeout(() => {
					resolve(true);
				}, 1000);
			}
		});
	}
}

export default new Database();
