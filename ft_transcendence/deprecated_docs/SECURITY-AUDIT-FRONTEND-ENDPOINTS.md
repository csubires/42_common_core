# Security Audit: Frontend-Called Endpoints

**Date:** February 27, 2026  
**Scope:** Authorization vulnerabilities in backend endpoints actually called by frontend  
**Risk Level:** HIGH - Authenticated users can manipulate other users' data

---

## Executive Summary

This audit identified **6 critical authorization vulnerabilities** in backend endpoints that are actively used by the frontend application. While authentication is properly handled by the gateway (JWT validation), the endpoints fail to verify that authenticated users have permission to modify the requested resources.

**Impact:** An authenticated attacker can:
- Accept/reject friend requests meant for other users
- Delete friendships between any users
- Start/complete/manipulate any user's tournaments
- Set themselves as creator of tournaments

---

## Critical Vulnerabilities (Used by Frontend)

### 1. Friend Request Manipulation

#### 🔴 PUT `/api/database/friends/:id` - Accept/Reject Friend Request

**Backend File:** `database/routes/friends.js` (lines 380-413)

**Frontend Usage:**
- File: `frontend/src/pages/friends.ts`
- Functions: `acceptRequest()` (line 518), `rejectRequest()` (line 542)
- Called from: User clicks "Accept" or "Reject" buttons on friend requests

**Current Code:**
```javascript
fastify.put('/friends/:id', async (request, reply) => {
    const { id } = request.params;
    const { status } = request.body;

    // ❌ NO CHECK: Is the authenticated user the RECIPIENT of this request?
    
    const friendship = await db.get('SELECT * FROM friendships WHERE id = ?', [id]);
    if (!friendship) {
        return reply.status(404).send({ error: 'Friendship not found' });
    }

    await db.run('UPDATE friendships SET status = ? WHERE id = ?', [status, id]);
    return { success: true };
});
```

**Vulnerability:**
- The endpoint accepts `friendship ID` from URL params
- No verification that the authenticated user (from `x-user-id` header) is the **recipient** (`friend_id`) of this request
- Any user can accept/reject ANY friend request if they know the friendship ID

**Attack Vector:**
1. Attacker logs in normally
2. Opens browser console
3. Calls: `acceptRequest(123)` where `123` is someone else's friend request ID
4. The request is accepted as if the victim accepted it

**Frontend Code:**
```typescript
// frontend/src/pages/friends.ts:525
async function acceptRequest(requestId: number): Promise<void> {
    const response = await api(`/api/database/friends/${requestId}`, {
        method: 'PUT',
        body: JSON.stringify({ status: 'accepted' })
    });
}
```

**Required Fix:**
```javascript
fastify.put('/friends/:id', async (request, reply) => {
    const authenticatedUserId = request.headers['x-user-id'];
    const { id } = request.params;
    const { status } = request.body;

    if (!authenticatedUserId) {
        return reply.status(401).send({ 
            success: false, 
            error: 'Authentication required' 
        });
    }

    const friendship = await db.get('SELECT * FROM friendships WHERE id = ?', [id]);
    
    if (!friendship) {
        return reply.status(404).send({ error: 'Friendship not found' });
    }

    // ✅ Verify the authenticated user is the RECIPIENT of this request
    if (friendship.friend_id !== authenticatedUserId) {
        return reply.status(403).send({
            success: false,
            error: 'Forbidden: You can only respond to your own friend requests'
        });
    }

    await db.run('UPDATE friendships SET status = ? WHERE id = ?', [status, id]);
    return { success: true };
});
```

---

### 2. Friendship Deletion

#### 🔴 DELETE `/api/database/friends/:id` - Remove Friend or Cancel Request

**Backend File:** `database/routes/friends.js` (lines 419-430)

**Frontend Usage:**
- File: `frontend/src/pages/friends.ts`
- Functions: `cancelRequest()` (line 566), `removeFriend()` (line 590)
- Called from: User clicks "Cancel" on sent requests or "Remove" on friends list

**Current Code:**
```javascript
fastify.delete('/friends/:id', async (request, reply) => {
    const { id } = request.params;
    
    // ❌ NO CHECK: Is the authenticated user part of this friendship?

    try {
        await db.run('DELETE FROM friendships WHERE id = ?', [id]);
        return { success: true };
    } catch (error) {
        return reply.status(500).send({ error: 'Database error' });
    }
});
```

**Vulnerability:**
- No verification that authenticated user is either `user_id` or `friend_id` in the friendship
- Any user can delete ANY friendship between ANY users

**Attack Vector:**
1. Attacker obtains friendship IDs (exposed in GET responses)
2. Calls: `removeFriend(456)` where `456` is a friendship between two other users
3. The friendship is deleted, breaking the connection between innocent users

