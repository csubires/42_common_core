# Frontend Error Handling Audit

**Audit Date:** March 1, 2026

## Current State

The frontend currently has **inconsistent error handling** across all API calls. Most errors are caught but handled generically with `console.error()`, which:
- Logs ALL errors to console (including validation errors that should be silent)
- Doesn't differentiate between server errors (500) and client errors (400/422)
- Provides poor user experience (users see console errors for normal validation failures)

---

## Files with API Error Handling

### 1. **auth.ts** - Authentication
- **Lines:** 71, 100, 134
- **Pattern:** Generic `catch (error: any)` with `showResult()` or `console.error()`
- **Issues:**
  - Login errors shown to user, but console.error for heartbeat
  - No differentiation between validation errors and server errors

### 2. **twofa.ts** - Two-Factor Authentication
- **Lines:** 41, 80, 146, 190, 210, 302
- **Pattern:** `catch` blocks with `showError()` or `showSuccess()`
- **Issues:**
  - All errors treated the same
  - No special handling for validation vs server errors

### 3. **gdpr.ts** - GDPR Operations
- **Lines:** 11, 39, 61, 83, 96, 116
- **Pattern:** `catch` with `console.error()` and `showGDPRMessage()`
- **Issues:**
  - Console.error called for ALL errors
  - User-friendly messages shown, but console cluttered

### 4. **gameService.ts** - Game Operations
- **Lines:** 62, 122, 188, 217, 229
- **Pattern:** Mixed - some `console.error()`, some silent
- **Issues:**
  - Inconsistent - some errors logged, others not
  - No structured error handling

### 5. **i18n.ts** - Internationalization
- **Lines:** 71, 96, 113, 128, 230
- **Pattern:** `catch (error)` with fallback to default language
- **Issues:**
  - Silent failures (good for i18n)
  - But could hide real server issues

### 6. **pages/profile.ts** - Profile Management
- **Lines:** 221, 305, 407, 437, 469, 523, 685
- **Pattern:** `catch` with `showProfileMessage()` or console.error
- **Issues:**
  - Mixed error handling
  - Some errors shown to user, others just logged

### 7. **pages/players.ts** - Players Page
- **Lines:** 147, 160, 297, 437
- **Pattern:** Checks for `auth.authenticationRequired` specifically
- **Good practices:**
  - ✅ Differentiates auth errors from other errors
  - ✅ Shows different messages based on error type
- **Issues:**
  - Could extend this pattern to other error types

### 8. **pages/friends.ts** - Friends Management
- **Lines:** 166, 222, 268, 298, 412, 483, 583, 607, 631, 661
- **Pattern:** `catch` with `showToast()` errors
- **Issues:**
  - All errors treated the same
  - No distinction between validation and server errors

### 9. **pages/dashboard.ts** - Dashboard
- **Lines:** 73
- **Pattern:** Silent catch or generic error handling
- **Issues:**
  - Could hide important errors

### 10. **pages/games.ts** - Games Page
- **Lines:** 270
- **Pattern:** Generic catch
- **Issues:**
  - No specific error handling

### 11. **pages/testpage.ts** - Test Page
- **Lines:** 132, 222
- **Pattern:** Generic catch with console.error
- **Issues:**
  - Test page, acceptable for debugging

### 12. **tournamentEngine.ts** - Tournament Operations
- **Lines:** 127, 152, 169, 219, 244, 263
- **Pattern:** `catch (error)` with `console.error()`
- **Issues:**
  - All errors logged to console
  - User feedback inconsistent

### 13. **imageUtils.ts** - Image Utilities
- **Lines:** 22
- **Pattern:** Returns default avatar on error
- **Good practices:**
  - ✅ Silent fallback for non-critical errors
  - ✅ Good UX pattern

---

## Current Error Handling Patterns

### Pattern 1: Generic Console.error (❌ BAD)
```typescript
try {
    await api(...);
} catch (error) {
    console.error('Error:', error);  // Shows for ALL errors including validation
}
```
**Problem:** Clutters console with expected validation errors

### Pattern 2: Show User Message (✅ BETTER)
```typescript
try {
    await api(...);
} catch (error: any) {
    showMessage(error.message, 'error');  // Good - shows user message
}
```
**Problem:** Still doesn't differentiate error types

