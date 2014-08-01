#include <fstream>
#include <string>

#include <BitmapGenerator.h>


int main(int argv, char** argc) {

  ofstream bitfile;
  bitfile.open("example.bmp");
    
  bitfile.close();
  return 0;
}
