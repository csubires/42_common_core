import { loadTournament } from "./tournamentEngine.js";
import { startCurrentMatch } from "./tournamentController.js";

(window as any).startCurrentMatch = startCurrentMatch;

function applyTranslations(): void {
	if ((window as any).languageManager?.isReady()) {
		(window as any).languageManager.applyTranslations();
	}
}

export function renderTournamentPage(): string {
	const tournament = loadTournament();
	if (!tournament) return `<p data-i18n="tournament.notFound">No tournament found</p>`;

	// Derive the type code from the stored gameType field
	const typeCode = tournament.gameType === 'tictactoe' ? 'T' : 'P';

	let html = `
    <div class="max-w-4xl mx-auto">
      <h1 class="text-4xl font-bold text-center text-yellow-400 mb-8" data-i18n="tournament.title">🏆 Tournament</h1>
  `;

	tournament.rounds.forEach((round, r) => {
		const isCurrentRound = r === tournament.currentRoundIndex;
		html += `
      <div class="mb-8">
        <h2 class="text-2xl font-bold mb-4 ${isCurrentRound ? 'text-yellow-400' : 'text-gray-400'}">
          <span data-i18n="tournament.round">Round</span> ${r + 1} ${isCurrentRound ? `<span data-i18n="tournament.current">(Current)</span>` : ''}
        </h2>
        <div class="grid gap-4">
    `;

		round.matches.forEach((match, m) => {
			const isCurrentMatch = isCurrentRound && m === tournament.currentMatchIndex;
			const matchStatus = match.winner
				? `<span class="text-green-400">✓ <span data-i18n="tournament.winner">Winner</span>: ${match.winner.name}</span>`
				: isCurrentMatch
					? `<span class="text-yellow-400" data-i18n="tournament.nextMatch">⏳ Next Match</span>`
					: `<span class="text-gray-400" data-i18n="tournament.pending">Pending</span>`;

			html += `
        <div class="card ${isCurrentMatch ? 'ring-2 ring-yellow-400' : ''}">
          <div class="flex justify-between items-center">
            <div class="flex-1">
              <div class="text-lg">${match.player1.name}</div>
              <div class="text-gray-400 text-sm" data-i18n="tournament.vs">vs</div>
              <div class="text-lg">${match.player2.name}</div>
            </div>
            <div class="text-right">
              ${matchStatus}
            </div>
          </div>
        </div>
      `;
		});

		html += `
        </div>
      </div>
    `;
	});

	html += `
      <div class="text-center mt-8">
        <button id="playNextMatchBtn" data-type="${typeCode}" class="btn btn-green text-xl px-8 py-4" data-i18n="tournament.playNext">
          ▶️ Play Next Match
        </button>
      </div>
    </div>
  `;

	// Attach listener after HTML is set (called from router after innerHTML is set)
	setTimeout(() => {
		const btn = document.getElementById('playNextMatchBtn');
		btn?.addEventListener('click', () => {
			const t = btn.getAttribute('data-type') ?? 'P';
			startCurrentMatch(t);
		});
	}, 0);

	return html;
}

(window as any).renderTournamentPage = renderTournamentPage;