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

typedef struct Room Room;

/* Room struct */
struct Room {
	int visited;	//0 not vidited, 1 visited	
	char *type;		// room type
	char *name;		// room name
	char *longDescription;
	char *shortDescription;
	char *feature1;
	char *look1;
	char *hit1;
	char *open1;
	char *move1;
	char *feature2;
	char *look2;
	char *hit2;
	char *open2;
	char *move2;
	char *lookatd2;
	char *hitd2;
	char *opend2;
	char *moved2;
	char *objectd2;
	char *exit1name;
	char *exit1direction;
	char *exit2name;
	char *exit2direction;
	char *exit3name;
	char *exit3direction;
	char *exit4name;
	char *exit4direction;	
	int numExits;
	char *exitDirection[MAX_EXITS];
	struct Room *Exits[MAX_EXITS];
};

void readRooms(Room* array, char newestDirName[256]);

/* Place at end of file - End of header conditional */
#endif