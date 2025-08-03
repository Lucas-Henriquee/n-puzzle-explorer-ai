/* ====================================================== */
/* ========== 1. VARIÁVEIS DE ESTADO                   = */
/* ====================================================== */

let selectedSize = 3;
let customGoalBoard = null;
let customInitialBoard = null;
let selectedAlgorithm = null;
let selectedHeuristic = null;
let currentBoard = [];
let goalType = '';
let initialType = '';
let hasHeuristics = false;
let currentSolution = [];
let animationInterval = null;
let animationSpeed = 500;
let animationIndex = 0;
let isAnimating = false;
let fullSolutionData = null;
let currentSpeedMultiplier = 1;

/* ====================================================== */
/* ========== 2. MANIPULAÇÃO DO ESTADO & NAVEGAÇÃO     = */
/* ====================================================== */

function clearScreenState(screenId) {
  if (screenId === 'screen-size-select') {
    document.querySelectorAll('.size-tile').forEach(tile => tile.classList.remove('selected'));
    document.getElementById('confirm-size').disabled = true;
  }
  if (screenId === 'screen-goal-choice') {
    document.querySelectorAll('#goal-selector .goal-option').forEach(option => option.classList.remove('selected'));
    document.getElementById('confirm-goal').disabled = true;
    goalType = '';
  }
  if (screenId === 'screen-goal-input') {
    document.getElementById('goal-board-input').innerHTML = '';
    document.getElementById('confirm-goal-board-btn').disabled = true;
    customGoalBoard = null;
  }
  if (screenId === 'screen-initial-choice') {
    document.querySelectorAll('#initial-selector .goal-option').forEach(option => option.classList.remove('selected'));
    document.getElementById('confirm-initial-choice').disabled = true;
    initialType = '';
    document.getElementById('goal-board-preview').innerHTML = '';
  }
  if (screenId === 'screen-initial-input') {
    document.getElementById('initial-board-input').innerHTML = '';
    document.getElementById('confirm-initial-board-btn').disabled = true;
    customInitialBoard = null;
  }
  if (screenId === 'screen-random-preview') {
    document.getElementById('random-board-preview').innerHTML = '';
  }
  if (screenId === 'screen-test-algorithms') {
    selectedAlgorithm = null;
    selectedHeuristic = null;
    document.querySelectorAll('.goal-option').forEach(o => o.classList.remove('selected'));
    showAlgorithmPanel();
    document.getElementById('stats').innerHTML = "";
    document.getElementById('solver-info').textContent = "Selecione um algoritmo para começar.";
    document.getElementById('animation-controls').style.display = 'none';
    currentSolution = [];
    clearInterval(animationInterval);
    animationIndex = 0;
  }
}

function showScreen(screenId) {
  document.querySelectorAll(".screen").forEach((screen) => {
    if (screen.classList.contains('active')) {
      clearScreenState(screen.id);
    }
    screen.classList.remove("active");
  });
  
  if (screenId === "screen-test-algorithms") {
    document.getElementById(screenId).classList.add("active");
    generateBoard("test-board", selectedSize);
  } else {
    document.getElementById(screenId).classList.add("active");
  }
}
function showCustomGoalInput() {
  drawEditableBoard("goal-board-input", "confirm-goal-board-btn", selectedSize);
  showScreen("screen-goal-input");
}
function confirmGoalBoard() {
  const boardSize = selectedSize;
  const flatBoard = Array.from(document.getElementById('goal-board-input').querySelectorAll('.tile')).map(tile => parseInt(tile.dataset.value));
  const board = [];
  while(flatBoard.length) board.push(flatBoard.splice(0, boardSize));
  customGoalBoard = board;

  const previewContainer = document.getElementById("goal-board-preview");
  if (previewContainer) {
    drawStaticTiles(customGoalBoard, previewContainer);
  }
  showScreen("screen-initial-choice");
}

