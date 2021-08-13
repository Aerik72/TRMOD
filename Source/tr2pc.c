// This file handles Tomb Raider 2 PC (tr2) files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "tr1pc.h"
#include "tr2pc.h"
void tr2pc_main(int argc, char *args[], char *bytelist, unsigned fsize){
	unsigned curpos = 0; // Current Position in the file navigation
	unsigned p_NumFloorData; // Offset of NumFloorData
	unsigned p_NumSpriteSequences; // Offset of NumSpriteSequences
	unsigned p_NumCameras; // Offset of NumCameras
	unsigned p_NumSoundSources; // Offset of NumSoundSources
	unsigned p_NumBoxes; // Offset of NumBoxes
	unsigned p_NumOverlaps; // Offset of NumOverlaps
	unsigned p_NumItems; // Offset of NumItems
	unsigned p_NumDemoData; // Offset of NumDemoData
	unsigned freeuint1;
	unsigned freeUInt2;
	unsigned short freeshort1;
	unsigned short freeshort2;
	unsigned short freeshort3;
	unsigned short freeshort4;
	BYTE* palette8 = malloc(768 * sizeof(BYTE));
	BYTE* palette16 = malloc(768 * sizeof(BYTE));
	unsigned short numTexTiles;
	unsigned* p_TexTiles8;
	unsigned* p_TexTiles16;

	// <FILE NAVIGATION>
	curpos += 4; // Version already read (4 bytes)

	// 8-bit palette
	// tr_colour Palette[256]; // 8-bit palette (768 bytes)
	// This consists of 256[tr_colour] structs, one for each palette entry.
	// However, the individual colour values range from 0 to 63; they must be multiplied by 4 to get the correct values.
	// This is used for all 8-bit colour, such as 8-bit textures.
	for (int i = 0; i < 256; i++)
	{
		memcpy(&palette8[i * 3 + 0], bytelist + curpos + 2, 1); // r
		memcpy(&palette8[i * 3 + 1], bytelist + curpos + 1, 1); // g
		memcpy(&palette8[i * 3 + 2], bytelist + curpos + 0, 1); // b
		palette8[i * 3 + 0] *= 4;
		palette8[i * 3 + 1] *= 4;
		palette8[i * 3 + 2] *= 4;
		curpos += 3; // tr_colour is 3 bytes wide
	}

	// 16-bit palette
	// NOTE: There is no reason for us to store the unused byte, so we'll discard it for a smaller memory footprint.
	// tr_colour4 Palette16[256]; // 16-bit palette (1024 bytes)
	// The 16-bit palette is used for identifying the colors of solid polygons, *not* textile colors.
	// struct tr_colour4  // 4 bytes
	// {
	//		uint8_t Red;
	//		uint8_t Green;
	//		uint8_t Blue;
	//		uint8_t Unused;
	// };
	for (int i = 0; i < 256; i++)
	{
		memcpy(&palette16[i * 3 + 0], bytelist + curpos + 3, 1); // r
		memcpy(&palette16[i * 3 + 1], bytelist + curpos + 2, 1); // g
		memcpy(&palette16[i * 3 + 2], bytelist + curpos + 1, 1); // b
		palette16[i * 3 + 0] *= 4;
		palette16[i * 3 + 1] *= 4;
		palette16[i * 3 + 2] *= 4;
		curpos += 4; // tr_colour4 is 4 bytes wide
	}

	// Texture tiles
	// uint32_t NumTextiles; // number of texture tiles (4 bytes)
	memcpy(&freeuint1, bytelist + curpos, 4); // Number of Texture Tiles
	numTexTiles = freeuint1;
	curpos += 4;

	// tr2_textile8 Textile8[NumTextiles]; // 8-bit (palettized) textiles (NumTextiles * 65536 bytes)
	p_TexTiles8 = malloc(numTexTiles * sizeof(unsigned)); // Offsets of 8-bit TexTiles
	for (int i = 0; i < numTexTiles; i++)
	{
		p_TexTiles8[i] = curpos;
		curpos += (1 << 16); // Each texture is 8 bits in a 256 x 256 grid a.k.a. 2^16
	}

	// tr2_textile16 Textile16[NumTextiles]; // 16-bit (ARGB) textiles (NumTextiles * 131072 bytes)
	// The 16-bit textile array, which contains[tr_textile16] structures, specifies colours using 16 - bit ARGB,
	// where the highest bit (0x8000) is a crude alpha channel (really just a simple transparency: 0==transparent, 1==opaque).
	// The next 5 bits(0x7C00) specify the red channel, the next 5 bits(0x03E0) specify the green channel,
	// and the last 5 bits(0x001F) specify the blue channel, each on a scale from 0..31.
	p_TexTiles16 = malloc(numTexTiles * sizeof(unsigned)); // Offsets of 16-bit TexTiles
	for (int i = 0; i < numTexTiles; i++)
	{
		p_TexTiles16[i] = curpos;
		curpos += (2 << 16); // Each texture is 16 bits in a 256 x 256 grid a.k.a. 2 * (2^16)
	}

	memcpy(&freeuint1, bytelist + 1796, 4);
	curpos=1804+(freeuint1*196608); // [NumRooms]
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
		curpos+=2+(freeshort3*12); // [NumRectangles]
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
		curpos+=10+(freeshort3*freeshort4*8); // [NumLights]
		p_NumLights[freeshort2]=curpos;
		memcpy(&freeshort3, bytelist+curpos, 2);
		curpos+=2+(freeshort3*24); // [NumStaticMeshes]
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
	curpos+=4+(freeuint1*18); // [NumStaticMeshes]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<5); // [NumObjectTextures]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1*20); // [NumSpriteTextures]
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
	curpos+=4+(freeuint1<<3); // [NumOverlaps]
	p_NumOverlaps = curpos;
	memcpy(&freeUInt2, bytelist+curpos, 4);
	curpos+=4+(freeUInt2*2)+(freeuint1*20); // [NumAnimatedTextures]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<1); // [NumItems]
	p_NumItems=curpos;
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=8196+(freeuint1*24); // [NumCinematicFrames]
	memcpy(&freeshort3, bytelist+curpos, 2);
	curpos+=2+(freeshort3<<4); // [NumDemoData]
	p_NumDemoData=curpos;
	/*
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=742+freeuint1; // [NumSoundDetails]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<3); // [NumSampleIndices]
	memcpy(&freeuint1, bytelist+curpos, 4);
	curpos+=4+(freeuint1<<2); // [EOF]
	*/
	// </FILE NAVIGATION>
	if (!_strnicmp(args[2],"list",4)||!_strnicmp(args[2],"clist",5)) tr2pc_list(bytelist, args, roomX, roomY, roomZ, p_NumVertices, p_NumSprites, p_NumLights, p_NumZSector, p_NumStaticMeshes, p_AlternateRoom, p_NumFloorData, p_NumSpriteSequences, p_NumCameras, p_NumBoxes, p_NumSoundSources, p_NumItems, numRooms, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"item",4)) tr2pc_add_item(bytelist, args, roomX, roomY, roomZ, p_NumItems, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"item",4)) tr2pc_replace_item(bytelist, argc, args, roomX, roomY, roomZ, p_NumItems, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"item",4)) tr2pc_remove_item(bytelist, argc, args, p_NumZSector, p_NumFloorData, p_NumItems, numRooms, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"staticmesh",10)) tr2pc_add_staticmesh(bytelist, args, roomX, roomY, roomZ, p_NumStaticMeshes, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"staticmesh",10)) tr2pc_replace_staticmesh(bytelist, argc, args, roomX, roomY, roomZ, p_NumStaticMeshes, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"staticmesh",10)) tr2pc_remove_staticmesh(bytelist, args, p_NumStaticMeshes, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"sprite",6)) tr2pc_add_sprite(bytelist, args, roomY, p_NumVertices, p_NumSprites, p_NumSpriteSequences, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"sprite",6)) tr2pc_replace_sprite(bytelist, args, argc, roomY, p_NumVertices, p_NumSprites, p_NumSpriteSequences, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"sprite",6)) tr1pc_remove_sprite(bytelist, args, p_NumVertices, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"soundsource",11)) tr1pc_add_soundsource(bytelist, args, p_NumSoundSources, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"soundsource",11)) tr1pc_replace_soundsource(bytelist, argc, args, p_NumSoundSources, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"soundsource",11)) tr1pc_remove_soundsource(bytelist, args, p_NumSoundSources, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"light",5)) tr2pc_add_light(bytelist, args, roomX, roomY, roomZ, p_NumLights, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"light",5)) tr2pc_replace_light(bytelist, args, roomX, roomY, roomZ, p_NumLights, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"light",5)) tr2pc_remove_light(bytelist, args, p_NumLights, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"floordata",9)) tr2pc_replace_floordata(bytelist, args, argc, roomX, roomY, roomZ, p_NumZSector, p_NumFloorData, p_NumCameras, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"floordata",9)) tr1pc_remove_floordata(bytelist, args, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"all",3)) tr2pc_remove_all(bytelist, argc, args, p_NumVertices, p_NumSprites, p_NumLights, p_NumZSector, p_NumStaticMeshes, p_NumFloorData, p_NumCameras, p_NumSoundSources, p_NumItems, p_NumBoxes, numRooms, fsize);
	if (!_strnicmp(args[2],"alternate",9)&&!_strnicmp(args[3],"room",4)) tr1pc_alternate_room(bytelist, args, p_AlternateRoom, fsize);
	if (!_strnicmp(args[2],"roomlight",9)) tr2pc_roomlight(bytelist, args, p_NumLights, numRooms, fsize);
	if (!_strnicmp(args[2],"water",5)) tr1pc_water(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"nowater",7)) tr1pc_nowater(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"sky",3)) tr2pc_sky(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"nosky",5)) tr2pc_nosky(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"wind",4)) tr2pc_wind(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"nowind",6)) tr2pc_nowind(bytelist, args, p_AlternateRoom, numRooms, fsize);
	if (!_strnicmp(args[2],"extract",7)&&!_strnicmp(args[3],"demo",4)) tr1pc_extract_demo(bytelist, args, p_NumDemoData);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"demo",4)) tr1pc_replace_demo(bytelist, args, p_NumDemoData, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"geometry",8)) tr2pc_get_geometry(bytelist, args, roomX, roomY, roomZ, p_NumVertices, p_NumLights, p_NumZSector, numRooms, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"roompos",7)) printf("X=%i Z=%i Y=%i\n",roomX[strtol(args[4], NULL, 10)],roomZ[strtol(args[4], NULL, 10)],roomY[strtol(args[4], NULL, 10)]); // This returns the position of a room. The syntax is "trmod [FILE] GET ROOMPOS [Room]"
	if (!_strnicmp(args[2],"move",4)&&!_strnicmp(args[3],"room",4)) tr2pc_move_room(bytelist, argc, args, p_NumVertices, p_NumZSector, p_NumStaticMeshes, p_NumItems, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"roomsize",8)) tr1pc_get_roomsize(bytelist, args, p_NumVertices, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"resize",6)&&!_strnicmp(args[3],"room",4)) tr1pc_resize_room(bytelist, args, p_NumVertices, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"room",4)) tr2pc_add_room(bytelist, args, p_NumVertices, p_NumFloorData, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"floorheight",11)) tr1pc_get_floorheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"ceilingheight",13)) tr1pc_get_ceilingheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"set",3)&&!_strnicmp(args[3],"floorheight",11)) tr1pc_set_floorheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"set",3)&&!_strnicmp(args[3],"ceilingheight",13)) tr1pc_set_ceilingheight(bytelist, args, roomY, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"vertex",6)) tr2pc_add_vertex(bytelist, args, p_NumVertices, roomY, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"vertex",6)) tr2pc_replace_vertex(bytelist, args, p_NumVertices, roomY, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"vertex",6)) tr2pc_remove_vertex(bytelist, argc, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"rectangle",9)) tr2pc_add_rectangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"rectangle",9)) tr2pc_replace_rectangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"rectangle",9)) tr2pc_remove_rectangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"triangle",8)) tr2pc_add_triangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"triangle",8)) tr2pc_replace_triangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"triangle",8)) tr2pc_remove_triangle(bytelist, args, p_NumVertices, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"viewport",8)) tr1pc_add_viewport(bytelist, args, roomY, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"viewport",8)) tr1pc_replace_viewport(bytelist, args, roomY, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"remove",6)&&!_strnicmp(args[3],"viewport",8)) tr1pc_remove_viewport(bytelist, args, p_NumSprites, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"zones",5)) tr2pc_get_zones(bytelist, args, p_NumBoxes, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"zone",4)) tr1pc_zone(bytelist, args, p_NumZSector, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"zone",4)) tr2pc_add_zone(bytelist, args, p_NumBoxes, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"replace",7)&&!_strnicmp(args[3],"zone",4)) tr2pc_replace_zone(bytelist, args, p_NumBoxes, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"add",3)&&!_strnicmp(args[3],"overlap",7)) tr1pc_add_overlap(bytelist, args, argc, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"overwrite",7)&&!_strnicmp(args[3],"overlap",7)) tr1pc_overwrite_overlap(bytelist, args, argc, p_NumOverlaps, fsize);
	if (!_strnicmp(args[2],"get",3)&&!_strnicmp(args[3],"offset",6)) tr2pc_get_offset(bytelist, args, argc, p_NumVertices, p_NumSprites, p_NumLights, p_NumZSector, p_NumStaticMeshes, p_AlternateRoom, p_NumFloorData, p_NumItems, p_NumSpriteSequences, p_NumCameras, p_NumDemoData, p_NumBoxes, p_NumOverlaps, p_NumSoundSources, fsize);

	if (!_strnicmp(args[2], "extract", 7))
	{
		if (!strnicmp(args[3], "textile", 9))
		{
			tr2pc_extract_textile(bytelist, args, numTexTiles, p_TexTiles16, !strnicmp(args[4], "all", 3) ? -1 : atoi(args[4]));
		}
		else if (!strnicmp(args[3], "textile8", 7))
		{
			printf("WARNING: 8-bit textures are a legacy feature, and will probably not render on a modern PC.\n");
			tr2pc_extract_textile8(bytelist, args, numTexTiles, p_TexTiles8, palette8, !strnicmp(args[4], "all", 3) ? -1 : atoi(args[4]));
		}
	}

	if (!_strnicmp(args[2], "replace", 7))
	{
		if (!strnicmp(args[3], "textile", 9))
		{
			tr2pc_replace_textile(bytelist, args, numTexTiles, p_TexTiles16, fsize);
		}
		else if (!strnicmp(args[3], "textile8", 7))
		{
			printf("WARNING: 8-bit textures are a legacy feature, and will probably not render on a modern PC.\n");
			tr2pc_replace_textile8(bytelist, args, numTexTiles, p_TexTiles8, palette8, fsize);
		}
	}

	free(palette8);
	free(palette16);
	free(p_TexTiles8);
	free(p_TexTiles16);
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
void tr2pc_list(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumBoxes, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned short numRooms, unsigned fsize){
	/*
	This function produces a list of all Items, Static Meshes, Sprites, Soundsources, Alternate rooms and FloorData
	The function LIST produces a clear and easy to read format, and CLIST produces the list in the form of TRMOD commands
	The syntax is "trmod [FILE] LIST/CLIST [OUTPUT FILE]"
	=================================================================================
		The List format is as follows:
		____________________________________________________________________________
		Item(ObjectID,Room,X,Z,Y,Angle,Intensity1,Intensity2,Flags)
		Static Mesh(ObjectID,Room,X,Z,Y,Angle,Intensity1,Intensity2)
		Sprite(ObjectID,Room,X,Z,Y,Lighting1,Lighting2,Attributes)
		Light(Room,X,Z,Y,Intensity1,Intensity2,Fade1,Fade2)
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
			Climbable Walls(+X,-X,+Z,-Z)
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
			TRIGGER(Trigger_Type:Timer:Only_Once:Mask:Trigger_Action;Trigger_Action;Trigger_Action;Trigger_Action)
			KILL
			CLIMBWALLS(+X,-X,+Z,-Z)
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
	FILE *file = fopen(args[3],"w");
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
		fprintf(file,"%i%c",freeshort1,freechar1);
		memcpy(&freeshort1,bytelist+curpos+20,2);
		fprintf(file,"%i%c",freeshort1,freechar1);
		memcpy(&freeushort1,bytelist+curpos+22,2);
		fprintf(file,"%04X",freeushort1);
		if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
		if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
		curpos+=24;
		freeuint1--;
	}
	// </ITEMS>
	// <STATIC MESHES>
	for (freeushort1=0;freeushort1<numRooms;freeushort1++){
		curpos=p_NumStaticMeshes[freeushort1];
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos+18,2);
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
			fprintf(file,"%i%c",freeshort1,freechar1);
			memcpy(&freeshort1,bytelist+curpos+16,2);
			fprintf(file,"%i",freeshort1);
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
			freeuint1 = p_NumVertices[freeushort1] + 2 + (12 * freeushort3);
			memcpy(&freeushort3,bytelist+freeuint1,2);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeushort3,bytelist+freeuint1+4,2);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeshort1,bytelist+freeuint1+2,2);
			fprintf(file,"%i%c",(roomY[freeushort1]-freeshort1),freechar1);
			memcpy(&freeushort3,bytelist+freeuint1+6,2);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeushort3,bytelist+freeuint1+10,2);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeushort3,bytelist+freeuint1+8,2);
			fprintf(file,"%04X",freeushort3);
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
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeushort3,bytelist+curpos+14,2);
			fprintf(file,"%u%c",freeushort3,freechar1);
			memcpy(&freeuint1,bytelist+curpos+16,4);
			fprintf(file,"%i%c",freeuint1,freechar1);
			memcpy(&freeuint1,bytelist+curpos+20,4);
			fprintf(file,"%i",freeuint1);
			if (!_strnicmp(args[2],"list",4)) fprintf(file,")\n");
			if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\n");
			curpos+=24;
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
						if (freeushort3==6){
							freeushort5=freeushort2 & 0x7F00;
							freeushort5 >>= 8;
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"    Climbable Walls(");
							if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\"CLIMBWALLS(");
							if (freeushort5==1) fprintf(file,"+Z)");
							if (freeushort5==2) fprintf(file,"+X)");
							if (freeushort5==3) fprintf(file,"+X,+Z)");
							if (freeushort5==4) fprintf(file,"-Z)");
							if (freeushort5==5) fprintf(file,"+Z,-Z)");
							if (freeushort5==6) fprintf(file,"+X,-Z)");
							if (freeushort5==7) fprintf(file,"+X,+Z,-Z)");
							if (freeushort5==8) fprintf(file,"-X)");
							if (freeushort5==9) fprintf(file,"-X,+Z)");
							if (freeushort5==10) fprintf(file,"+X,-X)");
							if (freeushort5==11) fprintf(file,"+X,-X,+Z)");
							if (freeushort5==12) fprintf(file,"-X,-Z)");
							if (freeushort5==13) fprintf(file,"-X,+Z,-Z)");
							if (freeushort5==14) fprintf(file,"+X,-X,-Z)");
							if (freeushort5==15) fprintf(file,"+X,-X,+Z,-Z)");
							if (!_strnicmp(args[2],"list",4)) fprintf(file,"\n");
							if (!_strnicmp(args[2],"clist",5)) fprintf(file,"\" ");
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
	fclose(file);
}
void tr2pc_add_item(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumItems, unsigned fsize){
	// This functions adds an item to the level. The syntax is "trmod [FILE] ADD ITEM [ObjectID] [Room] [X] [Z] [Y] [Angle] [Intensity] [Intensity2] [Flags]".
	char *temp=malloc(24);
	unsigned short freeushort1 = strtol(args[4], NULL, 10);
	memcpy(temp,&freeushort1,2);
	freeushort1 = strtol(args[5], NULL, 10);
	memcpy(temp+2,&freeushort1,2);
	int freeint1=strtol(args[6], NULL, 10);
	freeint1+=roomX[freeushort1];
	memcpy(temp+4,&freeint1,4);
	freeint1=strtol(args[8], NULL, 10);
	freeint1=roomY[freeushort1]-freeint1;
	memcpy(temp+8,&freeint1,4);
	freeint1=strtol(args[7], NULL, 10);
	freeint1+=roomZ[freeushort1];
	memcpy(temp+12,&freeint1,4);
	freeushort1 = strtol(args[9], NULL, 10);
	freeushort1=(freeushort1/45)<<13;
	memcpy(temp+16,&freeushort1,2);
	freeushort1 = strtol(args[10], NULL, 10);
	memcpy(temp+18,&freeushort1,2);
	freeushort1 = strtol(args[11], NULL, 10);
	memcpy(temp+20,&freeushort1,2);
	freeushort1 = strtol(args[12], NULL, 16);
	memcpy(temp+22,&freeushort1,2);
	memcpy(&freeint1,bytelist+p_NumItems,4);
	bytelist=insertrange(bytelist,(p_NumItems+4+freeint1*24),24,temp,fsize);
	fsize+=24;
	freeint1++;
	memcpy(bytelist+p_NumItems,&freeint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_replace_item(char *bytelist, int argc, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumItems, unsigned fsize){
	// This function replaces an item in the level. The syntax is "trmod [FILE] REPLACE ITEM [Item] [ObjectID] [Room] [X] [Z] [Y] [Angle] [Intensity1] [Intensity2] [Flags]".
	// The syntax can also be "trmod [FILE] REPLACE ITEM [Item] [ObjectID]", which will cause only the ObjectID to be replaced, but all other factors to remain identical.
	unsigned freeuint1 = p_NumItems+4+(strtol(args[4], NULL, 10)*24);
	unsigned short freeushort1 = strtol(args[5], NULL, 10);
	if (argc>6){
		memcpy(bytelist+freeuint1,&freeushort1,2);
		freeushort1 = strtol(args[6], NULL, 10);
		memcpy(bytelist+freeuint1+2,&freeushort1,2);
		int freeint1=strtol(args[7], NULL, 10);
		freeint1+=roomX[freeushort1];
		memcpy(bytelist+freeuint1+4,&freeint1,4);
		freeint1=strtol(args[9], NULL, 10);
		freeint1=roomY[freeushort1]-freeint1;
		memcpy(bytelist+freeuint1+8,&freeint1,4);
		freeint1=strtol(args[8], NULL, 10);
		freeint1+=roomZ[freeushort1];
		memcpy(bytelist+freeuint1+12,&freeint1,4);
		freeushort1 = strtol(args[10], NULL, 10);
		freeushort1=(freeushort1/45)<<13;
		memcpy(bytelist+freeuint1+16,&freeushort1,2);
		freeushort1 = strtol(args[11], NULL, 10);
		memcpy(bytelist+freeuint1+18,&freeushort1,2);
		freeushort1 = strtol(args[12], NULL, 10);
		memcpy(bytelist+freeuint1+20,&freeushort1,2);
		freeushort1 = strtol(args[13], NULL, 16);
		memcpy(bytelist+freeuint1+22,&freeushort1,2);
	}else{
		memcpy(bytelist+freeuint1,&freeushort1,2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_remove_item(char *bytelist, int argc, char *args[], unsigned p_NumZSector[], unsigned p_NumFloorData, unsigned p_NumItems, unsigned short numRooms, unsigned fsize){
	/*
	This function removes an item from the level. The syntax is "trmod [FILE] REMOVE ITEM [ITEM]" or "trmod [FILE] REMOVE ITEM [ITEM] RAW".
	It removes the item first, and then goes through all the floordata, replacing all the item numbers higher than the removed item number with one
	item lower, to make sure all triggers still work and refer to the correct items. If the argument "RAW" is added to the end of the command, the
	item is removed, but the floordata unaltered.
	*/
	short freeshort1;
	unsigned short freeushort1;
	unsigned short freeushort2;
	unsigned short freeushort3;
	unsigned short freeushort5;
	unsigned short freeushort6;
	unsigned short freeushort7;
	unsigned curpos;
	unsigned freeuint1;
	unsigned freeuint2;
	unsigned freeuint3;
	unsigned freeuint4;
	unsigned char freeuchar1;
	char freechar2;
	memcpy(&freeuint4,bytelist+p_NumItems,4);
	freeuint4-=1;
	memcpy(bytelist+p_NumItems,&freeuint4,4);
	freeuint4 = strtol(args[4], NULL, 10);
	fsize=removerange(bytelist,p_NumItems+4+(freeuint4*24),24,fsize);
	char freechar1=1;
	if (argc>5){
		if (!_strnicmp(args[5],"raw",3)) freechar1=0;
	}
	if (freechar1==1){
		for (freeushort1=0;freeushort1<numRooms;freeushort1++){
			curpos=p_NumZSector[freeushort1]+4;
			memcpy(&freeushort2,bytelist+curpos-2,2);
			memcpy(&freeushort3,bytelist+curpos-4,2);
			freeuint1=(freeushort2*freeushort3);
			for (freeuint2=0;freeuint2<freeuint1;freeuint2++){
				memcpy(&freeushort2,bytelist+curpos,2);
				if (freeushort2!=0){
					memcpy(&freeushort2,bytelist+curpos,2);
					if (freeushort2!=0){
						freeuint3=p_NumFloorData+4+(freeushort2*2);
						freechar2=0;
						while (freechar2==0){
							memcpy(&freeushort2,bytelist+freeuint3,2);
							if (freeushort2>=32768) freechar2=1;
							freeushort3=freeushort2 & 0x1F;
							freeuint3+=4;
							if (freeushort3==4){
								freeushort5=freeushort2 & 0x7F00;
								freeushort5 >>= 8;
								if (freeushort5>1&&freeushort5<5){
									memcpy(&freeushort6, bytelist+freeuint3,2);
									if (freeushort6>freeuint4){
										freeushort6--;
										memcpy(bytelist+freeuint3,&freeushort6,2);
									}
									freeuint3+=2;
								}
								freechar1=0;
								while (freechar1==0){
									memcpy(&freeushort6, bytelist+freeuint3,2);
									if ((freeushort6 & 0x8000)==32768) freechar1=1;
									freeshort1=(freeushort6 & 0x7C00);
									freeshort1 >>= 10;
									freeuchar1=freeshort1;
									if (freeuchar1==0||freeuchar1==6) {
										memcpy(&freeshort1,&freeushort6,2);
										freeushort7 = freeshort1&0x3FF;
										if (freeushort7>freeuint4){
											freeshort1--;
											memcpy(bytelist+freeuint3,&freeshort1,2);
										}
									}
									if (freeuchar1==1) {
										memcpy(&freeshort1, bytelist+freeuint3+2,2);
										if ((freeshort1 & 0x8000)==32768) freechar1=1;
										freeuint3+=2;
									}
									freeuint3+=2;
								}
							}
							if (freeushort3==5||freeushort3==6) freeuint3-=2;
						}
					}
				}
				curpos += 8;
			}
		}
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_add_staticmesh(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize){
	// This function adds a static mesh to the level. The syntax is "trmod [FILE] ADD STATICMESH [ObjectID] [Room] [X] [Z] [Y] [Angle] [Intensity1] [Intensity2]".
	char *temp=malloc(18);
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
	freeushort2 = strtol(args[11], NULL, 10);
	memcpy(temp+16,&freeushort2,2);
	freeushort2 = strtol(args[4], NULL, 10);
	memcpy(temp+18,&freeushort2,2);
	memcpy(&freeushort2,bytelist+p_NumStaticMeshes[freeushort1],2);
	bytelist=insertrange(bytelist,(p_NumStaticMeshes[freeushort1]+2+freeushort2*20),20,temp,fsize);
	fsize+=20;
	freeushort2++;
	memcpy(bytelist+p_NumStaticMeshes[freeushort1],&freeushort2,2);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_replace_staticmesh(char *bytelist, int argc, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize){
	// This function replaces a static mesh to the level. The syntax is "trmod [FILE] REPLACE STATICMESH [Room] [Staticmesh] [ObjectID] [X] [Z] [Y] [Angle] [Intensity1] [Intensity2]" or "trmod [FILE] REPLACE STATICMESH [Room] [Staticmesh] [ObjectID]".
	// The syntax can also be "trmod [FILE] REPLACE STATICMESH [Room] [StaticMesh] [ObjectID]", which will cause only the ObjectID to be replaced, but all other factors to remain identical.
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
		freeushort2 = strtol(args[12], NULL, 10);
		memcpy(bytelist+freeuint1+16,&freeushort2,2);
		memcpy(bytelist+freeuint1+18,&freeushort1,2);
	}else{
		memcpy(bytelist+freeuint1+18,&freeushort1,2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_remove_staticmesh(char *bytelist, char *args[], unsigned p_NumStaticMeshes[], unsigned fsize){
	// This function removes a static mesh from the level. The syntax is "trmod [FILE] REMOVE STATICMESH [Room] [Staticmesh]".
	unsigned freeuint1 = p_NumStaticMeshes[strtol(args[4], NULL, 10)]-18+(strtol(args[5], NULL, 10)*20);
	unsigned short freeushort1;
	memcpy(&freeushort1,bytelist+p_NumStaticMeshes[strtol(args[4], NULL, 10)],2);
	freeushort1--;
	memcpy(bytelist+p_NumStaticMeshes[strtol(args[4], NULL, 10)], &freeushort1, 2);
	fsize=removerange(bytelist,freeuint1,20,fsize);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_add_sprite(char *bytelist, char *args[], int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize){
	// This function adds a sprite to the level. The syntax is "trmod [FILE] ADD SPRITE [ObjectID] [Room] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]".
	int freeint1;
	char freechar1=0;
	char *temp=malloc(12);
	short freeshort1;
	short freeshort2=strtol(args[5], NULL, 10);
	unsigned freeuint1=p_NumVertices[freeshort2]+2;
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
	freeshort1=strtol(args[9], NULL, 10);
	memcpy(temp+6,&freeshort1,2);
	freeshort1=strtol(args[11], NULL, 16);
	memcpy(temp+8,&freeshort1,2);
	freeshort1=strtol(args[10], NULL, 10);
	memcpy(temp+10,&freeshort1,2);
	memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
	while (freeshort1>0){
		freeint1=memcmp(temp,bytelist+freeuint1,12);
		if (freeint1==0){
			freeuint2=freeuint1;
			freechar1=1;
		}
		freeuint1+=12;
		freeshort1--;
	}
	if (freechar1==0){
		freeuint2=freeuint1;
		bytelist=insertrange(bytelist,freeuint1,12,temp,fsize);
		fsize+=12;
		p_NumSprites[freeshort2]+=12;
		p_NumSpriteSequences+=12;
		memcpy(&freeuint1,bytelist+p_NumVertices[freeshort2]-4,4);
		freeuint1+=6;
		memcpy(bytelist+p_NumVertices[freeshort2]-4,&freeuint1,4);
		memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
		freeshort1++;
		memcpy(bytelist+p_NumVertices[freeshort2],&freeshort1,2);
	}
	temp=malloc(4);
	freeshort1=(freeuint2-p_NumVertices[freeshort2])/12;
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
void tr2pc_replace_sprite(char *bytelist, char *args[], unsigned argc, int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize){
	// This function replaces a sprite in the level. The syntax is "trmod [FILE] REPLACE SPRITE [Room] [Sprite] [ObjectID] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]".
	// The syntax can also be "trmod [FILE] REPLACE SPRITE [Room] [Sprite] [ObjectID]", which will cause only the ObjectID to be replaced, but all other factors to remain identical.
	int freeint1;
	char freechar1=0;
	char *temp=malloc(12);
	short freeshort1;
	short freeshort2=strtol(args[4], NULL, 10);
	unsigned freeuint1=p_NumVertices[freeshort2]+2;
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
		freeshort1=strtol(args[10], NULL, 10);
		memcpy(temp+6,&freeshort1,2);
		freeshort1=strtol(args[12], NULL, 16);
		memcpy(temp+8,&freeshort1,2);
		freeshort1=strtol(args[11], NULL, 10);
		memcpy(temp+10,&freeshort1,2);
		memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
		while (freeshort1>0){
			freeint1=memcmp(temp,bytelist+freeuint1,8);
			if (freeint1==0){
				freeuint2=freeuint1;
				freechar1=1;
			}
			freeuint1+=12;
			freeshort1--;
		}
		if (freechar1==0){
			freeuint2=freeuint1;
			bytelist=insertrange(bytelist,freeuint1,12,temp,fsize);
			fsize+=12;
			p_NumSprites[freeshort2]+=12;
			p_NumSpriteSequences+=12;
			memcpy(&freeuint1,bytelist+p_NumVertices[freeshort2]-4,4);
			freeuint1+=6;
			memcpy(bytelist+p_NumVertices[freeshort2]-4,&freeuint1,4);
			memcpy(&freeshort1,bytelist+p_NumVertices[freeshort2],2);
			freeshort1++;
			memcpy(bytelist+p_NumVertices[freeshort2],&freeshort1,2);
		}
		temp=malloc(4);
		freeshort1=(freeuint2-p_NumVertices[freeshort2])/12;
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
void tr2pc_add_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize){
	// This function adds a light. The syntax is "trmod [FILE] ADD LIGHT [Room] [X] [Z] [Y] [Intensity1] [Intensity2] [Fade1] [Fade2]"
	char *temp=malloc(24);
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
	freeushort2 = strtol(args[9], NULL, 10);
	memcpy(temp+14,&freeushort2,2);
	freeint1=strtol(args[10], NULL, 10);
	memcpy(temp+16,&freeint1,4);
	freeint1=strtol(args[11], NULL, 10);
	memcpy(temp+20,&freeint1,4);
	memcpy(&freeushort2,bytelist+p_NumLights[freeushort1],2);
	bytelist=insertrange(bytelist,(p_NumLights[freeushort1]+2+freeushort2*24),24,temp,fsize);
	fsize+=24;
	freeushort2++;
	memcpy(bytelist+p_NumLights[freeushort1],&freeushort2,2);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_replace_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize){
	// This function replaces a static mesh to the level. The syntax is "trmod [FILE] REPLACE LIGHT [Room] [Light] [X] [Z] [Y] [Intensity1] [Intensity2] [Fade1] [Fade2]"
	unsigned freeuint1 = p_NumLights[strtol(args[4], NULL, 10)]-22+(strtol(args[5], NULL, 10)*24);
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
	freeushort2 = strtol(args[10], NULL, 10);
	memcpy(bytelist+freeuint1+14,&freeushort2,2);
	freeint1=strtol(args[11], NULL, 10);
	memcpy(bytelist+freeuint1+16,&freeint1,4);
	freeint1=strtol(args[12], NULL, 10);
	memcpy(bytelist+freeuint1+20,&freeint1,4);
	memcpy(&freeushort2,bytelist+p_NumLights[freeushort1],2);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_remove_light(char *bytelist, char *args[], unsigned p_NumLights[], unsigned fsize){
	// This function removes a static mesh from the level. The syntax is "trmod [FILE] REMOVE LIGHT [Room] [Light]".
	unsigned freeuint1 = p_NumLights[strtol(args[4], NULL, 10)]-22+(strtol(args[5], NULL, 10)*24);
	unsigned short freeushort1;
	memcpy(&freeushort1,bytelist+p_NumLights[strtol(args[4], NULL, 10)],2);
	freeushort1--;
	memcpy(bytelist+p_NumLights[strtol(args[4], NULL, 10)], &freeushort1, 2);
	fsize=removerange(bytelist,freeuint1,24,fsize);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_replace_floordata(char *bytelist, char *args[], int argc, unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumZSector[], unsigned p_NumFloorData, unsigned p_NumCameras, unsigned fsize){
	/*
	This function replaces the floordata of a given sector. The syntax is "trmod [FILE] REPLACE FLOORDATA [Room] [Column] [Row] {Floordata}".
	The {Floordata} argument(s) follow the following syntax:
		"PORTAL(Adjoining Room)" (This creates a protal to a neighboring room)
		"FLOORSLANT(Slant on X Axis,Slant on Z Axis)" (This makes the floor slanted)
		"CEILINGSLANT(Slant on X Axis,Slant on Z Axis)" (This makes the ceiling slanted)
		"TRIGGER({Trigger Conventions})" (This creates a trigger on this sector)
		"KILL" (This kills Lara when she steps on this sector)
		"CLIMBWALLS(+X,-X,+Z,-Z)" (Makes the walls climbable)
	The Trigger Conventions are as follows:
	The contents of the trigger are in Parentheses and contain NO spaces. The general layout is as follows:
	(Subfunction:Flag:FDFunction;FDFunction)
	(Trigger_Type:Timer:Only_Once:Mask:Trigger_Action;Trigger_Action)
	First there is the Trigger type, which determines under what conditions the trigger is activated, followed by a colon.
	If the Trigger type includes an item, the syntax is (Trigger_Type:Item:Timer:Only_Once:Mask:Trigger_Action;Trigger_Action). After the Trigger type
	and the item (if needed), there follows the timer, only once boolean and mask, followed by a final colon. After that colon any Triggeraction can
	be added, and separated from other TriggerActions by a semicolon.
	____________________________________________________________________________________________
		The Trigger types are written as follows:
			"TRIGGER" (Activates the trigger if Lara is on or above this sector)
			"PAD" (Activates the trigger if Lara is on the ground in this sector)
			"SWITCH:Item" (Activates the trigger if the specified item is activated, and deactivates it
						when the item is deactivated. Best used for switches)
			"KEY:Item" (Activates the trigger if the specified item is activated, but never deactivates it again,
						Best used for keyholes)
			"PICKUP:Item" (Activates the trigger if the specified item is picked up)
			"HEAVYTRIGGER" (Activates if there is an item in this sector. Best used in block puzzles and such)
			"ANTIPAD" (Deactivates the trigger if Lara is on the ground in this sector)
			"COMBAT" (Activates the trigger if Lara has her pistols drawn)
			"DUMMY" (Activates the trigger if Lara is in this sector, but not on the ground. Best used for bridges)
			"ANTITRIGGER" (Deactivates the trigger if Lara is on or above this sector)
		Following the flag and colon, come the FDFunctions. These determine what the trigger does.
	____________________________________________________________________________________________
			The TriggerActions are written as follows:
				"OBJECT(Item)" (Activates the specified item. Used for doors, enemies etc.
				"CAMERA(Room,X,Z,Y,Flag,Movetime,Time,Only Once)" (Moves the camera. Room,X,Z and Y determine the new position of the camera.
																	Movetime is how long the camera takes to travel to this point. Time is how
																	long the camera will stay there, and Only Once is to be filled in with the
																	words "TRUE" or "FALSE" to determine whether this is to happen only once)
				"CURRENT(Room,X,Z,Y,Strength,Zone)" (Produces an underwater current. The word zone can either be filled in with the word "AUTO",
													which will detect the zone automatically, or the zone number of choice)
				"FLIPMAP(Unknown)"
				"FLIPON(Unknown)"
				"FLIPOFF(Unknown)"
				"LOOKITEM(Item)" (Tilts the camera to look at the specified object)
				"ENDLEVEL" (Ends the level)
				"SOUNDTRACK(Track)" (Plays a track from the CD)
				"EFFECT(Flag)" Unknown
				"SECRET(Secret Number)" (Lara found the secret number specified)
				"CLEARBODIES" (Clears dead bodies)
			Any FDFunction can be added to any other when divided by a semicolon.
	____________________________________________________________________________________________
	*/
	char *temp=malloc(0);
	char freechar1;
	char freechar2;
	char freechar3;
	unsigned char freeuchar1;
	unsigned char freeuchar2;
	int freeint1;
	unsigned freeuint1;
	unsigned freeuint2=0;
	unsigned freeuint3;
	unsigned freeuint4;
	unsigned freeuint5;
	unsigned short freeushort1;
	unsigned short freeushort2=strtol(args[4], NULL, 10);
	unsigned short freeushort3;
	memcpy(&freeushort1,bytelist+p_NumZSector[freeushort2],2);
	freeuint1=(p_NumZSector[(strtol(args[4], NULL, 10))]) + ((strtol(args[6], NULL, 10)-1)*8)+4+(((strtol(args[5], NULL, 10)-1)*freeushort1)*8);
	for ((freeushort1=7);freeushort1<argc;freeushort1++){
		if (!_strnicmp(args[freeushort1],"floorportal",11)){
			freechar1=strtol((substring(args[freeushort1],12,strlen(args[freeushort1])-13)), NULL, 10);
			memcpy(bytelist+freeuint1+4,&freechar1,1);
		}
		if (!_strnicmp(args[freeushort1],"ceilingportal",13)){
			freechar1=strtol((substring(args[freeushort1],14,strlen(args[freeushort1])-15)), NULL, 10);
			memcpy(bytelist+freeuint1+6,&freechar1,1);
		}
		if (!_strnicmp(args[freeushort1],"portal",6)){
			temp = (char *) realloc(temp,freeuint2+4);
			memset(temp+freeuint2,1,1);
			memset(temp+freeuint2+1,0,1);
			if (freeushort1==(argc-1)) memset(temp+freeuint2+1,128,1);
			freeushort3=strtol((substring(args[freeushort1],7,strlen(args[freeushort1])-8)), NULL, 10);
			memcpy(temp+freeuint2+2,&freeushort3,2);
			freeuint2+=4;
		}
		if (!_strnicmp(args[freeushort1],"floorslant",10)){
			temp = (char *) realloc(temp,freeuint2+4);
			memset(temp+freeuint2,2,1);
			memset(temp+freeuint2+1,0,1);
			if (freeushort1==(argc-1)) memset(temp+freeuint2+1,128,1);
			freechar1=strtol((splitString(substring(args[freeushort1],11,strlen(args[freeushort1])-12), ',', 0)), NULL, 10);
			memcpy(temp+freeuint2+2,&freechar1,1);
			freechar1=strtol((splitString(substring(args[freeushort1],11,strlen(args[freeushort1])-12), ',', 1)), NULL, 10);
			memcpy(temp+freeuint2+3,&freechar1,1);
			freeuint2+=4;
		}
		if (!_strnicmp(args[freeushort1],"ceilingslant",12)){
			temp = (char *) realloc(temp,freeuint2+4);
			memset(temp+freeuint2,3,1);
			memset(temp+freeuint2+1,0,1);
			if (freeushort1==(argc-1)) memset(temp+freeuint2+1,128,1);
			freechar1=strtol((splitString(substring(args[freeushort1],13,strlen(args[freeushort1])-14), ',', 0)), NULL, 10);
			memcpy(temp+freeuint2+2,&freechar1,1);
			freechar1=strtol((splitString(substring(args[freeushort1],13,strlen(args[freeushort1])-14), ',', 1)), NULL, 10);
			memcpy(temp+freeuint2+3,&freechar1,1);
			freeuint2+=4;
		}
		if (!_strnicmp(args[freeushort1],"trigger",7)){
			memmove(args[freeushort1],args[freeushort1]+8,strlen(args[freeushort1])-9);
			memset(args[freeushort1]+strlen(args[freeushort1])-9,0,1);
			if (!_strnicmp(args[freeushort1],"trigger",7)) freeuchar1=0;
			if (!_strnicmp(args[freeushort1],"pad",3)) freeuchar1=1;
			if (!_strnicmp(args[freeushort1],"switch",6)){
				memmove(args[freeushort1],args[freeushort1]+7,strlen(args[freeushort1])-7);
				memset(args[freeushort1]+strlen(args[freeushort1])-7,0,1);
				freeuchar1=2;
			}
			if (!_strnicmp(args[freeushort1],"key",3)){
				memmove(args[freeushort1],args[freeushort1]+4,strlen(args[freeushort1])-4);
				memset(args[freeushort1]+strlen(args[freeushort1])-4,0,1);
				freeuchar1=3;
			}
			if (!_strnicmp(args[freeushort1],"pickup",6)){
				memmove(args[freeushort1],args[freeushort1]+7,strlen(args[freeushort1])-7);
				memset(args[freeushort1]+strlen(args[freeushort1])-7,0,1);
				freeuchar1=4;
			}
			if (!_strnicmp(args[freeushort1],"heavytrigger",12)) freeuchar1=5;
			if (!_strnicmp(args[freeushort1],"antipad",7)) freeuchar1=6;
			if (!_strnicmp(args[freeushort1],"combat",6)) freeuchar1=7;
			if (!_strnicmp(args[freeushort1],"dummy",5)) freeuchar1=8;
			if (!_strnicmp(args[freeushort1],"antitrigger",11)) freeuchar1=9;
			temp = (char *) realloc(temp,freeuint2+6);
			memset(temp+freeuint2,4,1);
			if (freeushort1==(argc-1)) freeuchar1|=0x0080;
			memset(temp+freeuint2+1,freeuchar1,1);
			freechar2=strtol(splitString(args[freeushort1], ':', 1), NULL, 10);
			memset(temp+freeuint2+2,freechar2,1);
			freeuchar2=(strtol(splitString(args[freeushort1], ':', 3), NULL, 10))<<1;
			if (!_strnicmp((splitString(args[freeushort1], ':', 2)),"true",4)) freeuchar2|=0x1;
			memset(temp+freeuint2+3,freeuchar2,1);
			freeuint2+=4;
			freeuchar1&=0xFF7F;
			if (freeuchar1>1&&freeuchar1<5) {
				freeuint3=strtol(splitString(args[freeushort1], ':', 0), NULL, 10);
				memcpy(temp+freeuint2,&freeuint3,2);
				freeuint2+=2;
			}
			freeuint3=strlen(splitString(args[freeushort1], ':', 4));
			strcpy(args[freeushort1],splitString(args[freeushort1], ':', 4));
			memset(args[freeushort1]+freeuint3,0,1);
			freeuint3=countchar(args[freeushort1],';');
			for (freeuint3=countchar(args[freeushort1],';')+1;freeuint3>0;freeuint3--){
				if (!_strnicmp(args[freeushort1],"object",6)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), NULL, 10);
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"camera",6)){
					char *camera=malloc(16);
					temp = (char *) realloc(temp,freeuint2+4);
					freeushort3=strtol(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 0), NULL, 10);
					freeint1=strtol(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 1), NULL, 10)+roomX[freeushort3];
					memcpy(camera,&freeint1,4);
					freeint1=roomY[freeushort3]-strtol(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 3), NULL, 10);
					memcpy(camera+4,&freeint1,4);
					freeint1=strtol(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 2), NULL, 10)+roomZ[freeushort3];
					memcpy(camera+8,&freeint1,4);
					memcpy(camera+12,&freeushort3,2);
					freeushort3=strtol(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 4), NULL, 16);
					memcpy(camera+14,&freeushort3,2);
					memcpy(&freeuint4,bytelist+p_NumCameras,4);
					freeuint4=p_NumCameras+4+(freeuint4*16);
					freechar3=0;
					for (freeuint5=p_NumCameras+4;freeuint5<freeuint4;freeuint5+=16){
						if (memcmp(camera,bytelist+freeuint5,16)==0){
							freeuint4=freeuint5;
							freechar3=1;
						}
					}
					if (freechar3==0){
						bytelist=insertrange(bytelist,freeuint4,16,camera,fsize);
						fsize+=16;
						memcpy(&freeuint4,bytelist+p_NumCameras,4);
						freeuint4++;
						memcpy(bytelist+p_NumCameras,&freeuint4,4);
						freeuint5+=16;
					}
					freeushort3=(freeuint5-p_NumCameras-20)>>4;
					freeushort3|=0x400;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeushort3=strtol(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 5), NULL, 10);
					freeushort3+=(strtol(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 6), NULL, 10)<<9);
					if (!_strnicmp(splitString(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), ',', 7),"true",4)) freeushort3|=0x100;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2+2,&freeushort3,2);
					freeuint2+=4;
				}
				if (!_strnicmp(args[freeushort1],"current",7)){
					char *sink=malloc(16);
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(splitString(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), ',', 0), NULL, 10);
					freeint1=strtol(splitString(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), ',', 1), NULL, 10)+roomX[freeushort3];
					memcpy(sink,&freeint1,4);
					freeint1=roomY[freeushort3]-strtol(splitString(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), ',', 3), NULL, 10);
					memcpy(sink+4,&freeint1,4);
					freeint1=strtol(splitString(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), ',', 2), NULL, 10)+roomZ[freeushort3];
					memcpy(sink+8,&freeint1,4);
					freeushort3=strtol(splitString(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), ',', 4), NULL, 10);
					memcpy(sink+12,&freeushort3,2);
					if (!_strnicmp(splitString(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), ',', 5),"auto",4)){
						memcpy(&freeushort3,bytelist+freeuint1+2,2);
					}else{
						freeushort3=strtol(splitString(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), ',', 5), NULL, 10);
					}
					memcpy(sink+14,&freeushort3,2);
					memcpy(&freeuint4,bytelist+p_NumCameras,4);
					freeuint4=p_NumCameras+4+(freeuint4*16);
					freechar3=0;
					for (freeuint5=p_NumCameras+4;freeuint5<freeuint4;freeuint5+=16){
						if (memcmp(sink,bytelist+freeuint5,16)==0){
							freeuint4=freeuint5;
							freechar3=1;
						}
					}
					if (freechar3==0){
						bytelist=insertrange(bytelist,freeuint4,16,sink,fsize);
						fsize+=16;
						memcpy(&freeuint4,bytelist+p_NumCameras,4);
						freeuint4++;
						memcpy(bytelist+p_NumCameras,&freeuint4,4);
						freeuint5+=16;
					}
					freeushort3=(freeuint5-p_NumCameras-20)>>4;
					freeushort3|=0x800;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"flipmap",7)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), NULL, 10);
					freeushort3|=0xc00;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"flipon",6)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), NULL, 10);
					freeushort3|=0x1000;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"flipoff",7)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],8,strlen(splitString(args[freeushort1], ';', 0))-9), NULL, 10);
					freeushort3|=0x1400;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"lookitem",8)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],9,strlen(splitString(args[freeushort1], ';', 0))-10), NULL, 10);
					freeushort3|=0x1800;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"endlevel",8)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=7168;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"soundtrack",10)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],11,strlen(splitString(args[freeushort1], ';', 0))-12), NULL, 10);
					freeushort3|=0x2000;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"effect",6)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), NULL, 10);
					freeushort3|=0x2400;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"secret",6)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=strtol(substring(args[freeushort1],7,strlen(splitString(args[freeushort1], ';', 0))-8), NULL, 10)-1;
					freeushort3|=0x2800;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				if (!_strnicmp(args[freeushort1],"clearbodies",11)){
					temp = (char *) realloc(temp,freeuint2+2);
					freeushort3=11264;
					if (freeuint3==1) freeushort3|=0x8000;
					memcpy(temp+freeuint2,&freeushort3,2);
					freeuint2+=2;
				}
				freeushort3=strlen(splitString(args[freeushort1], ';', 0))+1;
				if (freeuint3!=1){
					memmove(args[freeushort1],args[freeushort1]+freeushort3,strlen(args[freeushort1])-freeushort3);
					memset(args[freeushort1]+(strlen(args[freeushort1])-freeushort3),0,1);
				}
			}
		}
		if (!_strnicmp(args[freeushort1],"kill",4)){
			temp = (char *) realloc(temp,freeuint2+2);
			memset(temp+freeuint2,5,1);
			memset(temp+freeuint2+1,0,1);
			if (freeushort1==(argc-1)) memset(temp+freeuint2+1,128,1);
			freeuint2+=2;
		}
		if (!_strnicmp(args[freeushort1],"climbwalls",10)){
			temp = (char *) realloc(temp,freeuint2+2);
			freeuint4=strlen(args[freeushort1])-11;
			freeushort3=6;
			memmove(args[freeushort1],args[freeushort1]+11,freeuint4);
			memset(args[freeushort1]+freeuint4,0,1);
			while (strlen(args[freeushort1])>0){
				freeuint4=strlen(args[freeushort1])-3;
				if (!_strnicmp(args[freeushort1],"+X",2)) freeushort3|=0x200;
				if (!_strnicmp(args[freeushort1],"-X",2)) freeushort3|=0x800;
				if (!_strnicmp(args[freeushort1],"+Z",2)) freeushort3|=0x100;
				if (!_strnicmp(args[freeushort1],"-Z",2)) freeushort3|=0x400;
				memmove(args[freeushort1],args[freeushort1]+3,freeuint4);
				memset(args[freeushort1]+freeuint4,0,1);
			}
			if (freeushort1==(argc-1)) freeushort3|=0x8000;
			memcpy(temp+freeuint2,&freeushort3,2);
			freeuint2+=2;
		}
	}
	if (freeuint2>0){
		freechar1=0;
		freeuint3=p_NumFloorData+4;
		memcpy(&freeuint4,bytelist+p_NumFloorData,4);
		freeuint4=p_NumFloorData+4+(freeuint4*2);
		while (freeuint3!=freeuint4){
			if (memcmp(temp,bytelist+freeuint3,freeuint2)==0){
				freechar1=1;
				freeushort2=(freeuint3-4-p_NumFloorData)/2;
				memcpy(bytelist+freeuint1,&freeushort2,2);
			}
			freeuint3+=2;
		}
		if (freechar1==0){
			freeushort2=(freeuint3-4-p_NumFloorData)/2;
			memcpy(bytelist+freeuint1,&freeushort2,2);
			bytelist=insertrange(bytelist,freeuint3,freeuint2,temp,fsize);
			fsize+=freeuint2;
			freeuint1=(((freeuint3+freeuint2)-p_NumFloorData-4)/2);
			memcpy(bytelist+p_NumFloorData,&freeuint1,4);
		}
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_remove_all(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumFloorData, unsigned p_NumCameras, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned p_NumBoxes, unsigned short numRooms, unsigned fsize){
	// This function removes all of a given object from a level. The syntax is "trmod [FILE] REMOVE ALL {ITEMS/STATICMESHSES/SPRITES/LIGHTS/SOUNDSOURCES/CAMERAS/FLOORDATA/GEOMETRY/RECTANGLES/TRIANGLES/VIEWPORTS/ZONES}".
	// GEOMETRY,RECTANGLES,TRIANGLES and VIEWPORTS require either a room number after, or the word "all" to apply to all rooms.
	int freeint1;
	unsigned curpos;
	unsigned freeuint1;
	unsigned freeuint2;
	unsigned short freeushort1;
	unsigned short freeushort2;
	if (!_strnicmp(args[4],"items",5)){
		memcpy(&freeuint1, bytelist+p_NumItems,4);
		fsize=removerange(bytelist,p_NumItems+4,(freeuint1*24),fsize);
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
			fsize=removerange(bytelist,p_NumLights[freeint1]+2,(freeushort1*24),fsize);
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
				freeuint1=p_NumVertices[freeint1]+10;
				fsize=removerange(bytelist,freeuint1,(p_NumZSector[freeint1]-freeuint1),fsize);
				memset(bytelist+p_NumVertices[freeint1]-3,0,13);
				memset(bytelist+p_NumVertices[freeint1]-4,4,1);
			}
		} else {
			freeint1=strtol(args[5], NULL, 10);
			freeuint1=p_NumVertices[freeint1]+10;
			fsize=removerange(bytelist,freeuint1,(p_NumZSector[freeint1]-freeuint1),fsize);
			memset(bytelist+p_NumVertices[freeint1]-3,0,13);
			memset(bytelist+p_NumVertices[freeint1]-4,4,1);
		}
	}
	if (!_strnicmp(args[4],"rectangles",10)){
		if (!_strnicmp(args[5],"all",3)) {
			for (freeint1=numRooms-1;freeint1>=0;freeint1--){
				memcpy(&freeushort1,bytelist+p_NumVertices[freeint1],2);
				freeuint1=p_NumVertices[freeint1]+2+(freeushort1*12);
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
			freeuint1=p_NumVertices[freeint1]+2+(freeushort1*12);
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
				freeuint1=p_NumVertices[freeint1]+2+(freeushort1*12);
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
			freeuint1=p_NumVertices[freeint1]+2+(freeushort1*12);
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
		freeuint1=p_NumBoxes+4+(freeint1*8);
		memcpy(&freeuint1, bytelist+freeuint1,4);
		fsize=removerange(bytelist,p_NumBoxes+8,(freeuint1*2)+(freeint1*28),fsize);
		memset(bytelist+p_NumBoxes,0,8);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_roomlight(char *bytelist, char *args[], unsigned p_NumLights[], unsigned short numRooms, unsigned fsize){
	// This function changes the Intensity and LightMode of a room. the Syntax is "trmod [FILE] ROOMLIGHT [Room] [Intensity1] [Intensity2] [LightMode]"
	short freeshort1;
	short freeshort2;
	if (!_strnicmp(args[3],"all",3)) {
		for (freeshort2=0;freeshort2<numRooms;freeshort2++){
			freeshort1=strtol(args[4], NULL, 10);
			memcpy(bytelist+p_NumLights[freeshort2]-6, &freeshort1, 2);
			freeshort1=strtol(args[5], NULL, 10);
			memcpy(bytelist+p_NumLights[freeshort2]-4, &freeshort1, 2);
			freeshort1=strtol(args[6], NULL, 10);
			memcpy(bytelist+p_NumLights[freeshort2]-2, &freeshort1, 2);
		}
	} else {
		freeshort2=strtol(args[3], NULL, 10);
		freeshort1=strtol(args[4], NULL, 10);
		memcpy(bytelist+p_NumLights[freeshort2]-6, &freeshort1, 2);
		freeshort1=strtol(args[5], NULL, 10);
		memcpy(bytelist+p_NumLights[freeshort2]-4, &freeshort1, 2);
		freeshort1=strtol(args[6], NULL, 10);
		memcpy(bytelist+p_NumLights[freeshort2]-2, &freeshort1, 2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_sky(char *bytelist, char *args[], unsigned p_AlternateRoom[], unsigned short numRooms, unsigned fsize){
	// This function makes the sky visible from this room. The syntax is "trmod [FILE] SKY [Room]"
	unsigned freeshort1;
	unsigned freeshort2;
	if (!_strnicmp(args[3],"all",3)) {
		for (freeshort2=0;freeshort2<numRooms;freeshort2++){
			memcpy(&freeshort1, bytelist+p_AlternateRoom[freeshort2]+2, 2);
			freeshort1|=0x0008;
			memcpy(bytelist+p_AlternateRoom[freeshort2]+2, &freeshort1, 2);
		}
	} else {
		freeshort1 = strtol(args[3], NULL, 10);
		memcpy(&freeshort2, bytelist+p_AlternateRoom[freeshort1]+2, 2);
		freeshort2|=0x0008;
		memcpy(bytelist+p_AlternateRoom[freeshort1]+2, &freeshort2, 2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_nosky(char *bytelist, char *args[], unsigned p_AlternateRoom[], unsigned short numRooms, unsigned fsize){
	// This function makes the sky invisible from this room. The syntax is "trmod [FILE] NOSKY [Room]"
	unsigned freeshort1;
	unsigned freeshort2;
	if (!_strnicmp(args[3],"all",3)) {
		for (freeshort2=0;freeshort2<numRooms;freeshort2++){
			memcpy(&freeshort1, bytelist+p_AlternateRoom[freeshort2]+2, 2);
			freeshort1&=0xFFF7;
			memcpy(bytelist+p_AlternateRoom[freeshort2]+2, &freeshort1, 2);
		}
	} else {
		freeshort1 = strtol(args[3], NULL, 10);
		memcpy(&freeshort2, bytelist+p_AlternateRoom[freeshort1]+2, 2);
		freeshort2&=0xFFF7;
		memcpy(bytelist+p_AlternateRoom[freeshort1]+2, &freeshort2, 2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_wind(char *bytelist, char *args[], unsigned p_AlternateRoom[], unsigned short numRooms, unsigned fsize){
	// This function makes the wind blow in this room. The syntax is "trmod [FILE] WIND [Room]"
	unsigned freeshort1;
	unsigned freeshort2;
	if (!_strnicmp(args[3],"all",3)) {
		for (freeshort2=0;freeshort2<numRooms;freeshort2++){
			memcpy(&freeshort1, bytelist+p_AlternateRoom[freeshort2]+2, 2);
			freeshort1|=0x0020;
			memcpy(bytelist+p_AlternateRoom[freeshort2]+2, &freeshort1, 2);
		}
	} else {
		freeshort1 = strtol(args[3], NULL, 10);
		memcpy(&freeshort2, bytelist+p_AlternateRoom[freeshort1]+2, 2);
		freeshort2|=0x0020;
		memcpy(bytelist+p_AlternateRoom[freeshort1]+2, &freeshort2, 2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_nowind(char *bytelist, char *args[], unsigned p_AlternateRoom[], unsigned short numRooms, unsigned fsize){
	// This function makes the wind not blow in this room. The syntax is "trmod [FILE] NOWIND [Room]"
	unsigned freeshort1;
	unsigned freeshort2;
	if (!_strnicmp(args[3],"all",3)) {
		for (freeshort2=0;freeshort2<numRooms;freeshort2++){
			memcpy(&freeshort1, bytelist+p_AlternateRoom[freeshort2]+2, 2);
			freeshort1&=0xFFDF;
			memcpy(bytelist+p_AlternateRoom[freeshort2]+2, &freeshort1, 2);
		}
	} else {
		freeshort1 = strtol(args[3], NULL, 10);
		memcpy(&freeshort2, bytelist+p_AlternateRoom[freeshort1]+2, 2);
		freeshort2&=0xFFDF;
		memcpy(bytelist+p_AlternateRoom[freeshort1]+2, &freeshort2, 2);
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_get_geometry(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned short numRooms, unsigned fsize){
	/*
	This function writes the geometry of a room to a text file. The syntax is "trmod [FILE] GET GEOMETRY [Room] [Text File]"
	The format is as follows:
	______________________________________________________________
	Vertex(Room,X,Z,Y,Lighting1,Lighting 2,Attributes)
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
	______________________________________________________________
	If one replaces the room number with the word "all", it will list all geometry in the level.
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
			curpos+=2;
			while (freeushort2>0){
				memcpy(&freeushort3,bytelist+curpos,2);
				fprintf(file,"Vertex(%u,%u,",freeushort1,freeushort3);
				memcpy(&freeushort3,bytelist+curpos+4,2);
				fprintf(file,"%u,",freeushort3);
				memcpy(&freeshort1,bytelist+curpos+2,2);
				fprintf(file,"%i,",(roomY[freeushort1]-freeshort1));
				memcpy(&freeushort3,bytelist+curpos+6,2);
				fprintf(file,"%u,",freeushort3);
				memcpy(&freeushort3,bytelist+curpos+10,2);
				fprintf(file,"%u,",freeushort3);
				memcpy(&freeushort3,bytelist+curpos+8,2);
				fprintf(file,"%04X)\n",freeushort3);
				curpos+=12;
				freeushort2--;
			}
			memcpy(&freeushort2,bytelist+curpos,2);
			curpos+=2;
			while (freeushort2>0){
				memcpy(&freeushort3,bytelist+curpos,2);
				fprintf(file,"Rectangle(%u,%u,",freeushort1,freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+2,2);
				fprintf(file,"%u,",freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+4,2);
				fprintf(file,"%u,",freeushort3+1);
				memcpy(&freeushort3,bytelist+curpos+6,2);
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
			fprintf(file,"RoomLight(%u,%i,",freeushort1,freeushort2);
			memcpy(&freeushort2,bytelist+curpos+2,2);
			fprintf(file,"%i,",freeushort2);
			memcpy(&freeushort2,bytelist+curpos+4,2);
			fprintf(file,"%i)\n",freeushort2);
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
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos,2);
			fprintf(file,"Vertex(%u,%u,",freeushort1,freeushort3);
			memcpy(&freeushort3,bytelist+curpos+4,2);
			fprintf(file,"%u,",freeushort3);
			memcpy(&freeshort1,bytelist+curpos+2,2);
			fprintf(file,"%i,",(roomY[freeushort1]-freeshort1));
			memcpy(&freeushort3,bytelist+curpos+6,2);
			fprintf(file,"%u,",freeushort3);
			memcpy(&freeushort3,bytelist+curpos+10,2);
			fprintf(file,"%u,",freeushort3);
			memcpy(&freeushort3,bytelist+curpos+8,2);
			fprintf(file,"%04X)\n",freeushort3);
			curpos+=12;
			freeushort2--;
		}
		memcpy(&freeushort2,bytelist+curpos,2);
		curpos+=2;
		while (freeushort2>0){
			memcpy(&freeushort3,bytelist+curpos,2);
			fprintf(file,"Rectangle(%u,%u,",freeushort1,freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+2,2);
			fprintf(file,"%u,",freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+4,2);
			fprintf(file,"%u,",freeushort3+1);
			memcpy(&freeushort3,bytelist+curpos+6,2);
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
		fprintf(file,"RoomLight(%u,%i,",freeushort1,freeushort2);
		memcpy(&freeushort2,bytelist+curpos+2,2);
		fprintf(file,"%i,",freeushort2);
		memcpy(&freeushort2,bytelist+curpos+4,2);
		fprintf(file,"%i)\n",freeushort2);
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
void tr2pc_move_room(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumItems, unsigned fsize){
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
	freeuint1=p_NumVertices[strtol(args[4], NULL, 10)]+2;
	while (freeushort1>0){ // Vertices
		memcpy(&freeshort1,bytelist+freeuint1+2,2);
		freeshort1-=freeint3;
		memcpy(bytelist+freeuint1+2,&freeshort1,2);
		freeuint1+=12;
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
	freeuint1+=6;
	freechar1=1;
	if (argc>8){
		if (!_strnicmp(args[8],"raw",3)) freechar1=0;
	}
	if (freechar1==1){
		memcpy(&freeushort1, bytelist+freeuint1, 2);
		freeuint1+=2;
		freeuint2=freeuint1+(freeushort1*24);
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
			freeuint1+=24;
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
		freeuint2=freeuint1+(freeint4*24);
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
			freeuint1+=24;
		}
	}
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_add_room(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned p_NumFloorData, unsigned fsize){
	// This function adds an empty room to a level. The syntax is "trmod [FILE] ADD ROOM"
	char *bytelist2 = realloc(bytelist,(fsize+44));
	bytelist=bytelist2;
	memmove(bytelist+p_NumFloorData+48,bytelist+p_NumFloorData,(fsize-p_NumFloorData));
	fsize+=48;
	memset(bytelist+p_NumFloorData,0,48);
	memset(bytelist+p_NumFloorData+16,4,1);
	memset(bytelist+p_NumFloorData+44,255,2);
	unsigned short freeushort1;
	memcpy(&freeushort1,bytelist+p_NumVertices[0]-22,2);
	freeushort1++;
	memcpy(bytelist+p_NumVertices[0]-22,&freeushort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_add_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize){
	// This function adds a vertex. "trmod [FILE] ADD VERTEX [Room] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]"
	char *temp=malloc(12);
	unsigned freeuint1;
	unsigned short freeushort1 = strtol(args[5], NULL, 10);
	memcpy(temp,&freeushort1,2);
	short freeshort1 = (roomY[strtol(args[4], NULL, 10)]-strtol(args[7], NULL, 10));
	memcpy(temp+2,&freeshort1,2);
	freeushort1 = strtol(args[6], NULL, 10);
	memcpy(temp+4,&freeushort1,2);
	freeshort1 = strtol(args[8], NULL, 10);
	memcpy(temp+6,&freeshort1,2);
	freeshort1 = strtol(args[10], NULL, 16);
	memcpy(temp+8,&freeshort1,2);
	freeshort1 = strtol(args[9], NULL, 10);
	memcpy(temp+10,&freeshort1,2);
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	bytelist=insertrange(bytelist,p_NumVertices[strtol(args[4], NULL, 10)]+2+(freeushort1*12),12,temp,fsize);
	fsize+=12;
	freeushort1++;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)],&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1+=6;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_replace_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize){
	// This function replaces a vertex. "trmod [FILE] REPLACE VERTEX [Room] [Vertex] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]"
	unsigned freeuint1=p_NumVertices[strtol(args[4], NULL, 10)]-10+(strtol(args[5], NULL, 10)*12);
	unsigned short freeushort1 = strtol(args[6], NULL, 10);
	memcpy(bytelist+freeuint1,&freeushort1,2);
	short freeshort1 = (roomY[strtol(args[4], NULL, 10)]-strtol(args[8], NULL, 10));
	memcpy(bytelist+freeuint1+2,&freeshort1,2);
	freeushort1 = strtol(args[7], NULL, 10);
	memcpy(bytelist+freeuint1+4,&freeushort1,2);
	freeshort1 = strtol(args[9], NULL, 10);
	memcpy(bytelist+freeuint1+6,&freeshort1,2);
	freeshort1 = strtol(args[11], NULL, 16);
	memcpy(bytelist+freeuint1+8,&freeshort1,2);
	freeshort1 = strtol(args[10], NULL, 10);
	memcpy(bytelist+freeuint1+10,&freeshort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_remove_vertex(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function removes a vertex. "trmod [FILE] REMOVE VERTEX [Room] [Vertex] (RAW)"
	unsigned short freeushort1;
	unsigned freeuint1=p_NumVertices[strtol(args[4], NULL, 10)]-10+(strtol(args[5], NULL, 10)*12);
	fsize=removerange(bytelist,freeuint1,12,fsize);
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	freeushort1--;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)],&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1-=6;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	char freechar1=1;
	if (argc>6){
		if (!_strnicmp(args[6],"raw",3)) freechar1=0;
	}
	if (freechar1==1){
		unsigned short freeushort2=strtol(args[5], NULL, 10)-1;
		memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
		unsigned curpos=(p_NumVertices[strtol(args[4], NULL, 10)]+2+(freeushort1*12));
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
void tr2pc_add_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function adds a rectangle. "trmod [FILE] ADD RECTANGLE [Room] [Vertex 1] [Vertex 2] [Vertex 3] [Vertex 4] [Texture]"
	char *temp=malloc(10);
	unsigned freeuint1;
	unsigned short freeushort1 = strtol(args[5], NULL, 10)-1;
	memcpy(temp,&freeushort1,2);
	freeushort1 = strtol(args[6], NULL, 10)-1;
	memcpy(temp+2,&freeushort1,2);
	freeushort1 = strtol(args[7], NULL, 10)-1;
	memcpy(temp+4,&freeushort1,2);
	freeushort1 = strtol(args[8], NULL, 10)-1;
	memcpy(temp+6,&freeushort1,2);
	freeushort1 = strtol(args[9], NULL, 10);
	memcpy(temp+8,&freeushort1,2);
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	curpos+=2+(freeushort1*12);
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
void tr2pc_replace_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function replaces a rectangle. "trmod [FILE] REPLACE RECTANGLE [Room] [Rectangle] [Vertex 1] [Vertex 2] [Vertex 3] [Vertex 4] [Texture]"
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)],2);
	curpos+=(freeushort1*12)-6+(strtol(args[5], NULL, 10)*10);
	freeushort1 = strtol(args[6], NULL, 10)-1;
	memcpy(bytelist+curpos,&freeushort1,2);
	freeushort1 = strtol(args[7], NULL, 10)-1;
	memcpy(bytelist+curpos+2,&freeushort1,2);
	freeushort1 = strtol(args[8], NULL, 10)-1;
	memcpy(bytelist+curpos+4,&freeushort1,2);
	freeushort1 = strtol(args[9], NULL, 10)-1;
	memcpy(bytelist+curpos+6,&freeushort1,2);
	freeushort1 = strtol(args[10], NULL, 10);
	memcpy(bytelist+curpos+8,&freeushort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_remove_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function removes a rectangle. "trmod [FILE] REMOVE RECTANGLE [Room] [Rectangle]"
	unsigned freeuint1;
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=(freeushort1*12)-6+(strtol(args[5], NULL, 10)*10);
	fsize=removerange(bytelist,curpos,10,fsize);
	curpos=p_NumVertices[strtol(args[4], NULL, 10)]+2+(freeushort1*12);
	memcpy(&freeushort1,bytelist+curpos,2);
	freeushort1--;
	memcpy(bytelist+curpos,&freeushort1,2);
	memcpy(&freeuint1,bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,4);
	freeuint1-=5;
	memcpy(bytelist+p_NumVertices[strtol(args[4], NULL, 10)]-4,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_add_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
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
	curpos+=2+(freeushort1*12);
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
void tr2pc_replace_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function replaces a triangle. "trmod [FILE] REPLACE TRIANGLE [Room] [Triangle] [Vertex 1] [Vertex 2] [Vertex 3] [Texture]"
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=2+(freeushort1*12);
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
void tr2pc_remove_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize){
	// This function removes a triangle. "trmod [FILE] REMOVE TRIANGLE [Room] [Triangle]"
	unsigned freeuint1;
	unsigned short freeushort1;
	unsigned curpos=p_NumVertices[strtol(args[4], NULL, 10)];
	memcpy(&freeushort1,bytelist+curpos,2);
	curpos+=2+(freeushort1*12);
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
void tr2pc_get_zones(char *bytelist, char *args[], unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned fsize){
	/*
	This function produces a list of all Zones and Overlaps. "trmod [FILE] GET ZONES [OUTPUT FILE]"
	Zone(Xmin,Xmax,Zmin,Zmax,TrueFloor,Overlap_Offset,GroundZone1_Normal,GroundZone2_Normal,GroundZone3_Normal,GroundZone4_Normal,FlyZone_Normal,GroundZone1_Alternate,GroundZone2_Alternate,GroundZone3_Alternate,GroundZone4_Alternate,FlyZone_Alternate))
	Overlap(Offset)(Zone,Zone,Zone...)
	*/
	unsigned freeuint1 = p_NumBoxes+4;
	unsigned freeuint2;
	unsigned freeuint3;
	short freeshort1;
	unsigned short freeushort1;
	memcpy(&freeuint2,bytelist+p_NumOverlaps,4);
	freeuint2=p_NumOverlaps+4+(freeuint2*2);
	FILE *file = fopen(args[4],"w");
	while (freeuint1<p_NumOverlaps){
		freeuint3=0;
		memcpy(&freeuint3,bytelist+freeuint1+2,1);
		freeuint3<<=10;
		fprintf(file,"Zone(%u,",freeuint3);
		freeuint3=0;
		memcpy(&freeuint3,bytelist+freeuint1+3,1);
		freeuint3<<=10;
		fprintf(file,"%u,",freeuint3);
		freeuint3=0;
		memcpy(&freeuint3,bytelist+freeuint1,1);
		freeuint3<<=10;
		fprintf(file,"%u,",freeuint3);
		freeuint3=0;
		memcpy(&freeuint3,bytelist+freeuint1+1,1);
		freeuint3<<=10;
		fprintf(file,"%u,",freeuint3);
		memcpy(&freeshort1,bytelist+freeuint1+4,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint1+6,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+2,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+4,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+6,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+8,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+10,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+12,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+14,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+16,2);
		fprintf(file,"%i,",freeshort1);
		memcpy(&freeshort1,bytelist+freeuint2+18,2);
		fprintf(file,"%i)\n",freeshort1);
		freeuint1+=8;
		freeuint2+=20;
	}
	memcpy(&freeuint2,bytelist+p_NumOverlaps,4);
	freeuint2=p_NumOverlaps+4+(freeuint2*2);
	freeuint1=p_NumOverlaps+4;
	freeshort1=1;
	while (freeuint1<freeuint2){
		if (freeshort1==1){
			fprintf(file,"Overlap(%u)(",(freeuint1-p_NumOverlaps-4)/2);
			freeshort1=0;
		}
		memcpy(&freeushort1,bytelist+freeuint1,2);
		fprintf(file,"%u",freeushort1&0x7FFF);
		if (freeushort1>=32768){
			fprintf(file,")\n");
			freeshort1=1;
		}else{
			fprintf(file,",");
		}
		freeuint1+=2;
	}
	fclose(file);
}
void tr2pc_add_zone(char *bytelist, char *args[], unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned fsize){
	// This function adds a zone. "trmod [FILE] ADD ZONE [Xmin] [Xmax] [Zmin] [Zmax] [TrueFloor] [Overlap_offset] [GroundZone 1] [GroundZone 2] [GroundZone 3] [GroundZone 4] [Fly Zone] [Alt. GroundZone 1] [Alt. GroundZone 2] [Alt. GroundZone 3] [Alt. GroundZone 4] [Alt. Fly Zone]"
	char *box=malloc(8);
	char *zone=malloc(20);
	unsigned freeuint1;
	unsigned freeuint2;
	char freechar1;
	short freeshort1;
	freechar1=strtol(args[6], NULL, 10)>>10;
	memcpy(box,&freechar1,1);
	freechar1=strtol(args[7], NULL, 10)>>10;
	memcpy(box+1,&freechar1,1);
	freechar1=strtol(args[4], NULL, 10)>>10;
	memcpy(box+2,&freechar1,1);
	freechar1=strtol(args[5], NULL, 10)>>10;
	memcpy(box+3,&freechar1,1);
	freeshort1=strtol(args[8], NULL, 10);
	memcpy(box+4,&freeshort1,2);
	freeshort1=strtol(args[9], NULL, 10);
	memcpy(box+6,&freeshort1,2);
	freeshort1=strtol(args[10], NULL, 10);
	memcpy(zone,&freeshort1,2);
	freeshort1=strtol(args[11], NULL, 10);
	memcpy(zone+2,&freeshort1,2);
	freeshort1=strtol(args[12], NULL, 10);
	memcpy(zone+4,&freeshort1,2);
	freeshort1=strtol(args[13], NULL, 10);
	memcpy(zone+6,&freeshort1,2);
	freeshort1=strtol(args[14], NULL, 10);
	memcpy(zone+8,&freeshort1,2);
	freeshort1=strtol(args[15], NULL, 10);
	memcpy(zone+10,&freeshort1,2);
	freeshort1=strtol(args[16], NULL, 10);
	memcpy(zone+12,&freeshort1,2);
	freeshort1=strtol(args[17], NULL, 10);
	memcpy(zone+14,&freeshort1,2);
	freeshort1=strtol(args[18], NULL, 10);
	memcpy(zone+16,&freeshort1,2);
	freeshort1=strtol(args[19], NULL, 10);
	memcpy(zone+18,&freeshort1,2);
	memcpy(&freeuint1,bytelist+p_NumOverlaps,4);
	memcpy(&freeuint2,bytelist+p_NumBoxes,4);
	freeuint1=p_NumOverlaps+4+(freeuint1*2)+(freeuint2*20);
	bytelist=insertrange(bytelist,freeuint1,20,zone,fsize);
	fsize+=20;
	bytelist=insertrange(bytelist,p_NumOverlaps,8,box,fsize);
	fsize+=8;
	memcpy(&freeuint1,bytelist+p_NumBoxes,4);
	freeuint1++;
	memcpy(bytelist+p_NumBoxes,&freeuint1,4);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_replace_zone(char *bytelist, char *args[], unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned fsize){
	// This function replaces a zone. "trmod [FILE] REPLACE ZONE [Zone] [Xmin] [Xmax] [Zmin] [Zmax] [TrueFloor] [Overlap_offset] [GroundZone 1] [GroundZone 2] [GroundZone 3] [GroundZone 4] [Fly Zone] [Alt. GroundZone 1] [Alt. GroundZone 2] [Alt. GroundZone 3] [Alt. GroundZone 4] [Alt. Fly Zone]"
	char freechar1;
	unsigned freeuint2;
	unsigned freeuint3=strtol(args[4],NULL,10);
	memcpy(&freeuint2,bytelist+p_NumOverlaps,4);
	freeuint2=p_NumOverlaps+4+(freeuint2*2);
	short freeshort1;
	unsigned freeushort1;
	freechar1=strtol(args[7], NULL, 10)>>10;
	memcpy(bytelist+p_NumBoxes+4+(freeuint3*8),&freechar1,1);
	freechar1=strtol(args[8], NULL, 10)>>10;
	memcpy(bytelist+p_NumBoxes+4+(freeuint3*8)+1,&freechar1,1);
	freechar1=strtol(args[5], NULL, 10)>>10;
	memcpy(bytelist+p_NumBoxes+4+(freeuint3*8)+2,&freechar1,1);
	freechar1=strtol(args[6], NULL, 10)>>10;
	memcpy(bytelist+p_NumBoxes+4+(freeuint3*8)+3,&freechar1,1);
	freeshort1=strtol(args[9], NULL, 10);
	memcpy(bytelist+p_NumBoxes+4+(freeuint3*8)+4,&freeshort1,2);
	freeshort1=strtol(args[10], NULL, 10);
	memcpy(bytelist+p_NumBoxes+4+(freeuint3*8)+6,&freeshort1,2);
	freeushort1=strtol(args[11], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20),&freeushort1,2);
	freeushort1=strtol(args[12], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+2,&freeushort1,2);
	freeushort1=strtol(args[13], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+4,&freeushort1,2);
	freeushort1=strtol(args[14], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+6,&freeushort1,2);
	freeushort1=strtol(args[15], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+8,&freeushort1,2);
	freeushort1=strtol(args[16], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+10,&freeushort1,2);
	freeushort1=strtol(args[17], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+12,&freeushort1,2);
	freeushort1=strtol(args[18], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+14,&freeushort1,2);
	freeushort1=strtol(args[19], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+16,&freeushort1,2);
	freeushort1=strtol(args[20], NULL, 10);
	memcpy(bytelist+freeuint2+(freeuint3*20)+18,&freeushort1,2);
	writeFile(args[1],bytelist, fsize);
}
void tr2pc_get_offset(char *bytelist, char *args[], unsigned argc, unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumItems, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumDemoData, unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned p_NumSoundSources, unsigned fsize){
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
		curpos+=2+(freeushort1*12);
		if (!_strnicmp(args[4],"numrectangles",13)) printf("%X\n",curpos);
		memcpy(&freeushort1, bytelist+curpos, 2);
		curpos+=2+(freeushort1*10);
		if (!_strnicmp(args[4],"numtriangles",12)) printf("%X\n",curpos);
	}
	if (!_strnicmp(args[4],"numsprites",10)&&argc>5) printf("%X\n",(p_NumSprites[strtol(args[5],NULL,10)]));
	if (!_strnicmp(args[4],"numdoors",8)){
		curpos=p_NumSprites[strtol(args[5],NULL,10)];
		memcpy(&freeushort1, bytelist+curpos, 2);
		curpos+=2+(freeushort1*8);
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
		curpos+=4+(freeuint1*18);
		if (!_strnicmp(args[4],"numstaticmeshes",15)&&argc==5) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*32);
		if (!_strnicmp(args[4],"numobjecttextures",17)) printf("%X\n",curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*20);
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
		curpos+=(freeuint1*20);
		if (!_strnicmp(args[4],"numanimatedtextures",19)) printf("%X\n",curpos);
	}
	if (!_strnicmp(args[4],"numitems",8)) printf("%X\n",p_NumItems);
	if (!_strnicmp(args[4],"lightmap",8)||!_strnicmp(args[4],"numcinematicframes",18)){
		curpos=p_NumItems;
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*24);
		if (!_strnicmp(args[4],"lightmap",8)) printf("%X\n",curpos);
		if (!_strnicmp(args[4],"numcinematicframes",18)) printf("%X\n",(curpos+8192));
	}
	if (!_strnicmp(args[4],"numdemodata",11)) printf("%X\n",p_NumDemoData);
	if (!_strnicmp(args[4],"soundmap",8)||!_strnicmp(args[4],"numsounddetails",15)||!_strnicmp(args[4],"numsampleindices",16)){
		curpos=p_NumDemoData;
		memcpy(&freeushort1, bytelist+curpos, 2);
		curpos+=2+freeushort1;
		if (!_strnicmp(args[4],"soundmap",8)) printf("%X\n",curpos);
		curpos+=740;
		if (!_strnicmp(args[4],"numsounddetails",15)) printf("%X\n", curpos);
		memcpy(&freeuint1, bytelist+curpos, 4);
		curpos+=4+(freeuint1*8);
		if (!_strnicmp(args[4],"numsampleindices",16)) printf("%X\n",curpos);
	}
}

// int selection // -1 for all, 0 - (numTexTiles-1) for an individual texture tile
void tr2pc_extract_textile8(char* bytelist, char* args[], unsigned numTexTiles, unsigned* p_TexTiles8, BYTE* palette8, int selection)
{
	if (selection < -1 || selection >= (int)numTexTiles)
	{
		printf("ERROR: Textile selection must be between \"0\" and \"%d\" or \"all\", argument was \"%d\"", numTexTiles - 1, selection);
		return 0;
	}

	printf("Extracting 8-bit textile %d...\n", selection);
	// This function extracts a texture tile from the level into a bitmap file. The syntax is "trmod [FILE] EXTRACT TEXTILE [#/All]".

	printf("Writing \"palette8.bmp\"...\n");
	writeBitmap(palette8, "palette8.bmp", 16, 16);

	const unsigned w = 256;
	const unsigned h = 256;

	for (int t = (selection == -1 ? 0 : selection); t <= (selection == -1 ? numTexTiles - 1 : selection); ++t)
	{
		BYTE* img = malloc(3 * w * h);
		memset(img, 0, 3 * w * h); // Fill the whole image with 0s

		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				unsigned int curpos = j * w + i;
				unsigned char pixelKey;
				unsigned char r;
				unsigned char g;
				unsigned char b;

				memcpy(&pixelKey, bytelist + p_TexTiles8[t] + curpos, 1);

				if (pixelKey != 0)
				{
					memcpy(&r, palette8 + pixelKey * 3 + 2, 1);
					memcpy(&g, palette8 + pixelKey * 3 + 1, 1);
					memcpy(&b, palette8 + pixelKey * 3 + 0, 1);
				}
				else // pixelKey == 0 // Reserved for pure-magenta aka transparent
				{
					r = 255;
					g = 0;
					b = 255;
				}

				img[i * 3 + j * w * 3 + 2] = r;
				img[i * 3 + j * w * 3 + 1] = g;
				img[i * 3 + j * w * 3 + 0] = b;
			}
		}

		unsigned fnameLen = 17 + (t < 10 ? 1 : 2);
		char* filename = malloc(fnameLen);
		snprintf(filename, fnameLen, "textile%u_8bit.bmp", t);
		printf("Writing \"%s\"...\n", filename);
		writeBitmap(img, filename, 256, 256);

		free(img);
		free(filename);
	}
}

// This function replaces a texture tile in the level from a bitmap file. The syntax is "trmod [FILE] REPLACE TEXTILE [#] [FILENAME.BMP]".
void tr2pc_replace_textile8(char* bytelist, char* args[], unsigned numTexTiles, unsigned* p_TexTiles, BYTE* palette8, unsigned fsize)
{
	unsigned int selection = atoi(args[4]);
	char* filename = args[5];

	if (selection < 0 || selection >= numTexTiles)
	{
		printf("ERROR: Textile selection must be between \"0\" and \"%d\", argument was \"%d\"", numTexTiles - 1, selection);
		return 0;
	}

	printf("Replacing 8-bit textile %d...\n", selection);

	const short w = 256;
	const short h = 256;
	unsigned memorySize = 3 * w * h;

	BYTE* bitmapImage = readBitmapFile(filename);
	if (bitmapImage == NULL)
	{
		printf("ERROR: Could not read bitmap.\n");
		return 0;
	}

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			unsigned int curpos = j * w + i;
			BYTE r;
			BYTE g;
			BYTE b;
			BYTE pixelKey;

			memcpy(&r, bitmapImage + curpos * 3 + 2, 1);
			memcpy(&g, bitmapImage + curpos * 3 + 1, 1);
			memcpy(&b, bitmapImage + curpos * 3 + 0, 1);

			if (r == 255 && g == 0 && b == 255)
			{
				pixelKey = 0; // Reserved for pure-magenta aka transparent
			}
			else
			{
				pixelKey = findPixelKey(palette8, r, g, b);
			}

			unsigned int curposFlip = ((h - 1 - j) * w) + i; // Bitmap rows are stored bottom-up
			memcpy(bytelist + p_TexTiles[selection] + curposFlip, &pixelKey, 1);
		}
	}

	writeFile(args[1], bytelist, fsize);

	free(bitmapImage);
}

// tr2_textile16 Textile16[NumTextiles]; // 16-bit (ARGB) textiles (NumTextiles * 131072 bytes)
// The 16-bit textile array, which contains[tr_textile16] structures, specifies colours using 16 - bit ARGB,
// where the highest bit (0x8000) is a crude alpha channel (really just a simple transparency: 0==transparent, 1==opaque).
// The next 5 bits(0x7C00) specify the red channel, the next 5 bits(0x03E0) specify the green channel,
// and the last 5 bits(0x001F) specify the blue channel, each on a scale from 0..31.
void tr2pc_extract_textile(char* bytelist, char* args[], unsigned numTexTiles, unsigned* p_TexTiles16, int selection)
{
	if (selection < -1 || selection >= (int)numTexTiles)
	{
		printf("ERROR: Textile selection must be between \"0\" and \"%d\" or \"all\", argument was \"%d\"", numTexTiles - 1, selection);
		return 0;
	}

	if (selection == -1)
	{
		printf("Extracting all 16-bit textiles to 24-bit bitmap (BMP)...");
	}
	{
		printf("Extracting 16-bit textile %d to 24-bit bitmap (BMP)...\n", selection);
	}

	// This function extracts a texture tile from the level into a bitmap file. The syntax is "trmod [FILE] EXTRACT TEXTILE [#/All]".

	const unsigned short w = 256;
	const unsigned short h = 256;

	for (int t = (selection == -1 ? 0 : selection); t <= (selection == -1 ? numTexTiles - 1 : selection); ++t)
	{
		BYTE* img = malloc(3 * w * h);

		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				unsigned int curpos = (j * w + i) * 2;
				unsigned short pixel16;
				BYTE a;
				BYTE r;
				BYTE g;
				BYTE b;

				memcpy(&pixel16, bytelist + p_TexTiles16[t] + curpos, 2);

				// Crack it
				a = pixel16 >> 15;
				r = (pixel16 >> 10) & 0b11111; // 5-bit red channel
				g = (pixel16 >> 5) & 0b11111; // 5-bit green channel
				b = pixel16 & 0b11111; // 5-bit blue channel

				if (a == 0)
				{
					// TR2 transparency - full magenta
					img[i * 3 + j * w * 3 + 2] = 255; // 8-bit red
					img[i * 3 + j * w * 3 + 1] = 0;   // 8-bit green
					img[i * 3 + j * w * 3 + 0] = 255; // 8-bit blue
				}
				else
				{
					// Full color / full opaque
					img[i * 3 + j * w * 3 + 2] = r * 255 / 31; // Convert to 8-bit red
					img[i * 3 + j * w * 3 + 1] = g * 255 / 31; // Convert to 8-bit green
					img[i * 3 + j * w * 3 + 0] = b * 255 / 31; // Convert to 8-bit blue
				}
			}
		}

		unsigned fnameLen = 12 + (t < 10 ? 1 : 2);
		char* filename = malloc(fnameLen);
		snprintf(filename, fnameLen, "textile%u.bmp", t);
		printf("Writing \"%s\"...\n", filename);
		writeBitmap(img, filename, 256, 256);

		free(img);
		free(filename);
	}
}

// This function replaces a texture tile in the level from a bitmap file. The syntax is "trmod [FILE] REPLACE TEXTILE [#] [FILENAME.BMP]".
// The 16-bit textile array, which contains[tr_textile16] structures, specifies colours using 16 - bit ARGB,
// where the highest bit (0x8000) is a crude alpha channel (really just a simple transparency: 0==transparent, 1==opaque).
// The next 5 bits(0x7C00) specify the red channel, the next 5 bits(0x03E0) specify the green channel,
// and the last 5 bits(0x001F) specify the blue channel, each on a scale from 0..31.
void tr2pc_replace_textile(char* bytelist, char* args[], unsigned numTexTiles, unsigned* p_TexTiles, unsigned fsize)
{
	unsigned int selection = atoi(args[4]);
	char* filename = args[5];

	if (selection < 0 || selection >= numTexTiles)
	{
		printf("ERROR: Textile selection must be between \"0\" and \"%d\", argument was \"%d\"", numTexTiles - 1, selection);
		return 0;
	}

	printf("Replacing 16-bit textile %d with 24-bit bitmap (BMP)...\n", selection);

	const short w = 256;
	const short h = 256;

	BYTE* bitmapImage = readBitmapFile(filename);
	if (bitmapImage == NULL)
	{
		printf("ERROR: Could not read 24-bit bitmap \"%s\".\n", filename);
		return 0;
	}

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			unsigned int curpos = j * w + i;
			BYTE a;
			BYTE r;
			BYTE g;
			BYTE b;
			unsigned short pixel16;
			
			memcpy(&r, bitmapImage + curpos * 3 + 2, 1);
			memcpy(&g, bitmapImage + curpos * 3 + 1, 1);
			memcpy(&b, bitmapImage + curpos * 3 + 0, 1);

			if (r == 255 && g == 0 && b == 255)
			{
				pixel16 = 0; // Reserved for pure-magenta aka transparent
			}
			else
			{
				a = 1; // Full color / full opaque
				r = r * 31 / 255; // Convert to 5-bit red
				g = g * 31 / 255; // Convert to 5-bit green
				b = b * 31 / 255; // Convert to 5-bit blue

				// Pack it
				pixel16 = (a << 15) | (r << 10) | (g << 5) | b;
			}

			unsigned int curposFlip = (((h - 1 - j) * w) + i) * 2; // Bitmap rows are stored bottom-up
			memcpy(bytelist + p_TexTiles[selection] + curposFlip, &pixel16, 2);
		}
	}

	writeFile(args[1], bytelist, fsize);

	free(bitmapImage);
}