**Frontend Code:**
```typescript
// frontend/src/pages/friends.ts:603
async function removeFriend(friendshipId: number, username: string): Promise<void> {
    const response = await api(`/api/database/friends/${friendshipId}`, {
        method: 'DELETE',
        body: JSON.stringify({ _dummy: true })
    });
}
```

**Required Fix:**
```javascript
fastify.delete('/friends/:id', async (request, reply) => {
    const authenticatedUserId = request.headers['x-user-id'];
    const { id } = request.params;

    if (!authenticatedUserId) {
        return reply.status(401).send({ 
            success: false, 
            error: 'Authentication required' 
        });
    }

    try {
        const friendship = await db.get('SELECT * FROM friendships WHERE id = ?', [id]);
        
        if (!friendship) {
            return reply.status(404).send({
                success: false,
                error: 'Friendship not found'
            });
        }

        // ✅ Verify the authenticated user is part of this friendship
        if (friendship.user_id !== authenticatedUserId && 
            friendship.friend_id !== authenticatedUserId) {
            return reply.status(403).send({
                success: false,
                error: 'Forbidden: You can only delete your own friendships'
            });
        }

        await db.run('DELETE FROM friendships WHERE id = ?', [id]);
        return { success: true };
    } catch (error) {
        return reply.status(500).send({ 
            success: false,
            error: 'Database error' 
        });
    }
});
```

---

### 3. Tournament Creator Spoofing

#### 🔴 POST `/api/database/tournaments` - Create Tournament

**Backend File:** `database/routes/tournaments.js` (lines 6-30)

**Frontend Usage:**
- File: `frontend/src/tournamentEngine.ts`
- Function: `createTournamentInDB()` (line 110)
- Called from: User starts a new tournament

**Current Code:**
```javascript
fastify.post('/tournaments', async (request, reply) => {
    const {
        name,
        creator_id = null,  // ❌ Accepts from request body!
        max_players = 8
    } = request.body;

    try {
        const result = await db.run(
            `INSERT INTO tournaments (name, creator_id, max_players, status, current_round, created_at)
            VALUES (?, ?, ?, 'pending', 0, CURRENT_TIMESTAMP)`,
            [name, creator_id, max_players]
        );
        return { success: true, tournamentId: result.id };
    }
});
```

**Vulnerability:**
- `creator_id` comes from request body, not from JWT
- Attacker can set any user as the tournament creator

**Attack Vector:**
1. Attacker modifies frontend code in console
2. Sets `creator_id` to victim's ID
3. Tournament appears as if victim created it

**Frontend Code:**
```typescript
// frontend/src/tournamentEngine.ts:110
const response = await api('/api/database/tournaments', {
    method: 'POST',
    body: JSON.stringify({
        name: `Pong Tournament ${new Date().toLocaleDateString()}`,
        creator_id: actualCreatorId,  // ⚠️ Could be manipulated
        max_players: players.length
    })
});
```

**Required Fix:**
```javascript
fastify.post('/tournaments', async (request, reply) => {
    const creatorId = request.headers['x-user-id']; // ✅ Use JWT
    const {
        name,
        max_players = 8
    } = request.body;

    if (!name) {
        return reply.status(400).send({
            error: 'Tournament name is required',
            success: false,
            code: 'MISSING_NAME'
        });
    }

    try {
        const result = await db.run(
            `INSERT INTO tournaments (name, creator_id, max_players, status, current_round, created_at)
            VALUES (?, ?, ?, 'pending', 0, CURRENT_TIMESTAMP)`,
            [name, creatorId || null, max_players]
        );
        return { success: true, tournamentId: result.id };
    } catch (error) {
        console.error('Error creating tournament:', error);
        return reply.status(500).send({
            error: 'Database error',
            success: false,
            code: 'DB_ERROR'
        });
    }
});
```

---

### 4. Tournament Start Manipulation

#### 🔴 PATCH `/api/database/tournaments/:id/start` - Start Tournament

**Backend File:** `database/routes/tournaments.js` (lines 436-456)

**Frontend Usage:**
- File: `frontend/src/tournamentEngine.ts`
- Function: `startTournamentInDB()` (line 162)
- Called from: Tournament is started

**Current Code:**
```javascript
fastify.patch('/tournaments/:id/start', async (request, reply) => {
    const { id } = request.params;
    const { status, started_at } = request.body;

    // ❌ NO CHECK: Is the authenticated user the tournament creator?

    try {
        await db.run(
            `UPDATE tournaments SET status = ?, started_at = ? WHERE id = ?`,
            [status || 'active', started_at || new Date().toISOString(), id]
        );
        return { success: true };
    }
});
```

