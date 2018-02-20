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
#include "ObjectLoader.h"

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
	//readRooms(rooms, "rooms");
	readObjects(objArray, "rooms");
	//intro();
	//runGame(rooms, objArray);
	int j;
	
	
	for(j=0; j<8; j++)
	{
		printf("OBJECT%dNAME: %s\n", j+1, objArray[j].name);
		printf("OBJECT%dSTARTROOM: %s\n", j+1, objArray[j].room);
		printf("OBJECT%dDESCRIPTION: %s\n", j+1, objArray[j].description);
	}
	
	
	/*
	for(j=0; j<15; j++)
	{
		printf("%s\n",rooms[j].name);
	}
	*/
	
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
	              "and obstacles. You will guide yourself through the maze of locations, defeating any enemies in your path\n"
	              "until you have found the final destination.\n\n";

	char *instructions = "You will navigate the game typing commands into the prompt. You will use natural language\n"
	                     "commands such as, 'go through...', 'look at...', 'pick up...', and so on to examine in room features, pick up\n"
	                     "and interact with objects and move throughout the game.\n\n";

	char *sendoff = "Good luck and have fun!\n";

	char *input;
	memset(input, '\0', sizeof(input));

	printf("%s\n", intro);
	printf("%s\n", instructions);
	printf("%s\n", sendoff);
	printf("\nType start game to begin: ");
	fgets(input, 25, stdin);
}


void getInput(char *inputBuff) {
	//get command from user
	memset(inputBuff, '\0', sizeof(inputBuff));
	printf("\nCommand: ");
	fgets(inputBuff, 255, stdin);
	inputBuff[strlen(inputBuff) - 1] = '\0';
}

/*********************************************************************
 ** Function: runGame();
 ** Description: starts and run game untill finished
 ** Parameters: struct Room
 ** Pre-Conditions: rooms must be created and connected
 ** Post-Conditions: game ends
 *********************************************************************/

void runGame(struct Room *rooms, struct Object *objArray) {
	int i, j, m;

	char *noun;
	char *tempRoomName;
	//buffer to hold keyboard input data
	char inputBuff[255];
	memset(inputBuff, '\0', sizeof(inputBuff));

	tempRoomName = rooms[0].name;
	
	while (1) {
		for (i = 0; i < 15; i++) {

			if (strcmp(tempRoomName, rooms[i].name) == 0) {

				if (rooms[i].visited == 0)
				{
					printf("\n%s\n", rooms[i].longDescription);
				}
				else
				{
					printf("\n%s\n", rooms[i].shortDescription);
				}
				printf("\nCurrent room: %s\n", tempRoomName);

				printf("Features:\n");
				for (j = 0; j < MAX_FEATURES; j++) {
					printf("\t%d. %s\n", j + 1, rooms[i].feature[j]);
				}

				rooms[i].visited = 1;

				do {
					getInput(inputBuff);
					pc = parseCommand(inputBuff);
					noun = pc.noun1;

					m = examineRoom(rooms[i], pc);
				} while (m == 0);

				/*
				if(m == 2)
				{
					for(j = 0; j < 8; j++)
					{
						if(noun == objArray[j].name && rooms[i].name == objArray[j].room)
							//put object in inventory
							//update object room to be NA
							printf("You said get %s in %s\n", noun, rooms[i].name);
							printf("Confirmed that you got %s in %s\n\n", objArray[j].name, objArray[j].room);
					}
				}
				*/
				//else{
					for (j = 0; j < rooms[i].numExits; j++) {

						if (strcmp(noun, rooms[i].exitDirection[j]) == 0) {

							tempRoomName = rooms[i].Exits[j];

							goto continue_game;
						}
					}
					if (strcmp(inputBuff, rooms[i].exitDirection[j]) != 0)
						printf("Invalid exit direction. You are still in %s\n", tempRoomName);
				//}
			}
		}
continue_game:
		if (strcmp(tempRoomName, "Cafe") == 0)
		{
			printf("Reached the end. \n");
			exit(0);
		}
	}
}


int examineRoom(struct Room room, struct parsed_command pc) 
{
	int i;
	char tempString[30];
	memset(tempString, '\0', sizeof(tempString));
	if (strcmp(pc.verb, "look at") == 0) 
	{
		strcat(tempString, pc.noun1);
		for (i = 0; i < MAX_FEATURES; i++) 
		{
			if (strcmp(tempString, room.feature[i]) == 0) 
			{
				printf("%s\n", room.look[i]);
			}
		}
	}
	//else if (strcmp(pc.verb, "get") == 0)
	//	return 2;
	else if (strcmp(pc.verb, "go") == 0)
		return 1;
	else
		printf("your command is not recognized\n");
	return 0;
}
