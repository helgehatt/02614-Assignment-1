for((bs=2; bs<100; bs += 3)); do matmult_c.gcc blk $1 $1 $1 $bs ; done > _optimalblk$1.dat
awk '{r = $6; s = $2}; {print r, s}' ./_optimalblk$1.dat > optimalblk$1.dat
rm _optimalblk$1.dat


