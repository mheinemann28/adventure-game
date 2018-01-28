/*********************************************************************
 ** Program Filename: CommandParser.c 
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Parses command line input using natural language
 **      parsing
 ** Input: a command string
 ** Output: a string array with 3 values: verb, noun1, noun2
 *********************************************************************/
 
#include "CommandParser.h"

#include <stdio.h>
#include <string.h>
 
struct parsed_command parseCommand(char commandLine[500]) {
	
	/* initialize new parsed_command  */
	struct parsed_command pc;
	
	/* initialize new command_line  */
	struct command_line cl;
	
	strcpy(cl.userInput, commandLine);
	
	
	
	
	
	
	
	printf("\nParser received: %s\n", cl.userInput);
	
	strcpy(pc.verb, "test verb");
	strcpy(pc.noun1, "test noun1");
	strcpy(pc.noun2, "test noun2");
	
	return pc;
	
}