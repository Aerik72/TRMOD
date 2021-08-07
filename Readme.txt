Tomb Raider Level Modifier (TRMOD) 0.3
2015 Beta 1-2 b122251
2021 0.3 Erik R
=========================================================

This program can modify and list the contents of Tomb Raider level files.
It supports TR1 PC, TR1 PSX, TUB PC, and TR2 PC formats.

This program comes with ABSOLUTELY NO WARRANTY.
This program is distributed under the GNU General Public License 3.0.
This program is dedicated to everybody on the Tomb Raider Forums.

If you find any bugs, please contact Aerik72 at tombraiderforums.com.
(I'll probably invite you to the github repository to fix it. ;))
This program uses a command line interface.

Here's a list of the commands.
I recommend keeping the TRosettaStone at hand for clarification, also
the clist command can teach you a lot about much of the syntax.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

In the folder "Binaries", you will find compiled versions of the program.
In the folder "Public Tests", you will find batch scripts for the public tests that have been released so far.
In the folder "Source", you will find the source code to this build.
In the folder "TRosetta Stone", you will find the rosetta stone documents for clarification.
The file "License.txt" contains a copy of the GNU General Public License 3.
The file "Readme.txt" is this file.

COMMAND LIST:
+===========================================================================================+
• trmod [FILE] LIST/CLIST [OUTPUT FILE]
  This command writes a list of all items, static meshes, sprites, lights, soundsources, alternate rooms and floordata.
  The LIST version writes it in a nice readable format, and CLIST writes it in the form of trmod-commands.
  Example: trmod level1.psx list 1.txt
  
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
+===========================================================================================+
• trmod [FILE] ADD ITEM [ObjectID] [Room] [X] [Z] [Y] [Angle] [Intensity] [Intensity2] [Flags]
  This command adds an item to the level.
  Example: trmod boat.tr2 ADD ITEM 0 0 1536 1536 2304 180 -1 -1 0000
+===========================================================================================+
• trmod [FILE] REPLACE ITEM [Item] [ObjectID] [Room] [X] [Z] [Y] [Angle] [Intensity1] [Intensity2] [Flags]
  This command replaces an item in the level.
  Example: trmod LEVEL4.PHD REPLACE ITEM 51 56 21 5632 7680 768 90 -1 -1 0000
  An alternative syntax is: trmod [FILE] REPLACE ITEM [Item] [ObjectID].
  This replaces only the ObjectID, but keeps the rest of the properties intact.
  (To be compatible with FexInspect, the items are counted from 0)
+===========================================================================================+
• trmod [FILE] REMOVE ITEM [ObjectID]
  This command removes an item from the level.
  Example: trmod boat.tr2 REMOVE ITEM 58
  (To be compatible with FexInspect, the items are counted from 0)
+===========================================================================================+
• trmod [FILE] REMOVE ALL ITEMS
  This removes all items from the level.
+===========================================================================================+
• trmod [FILE] ADD STATICMESH [ObjectID] [Room] [X] [Z] [Y] [Angle] [Intensity1] [Intensity2]
  This command adds a static mesh to a level.
  Example: trmod assault.tr2 ADD STATICMESH 7 1 8704 3584 0 0 4096 4096
+===========================================================================================+
• trmod [FILE] REPLACE STATICMESH [Room] [Staticmesh] [ObjectID] [X] [Z] [Y] [Angle] [Intensity1] [Intensity2]
  This command replaces a static mesh in a level.
  An alternative syntax is: trmod [FILE] REPLACE STATICMESH [Room] [Staticmesh] [ObjectID].
  This replaces only the ObjectID, but keeps the rest of the properties intact.
  (To be compatible with FexInspect, the static meshes are counted from 1 in each room)
+===========================================================================================+
• trmod [FILE] REMOVE STATICMESH [Room] [Staticmesh] 
  This command removes a static mesh from the level.
  (To be compatible with FexInspect, the static meshes are counted from 1 in each room)
+===========================================================================================+
• trmod [FILE] REMOVE ALL STATICMESHES
  This command removes all static meshes from the level.
+===========================================================================================+
• trmod [FILE] ADD SPRITE [ObjectID] [Room] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]
  This command adds a sprite to the level.
  Example: trmod assault.tr2 ADD SPRITE 291 53 10112 2560 1408 7168 7168 0010
+===========================================================================================+
• trmod [FILE] REPLACE SPRITE [Room] [Sprite] [ObjectID] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]
  This command replaces a sprite in a level.
  An alternative syntax is: trmod [FILE] REPLACE SPRITE [Room] [Sprite] [ObjectID].
  This replaces only the ObjectID, but keeps the rest of the properties intact.
  (The sprites are counted from 1 in each room)
