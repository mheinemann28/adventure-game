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
	int i, j, m, n, k;
	char *noun;
	char *tempRoomName;
	//buffer to hold keyboard input data
	char inputBuff[255];
	memset(inputBuff, '\0', sizeof(inputBuff));

	tempRoomName = rooms[0].name;
	invArray.invCount = 0;

	while (1) {

		for (i = 0; i < 6; i++) {

			if (strcmp(tempRoomName, rooms[i].name) == 0) {
				printf("--------------------------------------------------------------------------------------------\n");
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
					printf("\t%d. %s\n", j + 1, rooms[i].feature[j].name);
				}

				rooms[i].visited = 1;

				do {
blocked_door:
					getInput(inputBuff);
					pc = parseCommand(inputBuff);
					//noun = pc.noun1;

					m = examineRoom(&rooms[i], pc);
				} while (m == 0);


				for (j = 0; j < rooms[i].numExits; j++) {
					if (strcmp(pc.noun1, rooms[i].exitDirection[j]) == 0 && strcmp(rooms[i].blockedBy[j], "NA") == 0) {

						tempRoomName = rooms[i].Exits[j];

						goto continue_game;
					}
					else if (strcmp(pc.noun1, rooms[i].exitDirection[j]) == 0 && strcmp(rooms[i].blockedBy[j], "NA") != 0) {
						if (strcmp(rooms[i].blockedBy[j], "key") == 0) {
							printf("The door is locked, you must find the key\n");
						}
						else
							printf("The door is blocked by %s\n", rooms[i].blockedBy[j]);
						goto blocked_door;
						/*for (k = 0; k < MAX_FEATURES; k++) {
							if (rooms[i].feature[k].obstacle == 1) {
								printf("The door is blocked by %s\n", rooms[i].feature[k].name);
								goto blocked_door;
							}
							else
								printf("The door is locked\n");
						}*/
					}
				}
				printf("\nInvalid exit direction. You are still in %s\n", tempRoomName);

			}
		}
continue_game:
		//	printf("i: %d\n", i);
		if (strcmp(tempRoomName, "Cafe") == 0)
		{
			printf("Reached the end. \n");
			exit(0);
		}
	}
}


int examineRoom(struct Room *room, struct parsed_command pc)
{
	int i;
	char tempString[30];
	memset(tempString, '\0', sizeof(tempString));
//	printf("pc.verb: %s\n", pc.verb);
//	printf("noun1: %s\n", pc.noun1);
//	printf("noun2: %s\n", pc.noun2);

	if ((strcmp(pc.verb, "look at") == 0) && (strcmp(pc.noun1, "inventory") != 0))
	{
		strcat(tempString, pc.noun1);
		for (i = 0; i < MAX_FEATURES; i++)
		{
			if (strcmp(tempString, room->feature[i].name) == 0 && strcmp(room->feature[i].enemy, "Yes") == 0) {
				printf("%s\n", room->feature[i].description1);
				room->feature[i].firstLook = 1;
			}
			else if (strcmp(tempString, room->feature[i].name) == 0 && room->feature[i].containObject == 1)
			{
				if (i == MAX_FEATURES - 1 && strcmp(room->feature[i - 1].enemy, "Yes") == 0) {
					printf("%s is blocking the %s\n", room->feature[i - 1].name, room->feature[i].name);
				}
				if (i == 0 && strcmp(room->feature[i + 1].enemy, "Yes") == 0) {
					printf("%s is blocking the %s\n", room->feature[i + 1].name, room->feature[i].name);
				}
				else
					printf("%s\n", room->feature[i].description1);
			}
			else if (strcmp(tempString, room->feature[i].name) == 0 && room->feature[i].containObject == 0 && strcmp(room->feature[i].enemy, "No") == 0) {
				if (i == MAX_FEATURES - 1 && strcmp(room->feature[i - 1].enemy, "Yes") == 0) {
					printf("%s is blocking the %s\n", room->feature[i - 1].name, room->feature[i].name);
				}
				if (i == 0 && strcmp(room->feature[i + 1].enemy, "Yes") == 0) {
					printf("%s is blocking the %s\n", room->feature[i + 1].name, room->feature[i].name);
				}
				else
					printf("%s\n", room->feature[i].description2);
			}
		}
	}
	else if ((strcmp(pc.verb, "look at") == 0) && (strcmp(pc.noun1, "inventory") == 0))
		checkInventory(pc);
	else if ((strcmp(pc.verb, "open") == 0)) {
		openFeature(pc, room);
	}
	else if (strcmp(pc.verb, "take") == 0)
		takeObject(pc, room);
	else if (strcmp(pc.verb, "drop") == 0)
		dropObject(pc, room);
	else if (strcmp(pc.verb, "go") == 0)
		return 1;
	else if (strcmp(pc.verb, "move") == 0)
		moveFeature(pc, room);
	else if (strcmp(pc.verb, "hit") == 0)
		hitFeature(pc, room);
	else
		printf("your command is not recognized\n");
	return 0;
}

