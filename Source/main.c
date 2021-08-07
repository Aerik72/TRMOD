/*
Please note that this is a beta version of trmod.
Some aspects of this program might be different in the
final version. Also, this version only supports Tomb Raider 1
on the PC and PlayStation, and Tomb Raider 2 on the PC.

If you find any flaws or errors in this build, please inform me by
sending a message to b122251 a tombraiderforums.com.
*/


/*
Tomb Raider Level Modifier (TRMOD) 0.3
Copyright (C) 2015  b122251
2021 Erik R

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "tr1pc.h"
#include "tr1psx.h"
#include "tr2pc.h"
int main(int argc, char *args[]);
void displayText();
int main(int argc, char *args[]){
	char freechar1 = 0;
	if (argc<2) {
		freechar1=1;
		displayText();
	} else if (!strnicmp(substring(args[1],strlen(args[1])-4,4),"help",4)){
			freechar1=1;
			displayText();
	}
	if (freechar1 == 0){
		//printf("Reading file...\n");
		char* bytelist=readFile(args[1]);
		unsigned fsize = filesize(args[1]);
		//fprintf("File size: %u\n", filesize);
		unsigned freeuint1;
		if (!strnicmp(substring(args[1],strlen(args[1])-3,3),"sat",3)){
			// Determines Sega Saturn version
			printf("Sega Saturn format not current supported!\n");
		}else{
			if (!strnicmp(substring(args[1],strlen(args[1])-3,3),"psx",3)){
				printf("PSX format detected\n");
				freechar1=2;
				freeuint1=0x56414270;
				if (memcmp(bytelist+4,&freeuint1,4)==0) freechar1=1;
				freeuint1=0xFFFFFFC8;
				if (memcmp(bytelist,&freeuint1,4)==0) freechar1=3;
				if (freechar1==1) tr1psx_main(argc, args, bytelist, fsize);
				//if (freechar1==2) tr2psx_main(argc, args, bytelist, fsize);
				//if (freechar1==3) //tr3psx
			}else{
				printf("PC format detected\n");
				memcpy(&freeuint1, bytelist, 4);
				if (freeuint1 == 32)
				{
					printf("TR1 version detected\n");
					tr1pc_main(argc, args, bytelist, fsize);
				}
				if (freeuint1 == 45)
				{
					printf("TR2 version detected\n");
					tr2pc_main(argc, args, bytelist, fsize);
				}
				//if (freeuint1==4278714424||freeuint1==4279763000) tr3pc_main(argc, args, bytelist, fsize);
				//if (freeuint1==3428948&&!strncasecmp(substring(args[1],strlen(args[1])-3,3),"tr4",3)) // tr4pc
				//if (freeuint1==3428948&&!strncasecmp(substring(args[1],strlen(args[1])-3,3),"trc",3)) // tr5pc
			}
		}
	}
	return 0;
}
void displayText(){
	system("cls"); // Replace "cls" with "clear" on Linux
	printf("Tomb Raider Level Modifier (TRMOD) 0.3\n\n\n");
	printf("This program can modify and list the contents of Tomb Raider level files.\n");
	printf("It supports TR1 PC, TR1 PSX, TUB PC, and TR2 PC formats.\n");
	printf("For detailed instructions, please read the included manual.\n\n\n");
	printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
	printf("This program is distributed under the GNU General Public License 3.0.\n");
	printf("This program is dedicated to everybody on the Tomb Raider Forums.\n\n\n");
	printf("TRMOD Beta Copyright (C) 2015 b122251\n");
	printf("TRMOD 0.3 2021 Erik R\n\n");
}
