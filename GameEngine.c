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

	//Using hard coded data for testing
	//remove and format for real data when available

	char *roomNames[10] = {"Room 1", "Room 2", "Room 3", "Room 4", "Room 5", "Room 6", "Room 7", "Room 8", "Room 9", "Room 10"};


	int i;
	for (i = 0; i < 10; i++) {
		rooms[i].type = calloc(255, sizeof(char));
		rooms[i].name = calloc(255, sizeof(char));
		rooms[i].longDescription = calloc(255, sizeof(char));
		rooms[i].shortDescription = calloc(255, sizeof(char));

		rooms[i].visited = 0;
		rooms[i].name = roomNames[i];
		rooms[i].longDescription = "Long Description for ";
		rooms[i].shortDescription = "Short Description for ";
	}
	rooms[0].type = "START";
	rooms[9].type = "END";

	for (i = 1; i < 9; i++) {
		rooms[i].type = "MID_ROOM";
	}
	
	
	rooms[0].numExits = 4;
	rooms[0].Exit[0] = &rooms[1];
	rooms[0].Exit[1] = &rooms[3];
	rooms[0].Exit[2] = &rooms[5];
	rooms[0].Exit[3] = &rooms[7];

	rooms[1].numExits = 3;
	rooms[1].Exit[0] = &rooms[0];
	rooms[1].Exit[1] = &rooms[2];
	rooms[1].Exit[2] = &rooms[4];

	rooms[2].numExits = 2;
	rooms[2].Exit[0] = &rooms[1];
	rooms[2].Exit[1] = &rooms[3];

	rooms[3].numExits = 3;
	rooms[3].Exit[0] = &rooms[0];
	rooms[3].Exit[1] = &rooms[2];
	rooms[3].Exit[2] = &rooms[6];

	rooms[4].numExits = 2;
	rooms[4].Exit[0] = &rooms[1];
	rooms[4].Exit[1] = &rooms[5];
	
	rooms[5].numExits = 3;
	rooms[5].Exit[0] = &rooms[0];
	rooms[5].Exit[1] = &rooms[4];
	rooms[5].Exit[2] = &rooms[8];

	rooms[6].numExits = 2;
	rooms[6].Exit[0] = &rooms[3];
	rooms[6].Exit[1] = &rooms[7];
	
	rooms[7].numExits = 3;
	rooms[7].Exit[0] = &rooms[0];
	rooms[7].Exit[1] = &rooms[6];
	rooms[7].Exit[2] = &rooms[8];

	rooms[8].numExits = 3;
	rooms[8].Exit[0] = &rooms[5];
	rooms[8].Exit[1] = &rooms[7];
	rooms[8].Exit[2] = &rooms[9];
	//end of hard coded data

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

	//buffer to hold keyboard input data
	char inputBuff[255];
	memset(inputBuff, '\0', sizeof(inputBuff));

	//room description of start
	printf("%s%s\n\n", rooms[0].longDescription, rooms[0].name);

	//Loop through and print exits
	printf("Exits:\n");
	for (i = 0; i < rooms[0].numExits; i++) {
		printf("    %s\n", rooms[0].Exit[i]->name);
	}

	//mark start room as visited
	rooms[0].visited = 1;

	while (1) {
		//get command from user
		getInput(inputBuff);

		for (i = 0; i < 10; i++) {

			if (strcmp(inputBuff, rooms[i].name) == 0) {
				if(strcmp(rooms[i].type, "END") == 0){
					printf("\n%s%s\n\n", rooms[i].longDescription, rooms[i].name);
					printf("Made it to END\n");
					exit(1);
				}
				else if (rooms[i].visited == 0) {
					printf("\n%s%s\n\n", rooms[i].longDescription, rooms[i].name);
					rooms[i].visited = 1;
				}
				else
					printf("\n%s%s\n\n", rooms[i].shortDescription, rooms[i].name);

				printf("Exits:\n");
				
				for (j = 0; j < rooms[i].numExits; j++) {
					printf("    %s\n", rooms[i].Exit[j]->name);
				}
			}
		}
	}
}

void getInput(char *inputBuff){
	//get command from user
	memset(inputBuff, '\0', sizeof(inputBuff));
	printf("\nCommand: ");
	fgets(inputBuff, 255, stdin);
	inputBuff[strlen(inputBuff) - 1] = '\0';
}

