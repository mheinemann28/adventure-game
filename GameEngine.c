/*********************************************************************
 ** Program Filename: GameEngine.c
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: runs adventure game; takes input from user and moves
 **      them along in the game
 ** Input: command line input
 ** Output: game response
 *********************************************************************/

#include "CommandParser.h"
#include "GameEngine.h"
#include "GameEngine_helpers.h"
#include "GameStateLoader.h"
#include "RoomLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************************************
 ** Function: main();
 ** Description: starts adventure game
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: program exits
 *********************************************************************/

int main() {
	readRooms(rooms, "rooms");
	intro();
	runGame(rooms);

	return 0;
}



/*********************************************************************
 ** Function: intro();
 ** Description: Introduction of Adventure game, with instructions
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: Intro and instructions printed to screen.
 *********************************************************************/

void intro() {
	char *intro = "Welcome to the Adventure escape game. The goal of this game is to make it safely through all rooms\n"
	              "and obstacles. You will guide yourself through the maze of locations, defeating any enimies in your path\n"
	              "until you have found the final destination.\n\n";

	char *instructions = "You will navigate the game typing commands into the prompt. You will use natural language\n"
	                     "commands such as, 'go through...', 'look at...', 'pick up...', and so on to examine in room features, pick up\n"
	                     "and interact with objects and move throughout the game.\n\n";

	char *sendoff = "Good luck and have fun!\n";

	printf("%s\n", intro);
	printf("%s\n", instructions);
	printf("%s\n", sendoff);
}

/////////
void getInput(char *inputBuff) {
	//get command from user
	memset(inputBuff, '\0', sizeof(inputBuff));
	printf("\nCommand: ");
	fgets(inputBuff, 255, stdin);
	inputBuff[strlen(inputBuff) - 1] = '\0';
	printf("inputBuff: %s\n", inputBuff);
}

/*********************************************************************
 ** Function: runGame();
 ** Description: starts and run game untill finished
 ** Parameters: struct Room
 ** Pre-Conditions: rooms must be created and connected
 ** Post-Conditions: game ends
 *********************************************************************/
//All input and output here was used for testing purposes.
//Function at the moment can move between rooms.
//will add more functionality in the next week
void runGame(struct Room *rooms) {
	int i, j;
	struct parsed_command pc;
	char *noun;
	char *tempRoomName;
	//buffer to hold keyboard input data
	char inputBuff[255];
	memset(inputBuff, '\0', sizeof(inputBuff));

	tempRoomName = rooms[0].name;
	printf("current room: %s\n", rooms[0].name);
	getInput(inputBuff);
	
	while (1) {
		//printf("entered while loop. \n");
		for (i = 0; i < 15; i++) {
			printf("tempRoomName: %s\n", tempRoomName);
			printf("rooms[%d].name: %s\n", i, rooms[i].name);
			if (strcmp(tempRoomName, rooms[i].name) == 0) {	
				printf("entered if (strcmp(tempRoomName, rooms[%d].name) == 0). \n", i);
				rooms[i].visited = 1;
				printf("room: %s visited changed to %d\n", rooms[i].name, rooms[i].visited);	
				for (j = 0; j < rooms[i].numExits; j++) {	
					//printf("inputBuff: %s\n", inputBuff);
					printf("rooms[i].exitDirection[j]: %s\n", rooms[i].exitDirection[j]);				
					if (strcmp(inputBuff, rooms[i].exitDirection[j]) == 0) {
						printf("entered if (strcmp(inputBuff, rooms[i].exitDirection[j]) == 0). \n");
						tempRoomName = rooms[i].Exits[j];
						printf("current room: %s\n", tempRoomName);	
						goto continue_game;
					}
				}
			}
		}
		continue_game:
		if(strcmp(tempRoomName, "Cafe") == 0)
		{
			printf("Reached the end. \n");
			exit(0);
		}
		//printf("got to continue_game. \n");
		getInput(inputBuff);
	}
}



