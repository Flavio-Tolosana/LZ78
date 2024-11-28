#!/bin/bash

# Genera los dos siguientes plots:
#   - plotTasa: gráfica tasa compresion de LZ78, GZIP y BZIP2
#   - plotNumFrases: gráfica numero de frases empleadas en LZ78

dir="data"
dirPlots="plots"

# Archivos originales. Con alfabeto {0,1}
original_files=("1_file_1KB.txt" "2_file_10KB.txt" "3_file_100KB.txt" \
"4_file_1MB.txt" "5_file_10MB.txt" "6_file_100MB.txt" "7_file_1GB.txt")

fileTasa="$dirPlots/tasaCompresion.dat"
plotTasa="$dirPlots/tasaCompresion.png"
fileNumFrases="$dirPlots/numeroFrases.txt"
plotNumFrases="$dirPlots/numeroFrases.png"

echo "# originalSize GZIP BZIP2 LZ78" > $fileTasa

# Calcular tasas de compresión
for file in "${original_files[@]}"; do
    original_size=$(cat "$dir/$file" | wc -c)

    # Archivos comprimidos
    gzip_file="gzip_comprimido_${file}.gz"
    bzip2_file="bzip2_comprimido_${file}.bz2"
    lz78_file="LZ78_comprimido_${file%.txt}.bin"

    # Tamaños comprimidos
    gzip_size=$(cat "$dir/$gzip_file" | wc -c)
    bzip2_size=$(cat "$dir/$bzip2_file" | wc -c)
    lz78_size=$(cat "$dir/$lz78_file" | wc -c)

    # Tasa de compresión
    gzip_ratio=$(echo "$gzip_size / $original_size" | bc -l)
    bzip2_ratio=$(echo "$bzip2_size / $original_size" | bc -l)
    lz78_ratio=$(echo "$lz78_size / $original_size" | bc -l)

    # Guardar resultados en el archivo de datos
    echo "$original_size $gzip_ratio $bzip2_ratio $lz78_ratio" >> $fileTasa
done

gnuplot <<EOF
set terminal png size 800,600
set output '$plotTasa'
set title "Tasa de Compresión GZIP vs BZIP2 vs LZ78"
set xlabel "Tamaño Original (Bytes)"
set ylabel "Tasa de Compresión"
set logscale x 10
set grid
plot "$fileTasa" using 1:2 with linespoints title "GZIP", \
     "$fileTasa" using 1:3 with linespoints title "BZIP2", \
     "$fileTasa" using 1:4 with linespoints title "LZ78"
EOF

gnuplot <<EOF
set terminal png size 800,600
set output '$plotNumFrases'
set title "Frases del diccionario"
set xlabel "Tamaño Original (Bytes)"
set ylabel "Frases"
set logscale x 10
set logscale y 10
set grid
plot "$fileNumFrases" using 1:2 with linespoints title "Frases"
EOF
