// Envia/recebe JSON via `fetch()` para o backend Crow

async function fetchSolution(config) {
  const response = await fetch('/solve', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(config)
  });
  return await response.json();
}

