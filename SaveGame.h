/***************************************************************************
 ** Program Filename: SaveGame.h
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Description: saves players game into gameState files
 ** Input: 
 ** Output: new gameState files created for player
 *********************************************************************/

#ifndef SAVEGAME_H
#define SAVEGAME_H

//#include "GameEngine.h"
#include "RoomLoader.h"
#include "ObjectLoader.h"

typedef struct Room Room;
typedef struct Object Object;
typedef struct Inventory Inventory;

void writeRoomData(Room *room, char newDirName[256]);
void writeObjectData(Object *object, char newDirName[256]);
void writePlayerInventory(Inventory *inv, char newDirName[256]);

#endif