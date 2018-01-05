for i in $1 $2 $3; do(
for((bs=10; bs<150; bs += 3)); do matmult_c.gcc blk $i $i $i $bs ; done > _optimalblk$i.dat); done
awk '{r = $6; s = $2}; {print r, s}' ./_optimalblk$1.dat > optimalblk$1.dat
rm _optimalblk$1.dat
awk '{r = $6; s = $2}; {print r, s}' ./_optimalblk$2.dat > optimalblk$2.dat
rm _optimalblk$2.dat
awk '{r = $6; s = $2}; {print r, s}' ./_optimalblk$3.dat > optimalblk$3.dat
rm _optimalblk$3.dat
gnuplot -persist <<-EOFMarker
	set terminal postscript eps enhanced color font 'Helvetica,10'
	set xlabel "Block_size"
	set ylabel "MFlops"
	set output "testplot$1$2$3.eps"
	plot "optimalblk$1.dat" w lp title 'array size = $1', "optimalblk$2.dat" w lp title 'array size = $2', "optimalblk$3.dat" w lp title 'array size = $3'
EOFMarker




