for((bs=2; bs<100; bs += 3)); do matmult_c.gcc blk $1 $1 $1 $bs ; done > optimalblk$1.txt
awk '{r = $6; s = $2}; {print r, s}' ./optimalblk$1.txt > optimalblk$1.dat


