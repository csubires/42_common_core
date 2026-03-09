# Security Audit: Input Validation

This document identifies all backend endpoints that lack proper input validation and could be vulnerable to malicious requests.

## Audit Date
March 1, 2026

## Methodology
- Search for endpoints that directly destructure `request.body` without validation
- Check for missing type checking, length validation, and sanitization
- Identify endpoints that trust frontend input
- Review error handling patterns

---

## 🔴 CRITICAL VULNERABILITIES (High Priority)

### AUTH SERVICE

#### 1. `/api/auth/login` - Login Endpoint
**File:** `auth/routes/auth.js`
**Issue:** No validation on email/password format or length
```javascript
const { email, password } = request.body;
```
**Risks:**
- SQL injection if email not sanitized
- No password length check
- No email format validation
- Could send massive strings to crash server

#### 2. `/api/auth/register` - Registration Endpoint
**File:** `auth/routes/auth.js`
**Issue:** No validation on username, email, password
```javascript
const { username, email, password } = request.body;
```
**Risks:**
- Username could be empty, too long, or contain special characters
- No email format validation
- No password strength requirements
- Could register with malicious usernames

#### 3. `/api/2fa/verify-login` - 2FA Verification
**File:** `auth/routes/2fa.js`
**Issue:** No validation on tokens
```javascript
const { token: totpToken, tempToken } = request.body;
```
**Risks:**
- No token format validation
- Could send arbitrary data

#### 4. `/api/2fa/verify-setup` - 2FA Setup Verification
**File:** `auth/routes/2fa.js`
**Issue:** No validation on tokens
```javascript
const { token, setupToken } = request.body;
```

#### 5. `/api/auth/profile-data` - Update Profile
**File:** `auth/routes/user.js`
**Issue:** No validation on display_name, email, avatar
```javascript
const { display_name, avatar, email } = request.body;
```
**Risks:**
- Display name could be excessively long
- Email not validated
- Avatar path not sanitized (path traversal risk)

#### 6. `/api/gdpr/delete-account` - Delete Account
**File:** `auth/routes/gdpr.js`
**Issue:** No validation on confirmation text
```javascript
const { confirmation } = request.body;
```

#### 7. `/api/gdpr/update-consent` - Update Consent
**File:** `auth/routes/gdpr.js`
**Issue:** No validation on consent values
```javascript
const { marketingEmails, analytics, dataProcessing } = request.body;
```
**Risks:**
- Could send non-boolean values
- No type checking

---

### DATABASE SERVICE

#### 8. `/api/database/users` - Create User
**File:** `database/routes/users.js`
**Issue:** Accepts all fields without validation
```javascript
const { id, username, display_name, email, password_hash, avatar, oauth_provider, oauth_id } = request.body;
```
**Risks:**
- No validation on any field
- Direct database insertion vulnerability
- Could inject malicious SQL

#### 9. `/api/database/users/:id` - Update User (PUT)
**File:** `database/routes/users.js`
**Issue:** Accepts ANY updates without validation
```javascript
const updates = request.body;
```
**Risks:**
- **CRITICAL:** Could update ANY field in database
- Could escalate privileges
- Could modify protected fields

#### 10. `/api/database/users/:id/login-attempts` - Update Login Attempts
**File:** `database/routes/users.js`
**Issue:** No validation on increment value
```javascript
const { increment } = request.body;
```
**Risks:**
- Could send negative numbers
- Could send non-numeric values
- Could overflow counter

#### 11. `/api/database/backup-codes` - Store Backup Codes
**File:** `database/routes/users.js`
**Issue:** No validation on user_id or codes
```javascript
const { user_id, codes } = request.body;
```
**Risks:**
- Could store malicious codes
- No array validation on codes
- user_id not validated

#### 12. `/api/database/sessions` - Create Session
**File:** `database/routes/sessions.js`
**Issue:** No validation on session data
```javascript
const { id, user_id, jwt_token, expires_at } = request.body;
```
**Risks:**
- Could inject malicious session data
- No date validation on expires_at

#### 13. `/api/database/friends/me/add` - Add Friend
**File:** `database/routes/friends.js`
**Issue:** No validation on friend_username
```javascript
const { friend_username } = request.body;
```
**Risks:**
- Username not validated
- Could send SQL injection

#### 14. `/api/database/friends` - Create Friendship (POST)
**File:** `database/routes/friends.js`
**Issue:** No validation on user_id or friend_id
```javascript
const { user_id, friend_id } = request.body;
```
**Risks:**
- Could create arbitrary friendships
- No ownership validation

