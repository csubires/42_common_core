import { api, ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError } from '../api.js';

export function renderDashboard(): string {
  setTimeout(checkServices, 100);

  return `
    <h2 class="text-3xl font-bold text-center text-cyan-400 mb-8" data-i18n="dashboard.dashboard">📊 Dashboard</h2>
    <div class="grid grid-cols-1 md:grid-cols-2 gap-6">
      <div class="card">
        <h3 class="text-xl font-bold mb-4" data-i18n="dashboard.services">Services</h3>
        <div id="services" class="space-y-3"></div>
        <button onclick="checkServices()" class="btn btn-blue mt-4" data-i18n="dashboard.refresh">🔄 Refresh</button>
      </div>
    </div>
  `;
}


const services = [
  { name: 'Gateway', url: '/api/gateway/health' },
  { name: 'Auth', url: '/api/auth/health' },
  { name: 'Database', url: '/api/database/health' },
  { name: 'I18n', url: '/api/i18n/health' },
];

export async function checkServices(): Promise<void> {
  const container = document.getElementById('services');
  if (!container) return;

  container.innerHTML = services.map(s => `
    <div class="flex items-center gap-3">
      <div class="status-dot status-loading" id="dot-${s.name}"></div>
      <span>${s.name}</span>
      <span id="status-${s.name}" class="text-gray-400">...</span>
    </div>
  `).join('');

  for (const s of services) {
    try {
      const data = await api<any>(s.url);

      const status = data.status || data.message || 'UNKNOWN';
      const isOk = status === 'OK' || status === 'ok' || status === 'healthy';

      const okMsg = window.languageManager?.t('dashboard.serviceOk') || 'OK';
      setStatus(s.name, isOk, okMsg);
    } catch (error: any) {
      if (error instanceof ServerError) {
        console.error(`Server error checking ${s.name}:`, error);
      }
      const unavailableMsg = window.languageManager?.t('dashboard.serviceUnavailable') || 'Service Unavailable';
      setStatus(s.name, false, unavailableMsg);
    }
  }
}

function setStatus(name: string, ok: boolean, text: string): void {
  const dot = document.getElementById(`dot-${name}`);
  const status = document.getElementById(`status-${name}`);
  if (dot) dot.className = `status-dot ${ok ? 'status-ok' : 'status-error'}`;
  if (status) status.textContent = text;
}

(window as any).checkServices = checkServices;
