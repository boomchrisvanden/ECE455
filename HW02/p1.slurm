#!/usr/bin/env zsh
#SBATCH --job-name=p1
#SBATCH --partition=instruction
#SBATCH --output=hello_threads.output
#SBATCH --time=00:02:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4

cd $SLURM_SUBMIT_DIR
g++ -O2 -std=c++17 hello_threads.cpp -o hello_threads -pthread
./hello_threads