#### 15. `/api/database/friends/:id` - Update Friend Status
**File:** `database/routes/friends.js`
**Issue:** No validation on status value
```javascript
const { status } = request.body;
```
**Risks:**
- Could set invalid status values
- No enum validation

#### 16. `/api/database/friends/users/:id/status` - Update Online Status
**File:** `database/routes/friends.js`
**Issue:** No validation on online_status
```javascript
const { online_status } = request.body;
```
**Risks:**
- Could set invalid status values

#### 17. `/api/database/tournaments/:id` - Update Tournament (PUT)
**File:** `database/routes/tournaments.js`
**Issue:** Accepts ANY updates without validation
```javascript
const updates = request.body;
```
**Risks:**
- **CRITICAL:** Could update ANY field
- Could modify tournament state improperly

#### 18. `/api/database/tournaments/:id/participants` - Add Participant
**File:** `database/routes/tournaments.js`
**Issue:** No validation on user_id or display_name
```javascript
const { user_id = null, display_name } = request.body;
```

#### 19. `/api/database/tournament-participants` - Bulk Add Participants
**File:** `database/routes/tournaments.js`
**Issue:** No validation on participants array
```javascript
const { participants } = request.body;
```
**Risks:**
- No array validation
- Could send massive array to DoS server

#### 20. `/api/database/tournaments/:tournamentId/participants/:participantId` - Update Participant
**File:** `database/routes/tournaments.js`
**Issue:** No validation on seed, eliminated, eliminated_round
```javascript
const { seed, eliminated, eliminated_round } = request.body;
```

#### 21. `/api/database/tournaments/:id/start` - Start Tournament
**File:** `database/routes/tournaments.js`
**Issue:** No validation on status or started_at
```javascript
const { status, started_at } = request.body;
```

#### 22. `/api/database/tournaments/:id/round` - Update Round
**File:** `database/routes/tournaments.js`
**Issue:** No validation on current_round
```javascript
const { current_round } = request.body;
```
**Risks:**
- Could set invalid round numbers
- Could break tournament progression

#### 23. `/api/database/tournaments/:id/complete` - Complete Tournament
**File:** `database/routes/tournaments.js`
**Issue:** No validation on any field
```javascript
const { status, winner_id, winner_name, current_round, completed_at } = request.body;
```

#### 24. `/api/database/matches` - Create Match
**File:** `database/routes/matches.js`
**Issue:** Weak validation - no type checking, no length limits
```javascript
const { player1_id, player1_name, player2_id, player2_name, player1_score, player2_score, 
        winner_id, winner_name, opponent_id, opponent_name, user_score, opponent_score, 
        winner, game_type, tournament_id, match_duration } = request.body;
```
**Risks:**
- Names could be excessively long (XSS risk)
- Scores not validated as numbers
- game_type not validated against whitelist
- match_duration not validated as number
- No sanitization on any string fields

---

## 🟡 MEDIUM VULNERABILITIES

None found - i18n service properly validates language input.

---

## ✅ PROPERLY VALIDATED ENDPOINTS

### I18N SERVICE

#### `/api/i18n/change-language` - Change Language
**File:** `i18n/routes/i18n.js`
**Status:** ✅ Properly validated
```javascript
if (!language || !['en', 'es', 'ja'].includes(language)) {
    return reply.status(400).send({
        success: false,
        error: 'common.unsupportedLanguage'
    });
}
```
**Good practices:**
- Whitelist validation
- Proper error message

---

## Summary Statistics

- **Total Endpoints Audited:** 25
- **Critical Vulnerabilities:** 24
- **Properly Validated:** 1
- **Services Affected:** Auth, Database

## Recommended Actions

1. **Immediate:** Add input validation middleware for all POST/PUT/PATCH endpoints
2. **High Priority:** Implement schema validation (e.g., using Joi, Zod, or Fastify schemas)
3. **Critical:** Fix endpoints that accept `request.body` as updates object
4. **Essential:** Add length limits on all string inputs
5. **Required:** Add type checking for all inputs
6. **Important:** Sanitize all user inputs before database queries
7. **Security:** Add rate limiting on authentication endpoints

## Next Steps

1. Create validation schemas for each endpoint
2. Implement validation middleware
3. Add proper error messages for validation failures
4. Test with malicious inputs
5. Update frontend to handle validation errors gracefully
