export function renderTermsOfService(): string {
	return `
    <div class="max-w-4xl mx-auto space-y-4 sm:space-y-6 pb-8 px-2 sm:px-4">
      <div class="card">
        <h1 class="text-4xl font-bold mb-4 text-yellow-400" data-i18n="terms.title">Terms of Service</h1>
        <p class="text-gray-400 mb-4"><strong data-i18n="terms.lastUpdated">Last Updated:</strong> <span data-i18n="terms.lastUpdatedDate">February 18, 2026</span></p>
        <p class="text-gray-300 mb-4" data-i18n="terms.intro1">
          Welcome to Transcendence! These Terms of Service ("Terms") govern your access to and use of
          the Transcendence online gaming platform. By creating an account or using our services, you
          agree to be bound by these Terms.
        </p>
        <p class="text-gray-300 mb-4">
          <strong data-i18n="terms.intro2">Please read these Terms carefully before using our platform.</strong>
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s1Title">1. Acceptance of Terms</h2>
        <p class="text-gray-300 mb-4">
          <span data-i18n="terms.s1Text1Pre">By accessing or using Transcendence, you acknowledge that you have read, understood, and agree to be bound by these Terms, as well as our</span>
          <button onclick="navigate('privacy-policy')" class="text-yellow-400 hover:text-yellow-300 underline" data-i18n="terms.s1PrivacyLink">Privacy Policy</button>.
          <span data-i18n="terms.s1Text1Post">If you do not agree to these Terms, you may not use our services.</span>
        </p>
        <p class="text-gray-300 mb-4" data-i18n="terms.s1Text2">
          We reserve the right to modify these Terms at any time. Continued use of the platform after
          changes constitutes acceptance of the modified Terms.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s2Title">2. Eligibility</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s2Intro">
          You must meet the following requirements to use Transcendence:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s2Li1">Be at least 13 years of age</li>
          <li data-i18n="terms.s2Li2">If you are between 13 and 18, you should have parental or guardian consent</li>
          <li data-i18n="terms.s2Li3">Have the legal capacity to enter into binding agreements</li>
          <li data-i18n="terms.s2Li4">Not be prohibited from using the service under applicable laws</li>
          <li data-i18n="terms.s2Li5">Not have been previously banned or suspended from the platform</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="terms.s2Outro">
          By using Transcendence, you represent and warrant that you meet these eligibility requirements.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s3Title">3. Account Registration and Security</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s3AccTitle">3.1 Account Creation</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s3AccIntro">
          To access certain features, you must create an account by providing:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s3AccLi1">A unique username</li>
          <li data-i18n="terms.s3AccLi2">A valid email address</li>
          <li data-i18n="terms.s3AccLi3">A secure password</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="terms.s3AccOauth">
          Alternatively, you may register using OAuth authentication through supported third-party providers.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s3SecTitle">3.2 Account Security</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s3SecIntro">You are responsible for:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s3SecLi1">Maintaining the confidentiality of your password and account credentials</li>
          <li data-i18n="terms.s3SecLi2">All activities that occur under your account</li>
          <li data-i18n="terms.s3SecLi3">Notifying us immediately of any unauthorized access or security breach</li>
          <li data-i18n="terms.s3SecLi4">Enabling Two-Factor Authentication (2FA) for enhanced security (strongly recommended)</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s3AccuracyTitle">3.3 Account Accuracy</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s3AccuracyText">
          You agree to provide accurate, current, and complete information during registration and to
          update such information to keep it accurate and current. Providing false information may result
          in account termination.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s3ShareTitle">3.4 Account Sharing</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s3ShareText">
          You may not share your account with others or allow others to access your account. Each account
          is personal and non-transferable.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s4Title">4. Acceptable Use Policy</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s4PermTitle">4.1 Permitted Use</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s4PermIntro">
          Transcendence is provided for personal, non-commercial entertainment purposes. You may:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s4PermLi1">Play Pong and other available games</li>
          <li data-i18n="terms.s4PermLi2">Participate in tournaments and competitions</li>
          <li data-i18n="terms.s4PermLi3">Connect with other players and add friends</li>
          <li data-i18n="terms.s4PermLi4">View leaderboards and player statistics</li>
          <li data-i18n="terms.s4PermLi5">Customize your profile with avatars</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s4ProbTitle">4.2 Prohibited Conduct</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s4ProbIntro">You agree NOT to:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="terms.s4ProbCheat">Cheat or exploit:</strong> <span data-i18n="terms.s4ProbCheatDesc">Use bots, cheats, hacks, or exploits to gain unfair advantages</span></li>
          <li><strong data-i18n="terms.s4ProbHarass">Harass others:</strong> <span data-i18n="terms.s4ProbHarassDesc">Engage in harassment, bullying, hate speech, or threatening behavior</span></li>
          <li><strong data-i18n="terms.s4ProbSpam">Spam:</strong> <span data-i18n="terms.s4ProbSpamDesc">Send unsolicited messages or engage in disruptive behavior</span></li>
          <li><strong data-i18n="terms.s4ProbImpersonate">Impersonate:</strong> <span data-i18n="terms.s4ProbImpersonateDesc">Impersonate other users, staff, or any other person or entity</span></li>
          <li><strong data-i18n="terms.s4ProbLaws">Violate laws:</strong> <span data-i18n="terms.s4ProbLawsDesc">Use the platform for illegal activities or to violate applicable laws</span></li>
          <li><strong data-i18n="terms.s4ProbAttack">Attack the system:</strong> <span data-i18n="terms.s4ProbAttackDesc">Attempt to hack, DDoS, or compromise the platform's security</span></li>
          <li><strong data-i18n="terms.s4ProbScrape">Scrape data:</strong> <span data-i18n="terms.s4ProbScrapeDesc">Use automated tools to extract data from the platform</span></li>
          <li><strong data-i18n="terms.s4ProbReverse">Reverse engineer:</strong> <span data-i18n="terms.s4ProbReverseDesc">Decompile, disassemble, or reverse engineer any part of the platform</span></li>
          <li><strong data-i18n="terms.s4ProbMalware">Upload malware:</strong> <span data-i18n="terms.s4ProbMalwareDesc">Upload viruses, malware, or malicious code</span></li>
          <li><strong data-i18n="terms.s4ProbManipulate">Account manipulation:</strong> <span data-i18n="terms.s4ProbManipulateDesc">Create multiple accounts to manipulate rankings or abuse features</span></li>
          <li><strong data-i18n="terms.s4ProbContent">Inappropriate content:</strong> <span data-i18n="terms.s4ProbContentDesc">Upload offensive, explicit, or inappropriate avatars or content</span></li>
          <li><strong data-i18n="terms.s4ProbInterfere">Interfere with others:</strong> <span data-i18n="terms.s4ProbInterfereDesc">Disrupt the gaming experience of other users</span></li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s5Title">5. User-Generated Content</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s5ContentTitle">5.1 Your Content</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s5ContentText">
          You retain ownership of content you upload (such as profile avatars). However, by uploading
          content, you grant Transcendence a non-exclusive, worldwide, royalty-free license to use,
          display, and store such content for the purpose of operating the platform.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s5StdTitle">5.2 Content Standards</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s5StdIntro">All user-generated content must:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s5StdLi1">Comply with applicable laws and regulations</li>
          <li data-i18n="terms.s5StdLi2">Not infringe on intellectual property rights of others</li>
          <li data-i18n="terms.s5StdLi3">Not contain explicit, offensive, or inappropriate material</li>
          <li data-i18n="terms.s5StdLi4">Not promote violence, discrimination, or illegal activities</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s5ModTitle">5.3 Content Moderation</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s5ModText">
          We reserve the right to review, remove, or refuse any content that violates these Terms or
          that we deem inappropriate, without prior notice.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s6Title">6. Game Rules and Fair Play</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s6FairTitle">6.1 Fair Competition</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s6FairText">
          All players are expected to compete fairly. Cheating, match fixing, or any form of unfair
          gameplay is strictly prohibited and will result in penalties.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s6MatchTitle">6.2 Match Results</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s6MatchText">
          Match results are recorded automatically and are final. We may review and correct results only
          in cases of technical errors or proven cheating.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s6RankTitle">6.3 Rankings and Leaderboards</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s6RankText">
          Rankings are calculated based on match performance. We reserve the right to adjust rankings
          if manipulation or cheating is detected.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s6TournTitle">6.4 Tournaments</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s6TournText">
          Tournament participation is subject to specific rules that will be communicated for each event.
          Violations may result in disqualification.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s7Title">7. Intellectual Property</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s7RightsTitle">7.1 Our Rights</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s7RightsIntro">
          All content, features, and functionality of Transcendence, including but not limited to:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s7RightsLi1">Software code and architecture</li>
          <li data-i18n="terms.s7RightsLi2">Game mechanics and design</li>
          <li data-i18n="terms.s7RightsLi3">Graphics, logos, and trademarks</li>
          <li data-i18n="terms.s7RightsLi4">Text, images, and other materials</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="terms.s7RightsOutro">
          are owned by Transcendence and are protected by copyright, trademark, and other intellectual
          property laws. All rights not expressly granted are reserved.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s7LicTitle">7.2 Limited License</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s7LicText">
          We grant you a limited, non-exclusive, non-transferable, revocable license to access and use
          Transcendence for personal, non-commercial purposes in accordance with these Terms.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s7RestTitle">7.3 Restrictions</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s7RestIntro">You may not:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s7RestLi1">Copy, modify, or create derivative works of the platform</li>
          <li data-i18n="terms.s7RestLi2">Distribute, sell, or transfer any part of the platform</li>
          <li data-i18n="terms.s7RestLi3">Remove or modify any copyright, trademark, or proprietary notices</li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s8Title">8. Termination and Suspension</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s8ByYouTitle">8.1 Termination by You</h3>
        <p class="text-gray-300 mb-4">
          <span data-i18n="terms.s8ByYouPre">You may terminate your account at any time through the</span>
          <button onclick="navigate('gdpr')" class="text-yellow-400 hover:text-yellow-300 underline" data-i18n="terms.s8ByYouLink">Privacy &amp; Data Management</button>
          <span data-i18n="terms.s8ByYouPost">page. Upon termination, your personal data will be deleted or anonymized in accordance with our Privacy Policy.</span>
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s8ByUsTitle">8.2 Termination by Us</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s8ByUsIntro">
          We reserve the right to suspend or terminate your account immediately, without prior notice, if:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s8ByUsLi1">You violate these Terms of Service</li>
          <li data-i18n="terms.s8ByUsLi2">You engage in prohibited conduct or cheating</li>
          <li data-i18n="terms.s8ByUsLi3">Your account is used for fraudulent or illegal activities</li>
          <li data-i18n="terms.s8ByUsLi4">We are required to do so by law</li>
          <li data-i18n="terms.s8ByUsLi5">Continuing your access would harm other users or the platform</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s8EffectsTitle">8.3 Effects of Termination</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s8EffectsIntro">Upon termination:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s8EffectsLi1">Your right to access the platform immediately ceases</li>
          <li data-i18n="terms.s8EffectsLi2">Your account data will be handled according to our Privacy Policy</li>
          <li data-i18n="terms.s8EffectsLi3">Match history may be retained in anonymized form for leaderboard integrity</li>
          <li data-i18n="terms.s8EffectsLi4">Any pending friend requests or connections will be removed</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s8AppealsTitle">8.4 Appeals</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s8AppealsText">
          If you believe your account was suspended or terminated in error, you may contact us to appeal
          the decision. We will review appeals on a case-by-case basis.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s9Title">9. Disclaimers and Limitations of Liability</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s9AsIsTitle">9.1 Service "AS IS"</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s9AsIsIntro">
          Transcendence is provided "AS IS" and "AS AVAILABLE" without warranties of any kind, either
          express or implied, including but not limited to:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s9AsIsLi1">Warranties of merchantability or fitness for a particular purpose</li>
          <li data-i18n="terms.s9AsIsLi2">Warranties of uninterrupted or error-free service</li>
          <li data-i18n="terms.s9AsIsLi3">Warranties regarding the accuracy or reliability of content</li>
          <li data-i18n="terms.s9AsIsLi4">Warranties that the service will meet your requirements</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s9AvailTitle">9.2 Service Availability</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s9AvailIntro">
          We do not guarantee that the platform will be available at all times. We may experience:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s9AvailLi1">Scheduled maintenance and downtime</li>
          <li data-i18n="terms.s9AvailLi2">Technical issues or server problems</li>
          <li data-i18n="terms.s9AvailLi3">Updates or modifications to the service</li>
        </ul>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s9LiabTitle">9.3 Limitation of Liability</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s9LiabIntro">
          To the maximum extent permitted by law, Transcendence and its operators shall not be liable for:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s9LiabLi1">Any indirect, incidental, special, consequential, or punitive damages</li>
          <li data-i18n="terms.s9LiabLi2">Loss of profits, data, or goodwill</li>
          <li data-i18n="terms.s9LiabLi3">Service interruptions or errors</li>
          <li data-i18n="terms.s9LiabLi4">Actions or content of other users</li>
          <li data-i18n="terms.s9LiabLi5">Unauthorized access to your account</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="terms.s9LiabOutro">
          Our total liability to you for any claims arising from or related to these Terms or your use
          of the platform shall not exceed €100 or the amount you paid to us (if any) in the past 12 months.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s9UserTitle">9.4 User Responsibility</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s9UserIntro">You are solely responsible for:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s9UserLi1">Your interactions with other users</li>
          <li data-i18n="terms.s9UserLi2">Content you upload or share</li>
          <li data-i18n="terms.s9UserLi3">Your compliance with these Terms</li>
          <li data-i18n="terms.s9UserLi4">Any consequences of your actions on the platform</li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s10Title">10. Indemnification</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s10Intro">
          You agree to indemnify, defend, and hold harmless Transcendence, its operators, and affiliates
          from any claims, damages, liabilities, and expenses (including legal fees) arising from:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s10Li1">Your violation of these Terms</li>
          <li data-i18n="terms.s10Li2">Your violation of any applicable laws or regulations</li>
          <li data-i18n="terms.s10Li3">Your infringement of any third-party rights</li>
          <li data-i18n="terms.s10Li4">Your use or misuse of the platform</li>
          <li data-i18n="terms.s10Li5">Content you upload or share</li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s11Title">11. Privacy and Data Protection</h2>
        <p class="text-gray-300 mb-4">
          <span data-i18n="terms.s11Text1Pre">Your privacy is important to us. Please review our</span>
          <button onclick="navigate('privacy-policy')" class="text-yellow-400 hover:text-yellow-300 underline" data-i18n="terms.s11PrivacyLink">Privacy Policy</button>
          <span data-i18n="terms.s11Text1Post">to understand how we collect, use, and protect your personal information.</span>
        </p>
        <p class="text-gray-300 mb-4" data-i18n="terms.s11Text2">
          By using Transcendence, you consent to the collection and use of your information as described
          in the Privacy Policy. You have extensive privacy rights under GDPR and other applicable laws,
          which you can exercise through our Privacy &amp; Data Management page.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s12Title">12. Dispute Resolution</h2>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s12InfTitle">12.1 Informal Resolution</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s12InfText">
          If you have a dispute with us, please contact us first at support@transcendence.local to attempt
          to resolve the issue informally.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s12GovTitle">12.2 Governing Law</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s12GovText">
          These Terms shall be governed by and construed in accordance with the laws of the jurisdiction
          in which Transcendence operates, without regard to conflict of law principles.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s12JurisTitle">12.3 Jurisdiction</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s12JurisText">
          Any legal action or proceeding arising from these Terms shall be brought exclusively in the courts
          of competent jurisdiction in our operating location, and you consent to the personal jurisdiction
          of such courts.
        </p>

        <h3 class="text-xl font-semibold mb-3 text-gray-200" data-i18n="terms.s12EuTitle">12.4 EU Users</h3>
        <p class="text-gray-300 mb-4" data-i18n="terms.s12EuText">
          For users in the European Union, nothing in these Terms affects your statutory rights as a consumer
          under EU consumer protection laws.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s13Title">13. Modifications to the Service</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s13Intro">We reserve the right to:</p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s13Li1">Modify, suspend, or discontinue any aspect of the platform at any time</li>
          <li data-i18n="terms.s13Li2">Add or remove features and functionality</li>
          <li data-i18n="terms.s13Li3">Change game rules or mechanics</li>
          <li data-i18n="terms.s13Li4">Update system requirements</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="terms.s13Outro">
          We will make reasonable efforts to notify users of significant changes, but we are not obligated
          to provide advance notice for all modifications.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s14Title">14. Third-Party Services</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s14Intro">
          Transcendence may integrate with third-party services, including:
        </p>
        <ul class="list-disc list-inside text-gray-300 mb-4 space-y-2 ml-4">
          <li data-i18n="terms.s14Li1">OAuth authentication providers</li>
          <li data-i18n="terms.s14Li2">Monitoring and analytics tools</li>
        </ul>
        <p class="text-gray-300 mb-4" data-i18n="terms.s14Outro">
          Your use of third-party services is subject to their respective terms and conditions. We are
          not responsible for third-party services or their privacy practices.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s15Title">15. Severability</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s15Text">
          If any provision of these Terms is found to be invalid, illegal, or unenforceable, the remaining
          provisions shall continue in full force and effect. The invalid provision shall be modified to
          the minimum extent necessary to make it valid and enforceable.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s16Title">16. Entire Agreement</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s16Text">
          These Terms, together with our Privacy Policy, constitute the entire agreement between you and
          Transcendence regarding your use of the platform and supersede all prior agreements and understandings.
        </p>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s17Title">17. Contact Information</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s17Intro">
          If you have questions or concerns about these Terms of Service, please contact us:
        </p>
        <ul class="list-none text-gray-300 mb-4 space-y-2 ml-4">
          <li><strong data-i18n="terms.s17EmailLabel">Email:</strong> support@transcendence.local</li>
          <li><strong data-i18n="terms.s17LegalLabel">Legal inquiries:</strong> legal@transcendence.local</li>
        </ul>
      </div>

      <div class="card">
        <h2 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="terms.s18Title">18. Acknowledgment</h2>
        <p class="text-gray-300 mb-4" data-i18n="terms.s18Text1">
          By using Transcendence, you acknowledge that you have read, understood, and agree to be bound
          by these Terms of Service.
        </p>
        <p class="text-gray-300 mb-4 font-bold" data-i18n="terms.s18Text2">
          Thank you for being part of the Transcendence community. Enjoy the game! 🎮
        </p>
      </div>

      <div class="card">
        <div class="flex flex-wrap gap-4 justify-center">
          <button onclick="navigate('privacy-policy')" class="btn btn-yellow" data-i18n="terms.viewPrivacy">
            🔒 View Privacy Policy
          </button>
          <button onclick="navigate('home')" class="btn btn-gray" data-i18n="terms.backToHome">
            ← Back to Home
          </button>
        </div>
      </div>
    </div>
  `;
}
