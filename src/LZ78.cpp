#include "bitWriter.hpp"
#include "bitReader.hpp"

#include <iostream>
#include <unordered_map>
#include <cmath>
#include <cstring>

#include <random>

using namespace std;

void help(const string nombrePrograma) {
    cerr << "Uso: " << nombrePrograma << " -c <ficheroComprimir> <ficheroComprimido>" << endl;
    cerr << "Uso: " << nombrePrograma << " -d <ficheroComprimido> <ficheroDescomprimido>" << endl;
}

// Función para calcular los bits necesarios para representar un número n
int calcularBits(int n) {
    if (n <= 0) return 0; // 0 bits si n es 0
    return static_cast<int>(ceil(log2(n+1)));
}

int main(int argc, char *argv[]) {

    if (argc != 4) {
        help(argv[0]);
        return 0;
    } else if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0) {
        help(argv[0]);
        return 0;
    }

    const string ficheroEntrada = argv[2];
    const string ficheroSalida = argv[3];

    // Comprimir
    if(strcmp(argv[1], "-c") == 0) {

        ifstream inFile(ficheroEntrada);
        if (!inFile) {
            cerr << "Error al abrir el archivo " << ficheroEntrada << endl;
            return 1;
        }

        unordered_map<string, int> diccionario;
        diccionario[""] = 0;  // Frase vacía
        string prefijo = "";  // Frase actual hasta el momento
        string prefijoAnterior;  // Frase anterior (frase actual menos último char)
        int numeroFrase = 0;    // Numero frase actual
        int numeroFrasePrefijo = 0;   // Numero frase anterior
        char c;
        BitWriter bw = BitWriter(ficheroSalida);

        while (inFile.get(c)) {
            prefijo += c;  // Mientras se encuentre prefijo, seguir leyendo

            // No se encuentra prefijo
            if (diccionario.find(prefijo) == diccionario.end()) {
                // Guardar nueva frase
                numeroFrase = diccionario.size();
                diccionario[prefijo] = numeroFrase;

                // Encontrar numero frase anterior
                prefijoAnterior = prefijo;
                prefijoAnterior.erase(prefijoAnterior.size() - 1);
                if (diccionario.find(prefijo) == diccionario.end()) cerr << "Error: prefijo anterior no encontrado" << endl;
                numeroFrasePrefijo = diccionario[prefijoAnterior];

                // Escribir: (numFraseAnterior, nuevoChar)
                //     numFraseAnterior: con numFraseActual bits numFrases[0,numFrase-1]
                //     nuevoChar (0/1) 1 bit
                bw.writeBits(numeroFrasePrefijo, calcularBits(numeroFrase-1));
                bw.writeBit(c=='1');
                prefijo = "";
            }
        }
        // Escribir última frase (ya estaba en el diccionario)
        if(prefijo != "") {
            bw.writeBits(diccionario[prefijo], calcularBits(numeroFrase));
            cout << numeroFrase + 1 << " " << true << endl;
        } else {
            cout << numeroFrase << " " << false << endl;;
        }
        inFile.close();
        bw.writeLastByte();

        // Descomprimir
    } else {

        ofstream outFile(ficheroSalida);
        if (!outFile) {
            cerr << "Error al abrir el archivo " << ficheroSalida << endl;
            return 1;
        }

        BitReader br(ficheroEntrada);
        unordered_map<int, string> diccionario;
        diccionario[0] = "";  // Frase vacía

        int numFrase = 0;
        int numFrasesTotal;  // Total de frases guardadas en fichero comprimido
        bool residuo;        // Si última frase es solamente una frase anterior
        cin >> numFrasesTotal >> residuo;   // Leer de entrada estándar

        // Mientras no sea la última frase
        while (numFrase < numFrasesTotal) {

            // Leer numFrase bits para obtener numeroFrase del prefijo
            int numeroPrefijo = br.leerBits(calcularBits(numFrase));
            string prefijo = diccionario[numeroPrefijo];

            // Si es residuo, no es necesario leer char nuevo
            if(numFrase == numFrasesTotal-1 && residuo) {
                outFile << prefijo;

                // Leer nuevo char
            } else {
                string c = (br.leerUnBit() == 1) ? "1" : "0";
                outFile << prefijo << c;
                diccionario[numFrase+1] = prefijo + c;
            }
            numFrase++;
        }
        outFile.close();
    }

    return 0;
}