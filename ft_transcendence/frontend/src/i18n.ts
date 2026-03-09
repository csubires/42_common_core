import { api, ValidationError, ConflictError, AuthError, ForbiddenError, NotFoundError, ServerError } from './api.js';

type Language = 'en' | 'es' | 'ja';

interface Translations {
	[key: string]: string | Translations;
}

declare global {
	interface Window {
		languageManager: LanguageManager;
		applyTranslationsToProfile?: () => void;
	}
}

export class LanguageManager {
	private translations: Translations = {};
	private currentLanguage: Language = 'en';
	private initialized = false;

	async init(): Promise<void> {
		if (this.initialized) return;

		await this.loadCurrentLanguage();
		await this.loadTranslations();
		this.renderLanguageSelector();
		this.applyTranslations();

		this.initialized = true;
	}

	renderLanguageSelector(containerSelector: string | null = null): void {

		this.attachLanguageSelectorEvents();
	}

	private attachLanguageSelectorEvents(): void {
		document.addEventListener('change', (e: Event) => {
			const target = e.target as HTMLElement;

			if (
				target instanceof HTMLSelectElement &&
				target.id === 'languageSelect'
			) {
				const lang = target.value as Language;
				if (lang === 'en' || lang === 'es' || lang === 'ja') {
					this.changeLanguage(lang);
				}
			}
		});
	}


	private async loadCurrentLanguage(): Promise<void> {
		try {
			const savedLang = localStorage.getItem('preferredLanguage') as Language | null;

			if (savedLang === 'en' || savedLang === 'es' || savedLang === 'ja') {
				this.currentLanguage = savedLang;
			} else {
				const browserLang = navigator.language.split('-')[0];
				if (browserLang === 'es' || browserLang === 'ja') {
					this.currentLanguage = browserLang as Language;
				} else {
					this.currentLanguage = 'en';
				}
				localStorage.setItem('preferredLanguage', this.currentLanguage);
			}

			await this.syncWithServer();
		} catch (error) {
			if (error instanceof ServerError) {
				console.error('Server error loading current language:', error);
			}
			this.currentLanguage =
				(localStorage.getItem('preferredLanguage') as Language) || 'en';
		}

		const select = document.getElementById('languageSelect') as HTMLSelectElement | null;
		if (select) {
			select.value = this.currentLanguage;
		}
	}

	private async syncWithServer(): Promise<void> {
		try {
			const result = await api<any>('/api/i18n/change-language', {
				method: 'POST',
				credentials: 'include',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify({ language: this.currentLanguage })
			});
if (!result?.success) {
	throw new Error('Failed to sync language with server');
}

			await result;
		} catch (error) {
			if (error instanceof ServerError) {
				console.warn('Server error syncing language:', error);
			}
		}
	}

	private async loadTranslations(): Promise<void> {
		try {
			const result = await api<any>(`/api/i18n/translations?language=${this.currentLanguage}&t=${Date.now()}`, {
				credentials: 'include'
			});

			if (result?.success) {
				throw new Error(`HTTP error! status: ${result.status}`);
			}

			this.translations = await result;
        
		} catch (error) {
			if (error instanceof ServerError) {
				console.error('Server error loading translations:', error);
			}
			await this.loadFallbackTranslations();
		}
	}

	private async loadFallbackTranslations(): Promise<void> {
		try {
			 const result = await api<any>(
				`/api/i18n/locales/${this.currentLanguage}.json?t=${Date.now()}`
			);

			if (!result?.success) {
				this.translations = await result;
			}
		} catch (error) {
			if (error instanceof ServerError) {
				console.error('Server error loading fallback translations:', error);
			}
			this.translations = {};
		}
	}

	applyTranslations(): void {
		if (!Object.keys(this.translations).length) {
			console.warn('No translations available to apply');
			return;
		}

		document.querySelectorAll<HTMLElement>('[data-i18n]').forEach(element => {
			const key = element.getAttribute('data-i18n');
			if (!key) return;

			const value = this.getTranslation(key);
			// Only update if translation exists (not null)
			if (value !== null && typeof value === 'string') {
				if (
					element instanceof HTMLInputElement &&
					(element.type === 'submit' || element.type === 'button')
				) {
					element.value = value;
				} else {
					element.textContent = value;
				}
			}
			// Otherwise, keep the original HTML content (fallback)
		});

		document
			.querySelectorAll<HTMLInputElement>('[data-i18n-placeholder]')
			.forEach(element => {
				const key = element.getAttribute('data-i18n-placeholder');
				if (!key) return;

				const value = this.getTranslation(key);
				if (value !== null && typeof value === 'string') {
					element.placeholder = value;
				}
			});

		document.body.classList.remove('i18n-loading');
		document.body.classList.add('i18n-loaded');

		window.dispatchEvent(new CustomEvent('translationsApplied'));
	}

	private getTranslation(key: string): string | null {
		const parts = key.split('.');
		let current: string | Translations | undefined = this.translations;

		for (const part of parts) {
			if (
				typeof current !== 'object' ||
				current === null ||
				!(part in current)
			) {
				return null; // Translation not found
			}
			current = (current as Translations)[part];
		}

		return typeof current === 'string' ? current : null;
	}

	public t(key: string): string | null {
		return this.getTranslation(key);
	}

	async changeLanguage(lang: Language): Promise<boolean> {
		try {
			if (lang !== 'en' && lang !== 'es' && lang !== 'ja') {
				throw new Error('Unsupported language');
			}
			this.currentLanguage = lang;
			localStorage.setItem('preferredLanguage', lang);

			const response = await api<any>('/api/i18n/change-language', {
				method: 'POST',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify({ language: lang }),
				credentials: 'include'
			});

			const result: { success: boolean; error?: string } = await response;

			if (!result.success) {
				throw new Error(result.error);
			}

			await this.loadTranslations();
			this.applyTranslations();

			const select = document.getElementById('languageSelect') as HTMLSelectElement | null;
			if (select) {
				select.value = lang;
			}

			window.applyTranslationsToProfile?.();
			return true;
		} catch (error) {
			if (error instanceof ServerError) {
				console.error('Server error changing language:', error);
			}
			this.currentLanguage = 'en';
			localStorage.setItem('preferredLanguage', 'en');
			return false;
		}
	}

	getCurrentLanguage(): Language {
		return this.currentLanguage;
	}

	isReady(): boolean {
		return (
			this.initialized &&
			Object.keys(this.translations).length > 0
		);
	}
}

window.languageManager = new LanguageManager();