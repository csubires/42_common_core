export function renderGame(): string {
  return `
    <div class="flex flex-col items-center w-full">
      <button onclick="navigate('games')" class="btn btn-gray mb-4" data-i18n="common.back2">← Back</button>
      <div id="playerLabels" class="hidden flex justify-between w-full max-w-[600px] mb-2 px-2 text-lg font-bold">
        <span id="labelPlayerX" class="text-blue-400"></span>
        <span id="labelPlayerO" class="text-red-400"></span>
      </div>
      <div class="w-full flex justify-center">
        <canvas id="gameCanvas" class="border-4 border-gray-700 rounded-xl bg-black max-w-full"></canvas>
      </div>
    </div>
  `;
}