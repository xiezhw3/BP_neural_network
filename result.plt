set boxwidth 0.4 absolute
set term jpeg
set xrange[-1:100]
set yrange[0:1]
set ylabel "error"
set output "result/error.jpeg"
plot "result/error.data" with lines
replot
set ylabel "precision"
set output "result/precision.jpeg"
plot "result/precision.data" with lines
quit