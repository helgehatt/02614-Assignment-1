#!/bin/bash
#BSUB -J lsf
#BSUB -o lsf_%J.out
#BSUB -e lsf_%J.err
#BSUB -q hpcintro
#BSUB -W 15 -n 1,1
#BSUB -R "select[model == XeonE5_2650v4]"
#BSUB -R "rusage[mem=512MB]"

ADD SCRIPT TO RUN HERE