+===========================================================================================+
• trmod [FILE] REMOVE SPRITE [Room] [Sprite] 
  This command removes a sprite from the level.
  (The sprites are counted from 1 in each room)
+===========================================================================================+
• trmod [FILE] REMOVE ALL SPRITES
  This command removes all sprites from the level.
+===========================================================================================+
• trmod [FILE] ADD LIGHT [Room] [X] [Z] [Y] [Intensity1] [Intensity2] [Fade1] [Fade2]
  This command adds a light to the level.
+===========================================================================================+
• trmod [FILE] REPLACE LIGHT [Room] [Light] [X] [Z] [Y] [Intensity1] [Intensity2] [Fade1] [Fade2]
  This command replaces a light in the level.
  (Lights are counted from 1 in each room)
+===========================================================================================+
• trmod [FILE] REMOVE LIGHT [Room] [Light]
  This command removes a light from the level.
  (Lights are counted from 1 in each room)
+===========================================================================================+
• trmod [FILE] REMOVE ALL LIGHTS
  This command removes all lights from the level.
+===========================================================================================+
• trmod [FILE] ADD SOUNDSOURCE [SoundID] [X] [Z] [Y] [Flags]
  This commands adds a soundsource to the level.
  Example: trmod LEVEL3A.PSX ADD SOUNDSOURCE 80 37376 76288 -256 0080
+===========================================================================================+
• trmod [FILE] REPLACE SOUNDSOURCE [SoundSource] [SoundID] [X] [Z] [Y] [Flags]
  This command replaces a sound source in a level.
  An alternative syntax is: trmod [FILE] REPLACE SOUNDSOURCE [SoundSource] [SoundID].
  This replaces only the SoundID, but keeps the rest of the properties intact.
  (Sound sources are counted from 0)
+===========================================================================================+
• trmod [FILE] REMOVE SOUNDSOURCE [Sound source] 
  This command removes a sprite from the level.
  (Sound sources are counted from 0)
+===========================================================================================+
• trmod [FILE] REMOVE ALL SOUNDSOURCES
  This command removes all sound sources from the level.
+===========================================================================================+
• trmod [FILE] REPLACE FLOORDATA [Room] [Column] [Row] {Floordata}
  This command replaces the floordata in a given sector.
	The {Floordata} argument(s) follow the following syntax:
		"FLOORPORTAL(Room Below)" (This makes the floor a portal to a room below)
		"CEILINGPORTAL(Room Above)" (This makes the ceiling a portal to a room above)
		"PORTAL(Adjoining Room)" (This creates a protal to a neighboring room)
		"FLOORSLANT(Slant on X Axis,Slant on Z Axis)" (This makes the floor slanted)
		"CEILINGSLANT(Slant on X Axis,Slant on Z Axis)" (This makes the ceiling slanted)
		"TRIGGER({Trigger Conventions})" (This creates a trigger on this sector)
		"KILL" (This kills Lara when she steps on this sector)
		"CLIMBWALLS(+X,-X,+Z,-Z)" (Makes the walls climbable) (Not in Tomb Raider 1)
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
			
  The CLIST command can be very useful in learning this syntax.
+===========================================================================================+
• trmod [FILE] REMOVE FLOORDATA [Room] [Column] [Row]
  This command removes the floordata in a given sector.
+===========================================================================================+
• trmod [FILE] REMOVE ALL FLOORDATA
  This command remove all floordata from the level.
+===========================================================================================+
• trmod [FILE] REMOVE ALL CAMERAS
  This command remove all cameras from the level.
+===========================================================================================+
• trmod [FILE] ALTERNATE ROOM [Room] [Alternate Room]
  This command sets an alternate room for a given room.
+===========================================================================================+
• trmod [FILE] ROOMLIGHT [Room] [Intensity1] [Intensity2] [LightMode]
  This command sets the ambient light level in a given room.
+===========================================================================================+
• trmod [FILE] WATER [Room]
  This command floods a room with water. It will flood all rooms, 
  if instead of a room number, you enter the word "all".
+===========================================================================================+
• trmod [FILE] NOWATER [Room]
  This command drains a room of water. It will drain all rooms, 
  if instead of a room number, you enter the word "all".
+===========================================================================================+
• trmod [FILE] SKY [Room]
  This command makes the sky visible from this room. It will do this in all rooms, 
  if instead of a room number, you enter the word "all".
  (This command is not in Tomb Raider 1)
+===========================================================================================+
• trmod [FILE] NOSKY [Room]
  This command makes the sky invisible from this room. It will do this in all rooms, 
  if instead of a room number, you enter the word "all".
  (This command is not in Tomb Raider 1)
+===========================================================================================+
• trmod [FILE] WIND [Room]
  This command makes the wind blow in this room. It will do this in all rooms, 
  if instead of a room number, you enter the word "all".
  (This command is not in Tomb Raider 1)
