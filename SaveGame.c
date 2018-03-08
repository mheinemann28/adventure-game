/*********************************************************************
 ** Program Filename: SaveGame.c
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: writes room and player data to txt files
 ** Input:
 ** Output: new gameState files created for player
 *********************************************************************/
#include "SaveGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 32766

void writeRoomData(Room *room, char newDirName[256]) {
	int i;

	FILE* file;
	char *dirName = "gamestates";
	char fileName[BUFFER_SIZE];
	char buff[BUFFER_SIZE];
	char intBuff[10];
	memset(buff, '\0', sizeof(buff));

	for (i = 0; i < 15; i++) {
		sprintf(fileName, "%s/%s/room-%d.txt", dirName, newDirName, i + 1);

		file = fopen(fileName, "w");


		memset(buff, '\0', sizeof(buff));
		memset(intBuff, '\0', sizeof(intBuff));
		strcpy(buff, "VISITED: ");
		sprintf(intBuff, "%d", room[i].visited);
		strcat(buff, intBuff);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "ROOMTYPE: ");
		strcat(buff, room[i].type);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "ROOMNAME: ");
		strcat(buff, room[i].name);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "LONGDESCRIPTION: ");
		strcat(buff, room[i].longDescription);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "SHORTDESCRIPTION: ");
		strcat(buff, room[i].shortDescription);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "FEATURENAME1: ");
		strcat(buff, room[i].feature[0].name);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		memset(intBuff, '\0', sizeof(intBuff));
		strcpy(buff, "F1CONTAINOBJECT: ");
		sprintf(intBuff, "%d", room[i].feature[0].containObject);
		strcat(buff, intBuff);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1LOOK1: ");
		strcat(buff, room[i].feature[0].description1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1LOOK2: ");
		strcat(buff, room[i].feature[0].description2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1HIT1: ");
		strcat(buff, room[i].feature[0].hit1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1HIT2: ");
		strcat(buff, room[i].feature[0].hit2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1OPEN1: ");
		strcat(buff, room[i].feature[0].open1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1OPEN2: ");
		strcat(buff, room[i].feature[0].open2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1MOVE1: ");
		strcat(buff, room[i].feature[0].move1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F1MOVE2: ");
		strcat(buff, room[i].feature[0].move2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "FEATURENAME2: ");
		strcat(buff, room[i].feature[1].name);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		memset(intBuff, '\0', sizeof(intBuff));
		strcpy(buff, "F2CONTAINOBJECT: ");
		sprintf(intBuff, "%d", room[i].feature[1].containObject);
		strcat(buff, intBuff);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2LOOK1: ");
		strcat(buff, room[i].feature[1].description1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2LOOK2: ");
		strcat(buff, room[i].feature[1].description2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2HIT1: ");
		strcat(buff, room[i].feature[1].hit1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2HIT2: ");
		strcat(buff, room[i].feature[1].hit2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2OPEN1: ");
		strcat(buff, room[i].feature[1].open1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2OPEN2: ");
		strcat(buff, room[i].feature[1].open2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2MOVE1: ");
		strcat(buff, room[i].feature[1].move1);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "F2MOVE2: ");
		strcat(buff, room[i].feature[1].move2);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		memset(intBuff, '\0', sizeof(intBuff));
		strcpy(buff, "NUMOBJ: ");
		sprintf(intBuff, "%d", room[i].numObjects);
		strcat(buff, intBuff);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "OBJECT: ");
		strcat(buff, room[i].object[0]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		memset(intBuff, '\0', sizeof(intBuff));
		strcpy(buff, "NUMEXITS: ");
		sprintf(intBuff, "%d", room[i].numExits);
		strcat(buff, intBuff);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT1DIRECTION: ");
		strcat(buff, room[i].exitDirection[0]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT2DIRECTION: ");
		strcat(buff, room[i].exitDirection[1]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT3DIRECTION: ");
		strcat(buff, room[i].exitDirection[2]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT4DIRECTION: ");
		strcat(buff, room[i].exitDirection[3]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT1NAME: ");
		strcat(buff, room[i].Exits[0]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT2NAME: ");
		strcat(buff, room[i].Exits[1]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT3NAME: ");
		strcat(buff, room[i].Exits[2]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT4NAME: ");
		strcat(buff, room[i].Exits[3]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT1BLOCK: ");
		strcat(buff, room[i].blockedBy[0]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT2BLOCK: ");
		strcat(buff, room[i].blockedBy[1]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT3BLOCK: ");
		strcat(buff, room[i].blockedBy[2]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "EXIT4BLOCK: ");
		strcat(buff, room[i].blockedBy[3]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "FEATURE1ENEMY?: ");
		strcat(buff, room[i].feature[0].enemy);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		strcpy(buff, "FEATURE2ENEMY?: ");
		strcat(buff, room[i].feature[1].enemy);
		fputs(buff, file);

		fclose(file);
	}
}

void writeObjectData(Object *object, char newDirName[256]) {
	int i;

	FILE* file;
	char *dirName = "gamestates";
	char fileName[500];
	char buff[BUFFER_SIZE];
	char intBuff[10];
	memset(buff, '\0', sizeof(buff));

	sprintf(fileName, "%s/%s/objects.txt", dirName, newDirName);

	file = fopen(fileName, "w");

	for (i = 0; i < 9; i++) {
		memset(buff, '\0', sizeof(buff));
		sprintf(buff, "OBJECT%dNAME: ", i + 1);
		strcat(buff, object[i].name);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		sprintf(buff, "OBJECT%dSTARTROOM", i + 1);
		strcat(buff, object[i].room);
		strcat(buff, "\n");
		fputs(buff, file);

		if (i == 8) {
			memset(buff, '\0', sizeof(buff));
			strcpy(buff, "USEDFOR: ");
			strcat(buff, object[i].usedFor);
			fputs(buff, file);
		}
		else{
			memset(buff, '\0', sizeof(buff));
			strcpy(buff, "USEDFOR: ");
			strcat(buff, object[i].usedFor);
			strcat(buff, "\n");
			fputs(buff, file);
		}
	}
	fclose(file);
}

void writePlayerInventory(Inventory *inv, char newDirName[256]){
	int i;

	FILE* file;
	char *dirName = "gamestates";
	char fileName[500];
	char buff[BUFFER_SIZE];
	char intBuff[10];
	memset(buff, '\0', sizeof(buff));

	sprintf(fileName, "%s/%s/inventory.txt", dirName, newDirName);

	file = fopen(fileName, "w");

	strcpy(buff, "COUNT: ");
	sprintf(intBuff, "%d", inv->invCount);
	strcat(buff, intBuff);
	strcat(buff, "\n");
	fputs(buff, file);

	for (i = 0; i < inv->invCount; i++){
		memset(buff, '\0', sizeof(buff));
		sprintf(buff, "OBJECT%dNAME: ", i + 1);
		strcat(buff, inv->name[i]);
		strcat(buff, "\n");
		fputs(buff, file);

		memset(buff, '\0', sizeof(buff));
		sprintf(buff, "OBJECT%dSTARTROOM: ", i + 1);
		strcat(buff, inv->room[i]);
		strcat(buff, "\n");
		fputs(buff, file);

		if (i == inv->invCount - 1) {
			memset(buff, '\0', sizeof(buff));
			strcpy(buff, "USEDFOR: ");
			strcat(buff, inv->usedFor[i]);
			fputs(buff, file);
		}
		else{
			memset(buff, '\0', sizeof(buff));
			strcpy(buff, "USEDFOR: ");
			strcat(buff, inv->usedFor[i]);
			strcat(buff, "\n");
			fputs(buff, file);
		}
	}
	fclose(file);
}