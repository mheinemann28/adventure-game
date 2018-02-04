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
<<<<<<< HEAD
	memset(word, '\0', sizeof(word));

	for(i = 0; i < 11; i++)
	{	
		sprintf(filename, "%s/room-%d.txt", dirname, i+1);
//		printf("filename: %s\n", filename);
=======
	
	for(i = 0; i < 29; i++)
	{	
		sprintf(filename, "%s/room-%d.txt", dirname, i+1);
		printf("filename: %s\n", filename);
>>>>>>> origin/master
		/* Open file */
		file = fopen(filename, "r");
		
		/*change the file position of the stream by x bytes to get info after :
		  And remove the newline character read by fgets()
		*/
		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
<<<<<<< HEAD
		word[strlen(word) - 2] = '\0';
		array[i].visited = atoi(strtok(word, "\n"));
//		printf("%s\n",array[i].visited);
=======
		strcpy(array[i].visited, strtok(word, "\n"));
		printf("%s\n",array[i].visited);
>>>>>>> origin/master
		

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].type = calloc(255, sizeof(char));
		strcpy(array[i].type, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].type);
=======
		printf("%s\n",array[i].type);
>>>>>>> origin/master
		

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].name = calloc(255, sizeof(char));
		strcpy(array[i].name, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].name);

=======
		printf("%s\n",array[i].name);
		
>>>>>>> origin/master

		fseek(file, 17, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].longDescription = calloc(255, sizeof(char));
		strcpy(array[i].longDescription, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].longDescription);
	
=======
		printf("%s\n",array[i].longDescription);
		
>>>>>>> origin/master

		fseek(file, 18, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].shortDescription = calloc(255, sizeof(char));
		strcpy(array[i].shortDescription, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].shortDescription);
		
	
=======
		printf("%s\n",array[i].shortDescription);
		
>>>>>>> origin/master
		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].feature1 = calloc(255, sizeof(char));
		strcpy(array[i].feature1, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].feature1);
=======
		printf("%s\n",array[i].feature1);
>>>>>>> origin/master
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].look1 = calloc(255, sizeof(char));
		strcpy(array[i].look1, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].look1);
=======
		printf("%s\n",array[i].look1);
>>>>>>> origin/master
		
		fseek(file, 6, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].hit1 = calloc(255, sizeof(char));
		strcpy(array[i].hit1, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].hit1);
=======
		printf("%s\n",array[i].hit1);
>>>>>>> origin/master
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].open1 = calloc(255, sizeof(char));
		strcpy(array[i].open1, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].open1);
=======
		printf("%s\n",array[i].open1);
>>>>>>> origin/master
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].move1 = calloc(255, sizeof(char));
		strcpy(array[i].move1, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].move1);
=======
		printf("%s\n",array[i].move1);
>>>>>>> origin/master
		

		fseek(file, 10, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].feature2 = calloc(255, sizeof(char));
		strcpy(array[i].feature2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].feature2);
=======
		printf("%s\n",array[i].feature2);
>>>>>>> origin/master
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].look2 = calloc(255, sizeof(char));
		strcpy(array[i].look2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].look2);
=======
		printf("%s\n",array[i].look2);
>>>>>>> origin/master
		

		fseek(file, 6, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].hit2 = calloc(255, sizeof(char));
		strcpy(array[i].hit2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].hit2);
=======
		printf("%s\n",array[i].hit2);
>>>>>>> origin/master
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].open2 = calloc(255, sizeof(char));
		strcpy(array[i].open2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].open2);
=======
		printf("%s\n",array[i].open2);
>>>>>>> origin/master
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].move2 = calloc(255, sizeof(char));
		strcpy(array[i].move2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].move2);
=======
		printf("%s\n",array[i].move2);
>>>>>>> origin/master
		

		fseek(file, 9, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].lookatd2 = calloc(255, sizeof(char));
		strcpy(array[i].lookatd2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].lookatd2);
=======
		printf("%s\n",array[i].lookatd2);
>>>>>>> origin/master
		

		fseek(file, 7, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].hitd2 = calloc(255, sizeof(char));
		strcpy(array[i].hitd2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].hitd2);
=======
		printf("%s\n",array[i].hitd2);
>>>>>>> origin/master
		

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].opend2 = calloc(255, sizeof(char));
		strcpy(array[i].opend2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].opend2);
=======
		printf("%s\n",array[i].opend2);
>>>>>>> origin/master
		

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].moved2 = calloc(255, sizeof(char));
		strcpy(array[i].moved2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].moved2);
=======
		printf("%s\n",array[i].moved2);
>>>>>>> origin/master
		

		fseek(file, 8, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].objectd2 = calloc(255, sizeof(char));
		strcpy(array[i].objectd2, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].objectd2);
=======
		printf("%s\n",array[i].objectd2);
>>>>>>> origin/master
		

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].exit1name = calloc(255, sizeof(char));
		strcpy(array[i].exit1name, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].exit1name);
=======
		printf("%s\n",array[i].exit1name);
>>>>>>> origin/master
		

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].exit1direction = calloc(255, sizeof(char));
		strcpy(array[i].exit1direction, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].exit1direction);
=======
		printf("%s\n",array[i].exit1direction);
>>>>>>> origin/master
		

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].exit2name = calloc(255, sizeof(char));
		strcpy(array[i].exit2name, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].exit2name);
	
=======
		printf("%s\n",array[i].exit2name);
		
>>>>>>> origin/master

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].exit2direction = calloc(255, sizeof(char));
		strcpy(array[i].exit2direction, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].exit2direction);
=======
		printf("%s\n",array[i].exit2direction);
>>>>>>> origin/master
		
		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].exit3name = calloc(255, sizeof(char));
		strcpy(array[i].exit3name, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].exit3name);
=======
		printf("%s\n",array[i].exit3name);
>>>>>>> origin/master

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].exit3direction = calloc(255, sizeof(char));
		strcpy(array[i].exit3direction, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].exit3direction);

=======
		printf("%s\n",array[i].exit3direction);
>>>>>>> origin/master

		fseek(file, 11, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word) - 2] = '\0';
		array[i].exit4name = calloc(255, sizeof(char));
		strcpy(array[i].exit4name, strtok(word, "\n"));
<<<<<<< HEAD
//		printf("%s\n",array[i].exit4name);
=======
		printf("%s\n",array[i].exit4name);
>>>>>>> origin/master

		fseek(file, 16, SEEK_CUR);
		memset(word, '\0', sizeof(word));
		fgets(word, BUFFER_SIZE, file);
		word[strlen(word)] = '\0';
		array[i].exit4direction = calloc(255, sizeof(char));
		strcpy(array[i].exit4direction, strtok(word, "\n"));
//		printf("%s\n",array[i].exit4direction);

		fclose(file);	
	}
}
/*
int main()
{
  	Room roomArray[28];
  	readRooms(roomArray, "rooms");
  	
	return 0;
}
*/

