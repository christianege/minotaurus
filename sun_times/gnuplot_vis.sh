gnuplot << EOT
set title 'Linearized sunrise and sunset offsets'
set xlabel 'Day of year [day]'
set ylabel 'Offset since midnight [minutes]'
set xrange [1:365]
set grid
set terminal png 
plot 'sun.dat' using 1:2 title "sunrise" with points, 'sun.dat' using 1:3 title "sunset" with points
EOT