function showCustomInitialInput() {
  drawEditableBoard("initial-board-input", "confirm-initial-board-btn", selectedSize);
  showScreen("screen-initial-input");
}

function confirmInitialBoard() {
  const boardSize = selectedSize;
  const flatBoard = Array.from(document.getElementById('initial-board-input').querySelectorAll('.tile')).map(tile => parseInt(tile.dataset.value));
  const board = [];
  while(flatBoard.length) board.push(flatBoard.splice(0, boardSize));
  customInitialBoard = board;

  currentBoard = customInitialBoard;
  showScreen("screen-test-algorithms");
}

function generateRandomInitial() {
  const previewContainer = document.getElementById("random-board-preview");
  if (previewContainer) {
    previewContainer.innerHTML = '';
  }

  currentBoard = generateRandomBoard(selectedSize);
  if (previewContainer) {
    drawStaticTiles(currentBoard, previewContainer);
  }
  showScreen("screen-random-preview");
}

function regenerateRandomBoard() {
  currentBoard = generateRandomBoard(selectedSize);
  const previewContainer = document.getElementById("random-board-preview");
  if (previewContainer) {
    drawStaticTiles(currentBoard, previewContainer);
  }
}

function showAlgorithmPanel() {
  const algoPanel = document.getElementById('algo-selection-content');
  const heuristicPanel = document.getElementById('heuristic-selection-content');
  
  algoPanel.classList.add('active');
  heuristicPanel.classList.remove('active');

  selectedHeuristic = null;
  document.getElementById('run-algorithm-btn').disabled = true;
  document.querySelectorAll('#algo-selector-panel .goal-option').forEach(o => o.classList.remove('selected'));
  document.querySelectorAll('#heuristic-selector-panel .goal-option').forEach(o => o.classList.remove('selected'));
}

function selectAlgorithmPanel(algo) {
  if (isAnimating) return;
  
  selectedAlgorithm = algo;
  const heuristics = ["Greedy", "A*", "IDA*"];
  
  document.querySelectorAll('#algo-selector-panel .goal-option').forEach(o => o.classList.remove('selected'));
  document.querySelector(`div[data-algo="${algo}"]`).classList.add('selected');

  if (heuristics.includes(algo)) {
    document.getElementById('algo-selection-content').classList.remove('active');
    document.getElementById('heuristic-selection-content').classList.add('active');
    document.getElementById('run-heuristic-btn').disabled = true;
  } else {
    document.getElementById('run-algorithm-btn').disabled = false;
    selectedHeuristic = null;
  }
  
  document.querySelectorAll('#heuristic-selector-panel .goal-option').forEach(o => o.classList.remove('selected'));
}

function selectHeuristicPanel(h) {
  if (isAnimating) return;

  selectedHeuristic = h;
  document.querySelectorAll('#heuristic-selector-panel .goal-option').forEach(o => o.classList.remove('selected'));
  document.querySelector(`div[data-heuristic="${h}"]`).classList.add('selected');
  document.getElementById('run-heuristic-btn').disabled = false;
}


function selectHeuristicPanel(h) {
  if (isAnimating) return;

  selectedHeuristic = h;
  document.querySelectorAll('#heuristic-selector-panel .goal-option').forEach(o => o.classList.remove('selected'));
  document.querySelector(`#heuristic-selector-panel .goal-option[data-heuristic="${h}"]`).classList.add('selected');
  document.getElementById('run-heuristic-btn').disabled = false;
}


/* ====================================================== */
/* ========== 3. FUNÇÕES DE GERAÇÃO DE TABULEIRO       = */
/* ====================================================== */

