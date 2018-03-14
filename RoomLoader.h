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
typedef struct Feature Feature;

struct Feature {
	char *name;
	int firstLook;	// if has not been looked at yet set to 0, else 1
	int containObject;	// if object is located on or in feature set to 1, else 0
	char *enemy; // yes or no
	char *description1;	// prints if first time looking at feature
	char *description2;	// prints if feature has already been looked at
	char *hit1;
	char *hit2;
	char *open1;
	char *open2;
	char *move1;
	char *move2;
};

/* Room struct */
struct Room {
	int visited;	//0 not visited, 1 visited	
	char *type;		// room type
	char *name;		// room name
	char *longDescription;
	char *shortDescription;
	struct Feature feature[MAX_FEATURES];
	int numObjects;
	char *object[LENGTH];
	int numExits;
	char *exitDirection[MAX_EXITS];
	char *Exits[MAX_EXITS];
	char *blockedBy[MAX_EXITS]; // feature blocking door
	char *exitDescription[MAX_EXITS];
};



void readRooms(Room* array, char newestDirName[256]);
//void loadFeatures(Feature *f);

/* Place at end of file - End of header conditional */
#endif