// animation.js

const TILE_STEP = 90;
const introStates = [
  [ [2, 8, 3], [1, 6, 4], [7, 0, 5] ],
  [ [2, 8, 3], [1, 0, 4], [7, 6, 5] ],
  [ [2, 0, 3], [1, 8, 4], [7, 6, 5] ],
  [ [0, 2, 3], [1, 8, 4], [7, 6, 5] ],
  [ [1, 2, 3], [0, 8, 4], [7, 6, 5] ],
  [ [1, 2, 3], [7, 8, 4], [0, 6, 5] ],
  [ [1, 2, 3], [7, 8, 4], [6, 0, 5] ],
  [ [1, 2, 3], [7, 8, 4], [6, 5, 0] ],
  [ [1, 2, 3], [7, 8, 0], [6, 5, 4] ],
  [ [1, 2, 3], [7, 0, 8], [6, 5, 4] ],
  [ [1, 2, 3], [0, 7, 8], [6, 5, 4] ],
  [ [0, 2, 3], [1, 7, 8], [6, 5, 4] ],
  [ [2, 0, 3], [1, 7, 8], [6, 5, 4] ],
  [ [2, 7, 3], [1, 0, 8], [6, 5, 4] ],
  [ [2, 7, 3], [1, 5, 8], [6, 0, 4] ],
  [ [2, 7, 3], [1, 5, 8], [6, 4, 0] ],
  [ [2, 7, 3], [1, 5, 0], [6, 4, 8] ],
  [ [2, 7, 0], [1, 5, 3], [6, 4, 8] ],
  [ [2, 0, 7], [1, 5, 3], [6, 4, 8] ],
  [ [0, 2, 7], [1, 5, 3], [6, 4, 8] ]
];

// Função utilitária para criar um atraso
function delay(ms) {
  return new Promise(r => setTimeout(r, ms));
}

// Inicia um tabuleiro animado (cria as divs para as peças)
function initAnimatedBoard(container, size = 3) {
  container.innerHTML = "";
  container.style.gridTemplateColumns = `repeat(${size}, 1fr)`;
  for (let i = 0; i < size * size; i++) {
    const tile = document.createElement("div");
    tile.className = "tile";
    tile.dataset.value = "";
    container.appendChild(tile);
  }
}

// Atualiza a posição das peças no tabuleiro com base em uma matriz
function updateTilePositions(matrix, container) {
  const size = matrix.length;
  const flat = matrix.flat();
  const tiles = container.querySelectorAll(".tile");
  
  if (tiles.length === 0) return; 

  for (let i = 0; i < flat.length; i++) {
    const val = flat[i];
    const tile = tiles[i];

    const row = Math.floor(i / size);
    const col = i % size;

    if (val === 0) {
      tile.style.display = "none";
    } else {
      tile.style.display = "flex";
      tile.textContent = val;
      tile.style.transform = `translate(${col * TILE_STEP}px, ${row * TILE_STEP}px)`;
    }
  }
}

// Anima a transição de estados do tabuleiro
async function animateSolution(states, { stepMs = 700, containerId = "solver-board" } = {}) {

  firstStepDelay = 1000 

  const container = document.getElementById(containerId);
  if (!container) return; 

  const size = states[0].length;
  initAnimatedBoard(container, size);
  updateTilePositions(states[0], container);

  if (states.length > 1) {
    updateTilePositions(states[1], container);
    await delay(firstStepDelay);
  }

  for (let i = 2; i < states.length; i++) {
    updateTilePositions(states[i], container);
    await delay(stepMs);
  }
}

// Animação de loop para a tela inicial
async function loopIntroAnimation() {
  const container = document.getElementById("intro-board");
  if (!container) return;

  initAnimatedBoard(container, 3);

  const forward = introStates;
  const backward = [...introStates].slice(0, -1).reverse();
  const fullLoop = forward.concat(backward);

  while (true) {
    await animateSolution(fullLoop, {
      stepMs: 500,
      containerId: "intro-board"
    });
    await delay(500);
  }
}

// Inicia a animação da tela de boas-vindas assim que a página carrega
window.addEventListener("DOMContentLoaded", () => {
  loopIntroAnimation();
});