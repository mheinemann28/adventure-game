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
	int i=0;
	FILE* file;
	char dirname[80];
	sprintf(dirname, "%s", newestDirName);
	char filename[500];
	char word[BUFFER_SIZE];
	memset(word, '\0', sizeof(word));

	printf("i: %d\n", i);
	sprintf(filename, "%s/objects.txt", dirname);
//	printf("filename: %s\n", filename);
	/* Open file */
	file = fopen(filename, "r");
	
	for(i = 0; i < 8; i++)
	{		
		/*change the file position of the stream by x bytes to get info after :
		  And remove the newline character read by fgets()
		*/
		fseek(file, 13, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].name = calloc(255, sizeof(char));
		strcpy(array[i].name, word);
		//printf("OBJECT%dNAME: %s\n", i+1, array[i].name);

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].room = calloc(255, sizeof(char));
		strcpy(array[i].room, word);
		//printf("OBJECT%dSTARTROOM: %s\n", i+1, array[i].room);

		fseek(file, 20, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].description = calloc(255, sizeof(char));
		strcpy(array[i].description, word);	
		//printf("OBJECT%dDESCRIPTION: %s\n", i+1, array[i].description);		
	}	
	fclose(file);
}

/*
int main()
{
	struct Object *array;
	readObjects(array, "rooms");
	
	int j;
	for(j=0; j<8; j++)
	{
		printf("OBJECT%dNAME: %s\n", j+1, array[j].name);
		printf("OBJECT%dSTARTROOM: %s\n", j+1, array[j].room);
		printf("OBJECT%dDESCRIPTION: %s\n", j+1, array[j].description);
	}

	return 0;
}
*/