**Vulnerability:**
- No check if authenticated user is the tournament creator
- Any user can start ANY tournament

**Attack Vector:**
1. Attacker finds tournament IDs (exposed in GET responses)
2. Calls API to start someone else's tournament
3. Tournament starts without creator's consent

**Frontend Code:**
```typescript
// frontend/src/tournamentEngine.ts:162
await api(`/api/database/tournaments/${tournamentId}/start`, {
    method: 'PATCH',
    body: JSON.stringify({
        status: 'active',
        started_at: new Date().toISOString()
    })
});
```

**Required Fix:**
```javascript
fastify.patch('/tournaments/:id/start', async (request, reply) => {
    const authenticatedUserId = request.headers['x-user-id'];
    const { id } = request.params;
    const { status, started_at } = request.body;

    if (!authenticatedUserId) {
        return reply.status(401).send({
            success: false,
            error: 'Authentication required'
        });
    }

    try {
        // ✅ Check tournament ownership
        const tournament = await db.get(
            'SELECT creator_id FROM tournaments WHERE id = ?', 
            [id]
        );

        if (!tournament) {
            return reply.status(404).send({
                success: false,
                error: 'Tournament not found'
            });
        }

        // Allow if user is the creator OR if tournament has no creator (guest tournaments)
        if (tournament.creator_id && tournament.creator_id !== authenticatedUserId) {
            return reply.status(403).send({
                success: false,
                error: 'Forbidden: Only tournament creator can start it'
            });
        }

        await db.run(
            `UPDATE tournaments SET status = ?, started_at = ? WHERE id = ?`,
            [status || 'active', started_at || new Date().toISOString(), id]
        );

        return { success: true };
    } catch (error) {
        console.error('Error starting tournament:', error);
        return reply.status(500).send({
            error: 'Database error',
            success: false,
            code: 'DB_ERROR'
        });
    }
});
```

---

### 5. Tournament Round Manipulation

#### 🔴 PATCH `/api/database/tournaments/:id/round` - Update Tournament Round

**Backend File:** `database/routes/tournaments.js` (lines 458-486)

**Frontend Usage:**
- File: `frontend/src/tournamentEngine.ts`
- Function: `updateTournamentRound()` (line 257)
- Called from: Tournament advances to next round

**Current Code:**
```javascript
fastify.patch('/tournaments/:id/round', async (request, reply) => {
    const { id } = request.params;
    const { current_round } = request.body;

    // ❌ NO OWNERSHIP CHECK

    try {
        await db.run(
            `UPDATE tournaments SET current_round = ? WHERE id = ?`,
            [current_round, id]
        );
        return { success: true };
    }
});
```

**Vulnerability:**
- No check if authenticated user is the tournament creator
- Any user can manipulate tournament rounds

**Attack Vector:**
- Attacker can advance/rewind rounds in any tournament
- Can disrupt tournament progress

**Required Fix:**
```javascript
fastify.patch('/tournaments/:id/round', async (request, reply) => {
    const authenticatedUserId = request.headers['x-user-id'];
    const { id } = request.params;
    const { current_round } = request.body;

    if (!authenticatedUserId) {
        return reply.status(401).send({
            success: false,
            error: 'Authentication required'
        });
    }

    if (current_round === undefined) {
        return reply.status(400).send({
            error: 'current_round is required',
            success: false,
            code: 'MISSING_ROUND'
        });
    }

    try {
        // ✅ Check tournament ownership
        const tournament = await db.get(
            'SELECT creator_id FROM tournaments WHERE id = ?', 
            [id]
        );

        if (!tournament) {
            return reply.status(404).send({
                success: false,
                error: 'Tournament not found'
            });
        }

        if (tournament.creator_id && tournament.creator_id !== authenticatedUserId) {
            return reply.status(403).send({
                success: false,
                error: 'Forbidden: Only tournament creator can update rounds'
            });
        }

        await db.run(
            `UPDATE tournaments SET current_round = ? WHERE id = ?`,
            [current_round, id]
        );

        return { success: true };
    } catch (error) {
        console.error('Error updating tournament round:', error);
        return reply.status(500).send({
            error: 'Database error',
            success: false,
            code: 'DB_ERROR'
        });
    }
});
```

---

### 6. Tournament Completion Manipulation

#### 🔴 PATCH `/api/database/tournaments/:id/complete` - Complete Tournament

**Backend File:** `database/routes/tournaments.js` (lines 488-516)

**Frontend Usage:**
- File: `frontend/src/tournamentEngine.ts`
- Function: `completeTournamentInDB()` (line 234)
- Called from: Tournament finishes

