#!/usr/bin/env zsh
#SBATCH --job-name=p4
#SBATCH --partition=instruction
#SBATCH --output=producer_consumer.output
#SBATCH --time=00:02:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4

cd $SLURM_SUBMIT_DIR
g++ -O2 -std=c++17 producer_consumer.cpp -o producer_consumer -pthread
./producer_consumer