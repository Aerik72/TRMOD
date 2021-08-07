// This file contains common functions that trmod uses.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
