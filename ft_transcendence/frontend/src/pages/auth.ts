export function renderAuth(): string {
  return `
    <div class="max-w-md mx-auto space-y-6">
      <div class="card">
        <h3 class="text-2xl font-bold mb-4 text-center" data-i18n="auth.login">Login</h3>
        <input id="loginEmail" type="email" placeholder="Email" data-i18n-placeholder="auth.email" class="input mb-3" />
        <input id="loginPassword" type="password" placeholder="Password" data-i18n-placeholder="auth.password" class="input mb-4" />
        <button onclick="login()" class="btn btn-blue w-full" data-i18n="auth.login">Login</button>
        <div id="loginResult" class="hidden"></div>
      </div>

      <div class="card">
        <h3 class="text-2xl font-bold mb-4 text-center" data-i18n="auth.register">Register</h3>
        <input id="regUsername" type="text" placeholder="Username" data-i18n-placeholder="auth.username" class="input mb-3" />
        <input id="regEmail" type="email" placeholder="Email" data-i18n-placeholder="auth.email" class="input mb-3" />
        <input id="regPassword" type="password" placeholder="Password" data-i18n-placeholder="auth.password" class="input mb-3" />
        
        <label class="flex items-start gap-3 mb-4 cursor-pointer text-sm">
          <input type="checkbox" id="termsAccepted" class="w-5 h-5 rounded mt-0.5 flex-shrink-0" />
          <span class="text-gray-300">
            <span data-i18n="auth.iAgreeTo">I agree to the</span>
            <button onclick="event.preventDefault(); navigate('terms-of-service');" class="text-yellow-400 hover:text-yellow-300 underline">
              <span data-i18n="auth.termsOfService">Terms of Service</span>
            </button>
            <span data-i18n="auth.and">and</span>
            <button onclick="event.preventDefault(); navigate('privacy-policy');" class="text-yellow-400 hover:text-yellow-300 underline">
              <span data-i18n="auth.privacyPolicy">Privacy Policy</span>
            </button>
          </span>
        </label>
        
        <button onclick="register()" class="btn btn-green w-full" data-i18n="auth.register">Register</button>
        <div id="registerResult" class="hidden"></div>
      </div>

      <div class="card">
        <a href="/api/oauth/github" class="github-btn">
            <svg width="20" height="20" style="margin-right: 8px;" viewBox="0 0 16 16" fill="currentColor">
                <path d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"/>
            </svg>
            <span data-i18n="auth.github"></span>
        </a>
      </div>

    </div>
  `;
}
