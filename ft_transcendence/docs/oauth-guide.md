# OAuth Authentication Guide

## Overview

This project supports OAuth 2.0 authentication with GitHub. This allows users to sign in using their existing accounts from these platforms.

## Setup Requirements

### API Key Configuration

To enable OAuth authentication, you need to configure API keys in a `.env` file located in the **root of the project**.

The `.env` file should contain the necessary credentials for each OAuth provider you want to support:

```env
# GitHub OAuth
GITHUB_CLIENT_ID=your_github_client_id
GITHUB_CLIENT_SECRET=your_github_client_secret
```

**Note:** You can obtain these credentials by registering your application with each OAuth provider:
- **GitHub:** [GitHub OAuth Apps](https://github.com/settings/developers)

## How to Use OAuth Login

1. Navigate to your **profile page** in the application
2. Click on the **OAuth login button**
3. Follow the instructions provided by the OAuth provider
4. Authorize the application to access your account
5. You will be redirected back to the application and logged in automatically

## Important Notes

### Two-Factor Authentication (2FA) with OAuth

**Remember:** When logging in with OAuth, our application's 2FA system will be **ignored**.

This is by design, as two-factor authentication should be handled by the OAuth provider itself. If you want extra security when using OAuth login, please enable 2FA on your OAuth provider's account settings.

### Security Considerations

- OAuth tokens are securely managed through HashiCorp Vault
- All OAuth callbacks are validated and secured
- User data received from OAuth providers is handled according to our GDPR compliance policies

## Troubleshooting

**Issue:** OAuth login button doesn't work
- **Solution:** Ensure the `.env` file is properly configured with valid API keys

**Issue:** Redirected but not logged in
- **Solution:** Check that the callback URL registered with the OAuth provider matches your application's domain

**Issue:** Authorization denied
- **Solution:** Make sure you've authorized the application and granted the necessary permissions

For additional help, check the application logs or contact the development team.
