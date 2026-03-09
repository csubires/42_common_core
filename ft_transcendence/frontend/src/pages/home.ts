export function renderHome(): string {
  return `
    <div class="text-center py-20">
      <h1 class="text-3xl sm:text-4xl md:text-5xl lg:text-6xl xl:text-7xl font-extrabold text-yellow-400 mb-8">TRANSCENDENCE</h1>
      <p class="text-base sm:text-lg md:text-xl text-gray-400 mb-12" data-i18n="profile.madeBy">Made by DaBesTim</p>
      <div class="flex justify-center gap-4">
        <button onclick="navigate('games')" class="btn btn-yellow px-8 py-4 text-xl" data-i18n="auth.playGame">🎮 Play</button>
        <button onclick="navigate('dashboard')" class="btn btn-gray px-8 py-4 text-xl" data-i18n="profile.dashboard">📊 Dashboard</button>
      </div>
    </div>
  `;
}
