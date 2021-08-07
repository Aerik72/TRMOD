#ifndef tr1psx_H_INCLUDED
#define tr1psx_H_INCLUDED

void tr1psx_main(int argc, char *args[], char *bytelist, unsigned fsize);
void tr1psx_list(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumBoxes, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned short numRooms, unsigned fsize);
void tr1psx_add_staticmesh(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize);
void tr1psx_replace_staticmesh(char *bytelist, int argc, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumStaticMeshes[], unsigned fsize);
void tr1psx_remove_staticmesh(char *bytelist, char *args[], unsigned p_NumStaticMeshes[], unsigned fsize);
void tr1psx_add_sprite(char *bytelist, char *args[], int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize);
void tr1psx_replace_sprite(char *bytelist, char *args[], unsigned argc, int roomY[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumSpriteSequences, unsigned fsize);
void tr1psx_add_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize);
void tr1psx_replace_light(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumLights[], unsigned fsize);
void tr1psx_remove_light(char *bytelist, char *args[], unsigned p_NumLights[], unsigned fsize);
void tr1psx_remove_all(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumFloorData, unsigned p_NumCameras, unsigned p_NumSoundSources, unsigned p_NumItems, unsigned p_NumBoxes, unsigned short numRooms, unsigned fsize);
void tr1psx_extract_sample(char *bytelist, char *args[], unsigned fsize);
void tr1psx_replace_sample(char *bytelist, char *args[], unsigned fsize);
void tr1psx_get_geometry(char *bytelist, char *args[], unsigned roomX[], int roomY[], unsigned roomZ[], unsigned p_NumVertices[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned short numRooms, unsigned fsize);
void tr1psx_move_room(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_NumItems, unsigned fsize);
void tr1psx_add_room(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned p_NumFloorData, unsigned fsize);
void tr1psx_add_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize);
void tr1psx_replace_vertex(char *bytelist, char *args[], unsigned p_NumVertices[], int roomY[], unsigned fsize);
void tr1psx_remove_vertex(char *bytelist, int argc, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1psx_add_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1psx_replace_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1psx_remove_rectangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1psx_add_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1psx_replace_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1psx_remove_triangle(char *bytelist, char *args[], unsigned p_NumVertices[], unsigned fsize);
void tr1psx_get_offset(char *bytelist, char *args[], unsigned argc, unsigned p_NumVertices[], unsigned p_NumSprites[], unsigned p_NumLights[], unsigned p_NumZSector[], unsigned p_NumStaticMeshes[], unsigned p_AlternateRoom[], unsigned p_NumFloorData, unsigned p_NumItems, unsigned p_NumSpriteSequences, unsigned p_NumCameras, unsigned p_NumBoxes, unsigned p_NumOverlaps, unsigned p_NumSoundSources, unsigned fsize);

#endif
