#include <fstream>

using namespace std;

class BitReader {
private:
    ifstream file;
    unsigned char buffer; // Búfer para almacenar el byte actual
    int bitsDisponibles;  // Bits disponibles en el búfer

public:
    // Constructor: abre el archivo en modo binario
    BitReader(const string& filename);

    // Destructor: cierra el archivo
    ~BitReader();

    // Leer un número específico de bits
    int leerBits(int numBits);

    // Leer un solo bit
    int leerUnBit();

    // Comprobar si quedan bits por leer
    bool quedanBits();
};