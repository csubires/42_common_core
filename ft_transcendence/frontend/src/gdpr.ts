import { api, ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError, clearToken } from './api.js';

export async function loadUserData(): Promise<any> {
  try {
    const data = await api<any>('/api/gdpr/user-data');
    if (data.success) {
      return data.data;
    } else {
      throw new Error(data.error);
    }
  } catch (error: any) {
    if (error instanceof ServerError) {
      console.error('Server error loading user data:', error);
    }
    throw error;
  }
}

export async function exportUserData(): Promise<void> {
  try {
    const result = await api<any>('/api/gdpr/export-data', {
      method: 'POST',
      body: JSON.stringify({ _dummy: true })
    });

    if (result.success) {
      const dataStr = JSON.stringify(result.data, null, 2);
      const dataBlob = new Blob([dataStr], { type: 'application/json' });
      const url = URL.createObjectURL(dataBlob);
      const link = document.createElement('a');
      link.href = url;
      link.download = `my-data-${new Date().toISOString().split('T')[0]}.json`;
      document.body.appendChild(link);
      link.click();
      document.body.removeChild(link);
      URL.revokeObjectURL(url);
      showGDPRMessage('messages.dataExported', 'success');
    } else {
      throw new Error(result.error);
    }
  } catch (error: any) {
    if (error instanceof ServerError) {
      console.error('Server error exporting data:', error);
    }
    showGDPRMessage('gdpr.exportError', 'error');
  }
}

export async function anonymizeUserData(): Promise<void> {
  try {
    const result = await api<any>('/api/gdpr/anonymize', {
      method: 'POST',
      body: JSON.stringify({ _dummy: true })
    });

    if (result.success) {
      showGDPRMessage('messages.dataAnonymized', 'success');
      setTimeout(() => {
        clearToken();
        if (typeof (window as any).updateAuthBtn === 'function') {
          (window as any).updateAuthBtn();
        }
        window.location.href = '/';
      }, 3000);
    } else {
      showGDPRMessage(result.error, 'error');
    }
  } catch (error: any) {
    if (error instanceof ServerError) {
      console.error('Server error anonymizing data:', error);
    }
    showGDPRMessage('messages.connectionError', 'error');
  }
}

export async function deleteAccount(confirmationText: string): Promise<void> {
  try {
    const result = await api<any>('/api/gdpr/delete-account', {
      method: 'POST',
      body: JSON.stringify({ confirmation: confirmationText })
    });

    if (result.success) {
      showGDPRMessage('messages.accountDeleted', 'success');
      setTimeout(() => {
        clearToken();
        if (typeof (window as any).updateAuthBtn === 'function') {
          (window as any).updateAuthBtn();
        }
        window.location.href = '/';
      }, 2000);
    } else {
      showGDPRMessage(result.error, 'error');
    }
  } catch (error: any) {
    if (error instanceof ServerError) {
      console.error('Server error deleting account:', error);
    }
    showGDPRMessage('messages.connectionError', 'error');
  }
}

export async function loadUserConsent(): Promise<any> {
  try {
    const data = await api<any>('/api/gdpr/user-consent');
    if (data.success) {
      return data.consent;
    }
    return null;
  } catch (error) {
    if (error instanceof ServerError) {
      console.error('Server error loading user consent:', error);
    }
    return null;
  }
}

export async function updateConsent(consentData: any): Promise<boolean> {
  try {
    const result = await api<any>('/api/gdpr/update-consent', {
      method: 'POST',
      body: JSON.stringify(consentData)
    });

    if (result.success) {
      showGDPRMessage('messages.preferencesUpdated', 'success');
      return true;
    } else {
      showGDPRMessage(result.error, 'error');
      return false;
    }
  } catch (error: any) {
    if (error instanceof ServerError) {
      console.error('Server error updating consent:', error);
    }
    showGDPRMessage('messages.connectionError', 'error');
    return false;
  }
}

function showGDPRMessage(message: string, type: 'success' | 'error'): void {
  const messageDiv = document.createElement('div');
  messageDiv.className = `fixed top-4 right-4 p-4 rounded-lg shadow-lg ${
    type === 'success' ? 'bg-green-600' : 'bg-red-600'
  } text-white z-50`;
  const translatedMessage = window.languageManager?.t(message) || message;
  messageDiv.textContent = translatedMessage;
  document.body.appendChild(messageDiv);
  setTimeout(() => {
    messageDiv.remove();
  }, 5000);
}

(window as any).exportUserData = exportUserData;
(window as any).anonymizeUserData = anonymizeUserData;
(window as any).deleteAccount = deleteAccount;
