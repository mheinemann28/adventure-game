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
	int j=1;
	FILE* file;
	char dirname[80];
	sprintf(dirname, "%s", newestDirName);
	
	
		char filename[500];
		sprintf(filename, "%s/room-%d.txt", dirname, j);
		printf("filename: %s\n", filename);
		/* Open file */
		file = fopen(filename, "r");
		
		char word[BUFFER_SIZE];

		/*change the file position of the stream by x bytes to get info after :
		  And remove the newline character read by fgets()
		*/
		fseek(file, 9, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].visited, strtok(word, "\n"));
		printf("%s\n",array[i].visited);
		i=i+1;

		fseek(file, 10, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].type, strtok(word, "\n"));
		printf("%s\n",array[i].type);
		i=i+1;

		fseek(file, 10, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].name, strtok(word, "\n"));
		printf("%s\n",array[i].name);
		i=i+1;

		fseek(file, 17, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].longDescription, strtok(word, "\n"));
		printf("%s\n",array[i].longDescription);
		i=i+1;

		fseek(file, 18, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].shortDescription, strtok(word, "\n"));
		printf("%s\n",array[i].shortDescription);
		i=i+1;

		fseek(file, 10, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].feature1, strtok(word, "\n"));
		printf("%s\n",array[i].feature1);
		i=i+1;

		fseek(file, 7, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].look1, strtok(word, "\n"));
		printf("%s\n",array[i].look1);
		i=i+1;


		fseek(file, 6, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].hit1, strtok(word, "\n"));
		printf("%s\n",array[i].hit1);
		i=i+1;

		fseek(file, 7, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].open1, strtok(word, "\n"));
		printf("%s\n",array[i].open1);
		i=i+1;

		fseek(file, 7, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].move1, strtok(word, "\n"));
		printf("%s\n",array[i].move1);
		i=i+1;

		fseek(file, 10, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].feature2, strtok(word, "\n"));
		printf("%s\n",array[i].feature2);
		i=i+1;

		fseek(file, 7, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].look2, strtok(word, "\n"));
		printf("%s\n",array[i].look2);
		i=i+1;

		fseek(file, 6, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].hit2, strtok(word, "\n"));
		printf("%s\n",array[i].hit2);
		i=i+1;

		fseek(file, 7, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].open2, strtok(word, "\n"));
		printf("%s\n",array[i].open2);
		i=i+1;

		fseek(file, 7, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].move2, strtok(word, "\n"));
		printf("%s\n",array[i].move2);
		i=i+1;

		fseek(file, 9, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].lookatd2, strtok(word, "\n"));
		printf("%s\n",array[i].lookatd2);
		i=i+1;

		fseek(file, 7, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].hitd2, strtok(word, "\n"));
		printf("%s\n",array[i].hitd2);
		i=i+1;

		fseek(file, 8, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].opend2, strtok(word, "\n"));
		printf("%s\n",array[i].opend2);
		i=i+1;

		fseek(file, 8, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].moved2, strtok(word, "\n"));
		printf("%s\n",array[i].moved2);
		i=i+1;

		fseek(file, 8, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].objectd2, strtok(word, "\n"));
		printf("%s\n",array[i].objectd2);
		i=i+1;

		fseek(file, 11, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit1name, strtok(word, "\n"));
		printf("%s\n",array[i].exit1name);
		i=i+1;

		fseek(file, 16, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit1direction, strtok(word, "\n"));
		printf("%s\n",array[i].exit1direction);
		i=i+1;

		fseek(file, 11, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit2name, strtok(word, "\n"));
		printf("%s\n",array[i].exit2name);
		i=i+1;

		fseek(file, 16, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit2direction, strtok(word, "\n"));
		printf("%s\n",array[i].exit2direction);
		i=i+1;

		fseek(file, 11, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit3name, strtok(word, "\n"));
		printf("%s\n",array[i].exit3name);
		i=i+1;

		fseek(file, 16, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit3direction, strtok(word, "\n"));
		printf("%s\n",array[i].exit3direction);
		i=i+1;

		fseek(file, 11, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit4name, strtok(word, "\n"));
		printf("%s\n",array[i].exit4name);
		i=i+1;

		fseek(file, 16, SEEK_CUR);
		fgets(word, BUFFER_SIZE, file);
		strcpy(array[i].exit4direction, strtok(word, "\n"));
		printf("%s\n",array[i].exit4direction);

		fclose(file);	
	
}

int main()
{
  	Room roomArray[29];
  	readRooms(roomArray, "rooms");
  	
	return 0;
}