**Current Code:**
```javascript
fastify.patch('/tournaments/:id/complete', async (request, reply) => {
    const { id } = request.params;
    const { status, winner_id, winner_name, current_round, completed_at } = request.body;

    // ❌ NO OWNERSHIP CHECK
    // ❌ Accepts winner_id from body (could be manipulated)

    try {
        await db.run(
            `UPDATE tournaments 
            SET status = ?, winner_id = ?, winner_name = ?, current_round = ?, completed_at = ?
            WHERE id = ?`,
            [status || 'completed', winner_id || null, winner_name, 
             current_round, completed_at || new Date().toISOString(), id]
        );
        return { success: true };
    }
});
```

**Vulnerability:**
- No check if authenticated user is the tournament creator
- Any user can complete ANY tournament
- Can set fake winners

**Attack Vector:**
1. Attacker completes someone else's tournament
2. Sets themselves as winner
3. Gets false win statistics

**Required Fix:**
```javascript
fastify.patch('/tournaments/:id/complete', async (request, reply) => {
    const authenticatedUserId = request.headers['x-user-id'];
    const { id } = request.params;
    const { status, winner_id, winner_name, current_round, completed_at } = request.body;

    if (!authenticatedUserId) {
        return reply.status(401).send({
            success: false,
            error: 'Authentication required'
        });
    }

    try {
        // ✅ Check tournament ownership
        const tournament = await db.get(
            'SELECT creator_id FROM tournaments WHERE id = ?', 
            [id]
        );

        if (!tournament) {
            return reply.status(404).send({
                success: false,
                error: 'Tournament not found'
            });
        }

        if (tournament.creator_id && tournament.creator_id !== authenticatedUserId) {
            return reply.status(403).send({
                success: false,
                error: 'Forbidden: Only tournament creator can complete it'
            });
        }

        await db.run(
            `UPDATE tournaments 
            SET status = ?, winner_id = ?, winner_name = ?, current_round = ?, completed_at = ?
            WHERE id = ?`,
            [
                status || 'completed',
                winner_id || null,
                winner_name,
                current_round,
                completed_at || new Date().toISOString(),
                id
            ]
        );

        return { success: true };
    } catch (error) {
        console.error('Error completing tournament:', error);
        return reply.status(500).send({
            error: 'Database error',
            success: false,
            code: 'DB_ERROR'
        });
    }
});
```

---

## Endpoints NOT Called by Frontend

These endpoints have similar vulnerabilities but are **NOT** currently called by the frontend. They can be:
- Left as-is if they're for internal backend testing
- Removed if not needed
- Fixed if they'll be used in the future

### Test/Backend-Only Endpoints:
1. `PUT /api/database/users/:id` - Update any user
2. `DELETE /api/database/users/:id` - Delete any user
3. `POST /api/database/friends` - Create friend request with arbitrary IDs
4. `POST /api/database/sessions` - Create sessions for any user
5. `DELETE /api/database/sessions/user/:userId` - Delete any user's sessions
6. `POST /api/database/backup-codes` - Set backup codes for any user
7. `PUT /api/database/backup-codes/:id/use` - Mark any backup code as used
8. `PUT /api/database/users/:id/status` - Change any user's online status
9. `PUT /api/database/tournaments/:id` - Update any tournament
10. `DELETE /api/database/tournaments/:id` - Delete any tournament
11. `PUT /api/database/tournaments/:id/participants/:participantId` - Update any participant
12. `DELETE /api/database/tournaments/:id/participants/:participantId` - Remove any participant

---

## Recommended Action Plan

### Priority 1 (Critical - Fix Immediately):
1. ✅ Fix `PUT /api/database/friends/:id` - Friend request authorization
2. ✅ Fix `DELETE /api/database/friends/:id` - Friendship deletion authorization
3. ✅ Fix `POST /api/database/tournaments` - Use JWT for creator_id
4. ✅ Fix `PATCH /api/database/tournaments/:id/start` - Tournament start authorization
5. ✅ Fix `PATCH /api/database/tournaments/:id/round` - Tournament round authorization
6. ✅ Fix `PATCH /api/database/tournaments/:id/complete` - Tournament completion authorization

### Priority 2 (Future - If Needed):
- Review and potentially remove or fix endpoints not used by frontend
- Add comprehensive authorization middleware
- Implement audit logging for sensitive operations

---

## Notes

- All fixes follow the same pattern: Check `x-user-id` header against resource ownership
- Guest tournaments (creator_id = null) should still be allowed to be manipulated
- Error messages should not leak sensitive information about other users
- All authorization checks should happen BEFORE any database writes

---

**End of Report**
