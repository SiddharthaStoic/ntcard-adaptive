#!/bin/bash

# Benchmarking ntcard with adaptive spaced seed hashing
OUTPUT="benchmark_results.csv"
echo "Dataset,K,Time (s)" > "$OUTPUT"

# Updated dataset paths
DATASETS=("datasets/test-reads.fq.gz" "datasets/SRR2584863_1.fastq.gz" "datasets/Ecoli_k12.fasta.gz" "datasets/chr14.fa.gz")
K_VALUES=(15 17 19 21 23)

for file in "${DATASETS[@]}"; do
  for k in "${K_VALUES[@]}"; do
    echo "Running: $file with k=$k"
    start=$(date +%s.%N)

    ./ntcard -k "$k" -h 1 -e 1.5 "$file" > /dev/null 2>&1

    end=$(date +%s.%N)
    elapsed=$(awk "BEGIN {printf \"%.6f\", $end - $start}")
    echo "${file##*/},$k,$elapsed" >> "$OUTPUT"
  done
done

echo "Benchmarking complete. Results saved to $OUTPUT"