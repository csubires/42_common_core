import { loadUserData, exportUserData, anonymizeUserData, deleteAccount, loadUserConsent, updateConsent } from '../gdpr.js';
import { navigate } from '../router.js';

export function renderGdpr(): string {
  setTimeout(initGdpr, 100);

  return `
    <div class="max-w-4xl mx-auto space-y-6">
      <div class="card">
        <h2 class="text-3xl font-bold mb-2" data-i18n="gdpr.title">Privacy & Data Management</h2>
        <p class="text-gray-400 mb-6" data-i18n="gdpr.subtitle">Manage your personal data and privacy preferences</p>
      </div>

      <div class="card">
        <h3 class="text-xl font-bold mb-4" data-i18n="gdpr.personalData">Your Personal Data</h3>
        <div id="userDataSummary" class="mb-4">
          <div class="animate-pulse space-y-2">
            <div class="h-4 bg-gray-700 rounded w-3/4"></div>
            <div class="h-4 bg-gray-700 rounded w-1/2"></div>
          </div>
        </div>
        <button onclick="window.exportUserData()" class="btn btn-blue" data-i18n="gdpr.exportData">
          📥 Export My Data
        </button>
      </div>

      <div class="card">
        <h3 class="text-xl font-bold mb-4" data-i18n="gdpr.privacyPreferences">Privacy Preferences</h3>
        <form id="consentForm" class="space-y-4">
          <label class="flex items-center gap-3 cursor-pointer">
            <input type="checkbox" id="dataProcessing" class="w-5 h-5 rounded">
            <span data-i18n="gdpr.dataProcessing">Essential data processing</span>
          </label>
          <label class="flex items-center gap-3 cursor-pointer">
            <input type="checkbox" id="marketingEmails" class="w-5 h-5 rounded">
            <span data-i18n="gdpr.marketingEmails">Marketing emails</span>
          </label>
          <label class="flex items-center gap-3 cursor-pointer">
            <input type="checkbox" id="analytics" class="w-5 h-5 rounded">
            <span data-i18n="gdpr.analytics">Analytics and statistics</span>
          </label>
          <button type="submit" class="btn btn-blue" data-i18n="gdpr.savePreferences">
            Save Preferences
          </button>
        </form>
      </div>

      <div class="card bg-yellow-900/20 border border-yellow-600/50">
        <h3 class="text-xl font-bold mb-4 text-yellow-400" data-i18n="gdpr.anonymization">Anonymize Data</h3>
        <p class="text-gray-300 mb-4" data-i18n="gdpr.anonymizationDesc">
          Anonymize your personal data while keeping your account active
        </p>
        <ul class="list-disc list-inside text-gray-400 mb-4 space-y-1">
          <li data-i18n="gdpr.anonymizationList.0">Email will be replaced with anonymous ID</li>
          <li data-i18n="gdpr.anonymizationList.1">Username will be anonymized</li>
          <li data-i18n="gdpr.anonymizationList.2">Personal data will be removed</li>
        </ul>
        <button onclick="showAnonymizeModal()" class="btn btn-yellow" data-i18n="gdpr.anonymizeData">
          🔒 Anonymize My Data
        </button>
      </div>

      <div class="card bg-red-900/20 border border-red-600/50">
        <h3 class="text-xl font-bold mb-4 text-red-400" data-i18n="gdpr.accountDeletion">Delete Account</h3>
        <p class="text-gray-300 mb-4" data-i18n="gdpr.deletionDesc">
          Permanently delete your account and all associated data
        </p>
        <ul class="list-disc list-inside text-gray-400 mb-4 space-y-1">
          <li data-i18n="gdpr.deletionList.0">All personal data will be deleted</li>
          <li data-i18n="gdpr.deletionList.1">This action is irreversible</li>
          <li data-i18n="gdpr.deletionList.2">You will be logged out immediately</li>
        </ul>
        <button onclick="showDeleteModal()" class="btn btn-red" data-i18n="gdpr.deleteAccount">
          🗑️ Delete My Account
        </button>
      </div>

      <div class="card">
        <button onclick="navigate('profile')" class="btn btn-gray" data-i18n="common.back">
          ← Back to Profile
        </button>
      </div>
    </div>

    <div id="anonymizeModal" class="modal hidden">
      <div class="modal-content card max-w-lg">
        <h3 class="text-2xl font-bold mb-4 text-yellow-400" data-i18n="gdpr.anonymizeConfirmation">Confirm Anonymization</h3>
        <p class="mb-4" data-i18n="gdpr.anonymizeConfirmText">Are you sure you want to anonymize your data?</p>
        <div class="flex gap-4">
          <button onclick="confirmAnonymize()" class="btn btn-yellow flex-1" data-i18n="gdpr.yesAnonymize">Yes, Anonymize</button>
          <button onclick="hideAnonymizeModal()" class="btn btn-gray flex-1" data-i18n="common.cancel">Cancel</button>
        </div>
      </div>
    </div>

    <div id="deleteModal" class="modal hidden">
      <div class="modal-content card max-w-lg">
        <h3 class="text-2xl font-bold mb-4 text-red-400" data-i18n="gdpr.deletionConfirmation">Confirm Account Deletion</h3>
        <p class="mb-4" data-i18n="gdpr.deletionWarning">This action cannot be undone!</p>
        <p class="mb-4">
          <span data-i18n="gdpr.typeConfirmation">To confirm, type:</span>
          <strong id="deleteConfirmationTextDisplay" class="text-red-400"></strong>
        </p>
        <input type="text" id="deleteConfirmInput" class="input mb-4" data-i18n-placeholder="gdpr.deleteConfirmationText">
        <div class="flex gap-4">
          <button onclick="confirmDelete()" class="btn btn-red flex-1" data-i18n="gdpr.deleteButton">Delete Forever</button>
          <button onclick="hideDeleteModal()" class="btn btn-gray flex-1" data-i18n="common.cancel">Cancel</button>
        </div>
      </div>
    </div>
  `;
}