void takeObject(struct parsed_command pc, struct Room *room) {
	int i, j, n;
	for (j = 0; j < 8; j++)
	{
		printf("objArray[%d]: %s\n", j, objArray[j].name);
		if (strcmp(pc.noun1, objArray[j].name) == 0 && strcmp(room->name, objArray[j].room) == 0)
		{
			printf("Confirmed that you got %s\n", objArray[j].name);
			n = 0;

			do {
				if (invArray.name[n] == '\0')
				{
				//	printf("invArray.name[%d]: %s\n", n, invArray.name[n]);
					invArray.name[n] = calloc(255, sizeof(char));
					invArray.room[n] = calloc(255, sizeof(char));
					invArray.usedFor[n] = calloc(255, sizeof(char));
					strcpy(invArray.name[n], objArray[j].name);
					strcpy(invArray.room[n], objArray[j].room);
					strcpy(invArray.usedFor[n], objArray[j].usedFor);
				//	printf("invArray.name[%d]: %s\n", n, invArray.name[n]);
				//	printf("invArray.room[%d]: %s\n", n, invArray.room[n]);
				//	printf("invArray.usedFor[%d]: %s\n", n, invArray.usedFor[n]);
					invArray.invCount++;

					for (i = 0; i < room->numObjects; i++) {
						if (strcmp(invArray.name[n], room->object[i]) == 0) {
							strcpy(room->object[i], "NA");
							room->numObjects--;
						}
					}

					printf("%s was added to your inventory.\n", invArray.name[n]);

					for (i = 0; i < MAX_FEATURES; i++) {
						if (room->feature[i].containObject == 1) {
							room->feature[i].containObject = 0;
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

void dropObject(struct parsed_command pc, struct Room *room) {
	int i, j, k;
	for (i = 0; i < invArray.invCount; i++) {
		if (strcmp(pc.noun1, invArray.name[i]) == 0 || strcmp(pc.noun2, invArray.name[i]) == 0) {
			if (strcmp(invArray.name[i], "key") == 0) {
				for (j = 0; j < room->numExits; j++) {
					if (strcmp(room->exitDirection[j], invArray.usedFor[i]) == 0) {
						printf("%s door is now unlocked\n", room->exitDirection[j]);
						strcpy(room->blockedBy[j], "NA");
						return;
					}
				}
				printf("wrong key for this door.\n");
			}
			else {
				for (j = i; j < invArray.invCount; j++) {
					if (j == invArray.invCount - 1) {
						invArray.name[j] = '\0';
						invArray.room[j] = '\0';
						invArray.usedFor[j] = '\0';
						invArray.invCount--;
						for (k = 0; k < 8; k++)
						{
							if (strcmp(objArray[k].name, pc.noun1) == 0)
							{
								strcpy(objArray[k].room, room->name);
								printf("%s is now in %s\n", pc.noun1, room->name);
							}
						}
						break;
					}
					else {
						invArray.name[j] = invArray.name[j + 1];
						invArray.room[j] = invArray.room[j + 1];
						invArray.usedFor[j] = invArray.usedFor[j + 1];
					}
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

void moveFeature(struct parsed_command pc, struct Room *room) {
	int i, j;
	for (j = 0; j < room->numExits; j++) {
		for (i = 0; i < MAX_FEATURES; i++) {
			if (strcmp(room->blockedBy[j], room->feature[i].name) == 0 && strcmp(room->feature[i].name, pc.noun1) == 0) {
				printf("%s\n", room->feature[i].move1);

				strcpy(room->blockedBy[j], "NA");

				return;
			}
			else if (strcmp(room->feature[i].name, pc.noun1) == 0 && j == room->numExits - 1) {
				printf("%s\n", room->feature[i].move2);
				return;
			}
		}
	}
}

void hitFeature(struct parsed_command pc, struct Room *room) {
	int i, j;
	printf("pc.noun1: %s\n", pc.noun1);
	printf("pc.noun2: %s\n", pc.noun2);
	for (i = 0; i < MAX_FEATURES; i++) {
		if (strcmp(pc.noun2, room->feature[i].name) == 0) {
			for (j = 0; j < invArray.invCount; j++) {
				if (strcmp(pc.noun1, invArray.name[j]) == 0) {
					if (strcmp(invArray.usedFor[j], room->feature[i].name) == 0) {
						printf("%s\n", room->feature[i].hit2);
						strcpy(room->feature[i].enemy, "No");
					}
					else
						printf("%s\n", room->feature[i].hit1);
				}
				else
					printf("That is not in your inventory!\n");
			}
			if (invArray.invCount == 0)
				printf("You inventory is empty!\n");
		}
		else if (strcmp(pc.noun1, room->feature[i].name) == 0)
		{
			printf("%s\n", room->feature[i].hit1);
			strcpy(room->feature[i].enemy, "No");
		}
	}
}

void openFeature(struct parsed_command pc, struct Room *room) {
	int i;
	for (i = 0; i < MAX_FEATURES; i++) {
		if (i == MAX_FEATURES - 1 && strcmp(room->feature[i - 1].enemy, "Yes") == 0) {
			printf("%s is blocking the %s\n", room->feature[i - 1].name, room->feature[i].name);
		}
		else if (i == 0 && strcmp(room->feature[i + 1].enemy, "Yes") == 0) {
			printf("%s is blocking the %s\n", room->feature[i + 1].name, room->feature[i].name);
		}
		else if (strcmp(pc.noun1, room->feature[i].name) == 0) {
			if (room->feature[i].containObject == 1) {
				printf("%s\n", room->feature[i].open1);
			}
			else
				printf("%s\n", room->feature[i].open2);
		}
	}
}