let currentBoard = [];

function showScreen(screenId) {
  document.querySelectorAll(".screen").forEach((screen) => {
    screen.classList.remove("active");
  });

  document.getElementById(screenId).classList.add("active");

  if (screenId === "screen-home") {
    document.getElementById("game-board").innerHTML = "";
    document.getElementById("solver-board").innerHTML = "";
    document.getElementById("stats").innerHTML = "";
  }

  if (screenId === "screen-solver") {
    generateBoard("solver-board");
  }

  if (screenId === "screen-play") {
    generateBoard("game-board");
  }
}

function generateBoard(boardId) {
  const container = document.getElementById(boardId);
  container.innerHTML = "";

  const board = [
    [6, 2, 4],
    [5, 8, 3],
    [1, 7, 0]
  ];
  currentBoard = board;

  if (boardId === "game-board") {
    drawStaticTiles(board, container);
  }

  if (boardId === "solver-board") {
    animateSolution([board]);
  }
}

function drawStaticTiles(matrix, container) {
  container.innerHTML = "";
  matrix.forEach((row, i) => {
    row.forEach((val, j) => {
      const tile = document.createElement("div");
      tile.className = "tile";
      tile.textContent = val === 0 ? "" : val;
      tile.style.transform = `translate(${j * 90}px, ${i * 90}px)`;
      container.appendChild(tile);
    });
  });
}

async function solvePuzzle() {
  const stats = document.getElementById("stats");
  stats.innerHTML = "Executando algoritmo...";

  const algorithm = "BFS"; 
  const heuristic = " ";

  const config = {
    initial: currentBoard,
    algorithm: algorithm,
    heuristic: heuristic
  };

  const info = document.getElementById("solver-info");
  info.innerHTML = `
    <strong>Algoritmo:</strong> ${algorithm.toUpperCase()}<br>
    <strong>Heurística:</strong> ${heuristic.charAt(0).toUpperCase() + heuristic.slice(1)}
  `;

  const result = await fetchSolution(config);

  stats.innerHTML = `
    Tempo: ${result.stats.tempo_ms.toFixed(2)} ms<br>
    Nós visitados: ${result.stats.nos_visitados}<br>
    Profundidade: ${result.stats.profundidade}
  `;

  await animateSolution(result.solution);
}

