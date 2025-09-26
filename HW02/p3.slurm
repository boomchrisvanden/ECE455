#!/usr/bin/env zsh
#SBATCH --job-name=p3
#SBATCH --partition=instruction
#SBATCH --output=race_conditions.output
#SBATCH --time=00:02:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4

cd $SLURM_SUBMIT_DIR
g++ -O2 -std=c++17 race_conditions.cpp -o race_conditions -pthread
./race_conditions