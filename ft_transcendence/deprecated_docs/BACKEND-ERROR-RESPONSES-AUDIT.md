# Backend Error Response Audit

**Audit Date:** March 1, 2026

## Overview

This document catalogs ALL error responses in the backend to standardize status codes and error messages.

**Goal:** Replace generic 400/500 errors with specific status codes:
- **422** - Validation errors
- **409** - Conflicts (duplicate resources)
- **400** - Malformed requests
- **401** - Unauthorized
- **403** - Forbidden
- **404** - Not found
- **500** - Server errors (only for actual crashes)

---

## AUTH SERVICE (auth/routes/)

### File: **auth.js** (Login & Registration)

#### Line 22 - Login: No user found
```javascript
return reply.status(401).send({  // ✅ CORRECT (auth error)
    success: false,
    error: 'auth.userNotFound',
    code: 'USER_NOT_FOUND'
});
```

#### Line 38 - Login: Invalid password
```javascript
return reply.status(401).send({  // ✅ CORRECT (auth error)
    success: false,
    error: 'auth.invalidPassword',
    code: 'INVALID_PASSWORD'
});
```

#### Line 72 - Login: Database error
```javascript
return reply.status(500).send({  // ✅ CORRECT (server error)
    error: 'common.internalError',
    code: 'INTERNAL_ERROR'
});
```

#### Line 84 - Register: Missing fields
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422 (validation error)
    success: false,
    error: 'auth.missingCredentials',
    code: 'MISSING_CREDENTIALS'
});
```

#### Line 101 - Register: Database error
```javascript
return reply.status(500).send({  // ✅ CORRECT
    error: 'common.internalError',
    code: 'INTERNAL_ERROR'
});
```

---

### File: **2fa.js** (Two-Factor Authentication)

#### Line 13 - Verify Login: Missing fields
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.missingFields',
    code: 'MISSING_FIELDS'
});
```

#### Line 21 - Verify Login: Invalid temp token
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.invalidToken',
    code: 'INVALID_TOKEN'
});
```

#### Line 29 - Verify Login: 2FA not enabled
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.twoFactorNotEnabled',
    code: '2FA_NOT_ENABLED'
});
```

#### Line 37 - Verify Login: Invalid TOTP
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.invalidToken',
    code: 'INVALID_TOTP'
});
```

#### Line 55, 93, 135, 174, 199 - Various database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    success: false,
    error: 'common.internalError',
    code: 'INTERNAL_ERROR'
});
```

#### Line 73 - Setup: Invalid secret
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.invalidSecret',
    code: 'INVALID_SECRET'
});
```

#### Line 148 - Disable: Missing token
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.missingFields',
    code: 'MISSING_FIELDS'
});
```

#### Line 156 - Disable: Invalid token
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.invalidToken',
    code: 'INVALID_TOKEN'
});
```

#### Line 185 - Disable: 2FA not enabled
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.twoFactorNotEnabled',
    code: '2FA_NOT_ENABLED'
});
```

---

### File: **user.js** (Profile Management)

#### Lines 39, 70, 158, 201 - Database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    success: false,
    error: 'common.internalError',
    code: 'INTERNAL_ERROR'
});
```

#### Lines 51, 82 - No auth
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.authenticationRequired',
    code: 'AUTH_REQUIRED'
});
```

#### Lines 60, 93, 190 - User not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    success: false,
    error: 'user.notFound',
    code: 'USER_NOT_FOUND'
});
```

#### Line 103 - Update: Email already exists
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 409 (conflict)
    success: false,
    error: 'auth.emailInUse',
    code: 'EMAIL_IN_USE'
});
```

#### Line 115 - Update: Invalid email format
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'auth.invalidEmail',
    code: 'INVALID_EMAIL'
});
```

#### Line 124 - Update: Display name too long
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'user.displayNameTooLong',
    code: 'DISPLAY_NAME_TOO_LONG'
});
```

#### Line 142 - Update: No changes
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'user.noChanges',
    code: 'NO_CHANGES'
});
```

#### Lines 169, 178 - Delete: Not authenticated
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.authenticationRequired',
    code: 'AUTH_REQUIRED'
});
```

---

### File: **gdpr.js** (GDPR Operations)

#### Lines 11, 21 - Not authenticated
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.authenticationRequired',
    code: 'AUTH_REQUIRED'
});
```

#### Lines 36, 66, 98, 132 - User not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    success: false,
    error: 'user.notFound',
    code: 'USER_NOT_FOUND'
});
```

#### Line 176 - Delete: Invalid confirmation
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'gdpr.invalidConfirmation',
    code: 'INVALID_CONFIRMATION'
});
```

#### Lines 53, 81, 105, 116, 140, 153, 184, 195, 224, 235 - Database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    success: false,
    error: 'common.internalError',
    code: 'INTERNAL_ERROR'
});
```

---

### File: **jwt.js** (JWT Verification)

#### Line 8 - Invalid token
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.invalidToken'
});
```

---

### File: **vault.js** (Vault Secrets)

#### Lines 8, 17, 26 - Secret not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    success: false,
    error: 'vault.*NotFound'
});
```

---

## DATABASE SERVICE (database/routes/)

### File: **users.js**

#### Lines 15, 39 - User not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    error: 'User not found',
    success: false,
    code: 'USER_NOT_FOUND'
});
```

#### Lines 23, 47, 68, 100, 114, 127, 153, 183, 200, 217 - Database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    error: 'Database error',
    success: false,
    code: 'DB_ERROR'
});
```

