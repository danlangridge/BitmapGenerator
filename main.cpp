#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>


using namespace std;

/* 
    Note: All bytes must be stored as little-endian
*/

const unsigned char BITS_IN_BYTE = 8; 
static char LOG = 1;

enum FileStructure {
  BM = 1,
  BA = 2,
  CI = 3,
  CP = 4,
  IC = 5,
  PT = 6
};

enum SizeInBytes {
  CHAR = 1,
  SHORT = 2,
  LONG = 4,
  LONGLONG = 8
};

const unsigned char HEADER_SIZE = 14;

const char FILETYPE[2] = { 0x42, 0x4D }; 

/*-- LOGGING FUNCTIONS --*/

void outputByte(char byte) {
  for (unsigned i = 0; i < BITS_IN_BYTE; i++)
    cout << ((byte & (0x80 >> i)) > 0) ? "1" : "0";  
}

string byteToString(char byte) {
  string sByte = ""; 
  for (unsigned i = 0; i < BITS_IN_BYTE; i++)
    sByte += ((byte & (0x80 >> i)) > 0) ? "1" : "0";  
  return sByte;
}

void logDebug(string log) {
  if (LOG) cout << log << endl;
  cout.flush();
}

/*-- BITMAP CLASS --*/

struct Bitmap {
  char* header;
  char* dibHeader; 
  char* payload;
  char payloadSize;
  SizeInBytes pixelSize;
 
  Bitmap (SizeInBytes pixelSize, int PayloadSize) {
    pixelSize = pixelSize; 
    payloadSize = PayloadSize;
     
    payload = new char[payloadSize*pixelSize];
    
    generateMockPayload();
    generateHeader();
  } 
  
  void generateMockPayload() {
    for (unsigned i = 0; i < payloadSize*pixelSize; i++) {
      payload[i] = 16; 
    }
  }

  void generateHeader() {
    if (header != NULL) {
      free(header);
    }
    
    header = new char[HEADER_SIZE];

    header[0] = FILETYPE[0]; //B
    header[1] = FILETYPE[1]; //M
    header[2] = payloadSize*pixelSize + HEADER_SIZE + 1;
    // Pixel Gap Artifact 
    //Byte offset to payload
    header[10] = 0x00;
    header[11] = 0x00;
    header[12] = 0x00;
    header[13] = HEADER_SIZE;
    
    dibHeader = new char[1];
   
    
  }
  
  char* splitPayloadIntoBytes() {
    char* payloadBytes = new char[payloadSize*pixelSize]; 
    for (unsigned i = 0; i < payloadSize*pixelSize; i++) {
      for (unsigned byte = pixelSize - 1 ; byte >= 0; byte--) { 
        payloadBytes[i] = payload[i] & (0xFF << byte);  
      } 
    }
    return payloadBytes; 
  }

};

/*-- HELPER FUNCTIONS --*/

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

void BigEndianToLittleEndian(Bitmap &b) {
  
}

void writeBMP(ofstream &bitfile, Bitmap *bmp) {
    //logDebug("Header: " + byteToString(bmp->header[i]));
    bitfile.write((const char*)bmp->header, HEADER_SIZE);
    //logDebug("payloadByte: " + byteToString(bmp->payload[i]));
    bitfile.write((const char*)bmp->payload, bmp->pixelSize*bmp->payloadSize); 
}

/*-- TEST FUNCTIONS --*/

void byteSwapTest() {
  unsigned char test = rand() % 256;  

  for (unsigned i = 0; i < BITS_IN_BYTE; i++) {
    outputByte(test >> i);
    cout << "Reversed: ";
    outputByte(swapByte(test >> i)); 
  }
}

void generateBMPTest() {
  ofstream bitfile;
  bitfile.open("example.bmp");
  Bitmap* bmp = new Bitmap(SHORT, 10); 
  writeBMP(bitfile, bmp); 
  bitfile.close();
}

int main(int argv, char** argc) {
  //byteSwapTest();
  generateBMPTest(); 
  return 0;
}
