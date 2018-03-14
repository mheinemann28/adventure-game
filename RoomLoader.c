/*********************************************************************
 ** Program Filename: RoomLoader.c
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Loads rooms from text files into the game
 ** Input: rooms text files (there are 15)
 ** Output: data loaded into GameEngine
 *********************************************************************/


#include "RoomLoader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 32766

/*********************************************************************
* readRooms() - Read room info from files into Room array.
*********************************************************************/
void readRooms(Room* array, char newestDirName[256]) {
	int i = 0;

	FILE* file;
	char dirname[80];
	sprintf(dirname, "%s", newestDirName);
	char filename[500];
	char word[BUFFER_SIZE];
	memset(word, '\0', sizeof(word));

	for (i = 0; i < 16; i++)
	{
		sprintf(filename, "%s/room-%d.txt", dirname, i + 1);
//		printf("filename: %s\n", filename);
		/* Open file */
		file = fopen(filename, "r");

		/*change the file position of the stream by x bytes to get info after :
		  And remove the newline character read by fgets()
		*/
		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].visited = atoi(word);
//		printf("%d\n",array[i].visited);


		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].type = calloc(255, sizeof(char));
		strcpy(array[i].type, word);
//		printf("%s\n",array[i].type);


		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].name = calloc(255, sizeof(char));
		strcpy(array[i].name, word);
		//	printf("%s\n",array[i].name);


		fseek(file, 17, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].longDescription = calloc(1000, sizeof(char));
		strcpy(array[i].longDescription, word);
//		printf("%s\n",array[i].longDescription);


		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].shortDescription = calloc(1000, sizeof(char));
		strcpy(array[i].shortDescription, word);
//		printf("%s\n",array[i].shortDescription);


		fseek(file, 14, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].name = calloc(255, sizeof(char));
		strcpy(array[i].feature[0].name, word);
		array[i].feature[0].firstLook = 0;
//		printf("%s\n",array[i].feature1);


		fseek(file, 17, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].containObject = atoi(word);


		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].description1 = calloc(1000, sizeof(char));
		strcpy(array[i].feature[0].description1, word);
//		printf("%s\n",array[i].feature[0].description1);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].description2 = calloc(1000, sizeof(char));
		strcpy(array[i].feature[0].description2, word);
//		printf("%s\n",array[i].feature[0].description2);

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].hit1 = calloc(255, sizeof(char));
		strcpy(array[i].feature[0].hit1, word);
//		printf("%s\n",array[i].hit1);

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].hit2 = calloc(255, sizeof(char));
		strcpy(array[i].feature[0].hit2, word);
//		printf("%s\n",array[i].hit1);


		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].open1 = calloc(255, sizeof(char));
		strcpy(array[i].feature[0].open1, word);
//		printf("%s\n",array[i].open1);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].open2 = calloc(255, sizeof(char));
		strcpy(array[i].feature[0].open2, word);
//		printf("%s\n",array[i].open1);



		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].move1 = calloc(500, sizeof(char));
		strcpy(array[i].feature[0].move1, word);
//		printf("%s\n",array[i].move1);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].move2 = calloc(500, sizeof(char));
		strcpy(array[i].feature[0].move2, word);
//		printf("%s\n",array[i].move1);


		fseek(file, 14, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].name = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].name, word);
		array[i].feature[1].firstLook = 0;
//		printf("%s\n",array[i].feature2);


		fseek(file, 17, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].containObject = atoi(word);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].description1 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].description1, word);
//		printf("%s\n",array[i].feature[1].description1);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].description2 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].description2, word);
//		printf("%s\n",array[i].feature[1].description2);


		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].hit1 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].hit1, word);
//		printf("%s\n",array[i].hit2);

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].hit2 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].hit2, word);
//		printf("%s\n",array[i].hit2);


		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].open1 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].open1, word);
//		printf("%s\n",array[i].open2);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].open2 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].open2, word);
//		printf("%s\n",array[i].open2);


		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].move1 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].move1, word);
//		printf("%s\n",array[i].move2);

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].move2 = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].move2, word);
//		printf("%s\n",array[i].move2);


		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].numObjects = atoi(word);

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].object[0] = calloc(255, sizeof(char));
		strcpy(array[i].object[0], word);
//		printf("%s\n",array[i].objectd2);

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].numExits = atoi(word);
//		printf("%d\n",array[i].numExits);


		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[0] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[0], word);
//		printf("%s\n",array[i].exit1name);


		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[1] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[1], word);
//		printf("%s\n",array[i].exit1direction);


		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[2] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[2], word);
//		printf("%s\n",array[i].exit2name);


		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[3] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[3], word);
//		printf("%s\n",array[i].exit2direction);


//////////////////////////////////////////////////////////////////////////////

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[0] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[0], word);
//		printf("%s\n",array[i].exit3name);

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[1] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[1], word);
//		printf("%s\n",array[i].exit3direction);


		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[2] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[2], word);
//		printf("%s\n",array[i].exit4name);

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[3] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[3], word);
//		printf("%s\n",array[i].exit4direction);

		fseek(file, 12, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].blockedBy[0] = calloc(255, sizeof(char));
		strcpy(array[i].blockedBy[0], word);

		fseek(file, 12, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].blockedBy[1] = calloc(255, sizeof(char));
		strcpy(array[i].blockedBy[1], word);

		fseek(file, 12, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].blockedBy[2] = calloc(255, sizeof(char));
		strcpy(array[i].blockedBy[2], word);

		fseek(file, 12, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].blockedBy[3] = calloc(255, sizeof(char));
		strcpy(array[i].blockedBy[3], word);

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDescription[0] = calloc(500, sizeof(char));
		strcpy(array[i].exitDescription[0], word);
//		printf("%s\n",array[i].exit3name);

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDescription[1] = calloc(500, sizeof(char));
		strcpy(array[i].exitDescription[1], word);
//		printf("%s\n",array[i].exit3direction);


		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDescription[2] = calloc(500, sizeof(char));
		strcpy(array[i].exitDescription[2], word);
//		printf("%s\n",array[i].exit4name);

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDescription[3] = calloc(500, sizeof(char));
		strcpy(array[i].exitDescription[3], word);
//		printf("%s\n",array[i].exit4direction);

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0].enemy = calloc(255, sizeof(char));
		strcpy(array[i].feature[0].enemy, word);

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if (isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[1].enemy = calloc(255, sizeof(char));
		strcpy(array[i].feature[1].enemy, word);

		fclose(file);
	}
}