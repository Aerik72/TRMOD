#ifndef TR1PC_H_INCLUDED
#define TR1PC_H_INCLUDED

typedef unsigned char BYTE;

void tr1pc_main(int argc, char *args[], char *bytelist, unsigned fsize);
void tr1pc_list(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumBoxes, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned short numRooms, unsigned fsize);
void tr1pc_add_item(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumItems, unsigned fsize);
void tr1pc_replace_item(char *bytelist, int argc, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumItems, unsigned fsize);
void tr1pc_remove_item(char *bytelist, int argc, char *args[], unsigned p_NumZSector[], unsigned p_NumFloorData, unsigned p_NumItems, unsigned short numRooms, unsigned fsize);
void tr1pc_add_staticmesh(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize);
void tr1pc_replace_staticmesh(char *bytelist, int argc, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize);
void tr1pc_remove_staticmesh(char *bytelist, char *args[], unsigned p_NumStaticMeshes[], unsigned fsize);
void tr1pc_add_sprite(char *bytelist, char *args[], int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize);
void tr1pc_replace_sprite(char *bytelist, char *args[], unsigned argc, int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize);
void tr1pc_remove_sprite(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned fsize);
void tr1pc_add_soundsource(char *bytelist, char *args[], unsigned p_NumSoundSources, unsigned fsize);
void tr1pc_replace_soundsource(char *bytelist, int argc, char *args[], unsigned p_NumSoundSources, unsigned fsize);
void tr1pc_remove_soundsource(char *bytelist, char *args[], unsigned p_NumSoundSources, unsigned fsize);
void tr1pc_add_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize);
void tr1pc_replace_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize);
void tr1pc_remove_light(char *bytelist, char *args[], unsigned p_NumLights[], unsigned fsize);
void tr1pc_replace_floordata(char *bytelist, char *args[], int argc, unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumZSector[], unsigned p_NumFloorData, unsigned p_NumCameras, unsigned fsize);
void tr1pc_remove_floordata(char *bytelist, char *args[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_remove_all(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumFloorData, unsigned p_NumCameras, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned p_NumBoxes, unsigned short numRooms, unsigned fsize);
void tr1pc_alternate_room(char *bytelist, char *args[], unsigned p_AlternateRoom[], unsigned fsize);
void tr1pc_roomlight(char *bytelist, char *args[], unsigned p_NumLights[], unsigned short numRooms, unsigned fsize);
void tr1pc_water(char *bytelist, char *args[], unsigned p_AlternateRoom[], unsigned short numRooms, unsigned fsize);
void tr1pc_nowater(char *bytelist, char *args[], unsigned p_AlternateRoom[], unsigned short numRooms, unsigned fsize);
void tr1pc_get_samplenumber(char *bytelist, char *args[], unsigned p_NumSoundDetails, unsigned fsize);
void tr1pc_extract_sample(char *bytelist, char *args[], unsigned p_NumSampleIndices, unsigned p_NumSamples, unsigned fsize);
void tr1pc_replace_sample(char *bytelist, char *args[], unsigned p_NumSampleIndices, unsigned p_NumSamples, unsigned fsize);
void tr1pc_extract_demo(char *bytelist, char *args[], unsigned p_NumDemoData);
void tr1pc_replace_demo(char *bytelist, char *args[], unsigned p_NumDemoData, unsigned fsize);
void tr1pc_convert(char *bytelist, char * args[], unsigned p_NumCameras, unsigned p_NumItems, unsigned fsize);
void tr1pc_get_geometry(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned short numRooms, unsigned fsize);
void tr1pc_move_room(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumItems, unsigned fsize);
void tr1pc_get_roomsize(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_resize_room(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_add_room(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned p_NumFloorData, unsigned fsize);
void tr1pc_get_floorheight(char *bytelist, char *args[], int roomY[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_get_ceilingheight(char *bytelist, char *args[], int roomY[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_set_floorheight(char *bytelist, char *args[], int roomY[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_set_ceilingheight(char *bytelist, char *args[], int roomY[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_add_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize);
void tr1pc_replace_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize);
void tr1pc_remove_vertex(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1pc_add_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1pc_replace_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1pc_remove_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1pc_add_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1pc_replace_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1pc_remove_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1pc_add_viewport(char *bytelist, char *args[], int roomY[], unsigned p_NumSprites[], unsigned fsize);
void tr1pc_replace_viewport(char *bytelist, char *args[], int roomY[], unsigned p_NumSprites[], unsigned fsize);
void tr1pc_remove_viewport(char *bytelist, char *args[], unsigned p_NumSprites[], unsigned fsize);
void tr1pc_get_zones(char *bytelist, char *args[], unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned fsize);
void tr1pc_zone(char *bytelist, char *args[], unsigned p_NumZSector[], unsigned fsize);
void tr1pc_add_zone(char *bytelist, char *args[], unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned fsize);
void tr1pc_replace_zone(char *bytelist, char *args[], unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned fsize);
void tr1pc_add_overlap(char *bytelist, char *args[], unsigned argc, unsigned p_NumOverlaps, unsigned fsize);
void tr1pc_overwrite_overlap(char *bytelist, char *args[], unsigned argc, unsigned p_NumOverlaps, unsigned fsize);
void tr1pc_get_offset(char *bytelist, char *args[], unsigned argc, unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumItems, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumDemoData, unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned p_NumSoundDetails, unsigned p_NumSamples, unsigned p_NumSampleIndices, unsigned p_NumSoundSources, unsigned fsize);
void tr1pc_extract_textile(char *bytelist, char* args[], unsigned numTexTiles, unsigned* p_TexTiles, BYTE* palette, int selection);
void tr1pc_replace_textile(char* bytelist, char* args[], unsigned numTexTiles, unsigned* p_TexTiles, BYTE* palette, unsigned fsize);

#endif
