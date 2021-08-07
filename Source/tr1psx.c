// This file handles Tomb Raider 1 PlayStation (PSX) files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "tr1psx.h"
#include "tr1pc.h"
#include "vag.h"
void tr1psx_main(int argc, char *args[], char *bytelist, unsigned fsize){
	unsigned curpos; // Current Position in the file navigation
	unsigned p_NumFloorData; // Offset of NumFloorData
	unsigned p_NumSpriteSequences; // Offset of NumSpriteSequences
	unsigned p_NumCameras; // Offset of NumCameras
	unsigned p_NumSoundSources; // Offset of NumSoundSources
	unsigned p_NumBoxes; // Offset of NumBoxes
	unsigned p_NumOverlaps; // Offset of NumOverlaps
	unsigned p_NumItems; // Offset of NumItems
	unsigned p_NumSoundDetails; // Offset of NumSoundDetails
	unsigned freeuint1=0;
	unsigned freeuint2;
	unsigned short freeshort1;
	unsigned short freeshort2;
	unsigned short freeshort3;
	unsigned short freeshort4;
	// <FILE NAVIGATION>
	memcpy(&freeuint1, bytelist+16, 3);
	curpos=458764+freeuint1; // [NumRooms]
	memcpy(&freeshort1,bytelist+curpos,2);
	unsigned short numRooms=freeshort1; // Number of Rooms
	unsigned* roomX = malloc(freeshort1 * sizeof(unsigned));  // Array of position of rooms on X axis
	int* roomY = malloc(freeshort1 * sizeof(int)); // Array of position of rooms on Y axis
	unsigned* roomZ = malloc(freeshort1 * sizeof(unsigned)); // Array of position of rooms on Z axis
	unsigned* p_NumVertices = malloc(freeshort1 * sizeof(unsigned)); // Array of the offset of NumVertices of all rooms
	unsigned* p_NumSprites = malloc(freeshort1 * sizeof(unsigned)); // Array of the offset of NumSprites of all rooms
	unsigned* p_NumZSector = malloc(freeshort1 * sizeof(unsigned)); // Array of the offset of NumZSector of all rooms
	unsigned* p_NumLights = malloc(freeshort1 * sizeof(unsigned)); // Array of the offset of NumLights of all rooms
	unsigned* p_NumStaticMeshes = malloc(freeshort1 * sizeof(unsigned)); // Array of the offset of NumStaticMeshes of all rooms
	unsigned* p_AlternateRoom = malloc(freeshort1 * sizeof(unsigned)); // Array of the offset of AlternateRoom of all rooms
	curpos+=2;
	for (freeshort2=0;freeshort2<freeshort1;freeshort2++){
		memcpy(&roomX[freeshort2], bytelist+curpos, 4);
		memcpy(&roomZ[freeshort2], bytelist+curpos+4, 4);
		memcpy(&roomY[freeshort2], bytelist+curpos+8, 4);
		curpos+=20; // [NumVertices]
		p_NumVertices[freeshort2]=curpos;
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=4+(freeshort3<<3); // [NumRectangles]
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=2+(freeshort3*10); // [NumTriangles]
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=2+(freeshort3<<3); // [NumSprites]
		p_NumSprites[freeshort2]=curpos;
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=2+(freeshort3<<2); // [NumDoors]
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=2+(freeshort3<<5); // [NumZSector]
		p_NumZSector[freeshort2]=curpos;
		memcpy(&freeshort3, bytelist+curpos, 2);
		memcpy(&freeshort4, bytelist+curpos+2, 2);
		curpos+=6+(freeshort3*freeshort4*8); // [NumLights]
		p_NumLights[freeshort2]=curpos;
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=2+(freeshort3*20); // [NumStaticMeshes]
		p_NumStaticMeshes[freeshort2]=curpos;
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=6+(freeshort3*20); // [AlternateRoom]
		p_AlternateRoom[freeshort2]=curpos-4;
	}
	p_NumFloorData=curpos;
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<1); // [NumMeshData]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<1); // [NumMeshPointers]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<2); // [NumAnimations]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<5); // [NumStateChanges]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1*6); // [NumAnimDispatches]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<3); // [NumAnimCommands]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<1); // [NumMeshTrees]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<2); // [NumFrames]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<1); // [NumMoveables]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1*20); // [NumStaticMeshes]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<5); // [NumObjectTextures]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<4); // [NumSpriteTextures]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<4); // [NumSpriteSequences]
	p_NumSpriteSequences=curpos;
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<3); // [NumCameras]
	p_NumCameras=curpos;
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<4); // [NumSoundSources]
	p_NumSoundSources = curpos;
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<4); // [NumBoxes]
	p_NumBoxes = curpos;
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1*20); // [NumOverlaps]
	p_NumOverlaps = curpos;
	memcpy(&freeuint2, bytelist+curpos, 4);
	curpos+=4+(freeuint2<<1)+(freeuint1*12); // [NumAnimatedTextures]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<1); // [NumItems]
	p_NumItems=curpos;
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=516+(freeuint1*22); // [NumSoundDetails]
	p_NumSoundDetails=curpos;
	/*
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=8+(freeuint1<<3);
	memcpy(&freeshort1, bytelist+curpos, 2);
	curpos+=2+(freeshort1<<4);
	*/
	// </FILE NAVIGATION>
	if (!_strnicmp(args[2],"list",4)||!_strnicmp(args[2],"clist",5)) tr1psx_list(bytelist, args, roomX, roomY, roomZ, p_NumVertices, p_NumSprites, p_NumLights, p_NumZSector, p_NumStaticMeshes, p_AlternateRoom, p_NumFloorData, p_NumSpriteSequences, p_NumCameras, p_NumBoxes, p_NumSoundSources, p_NumItems, numRooms, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"item",4)) tr1pc_add_item(bytelist, args, roomX, roomY, roomZ, p_NumItems, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"item",4)) tr1pc_replace_item(bytelist, argc, args, roomX, roomY, roomZ, p_NumItems, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"item",4)) tr1pc_remove_item(bytelist, argc, args, p_NumZSector, p_NumFloorData, p_NumItems, numRooms, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"staticmesh",10)) tr1psx_add_staticmesh(bytelist, args, roomX, roomY, roomZ, p_NumStaticMeshes, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"staticmesh",10)) tr1psx_replace_staticmesh(bytelist, argc, args, roomX, roomY, roomZ, p_NumStaticMeshes, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"staticmesh",10)) tr1psx_remove_staticmesh(bytelist, args, p_NumStaticMeshes, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"sprite",6)) tr1psx_add_sprite(bytelist, args, roomY, p_NumVertices, p_NumSprites, p_NumSpriteSequences, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"sprite",6)) tr1psx_replace_sprite(bytelist, args, argc, roomY, p_NumVertices, p_NumSprites, p_NumSpriteSequences, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"sprite",6)) tr1pc_remove_sprite(bytelist, args, p_NumVertices, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"soundsource",11)) tr1pc_add_soundsource(bytelist, args, p_NumSoundSources, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"soundsource",11)) tr1pc_replace_soundsource(bytelist, argc, args, p_NumSoundSources, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"soundsource",11)) tr1pc_remove_soundsource(bytelist, args, p_NumSoundSources, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"light",5)) tr1psx_add_light(bytelist, args, roomX, roomY, roomZ, p_NumLights, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"light",5)) tr1psx_replace_light(bytelist, args, roomX, roomY, roomZ, p_NumLights, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"light",5)) tr1psx_remove_light(bytelist, args, p_NumLights, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"floordata",9)) tr1pc_replace_floordata(bytelist, args, argc, roomX, roomY, roomZ, p_NumZSector, p_NumFloorData, p_NumCameras, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"floordata",9)) tr1pc_remove_floordata(bytelist, args, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"all",3)) tr1psx_remove_all(bytelist, argc, args, p_NumVertices, p_NumSprites, p_NumLights, p_NumZSector, p_NumStaticMeshes, p_NumFloorData, p_NumCameras, p_NumSoundSources, p_NumItems, p_NumBoxes, numRooms, fsize);
	if (!_strnicmp(args[2],"alternate",9)&&!_strnicmp(args[3],"room",4)) tr1pc_alternate_room(bytelist, args, p_AlternateRoom, fsize);
	if (!_strnicmp(args[2],"roomlight",9)) tr1pc_roomlight(bytelist, args, p_NumLights, numRooms, fsize);
	if (!_strnicmp(args[2],"water",5)) tr1pc_water(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"nowater",7)) tr1pc_nowater(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"samplenumber",12)) tr1pc_get_samplenumber(bytelist, args, p_NumSoundDetails, fsize);
	if (!_strnicmp(args[2],"extract",7)&&!_strnicmp(args[3],"sample",6)) tr1psx_extract_sample(bytelist, args, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"sample",6)) tr1psx_replace_sample(bytelist, args, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"geometry",8)) tr1psx_get_geometry(bytelist, args, roomX, roomY, roomZ, p_NumVertices, p_NumLights, p_NumZSector, numRooms, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"roompos",7)) printf("X=%i Z=%i Y=%i\n",roomX[strtol(args[4], NULL, 10)],roomZ[strtol(args[4], NULL, 10)],roomY[strtol(args[4], NULL, 10)]); // This returns the position of a room. The syntax is "trmod [FILE] GET ROOMPOS [Room]"
	if (!_strnicmp(args[2],"move",4)&&!_strnicmp(args[3],"room",4)) tr1psx_move_room(bytelist,  argc, args, p_NumVertices, p_NumZSector, p_NumStaticMeshes, p_NumItems, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"roomsize",8)) tr1pc_get_roomsize(bytelist, args, p_NumVertices, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"resize",6)&&!_strnicmp(args[3],"room",4)) tr1pc_resize_room(bytelist, args, p_NumVertices, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"room",4)) tr1psx_add_room(bytelist, args, p_NumVertices, p_NumFloorData, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"floorheight",11)) tr1pc_get_floorheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"ceilingheight",13)) tr1pc_get_ceilingheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"set",3)&&!_strnicmp(args[3],"floorheight",11)) tr1pc_set_floorheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"set",3)&&!_strnicmp(args[3],"ceilingheight",13)) tr1pc_set_ceilingheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"vertex",6)) tr1psx_add_vertex(bytelist, args, p_NumVertices, roomY, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"vertex",6)) tr1psx_replace_vertex(bytelist, args, p_NumVertices, roomY, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"vertex",6)) tr1psx_remove_vertex(bytelist, argc, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"rectangle",9)) tr1psx_add_rectangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"rectangle",9)) tr1psx_replace_rectangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"rectangle",9)) tr1psx_remove_rectangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"triangle",8)) tr1psx_add_triangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"triangle",8)) tr1psx_replace_triangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"triangle",8)) tr1psx_remove_triangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"viewport",8)) tr1pc_add_viewport(bytelist, args, roomY, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"viewport",8)) tr1pc_replace_viewport(bytelist, args, roomY, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"viewport",8)) tr1pc_remove_viewport(bytelist, args, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"zones",5)) tr1pc_get_zones(bytelist, args, p_NumBoxes, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"zone",4)) tr1pc_zone(bytelist, args, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"zone",4)) tr1pc_add_zone(bytelist, args, p_NumBoxes, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"zone",4)) tr1pc_replace_zone(bytelist, args, p_NumBoxes, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"overlap",7)) tr1pc_add_overlap(bytelist, args, argc, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"overwrite",7)&&!_strnicmp(args[3],"overlap",7)) tr1pc_overwrite_overlap(bytelist, args, argc, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"offset",6)) tr1psx_get_offset(bytelist, args, argc, p_NumVertices, p_NumSprites, p_NumLights, p_NumZSector, p_NumStaticMeshes, p_AlternateRoom, p_NumFloorData, p_NumItems, p_NumSpriteSequences, p_NumCameras, p_NumBoxes, p_NumOverlaps, p_NumSoundSources, fsize);

	free(roomX);
	free(roomY);
	free(roomZ);
	free(p_NumVertices);
	free(p_NumSprites);
	free(p_NumZSector);
	free(p_NumLights);
	free(p_NumStaticMeshes);
	free(p_AlternateRoom);
}
void tr1psx_list(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumBoxes, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned short numRooms, unsigned fsize){
	/*
	This function produces a list of all Items, Static Meshes, Sprites, Soundsources, Alternate rooms and FloorData
	The function LIST produces a clear and easy to read format, and CLIST produces the list in the form of TRMOD commands
	The syntax is "trmod [FILE] LIST/CLIST [OUTPUT FILE]"
	=================================================================================
		The List format is as follows:
		____________________________________________________________________________
		Item(ObjectID,Room,X,Z,Y,Angle,Intensity1,Intensity1,Flags)
		Static Mesh(ObjectID,Room,X,Z,Y,Angle,Intensity1,Intensity1)
		Sprite(ObjectID,Room,X,Z,Y,Lighting1,Lighting1,0)
		Light(Room,X,Z,Y,Intensity1,Intensity1,Fade1,Fade1)
		Sound Source(SoundID,X,Z,Y,Flags)
		Alternate Room(Room,Alternate Room)
		FloorData(Room,X,Z,Y(
			FDFunction
			FDFunction
			FDFunction
		)
		The FDFunctions are as follows:
		-------------------------------
			Floorportal(Room Below)
			Ceilingportal(Room Above)
			Portal(Adjoining Room)
			Floorslant(XSlant,ZSlant)
			Ceilingslant(XSlant,ZSlant)
			Trigger(Timer,Only Once,Mask
				Trigger Type
					Trigger Action
					Trigger Action
					Trigger Action
					Trigger Action
				)
			)
			Kill Lara
			The Trigger Types are as follows:
			---------------------------------
				Trigger(
				Pad(
				Switch(Switch Item)(
				Key(Keyhole Item)(
				Pickup(Picked up Item)(
				Heavy Trigger(
				Antipad(
				Combat(
				Dummy(
				Antitrigger(
			The Trigger Actions are as follows:
			-----------------------------------
					Object(Item)
					Camera(Room,X,Z,Y,Flag,Movetime,Time,Only Once)
					Underwater Current(Room,X,Z,Y,Strength,Zone)
					Flip Map(Parameter)
					Flip On(FlipMap)
					Flip Off(FlipMap)
					Look at Item(Item)
					End Level
					Play Soundtrack(Track Number)
					Effect(Effect)
					Found Secret(Secret Number)
					Clear Bodies
		____________________________________________________________________________
		The CList format is as follows:
		____________________________________________________________________________
		ADD ITEM ObjectID Room X Z Y Angle Intensity1 Intensity1 Flags
		ADD STATICMESH ObjectID Room X Z Y Angle Intensity1 Intensity1
		ADD SPRITE ObjectID Room X Z Y Lighting1 Lighting1 0
		ADD LIGHT Room X Z Y Intensity1 Intensity1 Fade1 Fade1
		ADD SOUNDSOURCE SoundID X Z Y Flags
		ALTERNATE ROOM Room Alternate_Room
		REPLACE FLOORDATA Room X Z Y FDFUNCTION FDFUNCTION FDFUNCTION
		The FDFunctions are as follows:
		-------------------------------
			FLOORPORTAL(Room_Below)
			CEILINGPORTAL(Room_Above)
			PORTAL(Adjoining_Room)
			FLOORSLANT(XSlant,ZSlant)
			CEILINGSLANT(XSlant,ZSlant)
			TRIGGER(Trigger_Type:TIMER:ONLY_ONCE:MASK:Trigger_Action;Trigger_Action;Trigger_Action;Trigger_Action)
			KILL
			The Trigger_Types are as follows:
			---------------------------------
				TRIGGER
				PAD
				SWITCH:Switch_Item
				KEY:Keyhole_Item
				PICKUP:Picked_up_Item
				HEAVYTRIGGER
				ANTIPAD
				COMBAT
				DUMMY
				ANTITRIGGER
			The Trigger Actions are as follows:
			-----------------------------------
					OBJECT(Item)
					CAMERA(Room,X,Z,Y,Flag,Movetime,Time,Only_Once)
					CURRENT(Room,X,Z,Y,Strength,Zone)
					FLIPMAP(Parameter)
					FLIPON(FlipMap)
					FLIPOFF(FlipMap)
					LOOKITEM(Item)
					ENDLEVEL
					SOUNDTRACK(Track Number)
					EFFECT(Effect)
					SECRET(Secret Number)
					CLEARBODIES
		____________________________________________________________________________
	=================================================================================
	*/
	unsigned curpos;
	int freeint1;
	int freeint2;
	unsigned freeuint1;
	unsigned freeuint2;
	unsigned freeuint3;
	unsigned freeuint4;
	unsigned freeuint5;
	short freeshort1;
	unsigned short freeushort1;
	unsigned short freeushort2;
	unsigned short freeushort3;
	unsigned short freeushort4;
	unsigned short freeushort5;
	unsigned short freeushort6;
	char *freestring1=malloc(6);
	char freechar1=44;
	char freechar2;
	char freechar3;
	char freechar4;
	unsigned char freeuchar1;
	if (!_strnicmp(args[2],"clist",5)) freechar1=32;
	FILE *file = fopen(args[3],"w"); // Opens text file
	// <ITEMS>
	curpos=p_NumItems+4;
	memcpy(&freeuint1,bytelist+p_NumItems,4);
	while (freeuint1>0){
		memcpy(&freeushort1,bytelist+curpos,2);
		if (!_strnicmp(args[2],"list",4)) fprintf(file,"Item(%i%c",freeushort1,freechar1);
		if (!_strnicmp(args[2],"clist",5)) fprintf(file,"trmod %s ADD ITEM %i%c",args[1],freeushort1,freechar1);
		memcpy(&freeushort1,bytelist+curpos+2,2);
		fprintf(file,"%u%c",freeushort1,freechar1);
		memcpy(&freeuint2,bytelist+curpos+4,4);
		fprintf(file,"%i%c",(freeuint2-roomX[freeushort1]),freechar1);
		memcpy(&freeuint2,bytelist+curpos+12,4);
		fprintf(file,"%i%c",(freeuint2-roomZ[freeushort1]),freechar1);
		memcpy(&freeint1,bytelist+curpos+8,4);
		fprintf(file,"%i%c",(roomY[freeushort1]-freeint1),freechar1);
		memcpy(&freeushort1,bytelist+curpos+16,2);
		freeushort1=(((freeushort1&0xe000)>>13)*45);
		fprintf(file,"%u%c",freeushort1,freechar1);
		memcpy(&freeshort1,bytelist+curpos+18,2);
		fprintf(file,"%i%c%i%c",freeshort1,freechar1,freeshort1,freechar1);
		memcpy(&freeushort1,bytelist+curpos+20,2);
		fprintf(file,"%04X",freeushort1);
		if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
		if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
		curpos+=22;
		freeuint1--;
	}
	// </ITEMS>
	// <STATIC MESHES>
	for (freeushort1=0;freeushort1<numRooms;freeushort1++){
		curpos=p_NumStaticMeshes[freeushort1];
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos+16,2);
			if (!_strnicmp(args[2],"list",4)) fprintf(file,"Static Mesh(%i%c%i%c",freeushort3,freechar1,freeushort1,freechar1);
			if (!_strnicmp(args[2],"clist",5)) fprintf(file,"trmod %s ADD STATICMESH %i%c%i%c",args[1],freeushort3,freechar1,freeushort1,freechar1);
			memcpy(&freeuint1,bytelist+curpos,4);
			fprintf(file,"%i%c",(freeuint1-roomX[freeushort1]),freechar1);
			memcpy(&freeuint1,bytelist+curpos+8,4);
			fprintf(file,"%i%c",(freeuint1-roomZ[freeushort1]),freechar1);
			memcpy(&freeint1,bytelist+curpos+4,4);
			fprintf(file,"%i%c",(roomY[freeushort1]-freeint1),freechar1);
			memcpy(&freeushort3,bytelist+curpos+12,2);
			freeushort3=(((freeushort3&0xe000)>>13)*45);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeshort1,bytelist+curpos+14,2);
			fprintf(file,"%i%c%i",freeshort1,freechar1,freeshort1);
			if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
			if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
			curpos+=20;
			freeushort2--;
		}
	}
	// </STATIC MESHES>
	// <SPRITES>
	for (freeushort1=0;freeushort1<numRooms;freeushort1++){
		curpos=p_NumSprites[freeushort1];
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos+2,2);
			freeuint1=p_NumSpriteSequences+4;
			memcpy(&freeushort4, bytelist+freeuint1+6,2);
			while (freeushort3!=freeushort4){
				freeuint1 += 8;
				memcpy(&freeushort4, bytelist+freeuint1+6,2);
			}
			memcpy(&freeuint1,bytelist+freeuint1,4);
			if (!_strnicmp(args[2],"list",4)) fprintf(file,"Sprite(%i%c%i%c",freeuint1,freechar1,freeushort1,freechar1);
			if (!_strnicmp(args[2],"clist",5)) fprintf(file,"trmod %s ADD SPRITE %i%c%i%c",args[1],freeuint1,freechar1,freeushort1,freechar1);
			memcpy(&freeushort3,bytelist+curpos,2);
			freeuint1 = p_NumVertices[freeushort1] + 4 + (8 * freeushort3);
			memcpy(&freeushort3,bytelist+freeuint1,2);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeushort3,bytelist+freeuint1+4,2);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeshort1,bytelist+freeuint1+2,2);
			fprintf(file,"%i%c",(roomY[freeushort1]-freeshort1),freechar1);
			memcpy(&freeushort3,bytelist+freeuint1+6,2);
			freeushort3=8191-((freeushort3*8191)/255);
			fprintf(file,"%u%c%u%c0",freeushort3,freechar1,freeushort3,freechar1);
			if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
			if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
			curpos+=4;
			freeushort2--;
		}
	}
	// </SPRITES>
	// <LIGHTS>
	for (freeushort1=0;freeushort1<numRooms;freeushort1++){
		curpos=p_NumLights[freeushort1];
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeuint1,bytelist+curpos,4);
			if (!_strnicmp(args[2],"list",4)) fprintf(file,"Light(%i%c%i%c",freeushort1,freechar1,(freeuint1-roomX[freeushort1]),freechar1);
			if (!_strnicmp(args[2],"clist",5)) fprintf(file,"trmod %s ADD LIGHT %i%c%i%c",args[1],freeushort1,freechar1,(freeuint1-roomX[freeushort1]),freechar1);
			memcpy(&freeuint1,bytelist+curpos+8,4);
			fprintf(file,"%i%c",(freeuint1-roomZ[freeushort1]),freechar1);
			memcpy(&freeint1,bytelist+curpos+4,4);
			fprintf(file,"%i%c",(roomY[freeushort1]-freeint1),freechar1);
			memcpy(&freeushort3,bytelist+curpos+12,2);
			fprintf(file,"%u%c%u%c",freeushort3,freechar1,freeushort3,freechar1);
			memcpy(&freeuint1,bytelist+curpos+16,4);
			fprintf(file,"%i%c%i",freeuint1,freechar1,freeuint1);
			if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
			if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
			curpos+=20;
			freeushort2--;
		}
	}
	// </LIGHTS>
	// <SOUNDSOURCES>
	curpos=p_NumSoundSources+4;
	memcpy(&freeuint1,bytelist+p_NumSoundSources,4);
	while (freeuint1>0){
		memcpy(&freeushort1,bytelist+curpos+12,2);
		if (!_strnicmp(args[2],"list",4)) fprintf(file,"Sound Source(%u,",freeushort1);
		if (!_strnicmp(args[2],"clist",5)) fprintf(file,"trmod %s ADD SOUNDSOURCE %u ",args[1],freeushort1);
		memcpy(&freeint1,bytelist+curpos,4);
		fprintf(file,"%i%c",freeint1,freechar1);
		memcpy(&freeint1,bytelist+curpos+8,4);
		fprintf(file,"%i%c",freeint1,freechar1);
		memcpy(&freeint1,bytelist+curpos+4,4);
		fprintf(file,"%i%c",freeint1,freechar1);
		memcpy(&freeushort1,bytelist+curpos+14,2);
		fprintf(file,"%04X",freeushort1);
		if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
		if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
		curpos+=16;
		freeuint1--;
	}
	// </SOUNDSOURCES>
	// <ALTERNATE ROOMS>
	for (freeushort1=0;freeushort1<numRooms;freeushort1++){
		memcpy(&freeushort2,bytelist+p_AlternateRoom[freeushort1],2);
		if (!_strnicmp(args[2],"list",4)&&freeushort2!=65535) fprintf(file,"Alternate Room(%i%c%i)\n",freeushort1,freechar1,freeushort2);
		if (!_strnicmp(args[2],"clist",5)&&freeushort2!=65535) fprintf(file,"trmod %s ALTERNATE ROOM %i%c%i\n",args[1],freeushort1,freechar1,freeushort2);
	}
	// </ALTERNATE ROOMS>
	// <FLOORDATA>
	for (freeushort1=0;freeushort1<numRooms;freeushort1++){
		curpos=p_NumZSector[freeushort1]+4;
		memcpy(&freeushort2,bytelist+curpos-2,2);
		memcpy(&freeushort3,bytelist+curpos-4,2);
		freeuint1=(freeushort2*freeushort3);
		for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
			freechar2=0;
			memcpy(&freeushort2,bytelist+curpos,2);
			if (freeushort2!=0) freechar2=1;
			memcpy(&freeuchar1,bytelist+curpos+4,1);
			if (freeuchar1!=255) freechar2=1;
			memcpy(&freeuchar1,bytelist+curpos+6,1);
			if (freeuchar1!=255) freechar2=1;
			if (freechar2==1){
				freeuint3=freeuint2+1;
				freeuint4=1;
				memcpy(&freeushort2,bytelist+p_NumZSector[freeushort1],2);
				while (freeuint3>freeushort2){
					freeuint3-=freeushort2;
					freeuint4++;
				}
				if (!_strnicmp(args[2],"list",4)) fprintf(file,"FloorData(%i,%i,%i(\n",freeushort1,freeuint4,freeuint3);
				if (!_strnicmp(args[2],"clist",5)) fprintf(file,"trmod %s REPLACE FLOORDATA %i %i %i ",args[1],freeushort1,freeuint4,freeuint3);
				memcpy(&freeuchar1,bytelist+curpos+4,1);
				if (freeuchar1!=255){
					if (!_strnicmp(args[2],"list",4)) fprintf(file,"    Floorportal(%i)\n",freeuchar1);
					if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\"FLOORPORTAL(%i)\" ",freeuchar1);
				}
				memcpy(&freeuchar1,bytelist+curpos+6,1);
				if (freeuchar1!=255){
					if (!_strnicmp(args[2],"list",4)) fprintf(file,"    Ceilingportal(%i)\n",freeuchar1);
					if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\"CEILINGPORTAL(%i)\" ",freeuchar1);
				}
				memcpy(&freeushort2,bytelist+curpos,2);
				if (freeushort2!=0){
					freeuint3=p_NumFloorData+4+(freeushort2*2);
					freechar2=0;
					while (freechar2==0){
						memcpy(&freeushort2,bytelist+freeuint3,2);
						if (freeushort2>=32768) freechar2=1;
						freeushort3=freeushort2 & 0x1F;
						if (freeushort3==1){
							memcpy(&freeushort4,bytelist+freeuint3+2,2);
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"    Portal(%i)\n",freeushort4);
							if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\"PORTAL(%i)\" ",freeushort4);
							freeuint3+=4;
						}
						if (freeushort3==2){
							memcpy(&freechar3,bytelist+freeuint3+2,1);
							memcpy(&freechar4,bytelist+freeuint3+3,1);
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"    FloorSlant(%i,%i)\n",freechar3,freechar4);
							if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\"FLOORSLANT(%i,%i)\" ",freechar3,freechar4);
							freeuint3+=4;
						}
						if (freeushort3==3){
							memcpy(&freechar3,bytelist+freeuint3+2,1);
							memcpy(&freechar4,bytelist+freeuint3+3,1);
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"    CeilingSlant(%i,%i)\n",freechar3,freechar4);
							if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\"CEILINGSLANT(%i,%i)\" ",freechar3,freechar4);
							freeuint3+=4;
						}
						if (freeushort3==4){
							memcpy(&freeushort4,bytelist+freeuint3+2,2);
							freeshort1=freeushort4 & 0xFF;
							freeuint5=freeushort4 & 0x100;
							freeuint4=freeushort4 & 0x3E00;
							freeuint4 >>= 9;
							if (!_strnicmp(args[2],"list",4)){
								if (freeuint5==256) fprintf(file,"    Trigger(%u,True,%u\n",freeshort1,freeuint4);
								if (freeuint5==0) fprintf(file,"    Trigger(%u,False,%u\n",freeshort1,freeuint4);
							}
							freeushort5=freeushort2 & 0x7F00;
							freeushort5 >>= 8;
							if (freeuint5==256) strcpy(freestring1,"TRUE\0\0");
							if (freeuint5==0) strcpy(freestring1,"FALSE\0");;
							memcpy(&freeushort6, bytelist+freeuint3+4,2);
							if (freeushort5==0&&!_strnicmp(args[2],"list",4)) fprintf(file,"          Trigger(\n");
							if (freeushort5==0&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(TRIGGER:%u:%s:%u:",freeshort1,freestring1,freeuint4);
							if (freeushort5==1&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Pad(\n");
							if (freeushort5==1&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(PAD:%u:%s:%u:",freeshort1,freestring1,freeuint4);
							if (freeushort5==2&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Switch(%u)(\n",freeushort6);
							if (freeushort5==2&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(SWITCH:%u:%u:%s:%u:",freeushort6,freeshort1,freestring1,freeuint4);
							if (freeushort5==3&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Key(%u)(\n",freeushort6);
							if (freeushort5==3&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(KEY:%u:%u:%s:%u:",freeushort6,freeshort1,freestring1,freeuint4);
							if (freeushort5==4&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Pickup(%u)(\n",freeushort6);
							if (freeushort5==4&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(PICKUP:%u:%u:%s:%u:",freeushort6,freeshort1,freestring1,freeuint4);
							if (freeushort5==5&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Heavy Trigger(\n");
							if (freeushort5==5&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(HEAVYTRIGGER:%u:%s:%u:",freeshort1,freestring1,freeuint4);
							if (freeushort5==6&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Antipad(\n");
							if (freeushort5==6&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(ANTIPAD:%u:%s:%u:",freeshort1,freestring1,freeuint4);
							if (freeushort5==7&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Combat(\n");
							if (freeushort5==7&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(COMBAT:%u:%s:%u:",freeshort1,freestring1,freeuint4);
							if (freeushort5==8&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Dummy(\n");
							if (freeushort5==8&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(DUMMY:%u:%s:%u:",freeshort1,freestring1,freeuint4);
							if (freeushort5==9&&!_strnicmp(args[2],"list",4)) fprintf(file,"        Antitrigger(\n");
							if (freeushort5==9&&!_strnicmp(args[2],"clist",5)) fprintf(file,"\"TRIGGER(ANTITRIGGER:%u:%s:%u:",freeshort1,freestring1,freeuint4);
							if (freeushort5>1&&freeushort5<5) freeuint3+=2;
							freeuint3+=4;
							freechar1=0;
							while (freechar1==0){
								memcpy(&freeushort6, bytelist+freeuint3,2);
								if ((freeushort6 & 0x8000)==32768) freechar1=1;
								freeshort1=(freeushort6 & 0x7C00);
								freeshort1 >>= 10;
								freeuchar1=freeshort1;
								if (freeuchar1==0) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Object(%i)\n",freeshort1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"OBJECT(%i)",freeshort1);
								}
								if (freeuchar1==1) {
									memcpy(&freeshort1, bytelist+freeuint3+2,2);
									freeushort5=(freeushort6 & 0x3FF);
									freeuint4=p_NumCameras+4+(16*freeushort5);
									memcpy(&freeushort5,bytelist+freeuint4+12,2);
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Camera(%u,",freeushort5);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"CAMERA(%u,",freeushort5);
									memcpy(&freeint2,bytelist+freeuint4+0,4);
									fprintf(file,"%i,",(freeint2-roomX[freeushort5]));
									memcpy(&freeint2,bytelist+freeuint4+8,4);
									fprintf(file,"%i,",(freeint2-roomZ[freeushort5]));
									memcpy(&freeint2,bytelist+freeuint4+4,4);
									fprintf(file,"%i,",(roomY[freeushort5]-freeint2));
									memcpy(&freeushort5,bytelist+freeuint4+14,2);
									fprintf(file,"%04X,",freeushort5);
									freeushort5=(freeshort1 & 0xFF);
									fprintf(file,"%u,",freeushort5);
									freeushort5=(freeshort1 & 0x3E00);
									freeushort5>>=9;
									fprintf(file,"%u,",freeushort5);
									freeushort5=(freeshort1 & 0x100);
									if (freeushort5==256&&!_strnicmp(args[2],"list",4)) fprintf(file,"True)\n");
									if (freeushort5==0&&!_strnicmp(args[2],"list",4)) fprintf(file,"False)\n");
									if (freeushort5==256&&!_strnicmp(args[2],"clist",5)) fprintf(file,"TRUE)");
									if (freeushort5==0&&!_strnicmp(args[2],"clist",5)) fprintf(file,"FALSE)");
									if ((freeshort1 & 0x8000)==32768) freechar1=1;
									freeuint3+=2;
								}
								if (freeuchar1==2) {
									freeshort1=(freeushort6 & 0x3FF);
									freeuint4=p_NumCameras+4+(16*freeshort1);
									memcpy(&freeint2,bytelist+freeuint4,4);
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Underwater Current(%i,%i,",freeushort1,(freeint2-roomX[freeushort1]));
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"CURRENT(%i,%i,",freeushort1,(freeint2-roomX[freeushort1]));
									memcpy(&freeint2,bytelist+freeuint4+8,4);
									fprintf(file,"%i,",(freeint2-roomZ[freeushort1]));
									memcpy(&freeint2,bytelist+freeuint4+4,4);
									fprintf(file,"%i,",(roomY[freeushort1]-freeint2));
									memcpy(&freeushort5,bytelist+freeuint4+12,2);
									fprintf(file,"%u,",freeushort5);
									memcpy(&freeushort5,bytelist+freeuint4+14,2);
									fprintf(file,"%u)",freeushort5);
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"\n");
								}
								if (freeuchar1==3) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Flip Map(%i)\n",freeshort1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"FLIPMAP(%i)",freeshort1);
								}
								if (freeuchar1==4) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Flip On(%i)\n",freeshort1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"FLIPON(%i)",freeshort1);
								}
								if (freeuchar1==5) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Flip Off(%i)\n",freeshort1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"FLIPOFF(%i)",freeshort1);
								}
								if (freeuchar1==6) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Look at Item(%i)\n",freeshort1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"LOOKITEM(%i)",freeshort1);
								}
								if (freeuchar1==7) {
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            End Level\n");
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"ENDLEVEL");
								}
								if (freeuchar1==8) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Play Soundtrack(%i)\n",freeshort1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"SOUNDTRACK(%i)",freeshort1);
								}
								if (freeuchar1==9) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Effect(%i)\n",freeshort1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"EFFECT(%i)",freeshort1);
								}
								if (freeuchar1==10) {
									memcpy(&freeshort1,&freeushort6,2);
									freeshort1 &= 0x3FF;
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Found Secret(%i)\n",freeshort1+1);
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"SECRET(%i)",freeshort1+1);
								}
								if (freeuchar1==11) {
									if (!_strnicmp(args[2],"list",4)) fprintf(file,"            Clear Bodies\n");
									if (!_strnicmp(args[2],"clist",5)) fprintf(file,"CLEARBODIES");
								}
								freeuint3+=2;
								if (!_strnicmp(args[2],"clist",5)&&freechar1==0) fprintf(file,";");
							}
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"        )\n");
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"    )\n");
							if (!_strnicmp(args[2],"clist",5)) fprintf(file,")\" ");
						}
						if (freeushort3==5){
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"    Kill Lara\n");
							if (!_strnicmp(args[2],"clist",5)) fprintf(file,"KILL ");
							freeuint3+=2;
						}
					}
				}
				if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
				if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
			}
			curpos += 8;
		}
	}
	// </FLOORDATA>
	fclose(file); // Closes text file
}
void tr1psx_add_staticmesh(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize){
	// This function adds a static mesh to the level. The syntax is "trmod [FILE] ADD STATICMESH [ObjectID] [Room] [X] [Z] [Y] [Angle] [Intensity] [Intensity2]".
	char *temp=malloc(20);
	unsigned short freeushort1 = strtol(args[5], NULL, 10);
	int freeint1=strtol(args[6], NULL, 10);
	freeint1+=roomX[freeushort1];
	memcpy(temp,&freeint1,4);
	freeint1=strtol(args[8], NULL, 10);
	freeint1=roomY[freeushort1]-freeint1;
	memcpy(temp+4,&freeint1,4);
	freeint1=strtol(args[7], NULL, 10);
	freeint1+=roomZ[freeushort1];
	memcpy(temp+8,&freeint1,4);
	unsigned short freeushort2 = strtol(args[9], NULL, 10);
	freeushort2=(freeushort2/45)<<13;
	memcpy(temp+12,&freeushort2,2);
	freeushort2 = strtol(args[10], NULL, 10);
	memcpy(temp+14,&freeushort2,2);
	freeushort2 = strtol(args[4], NULL, 10);
	memcpy(temp+16,&freeushort2,2);
	memset(temp+18,0,2);
	memcpy(&freeushort2,bytelist+p_NumStaticMeshes[freeushort1],2);
	bytelist=insertrange(bytelist,(p_NumStaticMeshes[freeushort1]+2+freeushort2*20),20,temp,fsize);
	fsize+=20;
	freeushort2++;
	memcpy(bytelist+p_NumStaticMeshes[freeushort1],&freeushort2,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_replace_staticmesh(char *bytelist, int argc, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize){
	// This function replaces a static mesh to the level. The syntax is "trmod [FILE] REPLACE STATICMESH [Room] [Staticmesh] [ObjectID] [X] [Z] [Y] [Angle] [Intensity] [Intensity2]" or "trmod [FILE] REPLACE STATICMESH [Room] [Staticmesh] [ObjectID]".
	unsigned freeuint1 = p_NumStaticMeshes[strtol(args[4], NULL, 10)]-18+(strtol(args[5], NULL, 10)*20);
	unsigned short freeushort1 = strtol(args[6], NULL, 10);
	if (argc>7){
		int freeint1=strtol(args[7], NULL, 10);
		freeint1+=roomX[strtol(args[4], NULL, 10)];
		memcpy(bytelist+freeuint1,&freeint1,4);
		freeint1=strtol(args[9], NULL, 10);
		freeint1=roomY[strtol(args[4], NULL, 10)]-freeint1;
		memcpy(bytelist+freeuint1+4,&freeint1,4);
		freeint1=strtol(args[8], NULL, 10);
		freeint1+=roomZ[strtol(args[4], NULL, 10)];
		memcpy(bytelist+freeuint1+8,&freeint1,4);
		unsigned short freeushort2 = strtol(args[10], NULL, 10);
		freeushort2=(freeushort2/45)<<13;
		memcpy(bytelist+freeuint1+12,&freeushort2,2);
		freeushort2 = strtol(args[11], NULL, 10);
		memcpy(bytelist+freeuint1+14,&freeushort2,2);
		memcpy(bytelist+freeuint1+16,&freeushort1,2);
	}else{
		memcpy(bytelist+freeuint1+16,&freeushort1,2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_remove_staticmesh(char *bytelist, char *args[], unsigned p_NumStaticMeshes[], unsigned fsize){
	// This function removes a static mesh from the level. The syntax is "trmod [FILE] REMOVE STATICMESH [Room] [Staticmesh]".
	unsigned freeuint1 = p_NumStaticMeshes[strtol(args[4], NULL, 10)]-18+(strtol(args[5], NULL, 10)*20);
	unsigned short freeushort1;
	memcpy(&freeushort1,bytelist+p_NumStaticMeshes[strtol(args[4], NULL, 10)],2);
	freeushort1--;
	memcpy(bytelist+p_NumStaticMeshes[strtol(args[4], NULL, 10)], &freeushort1, 2);
	fsize=removerange(bytelist,freeuint1,20,fsize);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_add_sprite(char *bytelist, char *args[], int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize){
	// This function adds a sprite to the level. The syntax is "trmod [FILE] ADD SPRITE [ObjectID] [Room] [X] [Z] [Y] [Lighting]".
	int freeint1;
	char freechar1=0;
	char *temp=malloc(8);
	short freeshort1;
	short freeshort2=strtol(args[5], NULL, 10);
	unsigned freeushort1;
	unsigned freeuint1=p_NumVertices[freeshort2]+4;
	unsigned freeuint2=0;
	unsigned freeuint3;
	unsigned freeuint4=strtol(args[4], NULL, 10);;
	freeshort1=strtol(args[6], NULL, 10);
	memcpy(temp,&freeshort1,2);
	freeshort1=strtol(args[8], NULL, 10);
	freeshort1=(roomY[freeshort2]-freeshort1);
	memcpy(temp+2,&freeshort1,2);
	freeshort1=strtol(args[7], NULL, 10);
	memcpy(temp+4,&freeshort1,2);
	freeushort1=strtol(args[9], NULL, 10);
	freeushort1=((8192-freeushort1)*255)/8191;
	memcpy(temp+6,&freeushort1,2);
	memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
	while (freeshort1>0){
		freeint1=memcmp(temp,bytelist+freeuint1,8);
		if (freeint1==0){
			freeuint2=freeuint1;
			freechar1=1;
		}
		freeuint1+=8;
		freeshort1--;
	}
	if (freechar1==0){
		freeuint2=freeuint1;
		bytelist=insertrange(bytelist,freeuint1,8,temp,fsize);
		fsize+=8;
		p_NumSprites[freeshort2]+=8;
		p_NumSpriteSequences+=8;
		memcpy(&freeuint1,bytelist+p_NumVertices[freeshort2]-4,4);
		freeuint1+=4;
		memcpy(bytelist+p_NumVertices[freeshort2]-4,&freeuint1,4);
		memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
		freeshort1++;
		memcpy(bytelist+p_NumVertices[freeshort2],&freeshort1,2);
		memcpy(bytelist+p_NumVertices[freeshort2]+2,&freeshort1,2);
	}
	temp=malloc(4);
	freeshort1=(freeuint2-p_NumVertices[freeshort2])/8;
	memcpy(temp,&freeshort1,2);
	freeuint1=p_NumSpriteSequences+4;
	memcpy(&freeuint2,bytelist+p_NumSpriteSequences,4);
	while (freeuint2>0){
		memcpy(&freeuint3,bytelist+freeuint1,4);
		if (freeuint3==freeuint4){
			memcpy(&freeshort1,bytelist+freeuint1+6,2);
			memcpy(temp+2,&freeshort1,2);
			break;
		}
		freeuint1+=8;
		freeuint2--;
	}
	freeuint1=p_NumSprites[freeshort2]+2;
	memcpy(&freeshort1,bytelist+p_NumSprites[freeshort2],2);
	freeuint1+=(freeshort1*4);
	bytelist=insertrange(bytelist,freeuint1,4,temp,fsize);
	fsize+=4;
	memcpy(&freeuint1,bytelist+p_NumVertices[freeshort2]-4,4);
	freeuint1+=2;
	memcpy(bytelist+p_NumVertices[freeshort2]-4,&freeuint1,4);
	memcpy(&freeshort1,bytelist+p_NumSprites[freeshort2],2);
	freeshort1++;
	memcpy(bytelist+p_NumSprites[freeshort2],&freeshort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_replace_sprite(char *bytelist, char *args[], unsigned argc, int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize){
	// This function replaces a sprite in the level. The syntax is "trmod [FILE] REPLACE SPRITE [Room] [Sprite] [ObjectID] [X] [Z] [Y] [Lighting]".
	int freeint1;
	char freechar1=0;
	char *temp=malloc(8);
	short freeshort1;
	short freeshort2=strtol(args[4], NULL, 10);
	unsigned short freeushort1;
	unsigned freeuint1=p_NumVertices[freeshort2]+4;
	unsigned freeuint2=0;
	unsigned freeuint3;
	unsigned freeuint4=strtol(args[6], NULL, 10);
	if (argc>7){
		freeshort1=strtol(args[7], NULL, 10);
		memcpy(temp,&freeshort1,2);
		freeshort1=strtol(args[9], NULL, 10);
		freeshort1=(roomY[freeshort2]-freeshort1);
		memcpy(temp+2,&freeshort1,2);
		freeshort1=strtol(args[8], NULL, 10);
		memcpy(temp+4,&freeshort1,2);
		freeushort1=strtol(args[10], NULL, 10);
		freeushort1=((8192-freeushort1)*255)/8191;
		memcpy(temp+6,&freeushort1,2);
		memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
		while (freeshort1>0){
			freeint1=memcmp(temp,bytelist+freeuint1,8);
			if (freeint1==0){
				freeuint2=freeuint1;
				freechar1=1;
			}
			freeuint1+=8;
			freeshort1--;
		}
		if (freechar1==0){
			freeuint2=freeuint1;
			bytelist=insertrange(bytelist,freeuint1,8,temp,fsize);
			fsize+=8;
			p_NumSprites[freeshort2]+=8;
			p_NumSpriteSequences+=8;
			memcpy(&freeuint1,bytelist+p_NumVertices[freeshort2]-4,4);
			freeuint1+=4;
			memcpy(bytelist+p_NumVertices[freeshort2]-4,&freeuint1,4);
			memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
			freeshort1++;
			memcpy(bytelist+p_NumVertices[freeshort2],&freeshort1,2);
			memcpy(bytelist+p_NumVertices[freeshort2]+2,&freeshort1,2);
		}
		temp=malloc(4);
		freeshort1=(freeuint2-p_NumVertices[freeshort2])/8;
		memcpy(temp,&freeshort1,2);
	}
	if (argc==7) temp=malloc(2);
	freeuint1=p_NumSpriteSequences+4;
	memcpy(&freeuint2,bytelist+p_NumSpriteSequences,4);
	while (freeuint2>0){
		memcpy(&freeuint3,bytelist+freeuint1,4);
		if (freeuint3==freeuint4){
			memcpy(&freeshort1,bytelist+freeuint1+6,2);
			if (argc>7) memcpy(temp+2,&freeshort1,2);
			if (argc==7) memcpy(temp,&freeshort1,2);
			break;
		}
		freeuint1+=8;
		freeuint2--;
	}
	freeuint1=strtol(args[5], NULL, 10);
	if (argc>7) memcpy((bytelist+p_NumSprites[freeshort2]-2+(freeuint1*4)),temp,4);
	if (argc==7) memcpy((bytelist+p_NumSprites[freeshort2]+(freeuint1*4)),temp,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_add_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize){
	// This function adds a light. The syntax is "trmod [FILE] ADD LIGHT [Room] [X] [Z] [Y] [Intensity1] [Intensity2] [Fade1] [Fade2]"
	char *temp=malloc(20);
	unsigned short freeushort1 = strtol(args[4], NULL, 10);
	int freeint1=strtol(args[5], NULL, 10);
	freeint1+=roomX[freeushort1];
	memcpy(temp,&freeint1,4);
	freeint1=strtol(args[7], NULL, 10);
	freeint1=roomY[freeushort1]-freeint1;
	memcpy(temp+4,&freeint1,4);
	freeint1=strtol(args[6], NULL, 10);
	freeint1+=roomZ[freeushort1];
	memcpy(temp+8,&freeint1,4);
	unsigned short freeushort2 = strtol(args[8], NULL, 10);
	memcpy(temp+12,&freeushort2,2);
	freeint1=strtol(args[10], NULL, 10);
	memcpy(temp+16,&freeint1,4);
	memset(temp+14,0,2);
	memcpy(&freeushort2,bytelist+p_NumLights[freeushort1],2);
	bytelist=insertrange(bytelist,(p_NumLights[freeushort1]+2+freeushort2*20),20,temp,fsize);
	fsize+=20;
	freeushort2++;
	memcpy(bytelist+p_NumLights[freeushort1],&freeushort2,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_replace_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize){
	// This function replaces a static mesh to the level. The syntax is "trmod [FILE] REPLACE LIGHT [Room] [Light] [X] [Z] [Y] [Intensity1] [Intensity2] [Fade1] [Fade2]"
	unsigned freeuint1 = p_NumLights[strtol(args[4], NULL, 10)]-18+(strtol(args[5], NULL, 10)*20);
	unsigned short freeushort1 = strtol(args[4], NULL, 10);
	int freeint1=strtol(args[6], NULL, 10);
	freeint1+=roomX[freeushort1];
	memcpy(bytelist+freeuint1,&freeint1,4);
	freeint1=strtol(args[8], NULL, 10);
	freeint1=roomY[freeushort1]-freeint1;
	memcpy(bytelist+freeuint1+4,&freeint1,4);
	freeint1=strtol(args[7], NULL, 10);
	freeint1+=roomZ[freeushort1];
	memcpy(bytelist+freeuint1+8,&freeint1,4);
	unsigned short freeushort2 = strtol(args[9], NULL, 10);
	memcpy(bytelist+freeuint1+12,&freeushort2,2);
	freeint1=strtol(args[11], NULL, 10);
	memcpy(bytelist+freeuint1+16,&freeint1,4);
	memcpy(&freeushort2,bytelist+p_NumLights[freeushort1],2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_remove_light(char *bytelist, char *args[], unsigned p_NumLights[], unsigned fsize){
	// This function removes a static mesh from the level. The syntax is "trmod [FILE] REMOVE LIGHT [Room] [Light]".
	unsigned freeuint1 = p_NumLights[strtol(args[4], NULL, 10)]-18+(strtol(args[5], NULL, 10)*20);
	unsigned short freeushort1;
	memcpy(&freeushort1,bytelist+p_NumLights[strtol(args[4], NULL, 10)],2);
	freeushort1--;
	memcpy(bytelist+p_NumLights[strtol(args[4], NULL, 10)], &freeushort1, 2);
	fsize=removerange(bytelist,freeuint1,20,fsize);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_remove_all(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumFloorData, unsigned p_NumCameras, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned p_NumBoxes, unsigned short numRooms, unsigned fsize){
	// This function removes all of a given object from a level. The syntax is "trmod [FILE] REMOVE ALL {ITEMS/STATICMESHSES/SPRITES/LIGHTS/SOUNDSOURCES/CAMERAS/FLOORDATA/GEOMETRY/RECTANGLES/TRIANGLES/VIEWPORTS/ZONES}".
	int freeint1;
	unsigned curpos;
	unsigned freeuint1;
	unsigned freeuint2;
	unsigned short freeushort1;
	unsigned short freeushort2;
	if (!_strnicmp(args[4],"items",5)){
		memcpy(&freeuint1, bytelist+p_NumItems,4);
		fsize=removerange(bytelist,p_NumItems+4,(freeuint1*22),fsize);
		memset(bytelist+p_NumItems,0,4);
	}
	if (!_strnicmp(args[4],"staticmeshes",12)){
		for (freeint1=numRooms-1;freeint1>=0;freeint1--){
			memcpy(&freeushort1,bytelist+p_NumStaticMeshes[freeint1],2);
			fsize=removerange(bytelist,p_NumStaticMeshes[freeint1]+2,(freeushort1*20),fsize);
			memset(bytelist+p_NumStaticMeshes[freeint1],0,2);
		}
	}
	if (!_strnicmp(args[4],"sprites",7)){
		for (freeint1=numRooms-1;freeint1>=0;freeint1--){
			memcpy(&freeushort1,bytelist+p_NumSprites[freeint1],2);
			fsize=removerange(bytelist,p_NumSprites[freeint1]+2,(freeushort1*4),fsize);
			memcpy(&freeuint1,bytelist+p_NumVertices[freeint1]-4,4);
			freeuint1-=(freeushort1*2);
			memcpy(bytelist+p_NumVertices[freeint1]-4,&freeuint1,4);
			memset(bytelist+p_NumSprites[freeint1],0,2);
		}
	}
	if (!_strnicmp(args[4],"lights",6)){
		for (freeint1=numRooms-1;freeint1>=0;freeint1--){
			memcpy(&freeushort1,bytelist+p_NumLights[freeint1],2);
			fsize=removerange(bytelist,p_NumLights[freeint1]+2,(freeushort1*20),fsize);
			memset(bytelist+p_NumLights[freeint1],0,2);
		}
	}
	if (!_strnicmp(args[4],"soundsources",12)){
		memcpy(&freeuint1, bytelist+p_NumSoundSources,4);
		fsize=removerange(bytelist,p_NumSoundSources+4,(freeuint1*16),fsize);
		memset(bytelist+p_NumSoundSources,0,4);
	}
	if (!_strnicmp(args[4],"cameras",7)){
		memcpy(&freeuint1, bytelist+p_NumCameras,4);
		fsize=removerange(bytelist,p_NumCameras+4,(freeuint1*16),fsize);
		memset(bytelist+p_NumCameras,0,4);
	}
	if (!_strnicmp(args[4],"floordata",9)){
		memcpy(&freeuint1, bytelist+p_NumFloorData,4);
		fsize=removerange(bytelist,p_NumFloorData+6,(freeuint1*2)-2,fsize);
		memset(bytelist+p_NumFloorData,1,1);
		memset(bytelist+p_NumFloorData+1,0,5);
		for (freeint1=numRooms-1;freeint1>=0;freeint1--){
			curpos=p_NumZSector[freeint1]+4;
			memcpy(&freeushort1,bytelist+curpos-2,2);
			memcpy(&freeushort2,bytelist+curpos-4,2);
			freeuint1=(freeushort1*freeushort2);
			for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
				memset(bytelist+curpos,0,2);
				memset(bytelist+curpos+4,255,1);
				memset(bytelist+curpos+6,255,1);
				curpos+=8;
			}
		}
	}
	if (!_strnicmp(args[4],"geometry",8)){
		if (!_strnicmp(args[5],"all",3)) {
			for (freeint1=numRooms-1;freeint1>=0;freeint1--){
				freeuint1=p_NumVertices[freeint1]+12;
				fsize=removerange(bytelist,freeuint1,(p_NumZSector[freeint1]-freeuint1),fsize);
				memset(bytelist+p_NumVertices[freeint1]-3,0,15);
				memset(bytelist+p_NumVertices[freeint1]-4,5,1);
			}
		} else {
			freeint1=strtol(args[5], NULL, 10);
			freeuint1=p_NumVertices[freeint1]+12;
			fsize=removerange(bytelist,freeuint1,(p_NumZSector[freeint1]-freeuint1),fsize);
			memset(bytelist+p_NumVertices[freeint1]-3,0,15);
			memset(bytelist+p_NumVertices[freeint1]-4,5,1);
		}
	}
	if (!_strnicmp(args[4],"rectangles",10)){
		if (!_strnicmp(args[5],"all",3)) {
			for (freeint1=numRooms-1;freeint1>=0;freeint1--){
				memcpy(&freeushort1,bytelist+p_NumVertices[freeint1],2);
				freeuint1=p_NumVertices[freeint1]+4+(freeushort1*8);
				memcpy(&freeushort1,bytelist+freeuint1,2);
				fsize=removerange(bytelist,freeuint1,freeushort1*10,fsize);
				memset(bytelist+freeuint1,0,2);
				memcpy(&freeuint1,bytelist+p_NumVertices[freeint1]-4,4);
				freeuint1-=freeushort1*5;
				memcpy(bytelist+p_NumVertices[freeint1]-4,&freeuint1,4);
			}
		} else {
			freeint1=strtol(args[5], NULL, 10);
			memcpy(&freeushort1,bytelist+p_NumVertices[freeint1],2);
			freeuint1=p_NumVertices[freeint1]+4+(freeushort1*8);
			memcpy(&freeushort1,bytelist+freeuint1,2);
			fsize=removerange(bytelist,freeuint1,freeushort1*10,fsize);
			memset(bytelist+freeuint1,0,2);
			memcpy(&freeuint1,bytelist+p_NumVertices[freeint1]-4,4);
			freeuint1-=freeushort1*5;
			memcpy(bytelist+p_NumVertices[freeint1]-4,&freeuint1,4);
		}
	}
	if (!_strnicmp(args[4],"triangles",9)){
		if (!_strnicmp(args[5],"all",3)) {
			for (freeint1=numRooms-1;freeint1>=0;freeint1--){
				memcpy(&freeushort1,bytelist+p_NumVertices[freeint1],2);
				freeuint1=p_NumVertices[freeint1]+4+(freeushort1*8);
				memcpy(&freeushort1,bytelist+freeuint1,2);
				freeuint1+=2+(freeushort1*10);
				memcpy(&freeushort1,bytelist+freeuint1,2);
				fsize=removerange(bytelist,freeuint1,freeushort1*8,fsize);
				memset(bytelist+freeuint1,0,2);
				memcpy(&freeuint1,bytelist+p_NumVertices[freeint1]-4,4);
				freeuint1-=freeushort1*4;
				memcpy(bytelist+p_NumVertices[freeint1]-4,&freeuint1,4);
			}
		} else {
			freeint1=strtol(args[5], NULL, 10);
			memcpy(&freeushort1,bytelist+p_NumVertices[freeint1],2);
			freeuint1=p_NumVertices[freeint1]+4+(freeushort1*8);
			memcpy(&freeushort1,bytelist+freeuint1,2);
			freeuint1+=2+(freeushort1*10);
			memcpy(&freeushort1,bytelist+freeuint1,2);
			fsize=removerange(bytelist,freeuint1,freeushort1*8,fsize);
			memset(bytelist+freeuint1,0,2);
			memcpy(&freeuint1,bytelist+p_NumVertices[freeint1]-4,4);
			freeuint1-=freeushort1*4;
			memcpy(bytelist+p_NumVertices[freeint1]-4,&freeuint1,4);
		}
	}
	if (!_strnicmp(args[4],"viewports",9)){
		if (!_strnicmp(args[5],"all",3)) {
			for (freeint1=numRooms-1;freeint1>=0;freeint1--){
				memcpy(&freeushort1,bytelist+p_NumSprites[freeint1],2);
				freeuint1=p_NumSprites[freeint1]+2+(freeushort1*4);
				memcpy(&freeushort1,bytelist+freeuint1,2);
				fsize=removerange(bytelist,freeuint1,(freeushort1*32),fsize);
				memset(bytelist+freeuint1,0,2);
			}
		} else {
			freeint1=strtol(args[5], NULL, 10);
			memcpy(&freeushort1,bytelist+p_NumSprites[freeint1],2);
			freeuint1=p_NumSprites[freeint1]+2+(freeushort1*4);
			memcpy(&freeushort1,bytelist+freeuint1,2);
			fsize=removerange(bytelist,freeuint1,(freeushort1*32),fsize);
			memset(bytelist+freeuint1,0,2);
		}
	}
	if (!_strnicmp(args[4],"zones",5)){
		memcpy(&freeint1, bytelist+p_NumBoxes,4);
		freeuint1=p_NumBoxes+4+(freeint1*20);
		memcpy(&freeuint1, bytelist+freeuint1,4);
		fsize=removerange(bytelist,p_NumBoxes+8,(freeuint1*2)+(freeint1*32),fsize);
		memset(bytelist+p_NumBoxes,0,8);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_extract_sample(char *bytelist, char *args[], unsigned fsize){
	// This function extracts a sample from the level into a wave file. The syntax is "trmod [FILE] EXTRACT SAMPLE [Sample] [Output File]".
	unsigned freeuint1;
	unsigned freeuint2=0;
	unsigned freeuint3;
	unsigned short freeushort1;
	unsigned short freeushort2;
	memcpy(&freeushort1,bytelist+22,2);
	freeuint1=2086+(freeushort1*512);
	for (freeushort2=strtol(args[4],NULL,10);freeushort2>0;freeushort2--){
		memcpy(&freeushort1,bytelist+freeuint1,2);
		freeuint2+=(freeushort1*8);
		freeuint1+=2;
	}
	memcpy(&freeushort1,bytelist+freeuint1,2);
	freeuint3=freeushort1<<3;
	char *vagfile=malloc(freeuint3);
	memcpy(&freeushort2,bytelist+22,2);
	freeuint1=2600+(freeushort2*512);
	//memcpy(vagfile,bytelist+freeuint1+freeuint2,freeuint3);
	char *pcm=unvag(bytelist+freeuint1+freeuint2,freeuint3);
	memcpy(&freeuint1,pcm,4);
	memset(pcm,82,1);
	memset(pcm+1,73,1);
	memset(pcm+2,70,2);
	memcpy(pcm+4,&freeuint1,4);
	memset(pcm+8,87,1);
	memset(pcm+9,65,1);
	memset(pcm+10,86,1);
	memset(pcm+11,69,1);
	memset(pcm+12,102,1);
	memset(pcm+13,109,1);
	memset(pcm+14,116,1);
	memset(pcm+15,32,1);
	memset(pcm+16,16,1);
	memset(pcm+20,1,1);
	memset(pcm+22,1,1);
	memset(pcm+24,17,1);
	memset(pcm+25,43,1);
	memset(pcm+28,34,1);
	memset(pcm+29,86,1);
	memset(pcm+32,2,1);
	memset(pcm+34,16,1);
	memset(pcm+36,100,1);
	memset(pcm+37,97,1);
	memset(pcm+38,116,1);
	memset(pcm+39,97,1);
	freeuint1-=44;
	memcpy(pcm+40,&freeuint1,4);
	writeFile(args[5],pcm,freeuint1);
}
void tr1psx_replace_sample(char *bytelist, char *args[], unsigned fsize){
	/* 
	This function replaces a sample in the level with a sample from a wave file. The syntax is "trmod [FILE] REPLACE SAMPLE [Sample] [Input File]"
	Remember that the samples are stored in VAG format, which uses ADPCM encoding. Therefore, the format is lossy.
	*/
	int freeint1;
	unsigned freeuint1;
	unsigned freeuint2=0;
	unsigned freeuint3;
	unsigned short freeushort1;
	unsigned short freeushort2;
	unsigned short freeushort3;
	memcpy(&freeushort1,bytelist+22,2);
	freeuint1=2086+(freeushort1*512);
	for (freeushort2=strtol(args[4],NULL,10);freeushort2>0;freeushort2--){
		memcpy(&freeushort1,bytelist+freeuint1,2);
		freeuint2+=(freeushort1*8);
		freeuint1+=2;
	}
	memcpy(&freeushort1,bytelist+freeuint1,2);
	freeuint3=freeushort1<<3;
	char *vagfile=malloc(freeuint3);
	memcpy(&freeushort2,bytelist+22,2);
	freeuint1=2600+(freeushort2*512)+freeuint2;
	fsize=removerange(bytelist,freeuint1,freeuint3,fsize);
	if (filesize(args[5])!=0){
		char *vagdata=vag(args[5]);
		memcpy(&freeuint2,vagdata,4);
		freeint1=(freeuint3-freeuint2);
		bytelist=insertrange(bytelist,freeuint1,freeuint2,vagdata+4,fsize);
		fsize+=freeuint2;
		freeushort1=freeuint2>>3;
	} else {
		freeint1=freeuint3;
		freeushort1=0;
	}
	memcpy(&freeushort3,bytelist+22,2);
	memcpy(bytelist+2086+(freeushort3*512)+(strtol(args[4],NULL,10)*2),&freeushort1,2);
	memcpy(&freeuint3,bytelist+(2596+(freeushort2*512)),4);
	freeuint3-=freeint1;
	memcpy(bytelist+(2596+(freeushort2*512)),&freeuint3,4);
	freeuint3=0;
	memcpy(&freeuint3,bytelist+16,3);
	freeuint3-=freeint1;
	memcpy(bytelist+16,&freeuint3,3);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_get_geometry(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned short numRooms, unsigned fsize){
	/*
	This function writes the geometry of a room to a text file. The syntax is "trmod [FILE] GET GEOMETRY [Room] [Text File]"
	Vertex(Room,X,Z,Y,Lighting, Attributes, Lighting 2)
	Rectangle(Room,Vertex 1, Vertex 2, Vertex3, Vertex 4, Texture)
	Triangle(Room,Vertex 1, Vertex 2, Vertex3, Texture)
	Viewport(Room,Room2,[X,Z,Y,][X,Z,Y,][X,Z,Y,][X,Z,Y,][X,Z,Y,])
	                     Normal,Vertex1,Vertex2,Vertex3,Vertex4
	FloorHeight(Room,Column,Row,Height)
	CeilingHeight(Room,Column,Row,Height)
	Zone(Room,Column,Row,Zone)
	Roomlight(Room,Intensity1,Intensity2,Lightmode)
	Roompos(Room,X,Z,Y)
	Roomsize(Room,X,Z,Y)
	*/
	unsigned short freeushort1;
	unsigned short freeushort2;
	unsigned short freeushort3;
	short freeshort1;
	char freechar1;
	int freeint1;
	int freeint2;
	unsigned curpos;
	unsigned freeuint1;
	unsigned freeuint2;
	unsigned freeuint3;
	unsigned freeuint4;
	unsigned freeuint5;
	FILE *file = fopen(args[5],"w");
	if (!_strnicmp(args[4],"all",3)){
		for (freeushort1=0;freeushort1<numRooms;freeushort1++){
			curpos=p_NumVertices[freeushort1];
			memcpy(&freeushort2,bytelist+curpos,2);
			curpos+=4;
			while (freeushort2>0){
				memcpy(&freeushort3,bytelist+curpos,2);
				fprintf(file,"Vertex(%u,%u,",freeushort1,freeushort3);
				memcpy(&freeushort3,bytelist+curpos+4,2);
				fprintf(file,"%u,",freeushort3);
				memcpy(&freeshort1,bytelist+curpos+2,2);
				fprintf(file,"%i,",(roomY[freeushort1]-freeshort1));
				memcpy(&freeushort3,bytelist+curpos+6,2);
				freeushort3=8191-((freeushort3*8191)/255);
				fprintf(file,"%u,%u,0000)\n",freeushort3,freeushort3);
				curpos+=8;
				freeushort2--;
			}
			memcpy(&freeushort2,bytelist+curpos,2);
			curpos+=2;
			while (freeushort2>0){
				memcpy(&freeushort3,bytelist+curpos,2);
				fprintf(file,"Rectangle(%u,%u,",freeushort1,freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+2,2);
				fprintf(file,"%u,",freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+6,2);
				fprintf(file,"%u,",freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+4,2);
				fprintf(file,"%u,",freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+8,2);
				fprintf(file,"%u)\n",freeushort3);
				curpos+=10;
				freeushort2--;
			}
			memcpy(&freeushort2,bytelist+curpos,2);
			curpos+=2;
			while (freeushort2>0){
				memcpy(&freeushort3,bytelist+curpos,2);
				fprintf(file,"Triangle(%u,%u,",freeushort1,freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+2,2);
				fprintf(file,"%u,",freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+4,2);
				fprintf(file,"%u,",freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+6,2);
				fprintf(file,"%u)\n",freeushort3);
				curpos+=8;
				freeushort2--;
			}
			memcpy(&freeushort2,bytelist+curpos,2);
			curpos+=2+(freeushort2*4);
			memcpy(&freeushort2,bytelist+curpos,2);
			curpos+=2;
			while (freeushort2>0){
				memcpy(&freeshort1,bytelist+curpos,2);
				fprintf(file,"Viewport(%u,%i,[",freeushort1,freeshort1);
				memcpy(&freeshort1,bytelist+curpos+2,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+6,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+4,2);
				fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
				memcpy(&freeshort1,bytelist+curpos+8,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+12,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+10,2);
				fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
				memcpy(&freeshort1,bytelist+curpos+14,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+18,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+16,2);
				fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
				memcpy(&freeshort1,bytelist+curpos+20,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+24,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+22,2);
				fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
				memcpy(&freeshort1,bytelist+curpos+26,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+30,2);
				fprintf(file,"%i,",freeshort1);
				memcpy(&freeshort1,bytelist+curpos+28,2);
				fprintf(file,"%i])\n",roomY[freeushort1]-freeshort1);
				curpos+=32;
				freeushort2--;
			}
			memcpy(&freeushort2,bytelist+curpos,2);
			memcpy(&freeushort3,bytelist+curpos+2,2);
			curpos+=4;
			freeuint5=curpos;
			freeuint1=(freeushort2*freeushort3);
			for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
				freeuint3=freeuint2+1;
				freeuint4=1;
				memcpy(&freeushort2,bytelist+p_NumZSector[freeushort1],2);
				while (freeuint3>freeushort2){
					freeuint3-=freeushort2;
					freeuint4++;
				}
				memcpy(&freechar1,bytelist+curpos+5,1);
				if (freechar1!=-127) {
					fprintf(file,"FloorHeight(%i,%i,%i,%i)\n",freeushort1,freeuint4,freeuint3,(roomY[freeushort1]-(freechar1*256)));
				}else{
					fprintf(file,"FloorHeight(%i,%i,%i,Wall)\n",freeushort1,freeuint4,freeuint3);
				}
				curpos+=8;
			}
			curpos=freeuint5;
			memcpy(&freeushort2,bytelist+curpos-4,2);
			memcpy(&freeushort3,bytelist+curpos-2,2);
			for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
				freeuint3=freeuint2+1;
				freeuint4=1;
				memcpy(&freeushort2,bytelist+p_NumZSector[freeushort1],2);
				while (freeuint3>freeushort2){
					freeuint3-=freeushort2;
					freeuint4++;
				}
				memcpy(&freechar1,bytelist+curpos+7,1);
				if (freechar1!=-127) {
					fprintf(file,"CeilingHeight(%i,%i,%i,%i)\n",freeushort1,freeuint4,freeuint3,(roomY[freeushort1]-(freechar1*256)));
				}else{
					fprintf(file,"CeilingHeight(%i,%i,%i,Wall)\n",freeushort1,freeuint4,freeuint3);
				}
				curpos+=8;
			}
			curpos=freeuint5;
			memcpy(&freeushort2,bytelist+curpos-4,2);
			memcpy(&freeushort3,bytelist+curpos-2,2);
			for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
				freeuint3=freeuint2+1;
				freeuint4=1;
				memcpy(&freeushort2,bytelist+p_NumZSector[freeushort1],2);
				while (freeuint3>freeushort2){
					freeuint3-=freeushort2;
					freeuint4++;
				}
				memcpy(&freeshort1,bytelist+curpos+2,2);
				fprintf(file,"Zone(%i,%i,%i,%i)\n",freeushort1,freeuint4,freeuint3,freeshort1);
				curpos+=8;
			}
			memcpy(&freeushort2,bytelist+curpos,2);
			fprintf(file,"RoomLight(%u,%i,%i,0)\n",freeushort1,freeushort2,freeushort2);
			fprintf(file,"RoomPosition(%u,%i,%i,%i)\n",freeushort1,roomX[freeushort1],roomZ[freeushort1],roomY[freeushort1]);
			freeuint1 = p_NumZSector[freeushort1];
			memcpy(&freeushort3,bytelist+freeuint1,2);
			memcpy(&freeushort2,bytelist+freeuint1+2,2);
			freeuint1 = p_NumVertices[freeushort1]-8;
			memcpy(&freeint1,bytelist+freeuint1,4);
			memcpy(&freeint2,bytelist+freeuint1-4,4);
			fprintf(file,"RoomSize(%u,%u,%u,%i)\n",freeushort1,freeushort2,freeushort3,freeint2-freeint1);
		}
	}else{
		freeushort1=strtol(args[4], NULL, 10);
		curpos=p_NumVertices[freeushort1];
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=4;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos,2);
			fprintf(file,"Vertex(%u,%u,",freeushort1,freeushort3);
			memcpy(&freeushort3,bytelist+curpos+4,2);
			fprintf(file,"%u,",freeushort3);
			memcpy(&freeshort1,bytelist+curpos+2,2);
			fprintf(file,"%i,",(roomY[freeushort1]-freeshort1));
			memcpy(&freeushort3,bytelist+curpos+6,2);
			freeushort3=8191-((freeushort3*8191)/255);
			fprintf(file,"%u,%u,0000)\n",freeushort3,freeushort3);
			curpos+=8;
			freeushort2--;
		}
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos,2);
			fprintf(file,"Rectangle(%u,%u,",freeushort1,freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+2,2);
			fprintf(file,"%u,",freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+6,2);
			fprintf(file,"%u,",freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+4,2);
			fprintf(file,"%u,",freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+8,2);
			fprintf(file,"%u)\n",freeushort3);
			curpos+=10;
			freeushort2--;
		}
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos,2);
			fprintf(file,"Triangle(%u,%u,",freeushort1,freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+2,2);
			fprintf(file,"%u,",freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+4,2);
			fprintf(file,"%u,",freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+6,2);
			fprintf(file,"%u)\n",freeushort3);
			curpos+=8;
			freeushort2--;
		}
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2+(freeushort2*4);
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeshort1,bytelist+curpos,2);
			fprintf(file,"Viewport(%u,%i,[",freeushort1,freeshort1);
			memcpy(&freeshort1,bytelist+curpos+2,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+6,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+4,2);
			fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
			memcpy(&freeshort1,bytelist+curpos+8,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+12,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+10,2);
			fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
			memcpy(&freeshort1,bytelist+curpos+14,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+18,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+16,2);
			fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
			memcpy(&freeshort1,bytelist+curpos+20,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+24,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+22,2);
			fprintf(file,"%i][",roomY[freeushort1]-freeshort1);
			memcpy(&freeshort1,bytelist+curpos+26,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+30,2);
			fprintf(file,"%i,",freeshort1);
			memcpy(&freeshort1,bytelist+curpos+28,2);
			fprintf(file,"%i])\n",roomY[freeushort1]-freeshort1);
			curpos+=32;
			freeushort2--;
		}
		memcpy(&freeushort2,bytelist+curpos,2);
		memcpy(&freeushort3,bytelist+curpos+2,2);
		curpos+=4;
		freeuint5=curpos;
		freeuint1=(freeushort2*freeushort3);
		for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
			freeuint3=freeuint2+1;
			freeuint4=1;
			memcpy(&freeushort2,bytelist+p_NumZSector[freeushort1],2);
			while (freeuint3>freeushort2){
				freeuint3-=freeushort2;
				freeuint4++;
			}
			memcpy(&freechar1,bytelist+curpos+5,1);
			if (freechar1!=-127) {
				fprintf(file,"FloorHeight(%i,%i,%i,%i)\n",freeushort1,freeuint4,freeuint3,(roomY[freeushort1]-(freechar1*256)));
			}else{
				fprintf(file,"FloorHeight(%i,%i,%i,Wall)\n",freeushort1,freeuint4,freeuint3);
			}
			curpos+=8;
		}
		curpos=freeuint5;
		memcpy(&freeushort2,bytelist+curpos-4,2);
		memcpy(&freeushort3,bytelist+curpos-2,2);
		for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
			freeuint3=freeuint2+1;
			freeuint4=1;
			memcpy(&freeushort2,bytelist+p_NumZSector[freeushort1],2);
			while (freeuint3>freeushort2){
				freeuint3-=freeushort2;
				freeuint4++;
			}
			memcpy(&freechar1,bytelist+curpos+7,1);
			if (freechar1!=-127) {
				fprintf(file,"CeilingHeight(%i,%i,%i,%i)\n",freeushort1,freeuint4,freeuint3,(roomY[freeushort1]-(freechar1*256)));
			}else{
				fprintf(file,"CeilingHeight(%i,%i,%i,Wall)\n",freeushort1,freeuint4,freeuint3);
			}
			curpos+=8;
		}
		curpos=freeuint5;
		memcpy(&freeushort2,bytelist+curpos-4,2);
		memcpy(&freeushort3,bytelist+curpos-2,2);
		for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
			freeuint3=freeuint2+1;
			freeuint4=1;
			memcpy(&freeushort2,bytelist+p_NumZSector[freeushort1],2);
			while (freeuint3>freeushort2){
				freeuint3-=freeushort2;
				freeuint4++;
			}
			memcpy(&freeshort1,bytelist+curpos+2,2);
			fprintf(file,"Zone(%i,%i,%i,%i)\n",freeushort1,freeuint4,freeuint3,freeshort1);
			curpos+=8;
		}
		memcpy(&freeushort2,bytelist+curpos,2);
		fprintf(file,"RoomLight(%u,%i,%i,0)\n",freeushort1,freeushort2,freeushort2);
		fprintf(file,"RoomPosition(%u,%i,%i,%i)\n",freeushort1,roomX[freeushort1],roomZ[freeushort1],roomY[freeushort1]);
		freeuint1 = p_NumZSector[freeushort1];
		memcpy(&freeushort3,bytelist+freeuint1,2);
		memcpy(&freeushort2,bytelist+freeuint1+2,2);
		freeuint1 = p_NumVertices[freeushort1]-8;
		memcpy(&freeint1,bytelist+freeuint1,4);
		memcpy(&freeint2,bytelist+freeuint1-4,4);
		fprintf(file,"RoomSize(%u,%u,%u,%i)\n",freeushort1,freeushort2,freeushort3,freeint2-freeint1);
	}
	fclose(file);
}
void tr1psx_move_room(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumItems, unsigned fsize){
	// This function moves a room. The syntax is "trmod [FILE] MOVE ROOM [Room] [X] [Z] [Y] {RAW}"
	int freeint1;
	int freeint2;
	int freeint3;
	int freeint4;
	unsigned freeuint1;
	unsigned freeuint2;
	unsigned short freeushort1;
	unsigned short freeushort2;
	short freeshort1;
	char freechar1;
	memcpy(&freeint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-20,4);
	freeint1-=strtol(args[5], NULL, 10); // Difference X
	memcpy(&freeint2,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-16,4);
	freeint2-=strtol(args[6], NULL, 10); // Difference Z
	memcpy(&freeint3,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-12,4);
	freeint3-=strtol(args[7], NULL, 10); // Difference Y
	freeint4=strtol(args[5], NULL, 10);
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-20,&freeint4,4);
	freeint4=strtol(args[6], NULL, 10);
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-16,&freeint4,4);
	freeint4=strtol(args[7], NULL, 10);
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-12,&freeint4,4);
	memcpy(&freeint4,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-8,4);
	freeint4-=freeint3;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-8,&freeint4,4);
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	freeuint1=p_NumVertices[strtol(args[4], NULL, 10)]+4;
	while (freeushort1>0){ // Vertices
		memcpy(&freeshort1,bytelist+freeuint1+2,2);
		freeshort1-=freeint3;
		memcpy(bytelist+freeuint1+2,&freeshort1,2);
		freeuint1+=8;
		freeushort1--;
	}
	memcpy(&freeushort1, bytelist+freeuint1, 2);
	freeuint1+=2+(freeushort1*10);
	memcpy(&freeushort1, bytelist+freeuint1, 2);
	freeuint1+=2+(freeushort1*8);
	memcpy(&freeushort1, bytelist+freeuint1, 2);
	freeuint1+=2+(freeushort1*4);
	memcpy(&freeushort1, bytelist+freeuint1, 2);
	freeuint1+=2;
	freeuint2=freeuint1+(freeushort1*32);
	while (freeuint1<freeuint2){ // Viewports
		memcpy(&freeushort1,bytelist+freeuint1+10,2);
		freeushort1-=freeint3;
		memcpy(bytelist+freeuint1+10,&freeushort1,2);
		memcpy(&freeushort1,bytelist+freeuint1+16,2);
		freeushort1-=freeint3;
		memcpy(bytelist+freeuint1+16,&freeushort1,2);
		memcpy(&freeushort1,bytelist+freeuint1+22,2);
		freeushort1-=freeint3;
		memcpy(bytelist+freeuint1+22,&freeushort1,2);
		memcpy(&freeushort1,bytelist+freeuint1+28,2);
		freeushort1-=freeint3;
		memcpy(bytelist+freeuint1+28,&freeushort1,2);
		freeuint1+=32;
	}
	memcpy(&freeushort1, bytelist+freeuint1, 2);
	memcpy(&freeushort2, bytelist+freeuint1+2, 2);
	freeuint1+=4;
	freeuint2=freeuint1+(freeushort1*freeushort2*8);
	while (freeuint1<freeuint2){ // Floor/Ceilingheights
		memcpy(&freechar1,bytelist+freeuint1+5,1);
		if (freechar1!=-127){
			freechar1=(((freechar1*256)-freeint3)/256);
			memcpy(bytelist+freeuint1+5,&freechar1,1);
		}
		memcpy(&freechar1,bytelist+freeuint1+7,1);
		if (freechar1!=-127){
			freechar1=(((freechar1*256)-freeint3)/256);
			memcpy(bytelist+freeuint1+7,&freechar1,1);
		}
		freeuint1+=8;
	}
	freeuint1+=2;
	freechar1=1;
	if (argc>8){
		if (!_strnicmp(args[8],"raw",3)) freechar1=0;
	}
	if (freechar1==1){
		memcpy(&freeushort1, bytelist+freeuint1, 2);
		freeuint1+=2;
		freeuint2=freeuint1+(freeushort1*20);
		while (freeuint1<freeuint2){ // Lights
			memcpy(&freeint4,bytelist+freeuint1,4);
			freeint4-=freeint1;
			memcpy(bytelist+freeuint1,&freeint4,4);
			memcpy(&freeint4,bytelist+freeuint1+4,4);
			freeint4-=freeint3;
			memcpy(bytelist+freeuint1+4,&freeint4,4);
			memcpy(&freeint4,bytelist+freeuint1+8,4);
			freeint4-=freeint2;
			memcpy(bytelist+freeuint1+8,&freeint4,4);
			freeuint1+=20;
		}
		memcpy(&freeushort1, bytelist+freeuint1, 2);
		freeuint1+=2;
		freeuint2=freeuint1+(freeushort1*20);
		while (freeuint1<freeuint2){ // StaticMeshes
			memcpy(&freeint4,bytelist+freeuint1,4);
			freeint4-=freeint1;
			memcpy(bytelist+freeuint1,&freeint4,4);
			memcpy(&freeint4,bytelist+freeuint1+4,4);
			freeint4-=freeint3;
			memcpy(bytelist+freeuint1+4,&freeint4,4);
			memcpy(&freeint4,bytelist+freeuint1+8,4);
			freeint4-=freeint2;
			memcpy(bytelist+freeuint1+8,&freeint4,4);
			freeuint1+=20;
		}
		freeuint1=p_NumItems;
		memcpy(&freeint4, bytelist+freeuint1, 4);
		freeuint1+=4;
		freeuint2=freeuint1+(freeint4*22);
		while (freeuint1<freeuint2){ // Items
			memcpy(&freeshort1,bytelist+freeuint1+2,2);
			if (freeshort1==strtol(args[4], NULL, 10)){
				memcpy(&freeint4,bytelist+freeuint1+4,4);
				freeint4-=freeint1;
				memcpy(bytelist+freeuint1+4,&freeint4,4);
				memcpy(&freeint4,bytelist+freeuint1+8,4);
				freeint4-=freeint3;
				memcpy(bytelist+freeuint1+8,&freeint4,4);
				memcpy(&freeint4,bytelist+freeuint1+12,4);
				freeint4-=freeint2;
				memcpy(bytelist+freeuint1+12,&freeint4,4);
			}
			freeuint1+=22;
		}
	}
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_add_room(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned p_NumFloorData, unsigned fsize){
	// This function adds an empty room to a level. The syntax is "trmod [FILE] ADD ROOM"
	char *bytelist2 = realloc(bytelist,(fsize+46));
	bytelist=bytelist2;
	memmove(bytelist+p_NumFloorData+46,bytelist+p_NumFloorData,(fsize-p_NumFloorData));
	fsize+=46;
	memset(bytelist+p_NumFloorData,0,46);
	memset(bytelist+p_NumFloorData+16,5,1);
	memset(bytelist+p_NumFloorData+42,255,2);
	unsigned short freeushort1;
	memcpy(&freeushort1,bytelist+p_NumVertices[0]-22,2);
	freeushort1++;
	memcpy(bytelist+p_NumVertices[0]-22,&freeushort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_add_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize){
	// This function adds a vertex. "trmod [FILE] ADD VERTEX [Room] [X] [Z] [Y] [Lighting]"
	char *temp=malloc(8);
	unsigned freeuint1;
	unsigned short freeushort1 = strtol(args[5], NULL, 10);
	memcpy(temp,&freeushort1,2);
	short freeshort1 = (roomY[strtol(args[4], NULL, 10)]-strtol(args[7], NULL, 10));
	memcpy(temp+2,&freeshort1,2);
	freeushort1 = strtol(args[6], NULL, 10);
	memcpy(temp+4,&freeushort1,2);
	freeushort1 = strtol(args[8], NULL, 10);
	freeushort1=((8192-freeushort1)*255)/8191;
	memcpy(temp+6,&freeushort1,2);
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	bytelist=insertrange(bytelist,p_NumVertices[strtol(args[4], NULL, 10)]+4+(freeushort1*8),8,temp,fsize);
	fsize+=8;
	freeushort1++;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)],&freeushort1,2);
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]+2,&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1+=4;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_replace_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize){
	// This function replaces a vertex. "trmod [FILE] REPLACE VERTEX [Room] [Vertex] [X] [Z] [Y] [Lighting]"
	unsigned freeuint1=p_NumVertices[strtol(args[4], NULL, 10)]-4+(strtol(args[5], NULL, 10)*8);
	unsigned short freeushort1 = strtol(args[6], NULL, 10);
	memcpy(bytelist+freeuint1,&freeushort1,2);
	short freeshort1 = (roomY[strtol(args[4], NULL, 10)]-strtol(args[8], NULL, 10));
	memcpy(bytelist+freeuint1+2,&freeshort1,2);
	freeushort1 = strtol(args[7], NULL, 10);
	memcpy(bytelist+freeuint1+4,&freeushort1,2);
	freeushort1 = strtol(args[9], NULL, 10);
	freeushort1=((8192-freeushort1)*255)/8191;
	memcpy(bytelist+freeuint1+6,&freeushort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_remove_vertex(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function removes a vertex. "trmod [FILE] REMOVE VERTEX [Room] [Vertex] (RAW)"
	unsigned short freeushort1;
	unsigned freeuint1=p_NumVertices[strtol(args[4], NULL, 10)]-4+(strtol(args[5], NULL, 10)*8);
	fsize=removerange(bytelist,freeuint1,8,fsize);
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	freeushort1--;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)],&freeushort1,2);
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]+2,&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1-=4;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	char freechar1=1;
	if (argc>6){
		if (!_strnicmp(args[6],"raw",3)) freechar1=0;
	}
	if (freechar1==1){
		unsigned short freeushort2=strtol(args[5], NULL, 10)-1;
		memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
		unsigned curpos=(p_NumVertices[strtol(args[4], NULL, 10)]+4+(freeushort1*8));
		memcpy(&freeushort1,bytelist+curpos,2);
		curpos+=2;
		freeuint1=curpos+(freeushort1*10);
		while (curpos<freeuint1){
			memcpy(&freeushort1,bytelist+curpos,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos,&freeushort1,2);
			}
			memcpy(&freeushort1,bytelist+curpos+2,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos+2,&freeushort1,2);
			}
			memcpy(&freeushort1,bytelist+curpos+4,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos+4,&freeushort1,2);
			}
			memcpy(&freeushort1,bytelist+curpos+6,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos+6,&freeushort1,2);
			}
			curpos+=10;
		}
		memcpy(&freeushort1,bytelist+curpos,2);
		curpos+=2;
		freeuint1=curpos+(freeushort1*8);
		while (curpos<freeuint1){
			memcpy(&freeushort1,bytelist+curpos,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos,&freeushort1,2);
			}
			memcpy(&freeushort1,bytelist+curpos+2,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos+2,&freeushort1,2);
			}
			memcpy(&freeushort1,bytelist+curpos+4,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos+4,&freeushort1,2);
			}
			curpos+=8;
		}
		memcpy(&freeushort1,bytelist+curpos,2);
		curpos+=2;
		freeuint1=curpos+(freeushort1*4);
		while (curpos<freeuint1){
			memcpy(&freeushort1,bytelist+curpos,2);
			if (freeushort1>freeushort2){
				freeushort1--;
				memcpy(bytelist+curpos,&freeushort1,2);
			}
			curpos+=4;
		}
	}
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_add_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function adds a rectangle. "trmod [FILE] ADD RECTANGLE [Room] [Vertex 1] [Vertex 2] [Vertex 3] [Vertex 4] [Texture]"
	char *temp=malloc(10);
	unsigned freeuint1;
	unsigned short freeushort1 = strtol(args[5], NULL, 10)-1;
	memcpy(temp,&freeushort1,2);
	freeushort1 = strtol(args[6], NULL, 10)-1;
	memcpy(temp+2,&freeushort1,2);
	freeushort1 = strtol(args[7], NULL, 10)-1;
	memcpy(temp+6,&freeushort1,2);
	freeushort1 = strtol(args[8], NULL, 10)-1;
	memcpy(temp+4,&freeushort1,2);
	freeushort1 = strtol(args[9], NULL, 10);
	memcpy(temp+8,&freeushort1,2);
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	curpos+=4+(freeushort1*8);
	memcpy(&freeushort1,bytelist+curpos,2);
	bytelist=insertrange(bytelist,curpos+2+(freeushort1*10),10,temp,fsize);
	fsize+=10;
	freeushort1++;
	memcpy(bytelist+curpos,&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1+=5;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_replace_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function replaces a rectangle. "trmod [FILE] REPLACE RECTANGLE [Room] [Rectangle] [Vertex 1] [Vertex 2] [Vertex 3] [Vertex 4] [Texture]"
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	curpos+=(freeushort1*8)-4+(strtol(args[5], NULL, 10)*10);
	freeushort1 = strtol(args[6], NULL, 10)-1;
	memcpy(bytelist+curpos,&freeushort1,2);
	freeushort1 = strtol(args[7], NULL, 10)-1;
	memcpy(bytelist+curpos+2,&freeushort1,2);
	freeushort1 = strtol(args[8], NULL, 10)-1;
	memcpy(bytelist+curpos+6,&freeushort1,2);
	freeushort1 = strtol(args[9], NULL, 10)-1;
	memcpy(bytelist+curpos+4,&freeushort1,2);
	freeushort1 = strtol(args[10], NULL, 10);
	memcpy(bytelist+curpos+8,&freeushort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_remove_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function removes a rectangle. "trmod [FILE] REMOVE RECTANGLE [Room] [Rectangle]"
	unsigned freeuint1;
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=(freeushort1*8)-4+(strtol(args[5], NULL, 10)*10);
	fsize=removerange(bytelist,curpos,10,fsize);
	curpos=p_NumVertices[strtol(args[4], NULL, 10)]+4+(freeushort1*8);
	memcpy(&freeushort1,bytelist+curpos,2);
	freeushort1--;
	memcpy(bytelist+curpos,&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1-=5;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_add_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function adds a triangle. "trmod [FILE] ADD TRIANGLE [Room] [Vertex 1] [Vertex 2] [Vertex 3] [Texture]"
	char *temp=malloc(8);
	unsigned freeuint1;
	unsigned short freeushort1 = strtol(args[5], NULL, 10)-1;
	memcpy(temp,&freeushort1,2);
	freeushort1 = strtol(args[6], NULL, 10)-1;
	memcpy(temp+2,&freeushort1,2);
	freeushort1 = strtol(args[7], NULL, 10)-1;
	memcpy(temp+4,&freeushort1,2);
	freeushort1 = strtol(args[8], NULL, 10);
	memcpy(temp+6,&freeushort1,2);
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	curpos+=4+(freeushort1*8);
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=2+(freeushort1*10);
	memcpy(&freeushort1,bytelist+curpos,2);
	bytelist=insertrange(bytelist,curpos+2+(freeushort1*8),8,temp,fsize);
	fsize+=8;
	freeushort1++;
	memcpy(bytelist+curpos,&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1+=4;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_replace_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function replaces a triangle. "trmod [FILE] REPLACE TRIANGLE [Room] [Triangle] [Vertex 1] [Vertex 2] [Vertex 3] [Texture]"
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=4+(freeushort1*8);
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=2+(freeushort1*10);
	curpos+=-6+(strtol(args[5], NULL, 10)*8);
	freeushort1 = strtol(args[6], NULL, 10)-1;
	memcpy(bytelist+curpos,&freeushort1,2);
	freeushort1 = strtol(args[7], NULL, 10)-1;
	memcpy(bytelist+curpos+2,&freeushort1,2);
	freeushort1 = strtol(args[8], NULL, 10)-1;
	memcpy(bytelist+curpos+4,&freeushort1,2);
	freeushort1 = strtol(args[9], NULL, 10);
	memcpy(bytelist+curpos+6,&freeushort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_remove_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function removes a triangle. "trmod [FILE] REMOVE TRIANGLE [Room] [Triangle]"
	unsigned freeuint1;
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=4+(freeushort1*8);
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=2+(freeushort1*10);
	freeuint1=curpos-6+(strtol(args[5], NULL, 10)*8);
	fsize=removerange(bytelist,freeuint1,8,fsize);
	memcpy(&freeushort1,bytelist+curpos,2);
	freeushort1--;
	memcpy(bytelist+curpos,&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1-=4;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr1psx_get_offset(char *bytelist, char *args[], unsigned argc, unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumItems, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned p_NumSoundSources, unsigned fsize){
	// This function returns the offset of a given position in a level file. The result is in Hexadecimals.
	unsigned curpos;
	unsigned freeuint1;
	unsigned freeuint2;
	unsigned short freeushort1;
	if (!_strnicmp(args[4],"numrooms",8)) printf("%X\n",(p_NumVertices[0]-22));
	if (!_strnicmp(args[4],"room",4)) printf("%X\n",(p_NumVertices[strtol(args[5],NULL,10)]-20));
	if (!_strnicmp(args[4],"numvertices",11)) printf("%X\n",(p_NumVertices[strtol(args[5],NULL,10)]));
	if (!_strnicmp(args[4],"numrectangles",13)||!_strnicmp(args[4],"numtriangles",12)){
		curpos=p_NumVertices[strtol(args[5],NULL,10)];
		memcpy(&freeushort1, bytelist+curpos, 2);
		curpos+=4+(freeushort1*8);
		if (!_strnicmp(args[4],"numrectangles",13)) printf("%X\n",curpos);
		memcpy(&freeushort1, bytelist+curpos, 2);
		curpos+=2+(freeushort1*10);
		if (!_strnicmp(args[4],"numtriangles",12)) printf("%X\n",curpos);
	}
	if (!_strnicmp(args[4],"numsprites",10)&&argc>5) printf("%X\n",(p_NumSprites[strtol(args[5],NULL,10)]));
	if (!_strnicmp(args[4],"numdoors",8)){
		curpos=p_NumSprites[strtol(args[5],NULL,10)];
		memcpy(&freeushort1, bytelist+curpos, 2);
		curpos+=2+(freeushort1*4);
		printf("%X\n",curpos);
	}
	if (!_strnicmp(args[4],"numzsector",10)) printf("%X\n",(p_NumZSector[strtol(args[5],NULL,10)]));
	if (!_strnicmp(args[4],"numlights",9)) printf("%X\n",(p_NumLights[strtol(args[5],NULL,10)]));
	if (!_strnicmp(args[4],"numstaticmeshes",15)&&argc>5) printf("%X\n",(p_NumStaticMeshes[strtol(args[5],NULL,10)]));
	if (!_strnicmp(args[4],"alternateroom",13)) printf("%X\n",(p_AlternateRoom[strtol(args[5],NULL,10)]));
	if (!_strnicmp(args[4],"numfloordata",12)) printf("%X\n",p_NumFloorData);
	if (!_strnicmp(args[4],"nummeshdata",11)||!_strnicmp(args[4],"nummeshpointers",15)||!_strnicmp(args[4],"numanimations",13)||!_strnicmp(args[4],"numstatechanges",15)||!_strnicmp(args[4],"numanimdispatches",17)||!_strnicmp(args[4],"numanimcommands",15)||!_strnicmp(args[4],"nummeshtrees",12)||!_strnicmp(args[4],"numframes",9)||!_strnicmp(args[4],"nummovables",11)||!_strnicmp(args[4],"numstaticmeshes",15)||!_strnicmp(args[4],"numobjecttextures",17)||!_strnicmp(args[4],"numspritetextures",17)){
		curpos=p_NumFloorData;
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*2);
		if (!_strnicmp(args[4],"nummeshdata",11)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*2);
		if (!_strnicmp(args[4],"nummeshpointers",15)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*4);
		if (!_strnicmp(args[4],"numanimations",13)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*32);
		if (!_strnicmp(args[4],"numstatechanges",15)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*6);
		if (!_strnicmp(args[4],"numanimdispatches",17)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*8);
		if (!_strnicmp(args[4],"numanimcommands",15)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*2);
		if (!_strnicmp(args[4],"nummeshtrees",12)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*4);
		if (!_strnicmp(args[4],"numframes",9)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*2);
		if (!_strnicmp(args[4],"nummovables",11)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*20);
		if (!_strnicmp(args[4],"numstaticmeshes",15)&&argc==5) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*32);
		if (!_strnicmp(args[4],"numobjecttextures",17)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*16);
		if (!_strnicmp(args[4],"numspritetextures",17)) printf("%X\n",curpos);
	}
	if (!_strnicmp(args[4],"numspritesequences",18)) printf("%X\n",p_NumSpriteSequences);
	if (!_strnicmp(args[4],"numcameras",10)) printf("%X\n",p_NumCameras);
	if (!_strnicmp(args[4],"numsoundsources",15)) printf("%X\n",p_NumSoundSources);
	if (!_strnicmp(args[4],"numboxes",8)) printf("%X\n",p_NumBoxes);
	if (!_strnicmp(args[4],"numoverlaps",11)) printf("%X\n",p_NumOverlaps);
	if (!_strnicmp(args[4],"zones",5)||!_strnicmp(args[4],"numanimatedtextures",19)){
		memcpy(&freeuint1,bytelist+p_NumBoxes,4);
		memcpy(&freeuint2,bytelist+p_NumOverlaps,4);
		curpos=p_NumOverlaps+4+(freeuint2*2);
		if (!_strnicmp(args[4],"zones",5)) printf("%X\n",curpos);
		curpos+=(freeuint1*12);
		if (!_strnicmp(args[4],"numanimatedtextures",19)) printf("%X\n",curpos);
	}
	if (!_strnicmp(args[4],"numitems",8)) printf("%X\n",p_NumItems);
	if (!_strnicmp(args[4],"numsounddetails",15)){
		curpos=p_NumItems;
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=516+(freeuint1*22);
		printf("%X\n",curpos);
	}
}
