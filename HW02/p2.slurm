#!/usr/bin/env zsh
#SBATCH --job-name=p2
#SBATCH --partition=instruction
#SBATCH --output=parallel_sums.output
#SBATCH --time=00:02:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4

cd $SLURM_SUBMIT_DIR
g++ -O2 -std=c++17 parallel_sum.cpp -o parallel_sum -pthread
./parallel_sum