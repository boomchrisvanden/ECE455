#!/usr/bin/env zsh
#SBATCH --job-name=p5
#SBATCH --partition=instruction
#SBATCH --output=parallel_matmul.output
#SBATCH --time=00:02:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4

cd $SLURM_SUBMIT_DIR
g++ -O2 -std=c++17 parallel_matmul.cpp -o parallel_matmul -pthread
./parallel_matmul