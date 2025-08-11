#!/bin/bash

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR" || exit 1

mkdir -p output  # Cria diretório para os arquivos de saída (se não existir)

find ./data -type f -name "*.txt" | while read -r arquivo; do
    if [[ "$arquivo" == "./data/test10x10.txt" || "$arquivo" == "./data/test5x5_1.txt" || "$arquivo" == "./data/test5x5_2.txt" || "$arquivo" == "./data/test5x5_3.txt" || "$arquivo" == "./data/test4x4_1.txt" || "$arquivo" == "./data/test4x4_2.txt" || "$arquivo" == "./data/test4x4_3.txt" ]]; then
        continue
    fi

    # Extrai o nome do arquivo base sem extensão e sem caminho
    nome_base=$(basename "$arquivo" .txt)
    mkdir -p "output/$nome_base"  # Cria diretório específico para o arquivo

    for i in {1..7}; do
        if [[ $i -ge 5 ]]; then
            for j in {1..6}; do
                ./npuzzle_exec "$arquivo" "$i" "$j" > "output/${nome_base}/c${i}_h${j}.txt" 2>&1
            done
        else
            ./npuzzle_exec "$arquivo" "$i" "0" > "output/${nome_base}/c${i}.txt" 2>&1
        fi
    done
done
