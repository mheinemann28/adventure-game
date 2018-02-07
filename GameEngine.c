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
	/*
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
	*/
	readRooms(rooms, "rooms");

	connectRooms(rooms);

	intro();
	runGame(rooms);

	return 0;
}

void connectRooms(struct Room *rooms) {
	int i;
	int j;
	int k;

	//loop through room to add exits
	for (i = 0; i < 11; i++) {
		k = 0;
		//rooms[i].numExits = k;

		//loop through potential exits
		for (j = 0; j < 11; j++) {
			//add exits to Library
			if (strcmp(rooms[i].name, "Library") == 0) {
				if (strcmp(rooms[j].name, "Cat Kingdom") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northeast";
					k++;
					printf("setting numexits\n");
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Courtyard") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southeast";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Doll Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "south";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits to Doll Room
			if (strcmp(rooms[i].name, "Doll Room") == 0) {
				if (strcmp(rooms[j].name, "Library") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "north";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Courtyard") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Basement") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "south";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for basement
			if (strcmp(rooms[i].name, "Basement") == 0) {
				if (strcmp(rooms[j].name, "Doll Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Courtyard") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northeast";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Riddle Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Cat Kingdom
			if (strcmp(rooms[i].name, "Cat Kingdom") == 0) {
				if (strcmp(rooms[j].name, "Library") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "west";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Tennis Court") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for CourtYard
			if (strcmp(rooms[i].name, "Courtyard") == 0) {
				if (strcmp(rooms[j].name, "Library") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Doll Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Basement") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "south";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Tennis Court") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Tennis Court
			if (strcmp(rooms[i].name, "Tennis Court") == 0) {
				if (strcmp(rooms[j].name, "Cat Kingdom") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Courtyard") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Cage Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Riddle Room
			if (strcmp(rooms[i].name, "Riddle Room") == 0) {
				if (strcmp(rooms[j].name, "Basement") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "west";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Storage") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "north";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Ghost Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Cage Room
			if (strcmp(rooms[i].name, "Cage Room") == 0) {
				if (strcmp(rooms[j].name, "Tennis Court") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "west";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Storage") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "south";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Music Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northeast";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Garage") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southeast";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Storage
			if (strcmp(rooms[i].name, "Storage Room") == 0) {
				if (strcmp(rooms[j].name, "Cage Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "north";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Riddle Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Ghost Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southeast";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Garage") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Ghost Room
			if (strcmp(rooms[i].name, "Ghost Room") == 0) {
				if (strcmp(rooms[j].name, "Riddle Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "west";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Storage") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "north";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Animal Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Music Room
			if (strcmp(rooms[i].name, "Music Room") == 0) {
				if (strcmp(rooms[j].name, "Cage Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "west";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Bar Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Garage
			if (strcmp(rooms[i].name, "Garage") == 0) {
				if (strcmp(rooms[j].name, "Cage Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Storage") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Bar Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Animal Room
			if (strcmp(rooms[i].name, "Animal Room") == 0) {
				if (strcmp(rooms[j].name, "Ghost Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "west";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Bar Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "north";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Cafe") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "east";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Bar Room
			if (strcmp(rooms[i].name, "Bar Room") == 0) {
				if (strcmp(rooms[j].name, "Music Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "northwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Garage") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "southwest";
					k++;
					rooms[i].numExits = k;
				}
				if (strcmp(rooms[j].name, "Animal Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "south";
					k++;
					rooms[i].numExits = k;
				}
			}
			//add exits for Cafe
			if (strcmp(rooms[i].name, "Cafe") == 0) {
				if (strcmp(rooms[j].name, "Animal Room") == 0) {
					rooms[i].Exits[k] = &rooms[j];
					rooms[i].exitDirection[k] = "west";
					k++;
					rooms[i].numExits = k;
				}
			}
		}
	}
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
	struct parsed_command pc;
	char *noun;
	char *tempRoomName;
	//buffer to hold keyboard input data
	char inputBuff[255];
	memset(inputBuff, '\0', sizeof(inputBuff));

	tempRoomName = rooms[1].name;
	
//	if(strcmp(tempRoomName, rooms[1].name) == 0)
//		printf("matched here\n");

	//mark start room as visited
//	rooms[0].visited = 1;

	while (1) {
		//begin_loop:
		//get command from user
		if (rooms[1].visited == 1) {
			getInput(inputBuff);
			pc = parseCommand(inputBuff);
			noun = pc.noun1;
		}

		for (i = 0; i < 11; i++) {
			if ((strcmp(rooms[i].type, "START") == 0) && rooms[i].visited == 0) {
				printf("%s\n\n", rooms[i].longDescription);
				printf("current room: %s\n", rooms[i].name);
				rooms[i].visited = 1;
			}
			if (strcmp(tempRoomName, rooms[i].name) == 0) {
				
				for (j = 0; j < rooms[i].numExits; j++) {
					
					if (strcmp(pc.noun1, rooms[i].exitDirection[j]) == 0) {
						if (strcmp(rooms[i].type, "END") == 0) {
							printf("\n%s\n\n", rooms[i].Exits[j]->longDescription);
							printf("Made it to END\n");
							exit(1);
						}
						else if (rooms[i].Exits[j]->visited == 0) {
							printf("\n%s\n\n", rooms[i].Exits[j]->longDescription);
							tempRoomName = rooms[i].Exits[j]->name;
							printf("current room: %s\n", tempRoomName);
							rooms[i].Exits[j]->visited = 1;
						}
						else {
							printf("\n%s\n\n", rooms[i].Exits[j]->shortDescription);
							tempRoomName = rooms[i].Exits[j]->name;
							printf("current room: %s\n", tempRoomName);
						}
						goto continue_game;

					}
				}
			}
		}
		continue_game:
		memset(inputBuff, '\0', sizeof(inputBuff));
		/*	for (i = 0; i < 10; i++) {
				if (strcmp(rooms[i].type, "START") == 0 && rooms[i].visited == 0) {
					printf("%s\n\n", rooms[i].longDescription);
					rooms[i].visited = 1;
				}
				for (j = 0; j < rooms[i].numExits; j++) {

					if (strcmp(pc.noun1, rooms[i].exitDirection[j]) == 0) {
						if (strcmp(rooms[i].type, "END") == 0) {
							printf("\n%s\n\n", rooms[i].Exits[j]->longDescription);
							printf("Made it to END\n");
							exit(1);
						}
						else if (rooms[i].visited == 0) {
							printf("\n%s\n\n", rooms[i].Exits[j]->longDescription);
							rooms[i].visited = 1;
						}
						else
							printf("\n%s\n\n", rooms[i].Exits[j]->shortDescription);
						goto begin_loop;
						//printf("Exits:\n");

		//				for (j = 0; j < rooms[i].numExits; j++) {
		//					printf("    %s\n", rooms[i].Exit[j]->name);
		//				}
					}
				}
			}*/
	}
}

void getInput(char *inputBuff) {
	//get command from user
	memset(inputBuff, '\0', sizeof(inputBuff));
	printf("\nCommand: ");
	fgets(inputBuff, 255, stdin);
	inputBuff[strlen(inputBuff) - 1] = '\0';
}