function isSolvable(board) {
  const size = board.length;
  const flatBoard = board.flat().filter(val => val !== 0);
  let inversions = 0;
  for (let i = 0; i < flatBoard.length; i++) {
    for (let j = i + 1; j < flatBoard.length; j++) {
      if (flatBoard[i] > flatBoard[j]) {
        inversions++;
      }
    }
  }
  
  if (size % 2 !== 0) {
    return inversions % 2 === 0;
  } else {
    let blankRow = -1;
    for (let i = 0; i < size; i++) {
      if (board[i].includes(0)) {
        blankRow = i;
        break;
      }
    }
    const blankRowFromBottom = size - blankRow;
    if (blankRowFromBottom % 2 === 0) {
      return inversions % 2 !== 0;
    } else {
      return inversions % 2 === 0;
    }
  }
}

function generateRandomBoard(size) {
  let board;
  let solvable = false;
  do {
    const total = size * size;
    const numbers = Array.from({ length: total }, (_, i) => i);
    
    for (let i = numbers.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [numbers[i], numbers[j]] = [numbers[j], numbers[i]];
    }
    
    board = [];
    while (numbers.length) board.push(numbers.splice(0, size));
    
    solvable = isSolvable(board);
  } while (!solvable);
  
  return board;
}

function drawStaticTiles(matrix, container) {
  if (!container) return;
  container.innerHTML = "";
  const size = matrix.length;
  container.dataset.size = size;
  container.style.gridTemplateColumns = `repeat(${size}, 1fr)`;
  matrix.forEach(row => {
    row.forEach(val => {
      const tile = document.createElement("div");
      tile.className = "tile";
      tile.textContent = val === 0 ? "" : val;
      container.appendChild(tile);
    });
  });
}


function drawEditableBoard(containerId, buttonId, size) {
  const container = document.getElementById(containerId);
  if (!container) return;
  container.innerHTML = "";
  container.classList.add('editable-board');
  container.dataset.size = size;
  container.style.gridTemplateColumns = `repeat(${size}, 1fr)`;
  const total = size * size;
  const used = new Set();
  
  const checkCompletion = () => {
    const filledCount = Array.from(container.querySelectorAll('.tile')).filter(tile => tile.dataset.value !== "?").length;
    const btn = document.getElementById(buttonId);
    
    if (!btn) {
      console.error(`Erro: Botão com ID "${buttonId}" não encontrado.`);
      return;
    }
    
    console.log("--- Verificando Conclusão ---");
    console.log("Total de células:", total);
    console.log("Células preenchidas:", filledCount);
    console.log("Valores únicos no Set:", used.size, used);

    if (filledCount === total && used.size === total) {
      console.log("Validação OK. Habilitando botão.");
      btn.disabled = false;
    } else {
      console.log("Validação falhou. Desabilitando botão.");
      btn.disabled = true;
    }
  };

  for (let i = 0; i < total; i++) {
    const cell = document.createElement("div");
    cell.className = "tile";
    cell.dataset.value = "?";
    cell.textContent = "?";

    cell.addEventListener("click", (e) => {
      e.stopPropagation();
      if (cell.querySelector('input')) return;
      
      const input = document.createElement("input");
      input.type = "number";
      input.min = "0";
      input.max = (total - 1).toString();
      input.className = "tile-input";
      
      Object.assign(input.style, {
        width: '100%',
        height: '100%',
        textAlign: 'center',
        border: 'none',
        outline: 'none',
        fontSize: '1.5rem',
        backgroundColor: 'transparent',
        color: 'inherit',
      });
      
      const processInput = () => {
        if (!cell.contains(input)) return;

        let val = parseInt(input.value);
        
        const oldVal = parseInt(cell.dataset.value);
        if (!isNaN(oldVal) && oldVal !== '?' && used.has(oldVal)) {
          used.delete(oldVal);
        }

        if (isNaN(val) || val < 0 || val >= total || used.has(val)) {
          alert("Valor inválido ou já usado. Por favor, tente novamente.");
          cell.textContent = "?";
          cell.dataset.value = "?";
          // Removendo a classe caso o valor seja inválido
          cell.classList.remove('filled-tile');
        } else {
          used.add(val);
          cell.dataset.value = val;
          cell.textContent = val === 0 ? "" : val;
          // Adicionando a classe para aplicar o estilo correto
          cell.classList.add('filled-tile');
        }

        if (cell.contains(input)) {
            cell.removeChild(input);
        }

        checkCompletion();
      };

      input.addEventListener('keydown', (e) => {
        if (e.key === "Enter") {
          processInput();
          cell.focus();
        }
      });
      
      input.addEventListener('blur', processInput);
      
      cell.textContent = '';
      cell.appendChild(input);
      input.focus();
    });

    container.appendChild(cell);
  }
}

