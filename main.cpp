#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* 
    Note: All bytes must be stored as little-endian
*/

const unsigned char BITS_IN_BYTE = 8; 


enum SizeInBytes {
  CHAR = 1,
  SHORT = 2,
  LONG = 4,
  DOUBLE = 8
};

const unsigned char HEADER_SIZE = 14;

unsigned char HEADER[HEADER_SIZE] = { 0x42, 0x4D, // 'B' 'M' 
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
  unsigned int payloadSize;
  SizeInBytes pixelSize;

  Bitmap (int pixelSize) {
    header = HEADER;
    pixelSize = SHORT; 
    payloadSize = 50;
    payload = new unsigned short[payloadSize*pixelSize];
    
    generateMockPayload();
  } 
  
  Bitmap (int pixelSize, int PayloadSize) {
    HEADER[5] = payloadSize;   
    header = HEADER;
    pixelSize = SHORT; 
    payloadSize = PayloadSize;
     
    payload = new unsigned short[payloadSize*pixelSize];
    
    generateMockPayload();
  } 
  
  void generateMockPayload() {
    for (unsigned i = 0; i < payloadSize; i++) {
      payload[i] = 16; 
    }
  }
};

unsigned char swapByte(unsigned char byte) {
  unsigned char reverse_byte = 0x00;
  unsigned char bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7;
  bit0 = (byte & 0x01) > 0 ? 0x80 : 0x00;
  bit1 = (byte & 0x02) > 0 ? 0x40 : 0x00;
  bit2 = (byte & 0x04) > 0 ? 0x20 : 0x00;
  bit3 = (byte & 0x08) > 0 ? 0x10 : 0x00;
  bit4 = (byte & 0x10) > 0 ? 0x08 : 0x00;
  bit5 = (byte & 0x20) > 0 ? 0x04 : 0x00;
  bit6 = (byte & 0x40) > 0 ? 0x02 : 0x00;
  bit7 = (byte & 0x80) > 0 ? 0x01 : 0x00;
 
  reverse_byte = bit0 + bit1 + bit2 + bit3 + bit4 + bit5 + bit6 + bit7; 

  return reverse_byte; 
}

void outputByte(unsigned char byte) {
  cout << "Byte: ";
  for (unsigned i = 0; i < BITS_IN_BYTE; i++)
    cout << ((byte & (0x80 >> i)) > 0) ? "1" : "0";
  
  cout << endl;
}

void bigEndianToLittleEndian(Bitmap &b) {
  
}

void endianSwapTest() {
  unsigned char test1 = 35;  

  for (unsigned i = 0; i < BITS_IN_BYTE; i++) {
    outputByte(test1 >> i);
    cout << "Reversed: ";
    outputByte(swapByte(test1 >> i)); 
  }
}

void generateBMP() {
  ofstream bitfile;

  unsigned char MOCK_HEADER[14] = { 0x42, 0x4D, // 'B' 'M' 
                             0x00, 0x00, // Size in Bytes
                             0x00, 0x01, // 
                             0x01, 0x01, // reserved
                             0x02, 0x02, // reserved
                             0x04, 0x04, // offset of pixel array
                             0x04, 0x04
                           };
  bitfile.open("example.bmp");
 
  bitfile.close();
}

int main(int argv, char** argc) {
  endianSwapTest();
  return 0;
}
