#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
#SBATCH --cpus-per-task=50

export OMP_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export MKL_NUM_THREADS=1

export G4FORCENUMBEROFTHREADS=50

#Horizontal run
./babel run_hor.mac

#Merging the output files
hadd -f output_hor.root output_hor_t*.root

if [ $? -eq 0 ]; then
    echo "--------------Merging Succeeded!--------------"
    rm output_hor_t*.root

else
    echo "--------------Merging Failed!--------------"
fi
