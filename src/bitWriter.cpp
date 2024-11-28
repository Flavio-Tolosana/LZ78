#include "bitWriter.hpp"

#include <iostream>

using namespace std;

// Constructor
BitWriter::BitWriter(const string &fileName) : buffer(0), bitCount(0) {
    outFile.open(fileName, ios::binary);
    if (!outFile) {
        cerr << "Error al abrir el archivo " + fileName << endl;
    }
}

// Destructor
void BitWriter::writeLastByte() {
    // Asegurarse de vaciar el buffer al final
    if (bitCount > 0) {
        buffer <<= (8 - bitCount); // Rellenar con ceros
        outFile.put(buffer);
    }
    outFile.close();
}

// Escribir un único bit (0 o 1)
void BitWriter::writeBit(bool bit) {
    buffer = (buffer << 1) | bit; // Añadir el bit al buffer
    bitCount++;

    if (bitCount == 8) { // Si el buffer está lleno, escribir al archivo
        outFile.put(buffer);
        buffer = 0;
        bitCount = 0;
    }
}

// Escribir varios bits desde un entero (especificando cuántos)
void BitWriter::writeBits(uint32_t value, int bitLength) {
    for (int i = bitLength - 1; i >= 0; --i) {
        writeBit((value >> i) & 1);
    }
}
