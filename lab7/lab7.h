#include <iostream>
#include <fstream>

using namespace std;

const int MAX_IMAGE_SIZE = 128;

// Struct definition
struct ASCIIImage
{
    int row;
    int col;
    char data[MAX_IMAGE_SIZE][MAX_IMAGE_SIZE];
};

// Image process functions
bool read_image(ASCIIImage&, const char[]);
void rotate_clockwise(ASCIIImage&);
void flip_horizontally(ASCIIImage&);
bool write_image(const ASCIIImage&, const char[]);
void plot(const ASCIIImage&);

// Utility functions
bool _check_image_size(const ASCIIImage&);
void _print(const ASCIIImage&, bool=false);

