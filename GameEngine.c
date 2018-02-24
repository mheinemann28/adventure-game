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
	readRooms(rooms, "rooms");
	readObjects(objArray, "rooms");
	intro();
	runGame(rooms, objArray, invArray);

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

void runGame(struct Room *rooms, struct Object *objArray, struct Inventory invArray) {
	//char* invArray[8] = { NULL };
	int i, j, m, n;
	char *noun;
	char *tempRoomName;
	//buffer to hold keyboard input data
	char inputBuff[255];
	memset(inputBuff, '\0', sizeof(inputBuff));

	tempRoomName = rooms[0].name;
	invArray.invCount = 0;

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
					//noun = pc.noun1;
					printf("You said %s %s in %s\n", pc.verb, pc.noun1, rooms[i].name);
					m = examineRoom(rooms[i], pc);
				} while (m == 0);


				for (j = 0; j < rooms[i].numExits; j++) {

					if (strcmp(pc.noun1, rooms[i].exitDirection[j]) == 0) {

						tempRoomName = rooms[i].Exits[j];

						goto continue_game;
					}
				}
				if (strcmp(inputBuff, rooms[i].exitDirection[j]) != 0)
					printf("Invalid exit direction. You are still in %s\n", tempRoomName);

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
	printf("pc.verb: %s\n", pc.verb);
	printf("pc.noun1: %s\n", pc.noun1);
	if ((strcmp(pc.verb, "look at") == 0) && (strcmp(pc.noun1, "inventory") != 0))
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
	else if ((strcmp(pc.verb, "look at") == 0) && (strcmp(pc.noun1, "inventory") == 0))
		checkInventory(pc);
	else if (strcmp(pc.verb, "take") == 0)
		takeObject(pc, room);
	else if(strcmp(pc.verb, "drop") == 0)
		dropObject(pc, room);
	else if (strcmp(pc.verb, "go") == 0)
		return 1;
	else
		printf("your command is not recognized\n");
	return 0;
}

void takeObject(struct parsed_command pc, struct Room room) {
	int i, j, n;
	for (j = 0; j < 8; j++)
	{
		if (strcmp(pc.noun1, objArray[j].name) == 0)
		{
			printf("Confirmed that you got %s\n", objArray[j].name);
			n = 0;

			do {
				if (invArray.name[n] == '\0')
				{
					invArray.name[n] = calloc(255, sizeof(char));
					invArray.room[n] = calloc(255, sizeof(char));
					invArray.description[n] = calloc(255, sizeof(char));
					strcpy(invArray.name[n], objArray[j].name);
					strcpy(invArray.room[n], objArray[j].room);
					strcpy(invArray.description[n], objArray[j].description);
					invArray.invCount++;

					for (i = 0; i < room.numObjects; i++) {
						if (strcmp(invArray.name[n], room.object[i]) == 0) {
							strcpy(room.object[i], "NA");
							room.numObjects--;
						}
					}

					n = 0;
				}
				else
					n++;
			} while (n != 0);
		}
	}

}

void dropObject(struct parsed_command pc, struct Room room) {
	int i, j;
	for (i = 0; i < invArray.invCount; i++) {
		if (strcmp(pc.noun1, invArray.name[i]) == 0) {
			for (j = i; j < invArray.invCount; j++) {
				if (j == invArray.invCount - 1) {
					invArray.name[j] = '\0';
					invArray.room[j] = '\0';
					invArray.description[j] = '\0';
					invArray.invCount--;
					break;
				}
				else {
					invArray.name[j] = invArray.name[j + 1];
					invArray.room[j] = invArray.room[j + 1];
					invArray.description[j] = invArray.description[j + 1];
				}
			}
		}
	}
}


void checkInventory(struct parsed_command pc) {
	int i;
	printf("Inventory:\n");
	for ( i = 0; i < invArray.invCount; i++) {
		printf("\t%s\n", invArray.name[i]);
	}
}