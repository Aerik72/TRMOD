#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef unsigned char BYTE;

char* readFile(char *inputFile);
BYTE* readBitmapFile(char* inputFilename);
void writeFile(char *outputFile, char *bytelist, unsigned fsize);
unsigned filesize(char *inputFile);
char* substring(char *string, unsigned offset, unsigned length);
char *splitString(char *instringraw, char splitChar, int partNum);
unsigned countchar(char *instring, char countChar);
char* insertrange(char *bytelist, unsigned offset, unsigned length, char *insertme, unsigned fsize);
unsigned removerange(char *bytelist, unsigned offset, unsigned length, unsigned fsize);
void writeBitmap(char* img, char* filename, const unsigned w, const unsigned h);
BYTE findPixelKey(BYTE* palette, BYTE r, BYTE g, BYTE b);

#endif