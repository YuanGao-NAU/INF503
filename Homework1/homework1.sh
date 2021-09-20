#!/bin/bash
#SBATCH --job-name=lazy                     # the name of your job
#SBATCH --output=/home/yg336/inf503/homework1/output.txt    # this is the file your output and errors go to
#SBATCH --chdir=/home/yg336/inf503/homework1/            # your work directory
#SBATCH --time=10:00                	    # (max time) 
#SBATCH --mem=4000                          # (total mem) 
#SBATCH -c1                                 # # of cpus

srun main problem1 /common/contrib/classroom/inf503/hw_dataset.fa
