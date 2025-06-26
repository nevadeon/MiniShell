#!/bin/bash

src_file="seed_corpus/seed"
output_dir="seed_corpus"

mkdir -p "$output_dir"

n=1
while IFS= read -r line; do
  printf "%s\n" "$line" > "$output_dir/$(printf "%03d" "$n").txt"
  n=$((n + 1))
done < "$src_file"
