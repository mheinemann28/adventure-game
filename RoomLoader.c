/*********************************************************************
 ** Program Filename: RoomLoader.c
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Loads rooms from text files into the game
 ** Input: rooms text files (there are 15)
 ** Output: data loaded into GameEngine
 *********************************************************************/
 
#include "GameEngine_helpers.h"
#include "RoomLoader.h"

struct Room rooms[2];

int main(){
	rooms[0].type = "START";
	rooms[0].name = "Basement";
	rooms[0].longDescription = "You notice a moldy smell, and can feel the dampness in the air as soon as you enter the room.\n
				There are stairs leading down.  The only lightsource is from the high window in the corner.\n
				You seem to have entered a basement.  Seems to be full of a lot of junk.  A rusty old bike,\n
				moldy bed sheets, papers scattered throughout.  You notice a chest along the east wall and a\n
				cabinet on the opposite west wall.  They may hold something useful.  You should examine the room\n
				further and figure out what to do next.";
}