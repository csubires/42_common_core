# Enabling Two-Factor Authentication (2FA)

Two-Factor Authentication (2FA) adds an extra layer of security to your account. Our implementation uses a TOTP (Time-based One-Time Password) system, compatible with most authenticator apps. 

> Note: We are tsting with google authenticator but some Android authenticator apps may not sync correctly. If you encounter issues, see the alternatives below for generating codes.

## What is the 2FA Secret?

- The 2FA setup provides you with a unique SECRET key (e.g., `OBHG2SKNGBGHO4TBHZHW6KDBMMXEWM32GZKGGM3IJJSF4QJVJJNA`).
- This SECRET is critical—keep it safe! It is used to generate your authentication codes.
- Normally, the SECRET is stored securely by your authenticator app after scanning a QR code and you will not need to manipulate it. If the app does not work, you can use the following alternatives.


## How to Enable 2FA

1. Go to your profile and click the "Manage 2FA" button.  
	![Enable 2FA](_assets/enable2fa.png)

2. Use your preferred code generator (remember, TOTP codes expire every few seconds. We recomend google autheticator).  
	![Generate TOTP](_assets/gentot.png)

3. After enabling 2FA, you will receive recovery codes. Save these! They are used if you lose access to your authenticator app. Each code can only be used once.
	![Recovery Codes](_assets/backcodes.png)

5. 2FA is now enabled.  
	![2FA Enabled](_assets/okenablef2a.png)

6. From now on, after logging in with your email and password, you will also be prompted for a TOTP code.  
	![2FA Access](_assets/acces2fa.png)

## Disabling 2FA

To disable 2FA, click the "Disable 2FA" button in your profile. You will be asked for a TOTP code. Enter it to complete the process.

## Alternative Ways to Generate Codes

1. Use an online QR code tool like [qrcoderaptor.com](https://qrcoderaptor.com/es/).
2. Download and use the command-line tool `oathtool`:
	```sh
	sudo apt install oathtool
	oathtool --totp -b OBHG2SKNGBGHO4TBHZHW6KDBMMXEWM32GZKGGM3IJJSF4QJVJJNA
	```