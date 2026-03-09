import { getToken } from './api.js';

// Helper function to fetch authenticated images and return blob URL
export async function fetchAuthenticatedImage(url: string): Promise<string | null> {
	try {
		const token = getToken();
		if (!token) return null;

		const response = await fetch(url, {
			headers: {
				'Authorization': `Bearer ${token}`
			}
		});

		if (!response.ok) {
			// Image not found or not accessible - return null for fallback
			return null;
		}

		const blob = await response.blob();
		return URL.createObjectURL(blob);
	} catch (error) {
		// Network error or other issue - return null for fallback
		return null;
	}
}

// Helper to load avatar with fallback
export async function loadAvatar(avatarUrl: string | null): Promise<string> {
  if (!avatarUrl) return '/default-avatar.png';

  if (avatarUrl.startsWith('http')) {
    return avatarUrl;
  }

  const authenticatedUrl = await fetchAuthenticatedImage(avatarUrl);
  return authenticatedUrl || '/default-avatar.png';
}