/*********************************************************************
 ** Program Filename: GameEngine_helpers.h
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: help file to store global variables and structs;
 **      includes the room struct and the gamestate struct;
 ** Input: none
 ** Output: none
 *********************************************************************/

#ifndef _GAMEENGINE_HELPERS_H
#define _GAMEENGINE_HELPERS_H
/*
//**Note to Team
//Make any changes you feel necessary here, this is just a basic example of how we can
//organize room data.  I was able to get basic movement from room to room with what is here
//--Mike
struct Room {
	int visited; //0 if not yet visited, 1 if has been visited
	char *type; //START, MID, END
	char *name;
	char *longDescription; //long description of room currently in
	char *shortDescription; //short desciption of room currently in
	char *feature[2];
	int *objectID;
	int numExits;
	struct Room* Exit[5];
};
*/
//**Note to team
//Not sure if this is necessary. Have not tried implementing with yet -- Mike
/*
struct Object{
	int id;
	char *objectName;
};
*/

#endif