### Pattern 3: Specific Error Checking (✅ BEST - Players.ts example)
```typescript
try {
    await api(...);
} catch (error: any) {
    if (error.message === 'auth.authenticationRequired') {
        // Handle auth error specifically
    } else {
        // Handle other errors
    }
}
```
**Good:** Differentiates error types

---

## Recommended Fix: Enhanced API Error Handling

### Step 1: Update api.ts with Custom Error Classes

```typescript
// Custom error classes for different scenarios
export class ValidationError extends Error {
    constructor(message: string, public details?: any) {
        super(message);
        this.name = 'ValidationError';
    }
}

export class AuthError extends Error {
    constructor(message: string) {
        super(message);
        this.name = 'AuthError';
    }
}

export class ConflictError extends Error {
    constructor(message: string) {
        super(message);
        this.name = 'ConflictError';
    }
}

export class ServerError extends Error {
    constructor(message: string) {
        super(message);
        this.name = 'ServerError';
    }
}

// Enhanced api function
async function api<T>(url: string, options: RequestInit = {}): Promise<T> {
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

    // Handle different status codes
    if (response.status === 422) {
        // Validation error - NO console.error, just throw
        throw new ValidationError(data.error, data.details);
    }
    
    if (response.status === 409) {
        // Conflict - NO console.error
        throw new ConflictError(data.error);
    }
    
    if (response.status === 401) {
        removeAuthToken();
        throw new AuthError(data.error);
    }

    if (response.status >= 500) {
        // ONLY NOW console.error - real server problem
        console.error('Server error:', data);
        throw new ServerError(data.error);
    }

    if (!response.ok) {
        throw new Error(data.error || 'Request failed');
    }

    return data;
}
```

### Step 2: Update Frontend Code to Handle Specific Errors

```typescript
// BEFORE (BAD)
try {
    await api('/api/auth/register', { ... });
} catch (error) {
    console.error('Registration error:', error);  // ❌ Shows for ALL errors
    showResult('registerResult', error.message, true);
}

// AFTER (GOOD)
try {
    await api('/api/auth/register', { ... });
} catch (error) {
    if (error instanceof ValidationError) {
        // Validation error - show user message, NO console.error
        showResult('registerResult', error.message, true);
    } else if (error instanceof ConflictError) {
        // Duplicate username - show user message, NO console.error
        showResult('registerResult', error.message, true);
    } else if (error instanceof AuthError) {
        // Auth error - redirect to login
        navigate('auth');
    } else {
        // Server error - NOW we console.error
        console.error('Unexpected error:', error);
        showResult('registerResult', 'messages.connectionError', true);
    }
}
```

---

## Action Items

1. ✅ Create custom error classes in api.ts
2. ✅ Update api() function to throw specific errors based on status codes
3. ❌ Update all 59 catch blocks to handle errors gracefully
4. ❌ Remove unnecessary console.error for validation errors
5. ❌ Add proper console.error only for 500+ server errors

---

## Expected Outcome

**After Fix:**
- ✅ Console stays clean (no validation errors logged)
- ✅ Users see appropriate messages based on error type
- ✅ Developers still see real server errors in console
- ✅ Better debugging experience
- ✅ Complies with project requirements (no unnecessary console errors/warnings)

---

## Files Requiring Updates

**Total:** 13 files, 59 catch blocks

### Priority Order:
1. **api.ts** - Core error handling (CRITICAL)
2. **auth.ts** - Login/register errors (HIGH)
3. **pages/profile.ts** - Profile updates (HIGH)
4. **pages/friends.ts** - Friend requests (MEDIUM)
5. **twofa.ts** - 2FA errors (MEDIUM)
6. **pages/players.ts** - Already good, minor improvements (LOW)
7. **gameService.ts** - Game operations (MEDIUM)
8. **tournamentEngine.ts** - Tournament errors (MEDIUM)
9. **gdpr.ts** - GDPR operations (LOW)
10. **i18n.ts** - Already handles well with silent fallback (LOW)
11. **pages/dashboard.ts** - Dashboard (LOW)
12. **pages/games.ts** - Games page (LOW)
13. **imageUtils.ts** - Already handles well (KEEP AS IS)
