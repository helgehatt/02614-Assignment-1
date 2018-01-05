for((var = 20; var <= 3500; var += var/3)); do matmult_c.gcc $1 $var $var $var; done > test_$2.dat
awk '{print $1, $2}' test_$2.dat > tmp_$2.dat
gnuplot -persist <<-EOFMarker
	set terminal postscript eps enhanced color font 'Helvetica,10'
	set output "plot_$2.eps"
	set title "matmult_$1"
	set xlabel "Memory [kBytes]"
	set ylabel "Performance [MFlop/s]"
	set xtics (16,64,256,1024,4096,16384,65536,262144)
	set logscale x 2	
	set arrow from    32,graph(0,0) to    32,graph(1,1) nohead
	set arrow from   256,graph(0,0) to   256,graph(1,1) nohead
	set arrow from 25600,graph(0,0) to 25600,graph(1,1) nohead
	plot "tmp_$2.dat" with lp
EOFMarker