function generateBoard(boardId, size) {
  const container = document.getElementById(boardId);
  if (!container) return;
  container.innerHTML = "";
  container.dataset.size = size;
  if (boardId === "game-board") {
    currentBoard = generateRandomBoard(size);
    drawStaticTiles(currentBoard, container);
  } else if (boardId === "test-board") {
    initAnimatedBoard(container, selectedSize);
    updateTilePositions(currentBoard, container);
  }
}


/* ====================================================== */
/* ========== 4. FUNÇÕES DE JOGO & ALGORITMO           = */
/* ====================================================== */

async function solvePuzzle() {
  if (isAnimating) return;
  
  animationSpeed = 500;
  currentSpeedMultiplier = 1;
  document.getElementById('accel-animation-btn').textContent = "Acelerar 1x";


  const stats = document.getElementById("stats");
  const info = document.getElementById("solver-info");
  const runAlgoBtn = document.getElementById('run-algorithm-btn');
  const runHeuristicBtn = document.getElementById('run-heuristic-btn');
  const runBtn = selectedHeuristic ? runHeuristicBtn : runAlgoBtn;

  info.innerHTML = "Executando algoritmo...";
  stats.innerHTML = "";
  runBtn.disabled = true;
  document.querySelectorAll('.goal-option').forEach(o => o.classList.add('disabled-for-run'));

  const config = {
    initial: currentBoard,
    goal: customGoalBoard || null, 
    algorithm: selectedAlgorithm,
    heuristic: selectedHeuristic || ""
  };
  
  const result = await fetchSolution(config);
  fullSolutionData = result;

  document.querySelectorAll('.goal-option').forEach(o => o.classList.remove('disabled-for-run'));
  
  let statsHtml = `
    <strong>Status:</strong> ${result.stats.solution_found ? '<span style="color:#2ecc71;">Com solução </span>' : '<span style="color:#e74c3c;">Sem solução</span>'}<br>
    <strong>Algoritmo:</strong> ${selectedAlgorithm}<br>
  `;
  if (selectedHeuristic) {
    statsHtml += `<strong>Heurística:</strong> ${selectedHeuristic}<br>`;
  }
  statsHtml += `<br>
    <strong>Tempo:</strong> ${result.stats.tempo_ms.toFixed(2)} ms<br>
    <strong>Nós visitados:</strong> ${result.stats.nos_visitados}<br>
    <strong>Profundidade:</strong> ${result.stats.profundidade}
  `;
  stats.innerHTML = statsHtml;
  info.innerHTML = "";

  currentSolution = result.solution;
  
  if (result.stats.solution_found) {
    document.getElementById('animation-controls').style.display = 'flex';
    document.getElementById('show-tree-btn').style.display = 'block'; 
    
    isAnimating = true;
    document.getElementById('end-animation-btn').disabled = false;
    document.getElementById('accel-animation-btn').disabled = false;
    document.getElementById('reset-animation-btn').disabled = false;
    
    setTimeout(() => {
        startAnimation();
    }, 1000); 

  } else {
    showNoSolutionBoard();
    document.getElementById('animation-controls').style.display = 'none';
  }

}

