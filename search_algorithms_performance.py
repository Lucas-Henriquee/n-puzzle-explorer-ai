import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os


FONT_SIZE = 18 

if not os.path.exists('results'):
    os.makedirs('results')

plt.rcParams.update({'font.size': FONT_SIZE})
plt.rcParams['axes.titlesize'] = FONT_SIZE * 1.2
plt.rcParams['axes.labelsize'] = FONT_SIZE
plt.rcParams['xtick.labelsize'] = FONT_SIZE * 0.9
plt.rcParams['ytick.labelsize'] = FONT_SIZE * 0.9
plt.rcParams['legend.fontsize'] = FONT_SIZE * 0.9

# --- Dados dos Algoritmos Não Informados ---
data_uninformed = {
    'Algoritmo': ['Backtracking', 'Order Search (OS)', 'Breadth-First Search (BFS)', 'Depth-First Search (DFS)'],
    'Custo da Solucao': [39, 25, 25, 41],
    'Nos Expandidos': [1505079, 159599, 159599, 43714],
    'Tempo de Execucao': [2.60513, 32.5632, 0.486148, 0.0869403]
}
df_uninformed = pd.DataFrame(data_uninformed)
custom_order = ['Backtracking', 'Depth-First Search (DFS)', 'Order Search (OS)', 'Breadth-First Search (BFS)']
df_uninformed['Algoritmo'] = pd.Categorical(df_uninformed['Algoritmo'], categories=custom_order, ordered=True)
df_uninformed = df_uninformed.sort_values(by='Algoritmo').reset_index(drop=True)

# Plot Tempo de Execução (Log) e Custo da Solução
fig, ax1 = plt.subplots(figsize=(14, 10)) 
width = 0.35
x = np.arange(len(df_uninformed['Algoritmo']))

color_tempo = 'steelblue'
ax1.set_xlabel('Algoritmo')
ax1.set_ylabel('Tempo de Execução (s) [Log]', color=color_tempo)
bars1 = ax1.bar(x - width/2, df_uninformed['Tempo de Execucao'], width, color=color_tempo, alpha=0.8, label='Tempo de Execução')
ax1.tick_params(axis='y', labelcolor=color_tempo)
ax1.set_yscale('log')
for bar in bars1:
    yval = bar.get_height()
    ax1.text(bar.get_x() + bar.get_width()/2.0, yval, f'{yval:.2f}', va='bottom', ha='center', fontsize=FONT_SIZE * 0.8)

ax2 = ax1.twinx()
color_custo = 'lightcoral'
ax2.set_ylabel('Custo da Solução', color=color_custo)
bars2 = ax2.bar(x + width/2, df_uninformed['Custo da Solucao'], width, color=color_custo, alpha=0.8, label='Custo da Solução', hatch='//')
ax2.tick_params(axis='y', labelcolor=color_custo)
for bar in bars2:
    yval = bar.get_height()
    ax2.text(bar.get_x() + bar.get_width()/2.0, yval, f'{yval}', va='bottom', ha='center', fontsize=FONT_SIZE * 0.8)

ax1.set_xticks(x)
ax1.set_xticklabels(df_uninformed['Algoritmo'])
ax1.set_title('Tempo de Execução e Custo da Solução por Algoritmo')
fig.tight_layout()
fig.legend(loc='upper right', bbox_to_anchor=(1,1), bbox_transform=ax1.transAxes)
plt.savefig('results/grafico1_nao_informados.png')
plt.close(fig)

# Plot Nós Expandidos 
fig, ax = plt.subplots(figsize=(14, 10))
bars = ax.bar(df_uninformed['Algoritmo'], df_uninformed['Nos Expandidos'], color='seagreen', label='Nós Expandidos')
ax.set_xlabel('Algoritmo')
ax.set_ylabel('Nós Expandidos')
ax.set_title('Nós Expandidos por Algoritmo')
plt.xticks(rotation=0, ha='center')
ax.grid(axis='y', linestyle='--', alpha=0.7)
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2.0, yval, f'{yval:,}', va='bottom', ha='center', fontsize=FONT_SIZE * 0.8)
ax.legend()
plt.tight_layout()
plt.savefig('results/grafico2_nao_informados.png')
plt.close(fig)

