# LZ78

## LZ78
Para compilar el compresor LZ78:

``` sh
make
```
### LZ78 (comprimir)
**Requisitos uso:** \<ficheroEntrada\> solo pude contener los dos siguientes caracteres: 0, 1.
Es así que el el alfabeto es:

$$a \in {0,1}$$

Uso:
``` sh
./bin/LZ78 -c <ficheroEntrada> <ficheroSalida>
```
> Al ejecutarlo saldrá por salida estándar lo siguiente: \<numFrases\> \<residuo\>
> - \<numFrases\>: es el número de frases utilizadas en la compresión LZ78 
> - \<residuo\>: 
>   - 1: la última frase es una frase anterior
>   - 0: la última frase es la unión de una frase anterior y un carácter

### LZ78 (descomprimir)
**Requisitos uso:** hay que pasar por la entrada estándar: \<numFrases\> \<residuo\>

``` sh
./bin/LZ78 -d <ficheroEntrada> <ficheroSalida>
```

Para comprobar su corrección se recomienda ejecutarlo de la siguiente manera.

``` sh
./bin/LZ78 -c <ficheroEntrada> <ficheroSalida> | ./bin/LZ78 -d <ficheroEntrada> <ficheroSalida>
```

## [run.sh](run.sh)
Comprime todos los archivos de una carpeta *(véase [run.sh](run.sh))*. Además descomprime dichos archivos y verifica utilizando `diff` que sean iguales.
Genera también un fichero llamado `numeroFrases.txt`, con la siguiente estructura:

``` txt
# size numFrases
1000 173
10000 1176
100000 8784
1000000 69586
10000000 574210
100000000 4877722
1000000000 42339065
```

**Requisitos uso:** Los archivos de la carpeta deben tener el alfabeto: $a \in {0, 1}$ y además deben tener extensión .txt.
Por ejemplo estos ficheros se recomiendan (cada uno con el tamaño que se indica):

> - 1_file_1KB.txt
> - 2_file_10KB.txt
> - 3_file_100KB.txt
> - 4_file_1MB.txt
> - 5_file_10MB.txt
> - 6_file_100MB.txt
> - 7_file_1GB.txt

## [plot.sh](plot.sh)
Genera los dos siguientes plots *(véase [plot.sh](plot.sh))*:
  - plotTasa: gráfica tasa compresion de LZ78, GZIP y BZIP2
  - plotNumFrases: gráfica numero de frases empleadas en LZ78

**Requisitos uso:** En la carpeta deben estar los archivos originales, y las compresiones con los tres algoritmos. Aquí un ejemplo:

> - 1_file_1KB.txt
> - 2_file_10KB.txt
> - 3_file_100KB.txt
> - 4_file_1MB.txt
> - 5_file_10MB.txt
> - 6_file_100MB.txt
> - 7_file_1GB.txt
> - bzip2_comprimido_1_file_1KB.txt.bz2
> - bzip2_comprimido_2_file_10KB.txt.bz2
> - bzip2_comprimido_3_file_100KB.txt.bz2
> - bzip2_comprimido_4_file_1MB.txt.bz2
> - bzip2_comprimido_5_file_10MB.txt.bz2
> - bzip2_comprimido_6_file_100MB.txt.bz2
> - bzip2_comprimido_7_file_1GB.txt.bz2
> - gzip_comprimido_1_file_1KB.txt.gz
> - gzip_comprimido_2_file_10KB.txt.gz
> - gzip_comprimido_3_file_100KB.txt.gz
> - gzip_comprimido_4_file_1MB.txt.gz
> - gzip_comprimido_5_file_10MB.txt.gz
> - gzip_comprimido_6_file_100MB.txt.gz
> - gzip_comprimido_7_file_1GB.txt.gz
> - LZ78_comprimido_1_file_1KB.bin
> - LZ78_comprimido_2_file_10KB.bin
> - LZ78_comprimido_3_file_100KB.bin
> - LZ78_comprimido_4_file_1MB.bin
> - LZ78_comprimido_5_file_10MB.bin
> - LZ78_comprimido_6_file_100MB.bin
> - LZ78_comprimido_7_file_1GB.bin

Además se necesita el fichero `numeroFrases.txt` para generar dicha gráfica.

