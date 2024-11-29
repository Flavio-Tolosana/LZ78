#!/bin/bash

# Script que comprime los archivos de la carpeta dirData
# Además los descomprime comprobando que sean idénticos (solamente caso LZ78)
# En el fichero fileNumeroFrases se irán guardando:
#   - size: el tamaño del archivo original
#   - numFrases: numero de frases utilizadas para la compresión del archivo

# Uso: ./run.sh [-c] opción para borrar archivos descomprimidos

make -s

dirData=data
fileNumeroFrases=plots/numeroFrases.txt
echo -e "# size numFrases" > $fileNumeroFrases

clean=false  # Por defecto, no se elimina nada
while getopts "c" opt; do
  case $opt in
    c)
      clean=true
      ;;
  esac
done

for inC in "$dirData"/*.txt; do
  if [ -f "$inC" ]; then 
    outC="$dirData/LZ78_comprimido_$(basename "$inC" .txt).bin"
    inD=$outC
    outD="$dirData/LZ78_descomprimido_$(basename "$inC")"

    salidaComprimir=$(./bin/LZ78 -c "$inC" "$outC")
    numFrases=$(echo $salidaComprimir | cut -d' ' -f1)
    size=$(cat "$inC" | wc -c)  
    echo $size $numFrases >> $fileNumeroFrases
    echo $salidaComprimir | ./bin/LZ78 -d "$inD" "$outD"

    diff $inC $outD

    gzip -k "$inC"
    mv "$inC".gz "$dirData/gzip_comprimido_$(basename "$inC").gz"

    bzip2 -k "$inC"
    mv "$inC".bz2 "$dirData/bzip2_comprimido_$(basename "$inC").bz2"

  fi
done

if $clean; then
  echo "Opción -c seleccionada: Eliminando archivos descomprimidos en $dirData"
  rm -rf "$dirData"/*descomprimido_*
fi