+===========================================================================================+
• trmod [FILE] NOWIND [Room]
  This command makes the wind not blow in this room. It will do this in all rooms, 
  if instead of a room number, you enter the word "all".
  (This command is not in Tomb Raider 1)
+===========================================================================================+
• trmod [FILE] GET SAMPLENUMBER [SoundID]
  This command returns the sample number of a given soundID in the level.
  (This command is not in Tomb Raider 2 on the PC)
+===========================================================================================+
• trmod [FILE] EXTRACT SAMPLE [Sample] [Output File]
  This command extracts a sample from the level into a wave file.
  (This command is not in Tomb Raider 2 on the PC)
+===========================================================================================+
• trmod [FILE] REPLACE SAMPLE [Sample] [Output File]
  This command replaces a sample in the level with a sample from a wave file.
  (This command is not in Tomb Raider 2 on the PC)
+===========================================================================================+
• trmod [FILE] EXTRACT DEMO [Output File]
  This command extracts the demodata from a level into a file.
  (This command is not in Tomb Raider 1 on the PlayStation)
+===========================================================================================+
• trmod [FILE] REPLACE DEMO [Output File]
  This command replaces the demodata in a level from a file.
  (This command is not in Tomb Raider 1 on the PlayStation)
+===========================================================================================+
• trmod [file] CONVERT [output file]
  This command converts between PHD and TUB formats.
  Example: trmod LEVEL1.PHD CONVERT LEVEL1.TUB
  (This command ONLY works on Tomb Raider 1 on the PC)
+===========================================================================================+
• trmod [FILE] GET GEOMETRY [Room] [Text File]
  This command prints a list of all Vertices, Rectangles, Triangles and Viewports, the 
  floor- and ceilingheight of every sector and to which zone each sector belongs, it also gives
  the size, position and roomlight of the room. If you replace the room number with the word
  "all", it will list these properties for every room.
+===========================================================================================+
• trmod [FILE] REMOVE ALL GEOMETRY [Room]
  This command removes all vertices, rectangles, triangles and sprites from a given room.
  If you replace the room number with the word "all" it will remove all geometry in the level.
+===========================================================================================+
• trmod [FILE] GET ROOMPOS [Room]
  This command returns the position of a room.
+===========================================================================================+
• trmod [FILE] MOVE ROOM [Room] [X] [Z] [Y]
  This command moves a room.
  An alternative syntax is: trmod [FILE] MOVE ROOM [Room] [X] [Z] [Y] RAW
  This does the same, but doesn't move the items, staticmeshes, lights etc. along with the room.
+===========================================================================================+
• trmod [FILE] GET ROOMSIZE [Room]
  This command returns the size of a room.
+===========================================================================================+
• trmod [FILE] RESIZE ROOM [Room] [Width in sectors] [Length in sectors] [Height in coordinates]
  This command changes the size of a room.
+===========================================================================================+
• trmod [FILE] ADD ROOM
  This command adds an empty room to the level.
+===========================================================================================+
• trmod [FILE] GET FLOORHEIGHT [Room] [Column] [Row]
  This command returns the height of the floor in a given sector.
+===========================================================================================+
• trmod [FILE] GET CEILINGHEIGHT [Room] [Column] [Row]
  This command returns the height of the ceiling in a given sector.
+===========================================================================================+
• trmod [FILE] SET FLOORHEIGHT [Room] [Column] [Row] [Height]
  This command changes the height of the floor in a given sector.
+===========================================================================================+
• trmod [FILE] SET CEILINGHEIGHT [Room] [Column] [Row] [Height]
  This command changes the height of the ceiling in a given sector.
+===========================================================================================+
• trmod [FILE] ADD VERTEX [Room] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]
  This command adds a vertex to a room.
+===========================================================================================+
• trmod [FILE] REPLACE VERTEX [Room] [Vertex] [X] [Z] [Y] [Lighting1] [Lighting2] [Attributes]
  This command replaces a vertex in a room.
+===========================================================================================+
• trmod [FILE] REMOVE VERTEX [Room] [Vertex]
  This command removes a vertex from a room.
+===========================================================================================+
• trmod [FILE] ADD RECTANGLE [Room] [Vertex 1] [Vertex 2] [Vertex 3] [Vertex 4] [Texture]
  This command adds a rectangle to a room.
+===========================================================================================+
• trmod [FILE] REPLACE RECTANGLE [Room] [Rectangle] [Vertex 1] [Vertex 2] [Vertex 3] [Vertex 4] [Texture]
  This command replaces a rectangle in a room.
+===========================================================================================+
• trmod [FILE] REMOVE RECTANGLE [Room] [Rectangle]
  This command removes a recatngle from a room.
+===========================================================================================+
• trmod [FILE] REMOVE ALL RECTANGLES [Room]
  This command removes all rectangles from a room.
  If you replace the room number with the word "all", it remove all rectangles from the level.
