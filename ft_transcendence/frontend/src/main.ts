import { initRouter } from './router.js';
import { initAuth } from './auth.js';
import { setupPongTournament } from './tournamentSetup.js';
import { setupTicTacToeTournament } from './tournamentSetup.js';
import { startCurrentMatch } from './tournamentController.js';
import './i18n.js';
import './gdpr.js';
import './pong.js';
import './tictactoe.js';
import './gameService.js';
import './tournamentSetup.js';
import './tournamentController.js';
import './tournamentEngine.js';
import './tournamentPage.js';

(window as any).setupPongTournament = setupPongTournament;
(window as any).setupTicTacToeTournament = setupTicTacToeTournament;
(window as any).startCurrentMatch = startCurrentMatch;

document.addEventListener('DOMContentLoaded', async () => {
  initRouter();
  initAuth();

  if (window.languageManager) {
    await window.languageManager.init();
    window.languageManager.applyTranslations();
  }

  setTimeout(() => {
    if (typeof window.updateAuthBtn === 'function') {
      window.updateAuthBtn();
    }
  }, 200);
});
