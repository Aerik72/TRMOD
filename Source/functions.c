// This file contains common functions that trmod uses.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

char* readFile(char *inputFile){
	// This function reads a file into memory, and returns a pointer
	printf("Reading binary file %s...\n", inputFile);
	FILE* levelFile;
	errno_t fopen_error = fopen_s(&levelFile, inputFile, "rb"); // Opens text file
	if (levelFile == NULL)
	{
		printf("ERROR: File cannot be read! (error code: %d)\n", fopen_error);
		return 0;
	}
	fseek(levelFile, 0, SEEK_END);
	unsigned freeuint1=ftell(levelFile); // Makes freeuint1 the size of file
	printf("File size: %u\n", freeuint1);
	char *bytelist = malloc(freeuint1); // Makes room in the memory, the size of file
	fseek(levelFile, 0, SEEK_SET);
	//printf("Reading file into memory...\n");
	fread(bytelist, 1, freeuint1, levelFile); // Reads file into memory
	fclose(levelFile); // Closes file
	return bytelist;
}

// This function requires a 24-bit bitmap with no compression
// The caller of the function is responsible for freeing the returned BYTE* memory
// Returns the pixel array in 3-byte RGB pixels, with rows bottom-to-top
BYTE* readBitmapFile(char* inputFilename)
{
	char* image = readFile(inputFilename);

	// Check bitmap integrity
	BYTE bmpIntegrityA;
	BYTE bmpIntegrityB;
	memcpy(&bmpIntegrityA, image + 0, 1);
	memcpy(&bmpIntegrityB, image + 1, 1);
	//printf("Bitmap integrity: %c%c\n", bmpIntegrityA, bmpIntegrityB);
	if (!(bmpIntegrityA == 'B' && bmpIntegrityB == 'M'))
	{
		printf("ERROR: File must be BM for Windows 3.1x, 95, NT, etc.\n");
		free(image);
		return NULL;
	}

	// Verify that the bitmap is 24 bits per pixel
	unsigned short bitsPerPixel;
	memcpy(&bitsPerPixel, image + 28, 2);
	//printf("Bitmap bpp: %d", bitsPerPixel);
	if (!bitsPerPixel == 24)
	{
		printf("ERROR: Bitmap must be 24 bits per pixel.\n");
		free(image);
		return NULL;
	}

	// Verify image is uncompressed
	signed int compression;
	memcpy(&compression, image + 30, 4);
	//printf("Compression method: %d", compression);
	if (compression != 0)
	{
		printf("ERROR: Bitmap must be uncompressed (found compression method %d, must be 0 a.k.a. BI_RGB).\n", compression);
		free(image);
		return NULL;
	}

	// Read width and height
	signed int width;
	signed int height;
	memcpy(&width, image + 18, 4);
	memcpy(&height, image + 22, 4);
	//printf("Width x height: %d x %d\n", width, height);

	// Read image size
	signed int imageSize;
	memcpy(&imageSize, image + 34, 4);
	if (imageSize == 0)
	{
		// For BI_RGB, a dummy 0 may indicate bpp x w x h
		imageSize = bitsPerPixel * width * height;
	}
	printf("Image size: %d\n", imageSize);

	// Allocate memory for result
	BYTE* result = malloc(imageSize * sizeof(BYTE));
	if (result == 0)
	{
		printf("ERROR: Could not allocate memory to read bmp! (error code: %d)\n", errno);
		return NULL;
	}

	// Determine the offset of the pixel array
	signed int offset;
	memcpy(&offset, image + 10, 4);
	//printf("Bitmap pixel array offset: %d", offset);

	memcpy(result, image + offset, imageSize);

	free(image);

	return result;
}

