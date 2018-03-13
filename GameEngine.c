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
#include "RoomLoader.h"
#include "ObjectLoader.h"
#include "SaveGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

/*********************************************************************
 ** Function: main();
 ** Description: starts adventure game
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: program exits
 *********************************************************************/

int main() {
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

	char input[255];
	char buff[255];
	memset(input, '\0', sizeof(input));

	printf("%s\n", intro);
	printf("%s\n", instructions);
	printf("%s\n", sendoff);

	while (1) {
		printf("\nDo you have a saved game you would like to load? ");
		fgets(input, 25, stdin);
		strtok(input, "\n");

		if (strcmp(input, "yes") == 0 || strcmp(input, "Yes") == 0 || strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) {

			memset(input, '\0', sizeof(input));
			printf("\nType in your save name: ");
			fgets(input, 255, stdin);
			strtok(input, "\n");

			memset(buff, '\0', sizeof(buff));
			strcpy(buff, "gamestates/");
			strcat(buff, input);


			//check if directory exists
			DIR *dir = opendir(buff);

			if (dir) {
				closedir(dir);

				//load game
				readRooms(rooms, buff);
				readObjects(objArray, buff);
				readInventory(&invArray, buff);

				return;
			}
			else if (ENOENT == errno) {
				printf("Directory does not exist\n");
			}
			else {
				printf("Problem opening directory\n");
			}
		}
		else if (strcmp(input, "no") == 0 || strcmp(input, "No") == 0 || strcmp(input, "n") == 0 || strcmp(input, "N") == 0) {
			readRooms(rooms, "rooms");
			readObjects(objArray, "rooms");
			readInventory(&invArray, "rooms");
			return;
		}
	}
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

	for (i = 0; i < 15; i++) {
		if (strcmp(rooms[i].type, "START") == 0) {
			tempRoomName = rooms[i].name;
			strcpy(rooms[i].type, "MID");
			break;
		}
	}

	while (1) {

		for (i = 0; i < 16; i++) {

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
					}
				}
				printf("\nInvalid exit direction. You are still in %s\n", tempRoomName);
				goto blocked_door;
			}
		}
continue_game:
		//	printf("i: %d\n", i);
		if (strcmp(rooms[i].type, "END") == 0)
		{
			printf("Reached the end. \n");
			exit(0);
		}
	}
}

/*********************************************************************
 ** Function: examineRoom(struct Room *room, struct parse_command pc)
 ** Description: based on player input this function will print out
 ** 	descriptions of different feature, or call the appropriate
 ** 	function to interact with objects.
 ** Parameters: struct parse_command pc, struct Room *room
 ** Pre-Conditions: none
 ** Post-Conditions: appropriate functions are called or descriptions
 ** 	are printed out.
 *********************************************************************/