function showNoSolutionBoard() {
  const container = document.getElementById("test-board");
  if (!container) return;
  
  container.innerHTML = "";
  container.classList.add('no-solution-grid'); 
  
  const size = selectedSize;
  container.dataset.size = size;
  
  const boardSizePx = size === 3 ? 270 : (size === 4 ? 360 : 450);
  Object.assign(container.style, {
    position: 'relative',
    width: `${boardSizePx}px`,
    height: `${boardSizePx}px`,
    display: 'grid',
    gap: '6px',
    gridTemplateColumns: `repeat(${size}, 1fr)`,
  });
  
  for (let i = 0; i < size * size; i++) {
    const tile = document.createElement("div");
    tile.className = "tile no-solution-tile";
    tile.textContent = "?";
    container.appendChild(tile);
  }

  isAnimating = false;
  showAlgorithmPanel();
}

function startAnimation() {
    if (currentSolution.length === 0) return;

    const container = document.getElementById("test-board");
    container.classList.remove('no-solution-grid'); 
    
    initAnimatedBoard(container, selectedSize);
    updateTilePositions(currentBoard, container);

    animationIndex = 0;
    
    clearInterval(animationInterval);
    animationInterval = setInterval(() => {
        if (animationIndex < currentSolution.length) {
            updateTilePositions(currentSolution[animationIndex], container);
            animationIndex++;
        } else {
            clearInterval(animationInterval);
            animationIndex = currentSolution.length - 1;
            isAnimating = false;
            document.getElementById('end-animation-btn').disabled = true;
            document.getElementById('accel-animation-btn').disabled = true;
            document.getElementById('reset-animation-btn').disabled = false;
            showAlgorithmPanel(); 
        }
    }, animationSpeed);
}

function accelerateAnimation() {
  if (!isAnimating) return;

  const speeds = [500, 250, 125]; 
  const currentSpeedIndex = speeds.indexOf(animationSpeed);
  const nextSpeedIndex = (currentSpeedIndex + 1) % speeds.length;
  
  animationSpeed = speeds[nextSpeedIndex];
  currentSpeedMultiplier = [1, 2, 4][nextSpeedIndex];

  const accelBtn = document.getElementById('accel-animation-btn');
  accelBtn.textContent = `Acelerar ${currentSpeedMultiplier}x`;
  
  clearInterval(animationInterval);
  animationInterval = setInterval(() => {
    if (animationIndex < currentSolution.length) {
        updateTilePositions(currentSolution[animationIndex], document.getElementById("test-board"));
        animationIndex++;
    } else {
        clearInterval(animationInterval);
        animationIndex = currentSolution.length - 1;
        isAnimating = false;
        document.getElementById('end-animation-btn').disabled = true;
        document.getElementById('accel-animation-btn').disabled = true;
        document.getElementById('reset-animation-btn').disabled = false;
        showAlgorithmPanel();
    }
  }, animationSpeed);
}

function resetAnimation() {

  if (isAnimating || currentSolution.length === 0) return;

  animationSpeed = 500;
  currentSpeedMultiplier = 1;
  document.getElementById('accel-animation-btn').textContent = "Acelerar 1x";
  
  document.getElementById('end-animation-btn').disabled = false;
  document.getElementById('accel-animation-btn').disabled = false;
  document.getElementById('reset-animation-btn').disabled = false;

  isAnimating = true;

  startAnimation();
}

function endAnimation() {
  if (!isAnimating || currentSolution.length === 0) return;

  clearInterval(animationInterval);
  animationIndex = currentSolution.length - 1;
  updateTilePositions(currentSolution[animationIndex], document.getElementById("test-board"));
  
  isAnimating = false;
  document.getElementById('end-animation-btn').disabled = true;
  document.getElementById('accel-animation-btn').disabled = true;
  document.getElementById('reset-animation-btn').disabled = false;
  showAlgorithmPanel(); 
}


