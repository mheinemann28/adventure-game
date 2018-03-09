/*********************************************************************
 ** Program Filename: RoomLoader.c
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Loads rooms from text files into the game
 ** Input: rooms text files (there are 15)
 ** Output: data loaded into GameEngine
 *********************************************************************/

#include "ObjectLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 32766

void readObjects(struct Object* array, char newestDirName[256])
{
	int i = 0;
	FILE* file;
	char dirname[80];
	sprintf(dirname, "%s", newestDirName);
	char filename[500];
	char word[BUFFER_SIZE];
	memset(word, '\0', sizeof(word));


	sprintf(filename, "%s/objects.txt", dirname);
//	printf("filename: %s\n", filename);
	/* Open file */
	file = fopen(filename, "r");

	for (i = 0; i < 9; i++)
	{
		/*change the file position of the stream by x bytes to get info after :
		  And remove the newline character read by fgets()
		*/
		fseek(file, 13, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].name = calloc(255, sizeof(char));
		strcpy(array[i].name, word);
		//printf("OBJECT%dNAME: %s\n", i+1, array[i].name);

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].room = calloc(255, sizeof(char));
		strcpy(array[i].room, word);
		//printf("OBJECT%dSTARTROOM: %s\n", i+1, array[i].room);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].usedFor = calloc(255, sizeof(char));
		strcpy(array[i].usedFor, word);
		//printf("OBJECT%dDESCRIPTION: %s\n", i+1, array[i].usedFor);
	}
	fclose(file);
}

void readInventory(struct Inventory* array, char newestDirName[256])
{
	int i = 0;
	FILE* file;
	char dirname[80];
	sprintf(dirname, "%s", newestDirName);
	char filename[500];
	char word[BUFFER_SIZE];
	memset(word, '\0', sizeof(word));


	sprintf(filename, "%s/inventory.txt", dirname);
//	printf("filename: %s\n", filename);
	/* Open file */
	file = fopen(filename, "r");

	fseek(file, 7, SEEK_CUR);
	fgets(word, BUFFER_SIZE, file);
	strtok(word, "\n");
	if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
	array->invCount = atoi(word);

	for(i = 0; i < array->invCount; i++){
		fseek(file, 13, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array->name[i] = calloc(255, sizeof(char));
		strcpy(array->name[i], word);

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array->room[i] = calloc(255, sizeof(char));
		strcpy(array->room[i], word);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array->usedFor[i] = calloc(255, sizeof(char));
		strcpy(array->usedFor[i], word);
	}
	fclose(file);
}