+===========================================================================================+
• trmod [FILE] ADD TRIANGLE [Room] [Vertex 1] [Vertex 2] [Vertex 3] [Texture]
  This command adds a triangle to a room.
+===========================================================================================+
• trmod [FILE] REPLACE TRIANGLE [Room] [Triangle] [Vertex 1] [Vertex 2] [Vertex 3] [Texture]
  This command replaces a triangle in a room.
+===========================================================================================+
• trmod [FILE] REMOVE TRIANGLE [Room] [Triangle]
  This command removes a triangle from a room.
+===========================================================================================+
• trmod [FILE] REMOVE ALL TRIANGLES [Room]
  This command removes all triangles from a room.
  If you replace the room number with the word "all", it remove all triangles from the level.
+===========================================================================================+
• trmod [FILE] ADD VIEWPORT [Room] [Room 2] [NormalX] [NormalZ] [NormalY] [1X] [1Z] [1Y] [2X] [2Z] [2Y] [3X] [3Z] [3Y] [4X] [4Z] [4Y]
  This command adds a viewport to a room.
+===========================================================================================+
• trmod [FILE] REPLACE VIEWPORT [Room] [Viewport] [Room 2] [NormalX] [NormalZ] [NormalY] [1X] [1Z] [1Y] [2X] [2Z] [2Y] [3X] [3Z] [3Y] [4X] [4Z] [4Y]
  This command replaces a viewport in a room.
+===========================================================================================+
• trmod [FILE] REMOVE VIEWPORT [Room] [Viewport]
  This command removes a viewport from a room.
+===========================================================================================+
• trmod [FILE] REMOVE ALL VIEWPORTS [Room]
  This command removes all viewports from a room.
  If you replace the room number with the word "all", it remove all viewports from the level.
+===========================================================================================+
• trmod [FILE] GET ZONES [OUTPUT FILE]
  This command produces a list of all zones and overlaps, in this format:
  Zone(Xmin,Xmax,Zmin,Zmax,TrueFloor,Overlap_Offset,GroundZone1_Normal,GroundZone2_Normal,GroundZone3_Normal,GroundZone4_Normal,FlyZone_Normal,GroundZone1_Alternate,GroundZone2_Alternate,GroundZone3_Alternate,GroundZone4_Alternate,FlyZone_Alternate))
  Overlap(Offset)(Zone,Zone,Zone...)
+===========================================================================================+
• trmod [FILE] ZONE [Room] [Column] [Row] [Zone]
  This command declares a particular zone to belong to a zone.
+===========================================================================================+
• trmod [FILE] ADD ZONE [Xmin] [Xmax] [Zmin] [Zmax] [TrueFloor] [Overlap_offset] [GroundZone 1] [GroundZone 2] [GroundZone 3] [GroundZone 4] [Fly Zone] [Alt. GroundZone 1] [Alt. GroundZone 2] [Alt. GroundZone 3] [Alt. GroundZone 4] [Alt. Fly Zone]
  This command adds a zone to the level.
+===========================================================================================+
• trmod [FILE] REPLACE ZONE [Zone] [Xmin] [Xmax] [Zmin] [Zmax] [TrueFloor] [Overlap_offset] [GroundZone 1] [GroundZone 2] [GroundZone 3] [GroundZone 4] [Fly Zone] [Alt. GroundZone 1] [Alt. GroundZone 2] [Alt. GroundZone 3] [Alt. GroundZone 4] [Alt. Fly Zone]
  This command replaces a zone in a level.
+===========================================================================================+
• trmod [FILE] ADD OVERLAP [Zone] [Zone] [Zone] ...
  This command adds a set of overlaps to a level.
+===========================================================================================+
• trmod [FILE] OVERWRITE OVERLAP [Offset] [Zone] [Zone] [Zone] ...
  This command overwrites a set of overlaps.
+===========================================================================================+
• trmod [FILE] REMOVE ALL ZONES
  This command remove all zones and overlaps from a level.
+===========================================================================================+
• trmod [FILE] GET OFFSET {Position}
  This command returns the offset of a given thing in a level.
  Example TRMOD LEVEL10C.PSX GET OFFSET NUMITEMS
+===========================================================================================+
• trmod [FILE] EXTRACT TEXTILE {Page # | "ALL"}
  This command extracts one or all texture tiles, and writes them to a .bmp file along with the palette.
  Note that Page # is 0-indexed
  Example TRMOD LEVEL3A.PHD EXTRACT TEXTILE ALL // Writes palette.bmp, textile0.bmp, textile1.bmp, ... textile11.bmp
          TRMOD EGYPT.TUB EXTRACT TEXTILE 7 // Writes palette.bmp, textile7.bmp
+===========================================================================================+