function showSearchTree() {
  // TODO: Implementar a visualização da árvore de busca em um modal ou nova tela.
  console.log("A funcionalidade de visualização da árvore de busca ainda não foi implementada.");
  console.log("Os dados da solução foram salvos na variável `fullSolutionData` e estão disponíveis para uso.");
}

/* ====================================================== */
/* ========== 5. INICIALIZAÇÃO DA APLICAÇÃO            = */
/* ====================================================== */

document.addEventListener("DOMContentLoaded", () => {
  const sizeTiles = document.querySelectorAll('.size-tile');
  const confirmSizeBtn = document.getElementById('confirm-size');
  sizeTiles.forEach(tile => {
    tile.addEventListener('click', () => {
      sizeTiles.forEach(t => t.classList.remove('selected'));
      tile.classList.add('selected');
      selectedSize = parseInt(tile.dataset.size);
      confirmSizeBtn.disabled = false;
    });
  });
  confirmSizeBtn?.addEventListener('click', () => {
    if (selectedSize) {
      showScreen('screen-goal-choice');
    }
  });

  const goalOptions = document.querySelectorAll('#goal-selector .goal-option');
  const confirmGoalBtn = document.getElementById('confirm-goal');
  goalOptions.forEach(option => {
    option.addEventListener('click', () => {
      goalOptions.forEach(o => o.classList.remove('selected'));
      option.classList.add('selected');
      goalType = option.dataset.goal; 
      confirmGoalBtn.disabled = false;
    });
  });
  confirmGoalBtn?.addEventListener('click', () => {
    if (goalType) {
      if (goalType === 'sequence') {
        showCustomGoalInput();
      } else if (goalType === 'random') {
        const size = selectedSize;
        const total = size * size;
        const goalBoard = [];
        let count = 1;
        for (let i = 0; i < size; i++) {
          const row = [];
          for (let j = 0; j < size; j++) {
            if (count < total) {
              row.push(count++);
            } else {
              row.push(0);
            }
          }
          goalBoard.push(row);
        }
        customGoalBoard = goalBoard;
        const previewContainer = document.getElementById("goal-board-preview");
        if (previewContainer) {
            drawStaticTiles(customGoalBoard, previewContainer);
        }
        showScreen('screen-initial-choice');
      }
    }
  });

  const initialOptions = document.querySelectorAll('#initial-selector .goal-option');
  const confirmInitialBtn = document.getElementById('confirm-initial-choice');
  initialOptions.forEach(option => {
    option.addEventListener('click', () => {
      initialOptions.forEach(o => o.classList.remove('selected'));
      option.classList.add('selected');
      initialType = option.dataset.goal;
      confirmInitialBtn.disabled = false;
    });
  });
  confirmInitialBtn?.addEventListener('click', () => {
    if (initialType === 'manual') {
      showCustomInitialInput();
    } else if (initialType === 'random') {
      generateRandomInitial();
    }
  });
  
  const algoPanelOptions = document.querySelectorAll('#algo-selector-panel .goal-option');
  algoPanelOptions.forEach(option => {
      option.addEventListener('click', () => {
          selectAlgorithmPanel(option.dataset.algo);
      });
  });

  const heuristicPanelOptions = document.querySelectorAll('#heuristic-selector-panel .goal-option');
  heuristicPanelOptions.forEach(option => {
      option.addEventListener('click', () => {
          selectHeuristicPanel(option.dataset.heuristic);
      });
  });

  document.getElementById('run-algorithm-btn')?.addEventListener('click', solvePuzzle);
    document.getElementById('run-heuristic-btn')?.addEventListener('click', solvePuzzle);
    document.getElementById('back-to-algos-btn')?.addEventListener('click', showAlgorithmPanel);

    document.getElementById('accel-animation-btn')?.addEventListener('click', accelerateAnimation);
    document.getElementById('reset-animation-btn')?.addEventListener('click', resetAnimation);
    document.getElementById('end-animation-btn')?.addEventListener('click', endAnimation);
});