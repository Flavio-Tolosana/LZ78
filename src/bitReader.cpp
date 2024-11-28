#include "bitReader.hpp"

#include <iostream>

// Constructor: abre el archivo en modo binario
BitReader::BitReader(const string& filename) : buffer(0), bitsDisponibles(0) {
    file.open(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo.\n";
    }
}

// Destructor: cierra el archivo
BitReader::~BitReader() {
    if (file.is_open()) {
        file.close();
    }
}

// Leer un número específico de bits
int BitReader::leerBits(int numBits) {
    int resultado = 0;
    while (numBits > 0) {
        if (bitsDisponibles == 0) {
            // Si el búfer está vacío, leer un nuevo byte
            if (!file.get(reinterpret_cast<char&>(buffer))) {
                cerr << "\nBitReader::leerBits: Fin del archivo alcanzado. NumBits: " << numBits << endl;
            }
            bitsDisponibles = 8;
        }

        // Determinar cuántos bits leer en esta iteración
        int bitsALeer = min(numBits, bitsDisponibles);
        resultado <<= bitsALeer; // Desplazar el resultado
        resultado |= (buffer >> (bitsDisponibles - bitsALeer)) & ((1 << bitsALeer) - 1);
        bitsDisponibles -= bitsALeer;
        numBits -= bitsALeer;
    }
    return resultado;
}

// Comprobar si quedan bits por leer
bool BitReader::quedanBits() {
    return bitsDisponibles > 0 || file.peek() != EOF;
}

// Leer un solo bit
int BitReader::leerUnBit() {
    return leerBits(1);
}