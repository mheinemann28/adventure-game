/*********************************************************************
 ** Program Filename: RoomLoader.h
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Loads rooms from text files into the game
 ** Input: rooms text files (there are 15)
 ** Output: data loaded into GameEngine
 *********************************************************************/
 
/* To prevent compiler from processing contents twice, wrap in a conditional */
#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#define LENGTH 50
#define MAX_EXITS 4
#define MAX_FEATURES 2

typedef struct Room Room;

/* Room struct */
struct Room {
	int visited;	//0 not vidited, 1 visited	
	char *type;		// room type
	char *name;		// room name
	char *longDescription;
	char *shortDescription;
	char *feature[MAX_FEATURES];
	char *look[MAX_FEATURES + 1];
	char *hit[MAX_FEATURES + 1];
	char *open[MAX_FEATURES + 1];
	char *move[MAX_FEATURES + 1];
	int numObjects;
	char *object[LENGTH];
	int numExits;
	char *exitDirection[MAX_EXITS];
	char *Exits[MAX_EXITS];
};

void readRooms(Room* array, char newestDirName[256]);

/* Place at end of file - End of header conditional */
#endif