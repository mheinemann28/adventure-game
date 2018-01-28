/*********************************************************************
 ** Program Filename: CommandParser-tester.c 
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 24, 2018
 ** Description: tests CommandParser.h without running GameEngine.c
 ** Input: command line input
 ** Output: parsed response
 *********************************************************************/

#include "CommandParser-tester.h"
#include "CommandParser.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
/*********************************************************************
 ** Function: main();
 ** Description: starts command parser testing program
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: program exits
 *********************************************************************/
 
 int main() {
 
 	/* initialize new parsed_command and string for input */
	struct parsed_command pc;
	char line[2000];
	
 	/* loop through recieving and parsing commands until user sends stop signal  */
 	while(1) {
 		memset(line, '\0', sizeof(line)); //clear memory
 		memset(pc.verb, '\0', sizeof(pc.verb));
 		memset(pc.noun1, '\0', sizeof(pc.noun1));
 		memset(pc.noun2, '\0', sizeof(pc.noun2));
 		printf("\n\nEnter Command: ");
 		fgets(line,500,stdin);
 		fflush(stdout);
 	
 		pc = parseCommand(line);
 	
 		printf("verb: %s\n", pc.verb);
 		printf("noun1: %s\n", pc.noun1);
 		printf("noun2: %s\n\n", pc.noun2);
 	
 	}
 
    return 0;
}