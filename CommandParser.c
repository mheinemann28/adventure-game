/*********************************************************************
 ** Program Filename: CommandParser.c 
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Parses command line input using natural language
 **      parsing
 ** Input: a command string
 ** Output: a struct parsed_command with 3 values: verb, noun1, noun2
 *********************************************************************/
 
#include "CommandParser.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*********************************************************************
 ** Function: struct parsed_command parseCommand(char commandLine[500])
 ** Description: function that GameEngine will call to parse
 ** 	a user's command
 ** Parameters: string of user input
 ** Pre-Conditions: none
 ** Post-Conditions: returns a struct parsed_command
 *********************************************************************/
 
struct parsed_command parseCommand(char commandLine[2000]) {
	
	/* initialize new parsed_command  */
	struct parsed_command pc;
	
	/* initialize new command_line  */
	struct command_line cl;
	
	/* clear memory  */ 
 	memset(pc.verb, '\0', sizeof(pc.verb));
 	memset(pc.noun1, '\0', sizeof(pc.noun1));
 	memset(pc.noun2, '\0', sizeof(pc.noun2));
 	memset(cl.userInput, '\0', sizeof(cl.userInput));
 	memset(cl.processedInput, '\0', sizeof(cl.processedInput));
 	cl.inputArraySize = 0;
 	int i;
 	for (i = 0; i < 40; i++) {
 		memset(cl.inputArray[i], '\0', sizeof(cl.inputArray[i]));
 	}
	 
	strcpy(cl.userInput, commandLine);
	
	/* split commandLine into array of strings  */
	char *rest = commandLine;
 	char *token;
    while ((token = strtok_r(rest, " ", &rest))) {
        if ((strcmp("", token) != 0) && (strcmp("\n", token) != 0)) {
        	strtok(token, "\n"); 
        	strcpy(cl.inputArray[cl.inputArraySize], token);
        	cl.inputArraySize++;
        } 
    }
	
	
	
	
	printf("\nParser received: %s\n", cl.userInput);
	
	strcpy(pc.verb, cl.inputArray[0]); 
	strcpy(pc.noun1, cl.inputArray[1]); 
	strcpy(pc.noun2, cl.inputArray[2]);
	
	return pc;
	
}