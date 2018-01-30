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
	 
	/* save original user input into command_line struct  */ 
	strcpy(cl.userInput, commandLine);
	strcpy(cl.processedInput, commandLine);
	
	/* parse command  */  
	lowercaseCommand(&cl);
	stripPunctuation(&cl);
	removeStopWords(&cl);
	splitCommandIntoArray(&cl);
	getVerb(&cl);
	getExit(&cl);
	getFeature(&cl);
	getOtherNouns(&cl);
	
	
	
	
	/* comments for debugging  */ 
	printf("\nParser received: %s\n", cl.userInput);
	printf("Processed string: %s\n", cl.processedInput);
	
	/* return parsed_command struct with verb and nouns  */ 
	strcpy(pc.verb, cl.inputArray[0]); 
	strcpy(pc.noun1, cl.inputArray[1]); 
	strcpy(pc.noun2, cl.inputArray[2]);
	return pc;
	
}

/*********************************************************************
 ** Function: void lowercaseCommand(struct command_line* cl)
 ** Description: lowercase the user input
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.processedInput contains lowercase version
 ** 	of cl.userInput
 *********************************************************************/

void lowercaseCommand(struct command_line* cl) {
	int i;
	for (i = 0; i < 2000; i++) {
		cl->processedInput[i] = tolower(cl->processedInput[i]);
  	}
}

/*********************************************************************
 ** Function: void stripPunctuation(struct command_line* cl)
 ** Description: strip punctuation from user input
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.processedInput has all punctuation removed
 *********************************************************************/

void stripPunctuation(struct command_line* cl) {
	int i = 0;
    int p = 0;
    for (i = 0; i < 2000; i++) {
        if (! ispunct(cl->processedInput[i])) {
            cl->processedInput[p] = cl->processedInput[i];
            p++; 
        }  
    }    
} 
 
/*********************************************************************
 ** Function: void removeStopWords(struct command_line* cl)
 ** Description: remove stop words from user input
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.processedInput has all stop words removed
 *********************************************************************/

void removeStopWords(struct command_line* cl) {

}

/*********************************************************************
 ** Function: void splitCommandIntoArray(struct command_line* cl
 ** Description: splits cl.processed into an array of strings
 ** 	for easier processing
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.inputArray contains tokens from processedInput
 *********************************************************************/

void splitCommandIntoArray(struct command_line* cl) {
	char line[2000];
	strcpy(line, cl->processedInput);
	char *rest = line;
 	char *token;
    while ((token = strtok_r(rest, " ", &rest))) {
        if ((strcmp("", token) != 0) && (strcmp("\n", token) != 0)) {
        	strtok(token, "\n"); 
        	strcpy(cl->inputArray[cl->inputArraySize], token);
        	cl->inputArraySize++;
        } 
    }
}

/*********************************************************************
 ** Function: void getVerb(struct command_line* cl)
 ** Description: gets verb from user input
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.verb contains verb
 *********************************************************************/

void getVerb(struct command_line* cl) {

}

/*********************************************************************
 ** Function: void getExit(struct command_line* cl)
 ** Description: gets exit from user input if exists
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.noun1 contains exit if it exists
 *********************************************************************/

void getExit(struct command_line* cl) {

}

/*********************************************************************
 ** Function: void getFeature(struct command_line* cl)
 ** Description: gets feature from user input if exits
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.noun1 or cl.noun2 (if there was an exit) 
 ** 	contains feature if exists in user input
 *********************************************************************/
 
void getFeature(struct command_line* cl) {

}

/*********************************************************************
 ** Function: void getOtherNouns(struct command_line* cl)
 ** Description: gets other nouns from user input if exits
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.noun1 or cl.noun2 if those were not already
 ** 	taken by a feature or exit
 *********************************************************************/

void getOtherNouns(struct command_line* cl) {

}