#### Line 82 - Update: No fields to update
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    error: 'No fields to update',
    success: false,
    code: 'NO_FIELDS'
});
```

#### Line 165 - Backup codes: Missing fields
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    error: 'Missing required fields',
    success: false,
    code: 'MISSING_FIELDS'
});
```

---

### File: **sessions.js**

#### Lines 20, 34, 51 - Database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    error: 'Database error',
    success: false,
    code: 'DB_ERROR'
});
```

---

### File: **heartbeat.js**

#### Lines 36, 59 - No auth
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.required'
});
```

#### Lines 47, 86 - Database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    success: false,
    error: 'common.internalError' / 'database.connectionError'
});
```

#### Line 77 - Logout: No user ID (validation)
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'database.updateFailed',
    code: 'DB_UPDATE_ERROR'
});
```

---

### File: **matches.js**

#### Lines 31, 78 - Missing fields
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    error: 'Missing required fields',
    success: false,
    code: 'MISSING_FIELDS'
});
```

#### Line 74 - Not authenticated
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.required'
});
```

#### Lines 63, 128, 151, 174, 195, 222, 268 - Database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    error: 'Database error',
    success: false,
    code: 'DB_ERROR'
});
```

#### Lines 143, 241 - Match not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    error: 'Match not found',
    success: false,
    code: 'MATCH_NOT_FOUND'
});
```

---

### File: **tournaments.js** (100+ error responses)

**Issues identified:**
- **Most 400s should be 422** (validation errors)
- Database errors correctly use 500
- 404s correctly used for not found

**Key problematic lines:**
- Line 14, 121, 166, 256 - Missing fields → **Should be 422**
- Lines 185, 199, 213, 227 - Tournament state validation → **Should be 422**
- Lines 330, 389, 402, 463 - Invalid participant data → **Should be 422**

---

### File: **friends.js**

#### Lines 12, 45, 87, 120, 170 - Not authenticated
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.authenticationRequired'
});
```

#### Lines 178, 247, 255, 388 - Missing fields
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'Missing required fields'
});
```

#### Lines 192, 134 - Friend not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    success: false,
    error: 'Friend not found'
});
```

#### Lines 202, 216, 271 - Already friends/request exists
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 409 (conflict)
    success: false,
    error: 'Already friends' / 'Request already exists'
});
```

#### Lines 160, 407, 449 - Forbidden operations
```javascript
return reply.status(403).send({  // ✅ CORRECT
    success: false,
    error: 'Cannot add yourself' / 'Forbidden'
});
```

#### Lines 30, 73, 105, 155, 233, 288, 323, 347, 371, 421, 459, 484 - Database errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    success: false,
    error: 'Database error'
});
```

---

### File: **avatars.js**

#### Line 31 - Not authenticated
```javascript
return reply.status(401).send({  // ✅ CORRECT
    success: false,
    error: 'auth.authenticationRequired'
});
```

#### Lines 52, 64 - No file / Invalid type
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422
    success: false,
    error: 'No file uploaded' / 'Only JPG files allowed'
});
```

#### Line 137 - Avatar not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    success: false,
    error: 'Avatar not found'
});
```

#### Line 160 - Delete: Forbidden
```javascript
return reply.status(403).send({  // ✅ CORRECT
    success: false,
    error: 'Cannot delete another user avatar'
});
```

#### Lines 111, 145, 191 - Server errors
```javascript
return reply.status(500).send({  // ✅ CORRECT
    success: false,
    error: 'Failed to upload/retrieve/delete avatar'
});
```

---

## I18N SERVICE (i18n/routes/)

### File: **i18n.js**

#### Line 11 - Language not found
```javascript
return reply.status(404).send({  // ✅ CORRECT
    success: false,
    error: 'Translations not found for language'
});
```

#### Line 24 - Invalid language
```javascript
return reply.status(400).send({  // ⚠️ SHOULD BE 422 (validation)
    success: false,
    error: 'common.unsupportedLanguage'
});
```

---

## Summary Statistics

### Total Error Responses: **164+**

### By Status Code:
- **400 (Bad Request):** 58 ⚠️ **Most should be 422 or 409**
- **401 (Unauthorized):** 24 ✅ **Correct**
- **403 (Forbidden):** 4 ✅ **Correct**
- **404 (Not Found):** 18 ✅ **Correct**
- **500 (Server Error):** 60 ✅ **Correct**

### Needed Changes:
- **~45 endpoints**: Change 400 → 422 (validation errors)
- **~8 endpoints**: Change 400 → 409 (conflict errors)
- **~5 endpoints**: Keep 400 (malformed requests)

---

## Action Plan

1. **Phase 1:** Fix validation errors (400 → 422)
   - Auth service: ~15 endpoints
   - Database service: ~30 endpoints
   
2. **Phase 2:** Fix conflict errors (400 → 409)
   - Email exists, username exists
   - Friend request exists
   - Already friends
   
3. **Phase 3:** Update frontend to handle new codes gracefully
   - 422 = show validation message (no console.error)
   - 409 = show conflict message (no console.error)
   - 500 = console.error + generic message

---

## Files Requiring Updates

### High Priority:
1. **auth/routes/auth.js** - Registration validation
2. **auth/routes/2fa.js** - 2FA validation
3. **auth/routes/user.js** - Profile updates
4. **database/routes/friends.js** - Friend conflicts
5. **database/routes/tournaments.js** - Tournament validation

### Medium Priority:
6. **database/routes/matches.js** - Match validation
7. **database/routes/avatars.js** - File upload validation
8. **database/routes/users.js** - User update validation
9. **auth/routes/gdpr.js** - GDPR validation

### Low Priority:
10. **i18n/routes/i18n.js** - Language validation
11. **database/routes/heartbeat.js** - Minor fixes
