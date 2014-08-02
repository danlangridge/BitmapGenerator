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

unsigned char bitswap(unsigned char byte) {
  unsigned char reverse_endian = 0x00;
  unsigned char bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7;
  bit0 = (byte && 0x01) > 0 ? 0x80 : 0x00;
  bit1 = (byte && 0x02) > 0 ? 0x40 : 0x00;
  bit2 = (byte && 0x04) > 0 ? 0x20 : 0x00;
  bit3 = (byte && 0x08) > 0 ? 0x10 : 0x00;
  bit4 = (byte && 0x10) > 0 ? 0x08 : 0x00;
  bit5 = (byte && 0x20) > 0 ? 0x04 : 0x00;
  bit6 = (byte && 0x40) > 0 ? 0x02 : 0x00;
  bit7 = (byte && 0x80) > 0 ? 0x01 : 0x00;
 
  reverse_endian = bit0 + bit1 + bit2 + bit3 + bit4 + bit5 + bit6 + bit7; 

  return reverse_endian; 
}

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