void writeFile(char *outputFile, char *bytelist, unsigned fsize){
	// This function writes bytelist to the level file.
	FILE *File = fopen(outputFile,"wb");
	fseek(File, 0, SEEK_SET);
	fwrite(bytelist, 1, fsize, File);
	fclose(File);
}
unsigned filesize(char *inputFile){
	// This function returns the size of a file
	FILE *File = fopen(inputFile,"rb"); // Opens file
	fseek(File, 0, SEEK_END);
	unsigned freeuint1=ftell(File); // Makes freeuint1 the size of file
	fclose(File); // Closes file
	return freeuint1;
}
char* substring(char *string, unsigned offset, unsigned length){
	// This function returns a substring of a string.
	char *string2 = malloc(length+1); // Makes a string the size of the length + 1 (for the NULL byte)
	memcpy(string2, string+offset, length); // Copies the substring
	char freechar1=0;
	memset(string2+length,freechar1,1); // Adds a 0-byte to the end of it
	return string2;
}
char *splitString(char *instringraw, char splitChar, int partNum){
	/*
	This function returns a substring of the entered string, defined by this split character.
	splitString(Input String, Character that defines the split, wanted part)
	*/
	char *instring=malloc(strlen(instringraw)+1);
	memcpy(instring,instringraw,strlen(instringraw));
	memset(instring+strlen(instringraw),0,1);
	int freeint1=0;
	const char s[2] = {splitChar, 0};
	char *token;
	token = strtok(instring, s);
	while( token != NULL )
	{
		if (freeint1==partNum) return token;
		token = strtok(NULL, s);
		freeint1++;
	}
	return token;
}
unsigned countchar(char *instring, char countChar){
	// This function returns the number of occurences of a character in a string.
	int i;
	for (i=0; instring[i]; instring[i]==countChar ? i++ : *instring++);
	return i;
}
char* insertrange(char *bytelist, unsigned offset, unsigned length, char *insertme, unsigned fsize){
	// This function inserts bytes into bytelist, and returns the new size.
	bytelist = (char *) realloc(bytelist,(fsize+length));
	memmove(bytelist+offset+length,bytelist+offset,fsize-offset);
	memcpy(bytelist+offset,insertme,length);
	return (bytelist);
}
unsigned removerange(char *bytelist, unsigned offset, unsigned length, unsigned fsize){
	// This function removes bytes from bytelist, and returns the new size
	memmove(bytelist+offset, bytelist+offset+length, (fsize-offset-length));
	return (fsize-length);
}

// This function writes a 24-bit bitmap (R8 G8 B8)
// In TR1, full black (0, 0, 0) represents transparent
// In TR2, full magenta (255, 0, 255) represents transparent
void writeBitmap(char* img, char* filename, const unsigned w, const unsigned h)
{
	FILE* f;
	int bmpFileSize = 54 + 3 * w * h;

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(bmpFileSize);
	bmpfileheader[3] = (unsigned char)(bmpFileSize >> 8);
	bmpfileheader[4] = (unsigned char)(bmpFileSize >> 16);
	bmpfileheader[5] = (unsigned char)(bmpFileSize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	f = fopen(filename, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i < h; i++)
	{
		fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
		fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f); // bmp requires all rows to be postfix padded to a multiple of 4
	}

	fclose(f);
}

void writeBitmap32(char* img, char* filename, const unsigned w, const unsigned h)
{
	FILE* f;
	int bmpFileSize = 54 + 4 * w * h;

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 32,0 };

	bmpfileheader[2] = (unsigned char)(bmpFileSize);
	bmpfileheader[3] = (unsigned char)(bmpFileSize >> 8);
	bmpfileheader[4] = (unsigned char)(bmpFileSize >> 16);
	bmpfileheader[5] = (unsigned char)(bmpFileSize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	f = fopen(filename, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i < h; i++)
	{
		fwrite(img + (w * (h - i - 1) * 4), 4, w, f);
	}

	fclose(f);
}

BYTE findPixelKey(BYTE* palette, BYTE r, BYTE g, BYTE b)
{
	BYTE pr, pg, pb;
	BYTE result;
	short closestMatch = 255 * 3;
	short diff;
	BYTE isExactMatch = 0;
	BYTE rpr, rpg, rpb;
	for (int i = 0; i < 256; i++)
	{
		short curpos = i * 3;
		memcpy(&pr, palette + curpos + 2, 1);
		memcpy(&pg, palette + curpos + 1, 1);
		memcpy(&pb, palette + curpos + 0, 1);

		if (pr == r &&
			pg == g &&
			pb == b)
		{
			result = i;
			isExactMatch = 1;
			break;
		}

		diff = abs(pr - r) +
			   abs(pg - g) +
			   abs(pb - b);

		if (diff < closestMatch)
		{
			closestMatch = diff;
			result = i;
			rpr = pr;
			rpg = pg;
			rpb = pb;
			isExactMatch = 0;
		}
	}

	/*
	if (isExactMatch == 1)
	{
		printf("Exact match: %d, %d, %d matches palette %d\n", r, g, b, result);
	}
	else
	{
		printf("No match: %d, %d, %d is closest to palette %d (%d, %d, %d)\n", r, g, b, result, rpr, rpg, rpb);
	}
	*/

	return result;
}
