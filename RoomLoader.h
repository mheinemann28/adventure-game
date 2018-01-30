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

typedef struct Room Room;

/* Room struct */
struct Room {
	char visited[LENGTH];	
	char type[LENGTH];		// room type
	char name[LENGTH];		// room name
	char longDescription[LENGTH];
	char shortDescription[LENGTH];
	char feature1[LENGTH];
	char look1[LENGTH];
	char hit1[LENGTH];
	char open1[LENGTH];
	char move1[LENGTH];
	char feature2[LENGTH];
	char look2[LENGTH];
	char hit2[LENGTH];
	char open2[LENGTH];
	char move2[LENGTH];
	char lookatd2[LENGTH];
	char hitd2[LENGTH];
	char opend2[LENGTH];
	char moved2[LENGTH];
	char objectd2[LENGTH];
	char exit1name[LENGTH];
	char exit1direction[LENGTH];
	char exit2name[LENGTH];
	char exit2direction[LENGTH];
	char exit3name[LENGTH];
	char exit3direction[LENGTH];
	char exit4name[LENGTH];
	char exit4direction[LENGTH];	
};

void readRooms(Room* array, char newestDirName[256]);

/* Place at end of file - End of header conditional */
#endif