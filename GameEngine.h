/*********************************************************************
 ** Program Filename: GameEngine.h
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: runs adventure game; takes input from user and moves
 **      them along in the game
 ** Input: command line input
 ** Output: game response
 *********************************************************************/

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "RoomLoader.h"
#include "ObjectLoader.h"

struct Room rooms[16];
struct Object objArray[9];
struct Inventory invArray;
struct parsed_command pc;

void intro();
void getInput(char *inputBuff);
void runGame(struct Room *rooms, struct Object *objArray, struct Inventory invArray);
int examineRoom(struct Room *room, struct parsed_command pc);
void list();
void takeObject(struct parsed_command pc, struct Room *room);
void dropObject(struct parsed_command pc, struct Room *room);
void checkInventory(struct parsed_command pc);
void moveFeature(struct parsed_command pc, struct Room *room);
void hitFeature(struct parsed_command pc, struct Room *room);
void openFeature(struct parsed_command pc, struct Room *room);
void save(struct Room *curRoom);

#endif
