/*********************************************************************
 ** Program Filename: CommandParser.h
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Parses command line input using natural language
 **      parsing
 ** Input: a command string
 ** Output: a string array with 3 values: verb, noun1, noun2
 *********************************************************************/
 
 /* To prevent compiler from processing contents twice, wrap in a conditional */
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

/* parsed command that is returned by void parseCommand(char command[500]) */
struct parsed_command {
	char verb[50];
	char noun1[50];
	char noun2[50];
};

/* stores everything needed by the command parser functions */
struct command_line {
	char userInput[500];
	char processedInput[500];
	char inputArray[10][50];
	int inputArraySize;
};

/* function declarations */
struct parsed_command parseCommand(char command[500]);


/* Place at end of file - End of header conditional */
#endif
 
