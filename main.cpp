#include <fstream>
#include <string>

using namespace std;

/* 
    Note: All bytes must be stored as little-endian
*/

enum SizeInBytes {
  CHAR = 1,
  SHORT = 2,
  LONG = 4,
  DOUBLE = 8
};

unsigned char HEADER[14] = { 0x42, 0x4D, // 'B' 'M' 
                             0x00, 0x00, // Size in Bytes
                             0x00, 0x00, // 
                             0x01, 0x01, // reserved
                             0x02, 0x02, // reserved
                             0x04, 0x04, // offset of pixel array
                             0x04, 0x04
                           };

struct Bitmap {
  unsigned char* header;
  unsigned short* payload;
};

void bigEndianToLittleEndian(Bitmap &b) {

}

void generateMockPayload(unsigned short* pixelArray, const unsigned &size) {
  for (unsigned i = 0; i < size; i++) {
    pixelArray[i] = 16; 
  }
}

int main(int argv, char** argc) {

  ofstream bitfile;
  bitfile.open("example.bmp");
  
  bitfile.close();
  return 0;
}