async function initGdpr(): Promise<void> {
  try {
    const data = await loadUserData();
    displayUserData(data);

    const consent = await loadUserConsent();
    if (consent) {
      (document.getElementById('dataProcessing') as HTMLInputElement).checked = consent.dataProcessing;
      (document.getElementById('marketingEmails') as HTMLInputElement).checked = consent.marketingEmails;
      (document.getElementById('analytics') as HTMLInputElement).checked = consent.analytics;
    }

    const form = document.getElementById('consentForm');
    if (form) {
      form.addEventListener('submit', handleConsentSubmit);
    }

    window.languageManager?.applyTranslations();
  } catch (error) {
    console.error('Error initializing GDPR:', error);
  }
}

function displayUserData(data: any): void {
  const summaryDiv = document.getElementById('userDataSummary');
  if (!summaryDiv || !data?.dataSummary) return;

  summaryDiv.innerHTML = `
    <div class="grid grid-cols-1 md:grid-cols-3 gap-4">
      <div class="p-4 bg-gray-800 rounded-lg">
        <div class="text-gray-400 text-sm" data-i18n="gdpr.sessions">Sessions</div>
        <div class="text-2xl font-bold">${data.dataSummary.activity?.sessionCount || 0}</div>
      </div>
      <div class="p-4 bg-gray-800 rounded-lg">
        <div class="text-gray-400 text-sm" data-i18n="gdpr.accountCreated">Account Created</div>
        <div class="text-lg font-bold">${new Date(data.dataSummary.activity?.accountCreated).toLocaleDateString()}</div>
      </div>
      <div class="p-4 bg-gray-800 rounded-lg">
        <div class="text-gray-400 text-sm" data-i18n="gdpr.lastUpdated">Last Updated</div>
        <div class="text-lg font-bold">${new Date(data.dataSummary.activity?.lastUpdated).toLocaleDateString()}</div>
      </div>
    </div>
  `;

  window.languageManager?.applyTranslations();
}

async function handleConsentSubmit(e: Event): Promise<void> {
  e.preventDefault();

  const consentData = {
    dataProcessing: (document.getElementById('dataProcessing') as HTMLInputElement).checked,
    marketingEmails: (document.getElementById('marketingEmails') as HTMLInputElement).checked,
    analytics: (document.getElementById('analytics') as HTMLInputElement).checked
  };

  await updateConsent(consentData);
}

function showAnonymizeModal(): void {
  document.getElementById('anonymizeModal')?.classList.remove('hidden');
}

function hideAnonymizeModal(): void {
  document.getElementById('anonymizeModal')?.classList.add('hidden');
}

function showDeleteModal(): void {
  const expectedText = window.languageManager?.t('gdpr.deleteConfirmationText') || 'DELETE MY ACCOUNT';
  const displayElement = document.getElementById('deleteConfirmationTextDisplay');
  if (displayElement) {
    displayElement.textContent = expectedText;
  }
  const input = document.getElementById('deleteConfirmInput') as HTMLInputElement;
  if (input) {
    input.value = '';
    input.placeholder = expectedText;
  }
  document.getElementById('deleteModal')?.classList.remove('hidden');
}

function hideDeleteModal(): void {
  document.getElementById('deleteModal')?.classList.add('hidden');
}

async function confirmAnonymize(): Promise<void> {
  hideAnonymizeModal();
  await anonymizeUserData();
}

async function confirmDelete(): Promise<void> {
  const input = (document.getElementById('deleteConfirmInput') as HTMLInputElement).value;
  const expectedText = window.languageManager?.t('gdpr.deleteConfirmationText') || 'DELETE MY ACCOUNT';

  if (input === expectedText) {
    hideDeleteModal();
    await deleteAccount(expectedText);
  } else {
    const errorMsg = window.languageManager?.t('gdpr.confirmationTextMismatch') || 'Please type the confirmation text exactly';
    alert(errorMsg);
  }
}

(window as any).showAnonymizeModal = showAnonymizeModal;
(window as any).hideAnonymizeModal = hideAnonymizeModal;
(window as any).showDeleteModal = showDeleteModal;
(window as any).hideDeleteModal = hideDeleteModal;
(window as any).confirmAnonymize = confirmAnonymize;
(window as any).confirmDelete = confirmDelete;