int examineRoom(struct Room * room, struct parsed_command pc)
{
	int i, j, count;
	char tempString[30];
	memset(tempString, '\0', sizeof(tempString));

	// if player chooses to look at features in room
	if ((strcmp(pc.verb, "look") == 0) && (strcmp(pc.noun1, "inventory") != 0))
	{
		strcat(tempString, pc.noun1);

		// if player chooses to look at whole room, print out general information
		if (strcmp(pc.noun1, "room") == 0) {
			// print current room
			printf("\nCurrent room: %s\n", room->name);

			// print out all features
			printf("\nFeatures:\n");
			for (j = 0; j < MAX_FEATURES; j++) {
				printf("\t%d. %s\n", j + 1, room->feature[j].name);
			}

			// print out any objects that were dropped and left on the floor
			count = 0;
			printf("\nObjects on floor\n");
			for (j = 0; j < 9; j++) {
				if (strcmp(objArray[j].room, room->name) == 0) {
					if (strcmp(objArray[j].dropped, "yes") == 0) {
						count++;
						printf("\t%d. %s\n", count, objArray[j].name);
					}
				}
			}

			// if no dropped object is found
			if (count == 0) {
				printf("\tnone\n");
			}
		}

		// loop through room features to print out feature descriptions
		for (i = 0; i < MAX_FEATURES; i++)
		{
			// if feature is enemy and still alive print first description
			if (strcmp(tempString, room->feature[i].name) == 0 && strcmp(room->feature[i].enemy, "Yes") == 0) {
				printf("%s\n", room->feature[i].description1);
				room->feature[i].firstLook = 1;
			}
			// if feature contains an object print first description
			else if (strcmp(tempString, room->feature[i].name) == 0 && room->feature[i].containObject == 1)
			{
				// if feature is blocked by enemy, let player know
				if (i == MAX_FEATURES - 1 && strcmp(room->feature[i - 1].enemy, "Yes") == 0) {
					printf("%s is blocking the %s\n", room->feature[i - 1].name, room->feature[i].name);
				}
				if (i == 0 && strcmp(room->feature[i + 1].enemy, "Yes") == 0) {
					printf("%s is blocking the %s\n", room->feature[i + 1].name, room->feature[i].name);
				}
				else
					printf("%s\n", room->feature[i].description1);
			}
			// if feature does not contain object or enemy is dead print description 2
			else if (strcmp(tempString, room->feature[i].name) == 0 && room->feature[i].containObject == 0 && strcmp(room->feature[i].enemy, "No") == 0) {
				// if blocked by enemy let player know
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
	// if user chooses to look at inventory
	else if ((strcmp(pc.verb, "look") == 0) && (strcmp(pc.noun1, "inventory") == 0))
		checkInventory(pc);
	// if user chooses to open feature
	else if ((strcmp(pc.verb, "open") == 0)) {
		openFeature(pc, room);
	}
	// if user chooses to take object
	else if (strcmp(pc.verb, "take") == 0)
		takeObject(pc, room);
	// if user chooses to drop object
	else if (strcmp(pc.verb, "drop") == 0)
		dropObject(pc, room);
	// if user chooses to go through door
	else if (strcmp(pc.verb, "go") == 0)
		return 1;
	// if user chooses to move feature
	else if (strcmp(pc.verb, "move") == 0)
		moveFeature(pc, room);
	// if user chooses to hit feature
	else if (strcmp(pc.verb, "hit") == 0)
		hitFeature(pc, room);
	// if user chooses to save game
	else if (strcmp(pc.verb, "save") == 0)
		save(room);
	// if user command is not listed
	else
		printf("your command is not recognized\n");
	return 0;
}

/*********************************************************************
 ** Function: takeObject(struct parse_command pc, struct Room *room)
 ** Description: adds in game objects to players inventory if player
 ** 	chooses to pick one up.
 ** Parameters: struct parse_command pc, struct Room *room
 ** Pre-Conditions: user must choose to take an object through the
 ** 	command line.
 ** Post-Conditions: players inventory is updated with selected object
 ** 	or if selected object is unavailable or missing message is
 ** 	outputed to user explaining so.
 *********************************************************************/
void takeObject(struct parsed_command pc, struct Room * room) {
	int i, j, n, k, tempCount;

	// loop through all objects
	for (j = 0; j < 9; j++)
	{
		// check if object exists and is in current room
		if (strcmp(pc.noun1, objArray[j].name) == 0 && strcmp(room->name, objArray[j].room) == 0)
		{
			n = 0;
			tempCount = invArray.invCount;
			// loop to find next available space in inventory array
			do {
				if (invArray.name[n] == '\0')
				{
					// loop through features in current room
					for (k = 0; k < MAX_FEATURES; k++) {

						// if feature contains object add to inventory
						if (room->feature[k].containObject == 1) {

							// allocate space
							invArray.name[n] = calloc(255, sizeof(char));
							invArray.room[n] = calloc(255, sizeof(char));
							invArray.usedFor[n] = calloc(255, sizeof(char));

							// add object information to inventory
							strcpy(invArray.name[n], objArray[j].name);
							strcpy(invArray.room[n], objArray[j].room);
							strcpy(invArray.usedFor[n], objArray[j].usedFor);

							// increment inventory count
							invArray.invCount++;

							// loop through objects in room data and remove object picked up
							for (i = 0; i < room->numObjects; i++) {
								if (strcmp(invArray.name[n], room->object[i]) == 0) {
									strcpy(room->object[i], "NA");
									room->numObjects--;
								}
							}

							printf("%s was added to your inventory.\n", invArray.name[n]);

							break;
						}
					}



					// if object was not found with feature check floor
					if (room->feature[k].containObject == 0) {
						// loop through all objects in room
						for (k = 0; k < room->numObjects; k++) {
							// check if object was dropped
							if (strcmp(objArray[j].name, pc.noun1) == 0 && strcmp(objArray[j].dropped, "yes") == 0) {
								// allocate space
								invArray.name[n] = calloc(255, sizeof(char));
								invArray.room[n] = calloc(255, sizeof(char));
								invArray.usedFor[n] = calloc(255, sizeof(char));

								// add object information to inventory
								strcpy(invArray.name[n], objArray[j].name);
								strcpy(invArray.room[n], objArray[j].room);
								strcpy(invArray.usedFor[n], objArray[j].usedFor);

								// increment inventory count
								invArray.invCount++;

								room->numObjects--;

								strcpy(objArray[j].dropped, "no");

								printf("%s was added to your inventory.\n", invArray.name[n]);

								break;
							}
						}

						// if no other objects found print message saying so
						if (tempCount == invArray.invCount) {
							printf("There is no %s.\n", pc.noun1);
						}
					}

					// remove object flag from feature
					room->feature[k].containObject = 0;

					n = 0;
				}
				else
					n++;
			} while (n != 0);

			return;
		}

		// object exists but not in current room display message
		if (strcmp(pc.noun1, objArray[j].name) == 0 && strcmp(room->name, objArray[j].room) != 0) {
			printf("There is no %s.\n", pc.noun1);
			return;
		}
	}

	// if at this line object does not exist
	printf("There is no %s.\n", pc.noun1);
}

void dropObject(struct parsed_command pc, struct Room * room) {
	int i, j, k;
	for (i = 0; i < invArray.invCount; i++) {
		if (strcmp(pc.noun1, invArray.name[i]) == 0 || strcmp(pc.noun2, invArray.name[i]) == 0) {

				for (j = i; j < invArray.invCount; j++) {
					if (j == invArray.invCount - 1) {
						invArray.name[j] = '\0';
						invArray.room[j] = '\0';
						invArray.usedFor[j] = '\0';
						invArray.invCount--;
						room->numObjects++;

						for (k = 0; k < 9; k++)
						{
							if (strcmp(objArray[k].name, pc.noun1) == 0)
							{
								strcpy(objArray[k].room, room->name);
								strcpy(objArray[k].dropped, "yes");
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
	//		}
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

void moveFeature(struct parsed_command pc, struct Room * room) {
	int i, j;
	for (j = 0; j < room->numExits; j++) {
		for (i = 0; i < MAX_FEATURES; i++) {
			if (strcmp(room->blockedBy[j], room->feature[i].name) == 0 && strcmp(room->feature[i].name, pc.noun1) == 0) {
				printf("%s\n", room->feature[i].move1);

				strcpy(room->blockedBy[j], "NA");

				return;
			}
			else if (strcmp(room->feature[i].name, pc.noun1) == 0 && strcmp(room->feature[i].enemy, "Yes") == 0) {
				printf("%s\n", room->feature[i].move1);
				return;
			}
			else if (strcmp(room->feature[i].name, pc.noun1) == 0 && j == room->numExits - 1) {
				printf("%s\n", room->feature[i].move2);
				return;
			}
		}
	}
}

/*********************************************************************
 ** Function: hitFeature(struct parse_command pc, struct Room *room)
 ** Description: function is used when a player chooses to hit something
 ** 	within the game. This could be an enemy to defeat or other features.
 ** Parameters: struct parse_command pc, struct Room *room
 ** Pre-Conditions: user must choose to hit a feature through the
 ** 	command line.
 ** Post-Conditions: Appropriate message is displayed afterwards. If against
 ** 	enemy, it may be defeated through hit.
 *********************************************************************/
void hitFeature(struct parsed_command pc, struct Room * room) {
	int i, j, k, n;

	//check if we are using a key and that it belongs to correct door
	for (i = 0; i < invArray.invCount; i++) {
		if (strcmp(invArray.name[i], "key") == 0) {
			for (j = 0; j < room->numExits; j++) {
				if (strcmp(room->exitDirection[j], invArray.usedFor[i]) == 0) {
					printf("%s door is now unlocked\n", room->exitDirection[j]);
					strcpy(room->blockedBy[j], "NA");
					return;
				}
			}
			printf("wrong key for this door.\n");
			return;
		}
	}

	// Loop through features in room
	for (i = 0; i < MAX_FEATURES; i++) {

		// check if feature matches user input
		if (strcmp(pc.noun2, room->feature[i].name) == 0) {

			// Loop through inventory
			for (j = 0; j < invArray.invCount; j++) {

				// check if object is used
				if (strcmp(pc.noun1, invArray.name[j]) == 0) {

					// If corect object is used to defeat enemy, eliminate obstacle
					if (strcmp(invArray.usedFor[j], room->feature[i].name) == 0) {
						printf("%s\n", room->feature[i].hit2);
						strcpy(room->feature[i].enemy, "No");

						// if enemy was blocking any exits, free them up
						for (k = 0; k < room->numExits; k++) {
							if (strcmp(room->blockedBy[k], room->feature[i].name) == 0)
								strcpy(room->blockedBy[k], "NA");
						}

						// if feature is the dog, bone must be removed from inventory after given
						if (strcmp(room->feature[i].name, "dog") == 0) {
							for (k = j; k < invArray.invCount; k++) {
								if (k == invArray.invCount - 1) {
									invArray.name[k] = '\0';
									invArray.room[k] = '\0';
									invArray.usedFor[k] = '\0';
									invArray.invCount--;

									break;
								}
								else {
									invArray.name[k] = invArray.name[k + 1];
									invArray.room[k] = invArray.room[k + 1];
									invArray.usedFor[k] = invArray.usedFor[k + 1];
								}
							}
						}

						return;
					}
					else {
						printf("%s\n", room->feature[i].hit1);
						return;
					}
				}
				else if (j == invArray.invCount - 1) {
					printf("That is not in your inventory!\n");
					return;
				}
			}
			if (invArray.invCount == 0) {
				printf("You inventory is empty!\n");
				return;
			}
		}
		else if (strcmp(pc.noun1, room->feature[i].name) == 0)
		{
			//loop through object array to check if object needed for enemy
			for (n = 0; n < 9; n++) {
				if (strcmp(objArray[n].usedFor, room->feature[i].name) == 0) {
					for (j = 0; j < invArray.invCount; j++) {
						if (strcmp(pc.noun2, invArray.name[j]) == 0) {
							if (strcmp(invArray.usedFor[j], room->feature[i].name) == 0) {
								printf("%s\n", room->feature[i].hit2);
								strcpy(room->feature[i].enemy, "No");
								for (k = 0; k < room->numExits; k++) {
									if (strcmp(room->blockedBy[k], room->feature[i].name) == 0)
										strcpy(room->blockedBy[k], "NA");
								}

								if (strcmp(room->feature[i].name, "dog") == 0) {
									for (k = j; k < invArray.invCount; k++) {
										if (k == invArray.invCount - 1) {
											invArray.name[k] = '\0';
											invArray.room[k] = '\0';
											invArray.usedFor[k] = '\0';
											invArray.invCount--;

											break;
										}
										else {
											invArray.name[k] = invArray.name[k + 1];
											invArray.room[k] = invArray.room[k + 1];
											invArray.usedFor[k] = invArray.usedFor[k + 1];
										}
									}
								}
								return;
							}
							else {
								printf("%s does nothing to %s\n", invArray.name[j], room->feature[i].name);
								return;
							}
						}
						else if (strlen(pc.noun2) == 0) {
							printf("%s\n", room->feature[i].hit1);
							break;
						}
						else if (j == invArray.invCount - 1) {
							printf("That is not in your inventory!\n");
							return;
						}
					}
					if (invArray.invCount == 0) {
						printf("%s\n", room->feature[i].hit1);
					}
					return;
				}
			}

			printf("%s\n", room->feature[i].hit2);
			strcpy(room->feature[i].enemy, "No");
			return;
		}
	}
}

void openFeature(struct parsed_command pc, struct Room * room) {
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

void save(struct Room *curRoom) {
	char input[255];
	char buff[255];
	char newDir[255];
	int i, getName;

	strcpy(curRoom->type, "START");


	while (1) {
		getName = 1;
		while (getName) {
			memset(input, '\0', sizeof(input));
			printf("\ncreate a save name: ");
			fgets(input, 255, stdin);
			strtok(input, "\n");
			if (isspace(input[strlen(input) - 1]) != 0)
				input[strlen(input) - 1] = '\0';

			for (i = 0; i < strlen(input); i++) {
				if (input[i] == ' ')
					printf("\nYou save name cannot contain any spaces.\n");
				else if (i == strlen(input) - 1) {
					getName = 0;
				}
			}
		}

		memset(buff, '\0', sizeof(buff));
		strcat(buff, input);


		//check if directory exists
		DIR *dir = opendir(buff);

		if (dir) {
			closedir(dir);

			printf("\nSave name already exists\n");
		}
		else if (ENOENT == errno) {
			memset(newDir, '\0', sizeof(newDir));
			strcpy(newDir, "gamestates/");
			strcat(newDir, buff);
			mkdir(newDir, 0700);

			writeRoomData(rooms, buff);
			writeObjectData(objArray, buff);
			writePlayerInventory(&invArray, buff);

			printf("\nGame successfully saved\n");
			printf("\nThanks for playing!\n");

			break;
		}
		else {
			printf("Problem saving directory\n");
		}
	}
	exit(0);
}
