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
	int i=0;

	FILE* file;
	char dirname[80];
	sprintf(dirname, "%s", newestDirName);
	char filename[500];
	char word[BUFFER_SIZE];
	memset(word, '\0', sizeof(word));

	for(i = 0; i < 15; i++)
	{	
		sprintf(filename, "%s/room-%d.txt", dirname, i+1);
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
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].visited = atoi(word);
//		printf("%d\n",array[i].visited);
		

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].type = calloc(255, sizeof(char));
		strcpy(array[i].type, word);
//		printf("%s\n",array[i].type);
		

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].name = calloc(255, sizeof(char));
		strcpy(array[i].name, word);
	//	printf("%s\n",array[i].name);


		fseek(file, 17, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].longDescription = calloc(1000, sizeof(char));
		strcpy(array[i].longDescription, word);
//		printf("%s\n",array[i].longDescription);
	

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].shortDescription = calloc(1000, sizeof(char));
		strcpy(array[i].shortDescription, word);
//		printf("%s\n",array[i].shortDescription);
		
	
		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].feature[0] = calloc(255, sizeof(char));
		strcpy(array[i].feature[0], word);
//		printf("%s\n",array[i].feature1);
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].look[0] = calloc(500, sizeof(char));
		strcpy(array[i].look[0], word);
//		printf("%s\n",array[i].look1);
		
		fseek(file, 6, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].hit[0] = calloc(255, sizeof(char));
		strcpy(array[i].hit[0], word);
//		printf("%s\n",array[i].hit1);
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].open[0] = calloc(255, sizeof(char));
		strcpy(array[i].open[0], word);
//		printf("%s\n",array[i].open1);
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].move[0] = calloc(255, sizeof(char));
		strcpy(array[i].move[0], word);
//		printf("%s\n",array[i].move1);
		

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';	
		array[i].feature[1] = calloc(255, sizeof(char));
		strcpy(array[i].feature[1], word);
//		printf("%s\n",array[i].feature2);
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].look[1] = calloc(255, sizeof(char));
		strcpy(array[i].look[1], word);
//		printf("%s\n",array[i].look2);
		

		fseek(file, 6, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].hit[1] = calloc(255, sizeof(char));
		strcpy(array[i].hit[1], word);
//		printf("%s\n",array[i].hit2);
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].open[1] = calloc(255, sizeof(char));
		strcpy(array[i].open[1], word);
//		printf("%s\n",array[i].open2);
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].move[1] = calloc(255, sizeof(char));
		strcpy(array[i].move[1], word);
//		printf("%s\n",array[i].move2);
		

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].look[2] = calloc(255, sizeof(char));
		strcpy(array[i].look[2], word);
//		printf("%s\n",array[i].lookatd2);
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].hit[2] = calloc(255, sizeof(char));
		strcpy(array[i].hit[2], word);
//		printf("%s\n",array[i].hitd2);
		

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].open[2] = calloc(255, sizeof(char));
		strcpy(array[i].open[2], word);
//		printf("%s\n",array[i].opend2);
		

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].move[2] = calloc(255, sizeof(char));
		strcpy(array[i].move[2], word);
//		printf("%s\n",array[i].moved2);
		

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].object = calloc(255, sizeof(char));
		strcpy(array[i].object, word);
//		printf("%s\n",array[i].objectd2);

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].numExits = atoi(word);
//		printf("%d\n",array[i].numExits);
		

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[0] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[0], word);
//		printf("%s\n",array[i].exit1name);
		

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[1] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[1], word);
//		printf("%s\n",array[i].exit1direction);
		

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[2] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[2], word);
//		printf("%s\n",array[i].exit2name);
	

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].exitDirection[3] = calloc(255, sizeof(char));
		strcpy(array[i].exitDirection[3], word);
//		printf("%s\n",array[i].exit2direction);
		

//////////////////////////////////////////////////////////////////////////////

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[0] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[0], word);
//		printf("%s\n",array[i].exit3name);

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[1] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[1], word);
//		printf("%s\n",array[i].exit3direction);


		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[2] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[2], word);
//		printf("%s\n",array[i].exit4name);

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		strtok(word, "\n");
		if(isspace(word[strlen(word) - 1]) != 0)
			word[strlen(word) - 1] = '\0';
		array[i].Exits[3] = calloc(255, sizeof(char));
		strcpy(array[i].Exits[3], word);
//		printf("%s\n",array[i].exit4direction);

		fclose(file);	
	}
}