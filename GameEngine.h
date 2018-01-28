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

#include "GameEngine_helpers.h"
#include "GameStateLoader.h"
#include "RoomLoader.h"

struct Room rooms[15];

void intro();
void runGame(struct Room *rooms);
void getInput(char *inputBuff);

#endif

