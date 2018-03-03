/*********************************************************************
 ** Program Filename: RoomLoader.h
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Loads rooms from text files into the game
 ** Input: rooms text files (there are 15)
 ** Output: data loaded into GameEngine
 *********************************************************************/
 
/* To prevent compiler from processing contents twice, wrap in a conditional */
#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#define MAX_INV 8

/* Object struct */
struct Object {
	char *name;		
	char *room;
	char *usedFor;		
};

struct Inventory {
	int invCount;
	char *name[MAX_INV];		
	char *room[MAX_INV];
	char *usedFor[MAX_INV];		
};

void readObjects(struct Object* array, char newestDirName[256]);

void initInventory(struct Inventory* invArray);

/* Place at end of file - End of header conditional */
#endif