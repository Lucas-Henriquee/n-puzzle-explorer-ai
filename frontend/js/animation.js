function initAnimatedBoard(container, size = 3) {
  container.innerHTML = "";
  for (let i = 0; i < size * size; i++) {
    const tile = document.createElement("div");
    tile.className = "tile";
    tile.dataset.value = ""; 
    container.appendChild(tile);
  }
}

function updateTilePositions(matrix) {
  const size = matrix.length;
  const flat = matrix.flat();
  const tiles = document.querySelectorAll("#solver-board .tile");

  for (let i = 0; i < flat.length; i++) {
    const val = flat[i];
    const tile = tiles[i];

    if (val === 0) {
      tile.style.display = "none";
    } else {
      tile.style.display = "flex";
      tile.textContent = val;

      const idx = flat.indexOf(val);
      const row = Math.floor(idx / size);
      const col = idx % size;

      tile.style.transform = `translate(${col * 90}px, ${row * 90}px)`;
    }
  }
}

async function animateSolution(states) {
  const container = document.getElementById("solver-board");
  initAnimatedBoard(container);

  for (const state of states) {
    updateTilePositions(state);
    await new Promise(resolve => setTimeout(resolve, 700));
  }
}