# --- Dados dos Algoritmos Informados ---
data_informed = {
    'Algoritmo': [
        'Greedy', 'Greedy', 'Greedy', 'Greedy', 'Greedy', 'Greedy',
        'IDA*', 'IDA*', 'IDA*', 'IDA*', 'IDA*', 'IDA*',
        'A*', 'A*', 'A*', 'A*', 'A*', 'A*'
    ],
    'Heuristica': [
        'Manhattan', 'Euclidean', 'Misplaced Tiles', 'Linear Conflict', 'Permutation Cycles', 'Weighted Sum',
        'Manhattan', 'Euclidean', 'Misplaced Tiles', 'Linear Conflict', 'Permutation Cycles', 'Weighted Sum',
        'Manhattan', 'Euclidean', 'Misplaced Tiles', 'Linear Conflict', 'Permutation Cycles', 'Weighted Sum'
    ],
    'Custo da Solucao': [
        41, 63, 57, 35, 53, 55,
        25, 25, 25, 25, 25, 25,
        25, 25, 25, 25, 25, 25
    ],
    'Nos Expandidos': [
        225, 315, 720, 58, 525, 358,
        9617, 373563, 188244, 3797, 964475, 80034,
        4509, 6519, 40052, 2190, 58938, 7679
    ],
    'Tempo de Execucao': [
        0.00112216, 0.00153231, 0.00299625, 0.000438779, 0.00505342, 0.00192054,
        0.024947, 1.59562, 0.367567, 0.0204353, 9.00747, 0.225507,
        0.0391678, 0.0789376, 4.62887, 0.0240345, 10.9188, 0.126473
    ]
}
df_informed = pd.DataFrame(data_informed)

colors_informed = [('steelblue', 'darkorange')]

algorithms = ['Greedy', 'A*', 'IDA*']
for i, alg in enumerate(algorithms):
    df_alg = df_informed[df_informed['Algoritmo'] == alg].sort_values(by='Heuristica')
    
    fig, ax1 = plt.subplots(figsize=(14, 10)) 
    width = 0.35
    x = np.arange(len(df_alg['Heuristica']))

    color_tempo = colors_informed[0][0]
    color_nos = colors_informed[0][1]

    # Eixo Y1 (Tempo de Execução)
    ax1.set_xlabel('Heurística')
    ax1.set_ylabel('Tempo de Execução (s)', color=color_tempo)
    bars1 = ax1.bar(x - width/2, df_alg['Tempo de Execucao'], width, color=color_tempo, alpha=0.8, label='Tempo de Execução')
    ax1.tick_params(axis='y', labelcolor=color_tempo)
    
    # Aplica escala logarítmica se a variação for grande
    if alg in ['A*', 'IDA*']:
        ax1.set_yscale('log')
        ax1.set_ylabel('Tempo de Execução (s) [Log]', color=color_tempo)

    # Eixo Y2 (Nós Expandidos)
    ax2 = ax1.twinx()
    ax2.set_ylabel('Nós Expandidos', color=color_nos)
    bars2 = ax2.bar(x + width/2, df_alg['Nos Expandidos'], width, color=color_nos, alpha=0.8, label='Nós Expandidos', hatch='//')
    ax2.tick_params(axis='y', labelcolor=color_nos)

    # Aplica escala logarítmica se a variação for grande
    if alg in ['A*', 'IDA*']:
        ax2.set_yscale('log')
        ax2.set_ylabel('Nós Expandidos [Log]', color=color_nos)
    
    ax1.set_xticks(x)
    ax1.set_xticklabels(df_alg['Heuristica'], rotation=45, ha='right')
    ax1.set_title(f'Desempenho do Algoritmo {alg} por Heurística')
    fig.tight_layout()
    fig.legend(loc='upper right', bbox_to_anchor=(1,1), bbox_transform=ax1.transAxes)
    plt.savefig(f'results/grafico_{alg.lower().replace("*", "star")}.png')
    plt.close(fig)

df_custo = df_informed.pivot_table(index='Heuristica', columns='Algoritmo', values='Custo da Solucao')
print("\n--- Tabela de Custo da Solução por Algoritmo e Heurística ---\n")
print(df_custo.to_string())