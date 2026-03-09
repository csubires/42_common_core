export function renderPrivacyPolicy(): string {
	return `
    <div class="max-w-4xl mx-auto space-y-4 sm:space-y-6 pb-8 px-2 sm:px-4">
      <div class="card">
        <h1 class="text-4xl font-bold mb-4 text-yellow-400" data-i18n="privacy.privacy">Privacy Policy</h1>
        <p class="text-gray-400 mb-4"><strong data-i18n="privacy.lastUpdated">Last Updated:</strong> <span data-i18n="privacy.lastUpdatedDate">February 18, 2026</span></p>
        <p class="text-gray-300 mb-4" data-i18n="privacy.intro">
          At Transcendence, we take your privacy seriously. This Privacy Policy explains how we collect,
          use, disclose, and safeguard your information when you use our online Pong gaming platform.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s1Title">1. Information We Collect</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s1AccTitle">1.1 Account Information</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s1AccIntro">
          When you create an account, we collect:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s1AccUsername">Username:</strong> <span data-i18n="privacy.s1AccUsernameDesc">Your chosen display name</span></li>
          <li><strong data-i18n="privacy.s1AccEmail">Email address:</strong> <span data-i18n="privacy.s1AccEmailDesc">For account verification and communication</span></li>
          <li><strong data-i18n="privacy.s1AccPassword">Password:</strong> <span data-i18n="privacy.s1AccPasswordDesc">Stored securely using industry-standard hashing (bcrypt)</span></li>
          <li><strong data-i18n="privacy.s1AccAvatar">Profile avatar:</strong> <span data-i18n="privacy.s1AccAvatarDesc">Optional image you upload</span></li>
          <li><strong data-i18n="privacy.s1Acc2fa">Two-Factor Authentication (2FA) data:</strong> <span data-i18n="privacy.s1Acc2faDesc">If you enable 2FA for enhanced security</span></li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s1OauthTitle">1.2 OAuth Authentication</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s1OauthIntro">
          If you choose to authenticate via OAuth providers (such as 42 School, Google, or other third-party services),
          we receive:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="privacy.s1OauthId">Your OAuth provider ID</li>
          <li data-i18n="privacy.s1OauthProfile">Basic profile information (name, email) as permitted by the provider</li>
          <li data-i18n="privacy.s1OauthPicture">Profile picture from the OAuth provider</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s1GamingTitle">1.3 Gaming Data</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s1GamingIntro">
          We automatically collect and store gameplay information:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s1GamingMatch">Match history:</strong> <span data-i18n="privacy.s1GamingMatchDesc">Records of games played, scores, opponents, and timestamps</span></li>
          <li><strong data-i18n="privacy.s1GamingTournament">Tournament participation:</strong> <span data-i18n="privacy.s1GamingTournamentDesc">Your participation in tournaments and results</span></li>
          <li><strong data-i18n="privacy.s1GamingStats">Game statistics:</strong> <span data-i18n="privacy.s1GamingStatsDesc">Win/loss ratios, performance metrics</span></li>
          <li><strong data-i18n="privacy.s1GamingRankings">Player rankings:</strong> <span data-i18n="privacy.s1GamingRankingsDesc">Your competitive ranking and leaderboard position</span></li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s1SocialTitle">1.4 Social Features</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s1SocialIntro">
          When you use our social features, we collect:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s1SocialFriends">Friend connections:</strong> <span data-i18n="privacy.s1SocialFriendsDesc">List of players you've added as friends</span></li>
          <li><strong data-i18n="privacy.s1SocialRequests">Friend requests:</strong> <span data-i18n="privacy.s1SocialRequestsDesc">Pending and accepted friend requests</span></li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s1TechTitle">1.5 Technical Information</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s1TechIntro">
          We automatically collect technical data:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s1TechSession">Session data:</strong> <span data-i18n="privacy.s1TechSessionDesc">Login times, session duration, and activity logs</span></li>
          <li><strong data-i18n="privacy.s1TechIp">IP addresses:</strong> <span data-i18n="privacy.s1TechIpDesc">For security and fraud prevention</span></li>
          <li><strong data-i18n="privacy.s1TechBrowser">Browser information:</strong> <span data-i18n="privacy.s1TechBrowserDesc">Browser type, version, and language preferences</span></li>
          <li><strong data-i18n="privacy.s1TechCookies">Cookies:</strong> <span data-i18n="privacy.s1TechCookiesDesc">Essential cookies for authentication and preferences (see Cookie Policy below)</span></li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s2Title">2. How We Use Your Information</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s2Intro">We use the collected information for:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s2Account">Account Management:</strong> <span data-i18n="privacy.s2AccountDesc">Creating and maintaining your account</span></li>
          <li><strong data-i18n="privacy.s2Auth">Authentication:</strong> <span data-i18n="privacy.s2AuthDesc">Verifying your identity and maintaining secure sessions</span></li>
          <li><strong data-i18n="privacy.s2Gameplay">Game Functionality:</strong> <span data-i18n="privacy.s2GameplayDesc">Enabling gameplay, matchmaking, and tournament features</span></li>
          <li><strong data-i18n="privacy.s2Leaderboards">Leaderboards &amp; Rankings:</strong> <span data-i18n="privacy.s2LeaderboardsDesc">Displaying player statistics and competitive rankings</span></li>
          <li><strong data-i18n="privacy.s2Social">Social Features:</strong> <span data-i18n="privacy.s2SocialDesc">Facilitating friend connections and social interactions</span></li>
          <li><strong data-i18n="privacy.s2Comms">Communication:</strong> <span data-i18n="privacy.s2CommsDesc">Sending important account-related notifications</span></li>
          <li><strong data-i18n="privacy.s2Security">Security:</strong> <span data-i18n="privacy.s2SecurityDesc">Detecting and preventing fraud, abuse, and unauthorized access</span></li>
          <li><strong data-i18n="privacy.s2Improvement">Service Improvement:</strong> <span data-i18n="privacy.s2ImprovementDesc">Analyzing usage patterns to improve our platform</span></li>
          <li><strong data-i18n="privacy.s2Legal">Legal Compliance:</strong> <span data-i18n="privacy.s2LegalDesc">Meeting legal obligations and enforcing our Terms of Service</span></li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s3Title">3. Legal Basis for Processing (GDPR)</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s3Intro">
          For users in the European Union, we process your personal data under the following legal bases:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s3Contractual">Contractual Necessity:</strong> <span data-i18n="privacy.s3ContractualDesc">To provide the gaming service you've signed up for</span></li>
          <li><strong data-i18n="privacy.s3Legitimate">Legitimate Interests:</strong> <span data-i18n="privacy.s3LegitimateDesc">To improve our services, ensure security, and prevent fraud</span></li>
          <li><strong data-i18n="privacy.s3Consent">Consent:</strong> <span data-i18n="privacy.s3ConsentDesc">For optional features like analytics (where required)</span></li>
          <li><strong data-i18n="privacy.s3LegalObligation">Legal Obligation:</strong> <span data-i18n="privacy.s3LegalObligationDesc">To comply with applicable laws and regulations</span></li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s4Title">4. Data Sharing and Disclosure</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s4NoSellTitle">4.1 We DO NOT Sell Your Data</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s4NoSellText">
          We do not sell, rent, or trade your personal information to third parties for marketing purposes.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s4PublicTitle">4.2 Public Information</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s4PublicIntro">
          The following information is publicly visible to other users:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="privacy.s4PublicUsername">Username and avatar</li>
          <li data-i18n="privacy.s4PublicMatch">Match history and game statistics</li>
          <li data-i18n="privacy.s4PublicRankings">Player rankings and leaderboard position</li>
          <li data-i18n="privacy.s4PublicTournament">Tournament participation</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s4ProvidersTitle">4.3 Service Providers</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s4ProvidersIntro">
          We may share data with trusted service providers who assist us:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s4ProvidersOauth">OAuth Providers:</strong> <span data-i18n="privacy.s4ProvidersOauthDesc">For third-party authentication</span></li>
          <li><strong data-i18n="privacy.s4ProvidersHosting">Hosting Services:</strong> <span data-i18n="privacy.s4ProvidersHostingDesc">To store and serve our application</span></li>
          <li><strong data-i18n="privacy.s4ProvidersMonitoring">Monitoring Tools:</strong> <span data-i18n="privacy.s4ProvidersMonitoringDesc">For performance monitoring and error tracking (Prometheus, Grafana)</span></li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="privacy.s4LegalTitle">4.4 Legal Requirements</h3>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s4LegalText">
          We may disclose your information if required by law, court order, or to protect our rights and safety.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s5Title">5. Data Security</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s5Intro">
          We implement robust security measures to protect your data:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s5Encryption">Encryption:</strong> <span data-i18n="privacy.s5EncryptionDesc">SSL/TLS encryption for data in transit</span></li>
          <li><strong data-i18n="privacy.s5Passwords">Password Protection:</strong> <span data-i18n="privacy.s5PasswordsDesc">Bcrypt hashing for password storage</span></li>
          <li><strong data-i18n="privacy.s5Vault">Vault Integration:</strong> <span data-i18n="privacy.s5VaultDesc">Secure storage for sensitive credentials using HashiCorp Vault</span></li>
          <li><strong data-i18n="privacy.s5TwoFa">Two-Factor Authentication:</strong> <span data-i18n="privacy.s5TwoFaDesc">Optional 2FA for enhanced account security</span></li>
          <li><strong data-i18n="privacy.s5Sessions">Session Management:</strong> <span data-i18n="privacy.s5SessionsDesc">Secure JWT tokens with expiration</span></li>
          <li><strong data-i18n="privacy.s5Headers">Security Headers:</strong> <span data-i18n="privacy.s5HeadersDesc">Implementation of CORS, CSP, and other security headers</span></li>
          <li><strong data-i18n="privacy.s5RateLimit">Rate Limiting:</strong> <span data-i18n="privacy.s5RateLimitDesc">Protection against brute force attacks</span></li>
          <li><strong data-i18n="privacy.s5Modsec">ModSecurity:</strong> <span data-i18n="privacy.s5ModsecDesc">Web application firewall for threat prevention</span></li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s5Disclaimer">
          However, no method of transmission over the internet is 100% secure. While we strive to protect
          your data, we cannot guarantee absolute security.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s6Title">6. Cookie Policy</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s6Intro">
          We use cookies and similar technologies for:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s6Essential">Essential Cookies:</strong> <span data-i18n="privacy.s6EssentialDesc">Required for authentication and session management</span></li>
          <li><strong data-i18n="privacy.s6Preference">Preference Cookies:</strong> <span data-i18n="privacy.s6PreferenceDesc">Storing your language and theme preferences</span></li>
          <li><strong data-i18n="privacy.s6Security">Security Cookies:</strong> <span data-i18n="privacy.s6SecurityDesc">Preventing fraud and enhancing security</span></li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s6Note">
          You can control cookies through your browser settings, but disabling essential cookies may
          prevent you from using certain features.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s7Title">7. Data Retention</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s7Intro">
          We retain your personal data for as long as necessary to provide our services and comply with legal obligations:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s7Active">Active Accounts:</strong> <span data-i18n="privacy.s7ActiveDesc">Data retained while your account is active</span></li>
          <li><strong data-i18n="privacy.s7Inactive">Inactive Accounts:</strong> <span data-i18n="privacy.s7InactiveDesc">Data retained for 2 years after last login, then anonymized or deleted</span></li>
          <li><strong data-i18n="privacy.s7Match">Match History:</strong> <span data-i18n="privacy.s7MatchDesc">Retained indefinitely for leaderboard integrity (anonymized if you delete your account)</span></li>
          <li><strong data-i18n="privacy.s7Logs">Security Logs:</strong> <span data-i18n="privacy.s7LogsDesc">Retained for 90 days</span></li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s8Title">8. Your Privacy Rights</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s8Intro">
          You have the following rights regarding your personal data:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s8Access">Right to Access:</strong> <span data-i18n="privacy.s8AccessDesc">Request a copy of your personal data</span></li>
          <li><strong data-i18n="privacy.s8Rectification">Right to Rectification:</strong> <span data-i18n="privacy.s8RectificationDesc">Correct inaccurate or incomplete data</span></li>
          <li><strong data-i18n="privacy.s8Erasure">Right to Erasure:</strong> <span data-i18n="privacy.s8ErasureDesc">Request deletion of your personal data ("Right to be Forgotten")</span></li>
          <li><strong data-i18n="privacy.s8Portability">Right to Data Portability:</strong> <span data-i18n="privacy.s8PortabilityDesc">Export your data in a machine-readable format</span></li>
          <li><strong data-i18n="privacy.s8Object">Right to Object:</strong> <span data-i18n="privacy.s8ObjectDesc">Object to processing of your personal data</span></li>
          <li><strong data-i18n="privacy.s8Restriction">Right to Restriction:</strong> <span data-i18n="privacy.s8RestrictionDesc">Request restriction of processing</span></li>
          <li><strong data-i18n="privacy.s8Withdraw">Right to Withdraw Consent:</strong> <span data-i18n="privacy.s8WithdrawDesc">Withdraw consent at any time</span></li>
        </ul>
        <p class="text-gray-300 mb-4">
          <span data-i18n="privacy.s8ExercisePre">You can exercise these rights through the</span>
          <button onclick="navigate('gdpr')" class="text-yellow-400 hover:text-yellow-300 underline" data-i18n="privacy.s8ExerciseLink">Privacy &amp; Data Management</button>
          <span data-i18n="privacy.s8ExercisePost">page in your profile, where you can:</span>
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="privacy.s8Export">Export all your personal data</li>
          <li data-i18n="privacy.s8Manage">Manage your privacy preferences</li>
          <li data-i18n="privacy.s8Anonymize">Anonymize your account data</li>
          <li data-i18n="privacy.s8Delete">Delete your account permanently</li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s9Title">9. Children's Privacy</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s9Text1">
          Transcendence is not intended for users under the age of 13. We do not knowingly collect
          personal information from children under 13. If we become aware that a child under 13 has
          provided us with personal information, we will take steps to delete such information.
        </p>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s9Text2">
          For users between 13 and 18, we recommend obtaining parental consent before using our services.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s10Title">10. International Data Transfers</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s10Text">
          Your data may be transferred to and processed in countries other than your country of residence.
          We ensure appropriate safeguards are in place to protect your personal information in accordance
          with this Privacy Policy and applicable data protection laws.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s11Title">11. Third-Party Links</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s11Text">
          Our platform may contain links to third-party websites or services (such as OAuth providers).
          We are not responsible for the privacy practices of these third parties. We encourage you to
          review their privacy policies.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s12Title">12. Changes to This Privacy Policy</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s12Intro">
          We may update this Privacy Policy from time to time. We will notify you of significant changes by:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="privacy.s12Date">Updating the "Last Updated" date at the top of this policy</li>
          <li data-i18n="privacy.s12Notice">Posting a notice on our platform</li>
          <li data-i18n="privacy.s12Email">Sending an email notification for material changes</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s12Acceptance">
          Your continued use of Transcendence after changes are posted constitutes acceptance of the updated policy.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="privacy.s13Title">13. Contact Us</h2>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s13Intro">
          If you have questions, concerns, or requests regarding this Privacy Policy or your personal data, please contact us:
        </p>
        <ul class="list-none text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="privacy.s13EmailLabel">Email:</strong> privacy@transcendence.local</li>
          <li><strong data-i18n="privacy.s13DpoLabel">Data Protection Officer:</strong> dpo@transcendence.local</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="privacy.s13Eu">
          For EU residents: If you believe we have not adequately addressed your concerns, you have the
          right to lodge a complaint with your local data protection authority.
        </p>
      </div>

      <div class="card">
        <div class="flex flex-wrap gap-4 justify-center">
          <button onclick="navigate('terms-of-service')" class="btn btn-yellow" data-i18n="privacy.viewTerms">
            📜 View Terms of Service
          </button>
          <button onclick="navigate('home')" class="btn btn-gray" data-i18n="privacy.backToHome">
            ← Back to Home
          </button>
        </div>
      </div>
    </div>
  `;
}
