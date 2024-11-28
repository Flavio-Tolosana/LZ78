#include <fstream>

using namespace std;

class BitWriter {
private:
    ofstream outFile;       // Archivo de salida
    uint8_t buffer;         // Acumulador de bits
    int bitCount;          // Número de bits en el buffer

public:
    // Constructor
    BitWriter(const string &fileName);

    // Destructor
    void writeLastByte();

    // Escribir un único bit (0 o 1)
    void writeBit(bool bit);

    // Escribir varios bits desde un entero (especificando cuántos)
    void writeBits(uint32_t value, int bitLength);
};