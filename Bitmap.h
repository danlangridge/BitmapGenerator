/*
Bitmap object
every pixel is initially 64 bits. which during output, can be downscaled to the preffered size.
*/
struct Bitmap {

  double* header;
  double* payload;
};
