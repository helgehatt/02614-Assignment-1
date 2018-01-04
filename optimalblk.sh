for((bs=1; bs<100; bs += 5)); do matmult_c.gcc blk $1 $1 $1 $bs ; done > optimalblk$1.txt
