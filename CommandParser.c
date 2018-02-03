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

/* data  */
const int stop_words_size = 174;
// stop word list from https://www.ranks.nl/stopwords
const char *stop_words[] = {"a","about","above","after","again","against",
	"all","am","an","and","any","are","arent","as","be","because","been",
	"before","being","below","between","both","but","by","cant","cannot",
	"could","couldnt","did","didnt","do","does","doesnt","doing","dont",
	"down","during","each","few","for","from","further","had","hadnt",
	"has","hasnt","have","havent","having","he","hed","hell","hes","her",
	"here","heres","hers","herself","him","himself","his","how","hows","i",
	"id","ill","im","ive","if","in","into","is","isnt","it","its","its",
	"itself","lets","me","more","most","mustnt","my","myself","no","nor",
	"not","of","off","on","once","only","or","other","ought","our","ours",
	"ourselves","out","over","own","same","shant","she","shed","shell",
	"shes","should","shouldnt","so","some","such","than","that","thats",
	"the","their","theirs","them","themselves","then","there","theres",
	"these","they","theyd","theyll","theyre","theyve","this","those",
	"through","to","too","under","until","up","very","was","wasnt","we",
	"wed","well","were","weve","were","werent","what","whats","when",
	"whens","where","wheres","which","while","who","whos","whom","why",
	"whys","with","wont","would","wouldnt","you","youd","youll",
	"youre","youve","your","yours","yourself","yourselves","around"};
const int verb_look_synonyms_size = 1;
const char *verb_look_synonyms[] = {"look"};
const int verb_go_synonyms_size = 1;
const char *verb_go_synonyms[] = {"go"};
const int verb_take_synonyms_size = 1;
const char *verb_take_synonyms[] = {"take"};
const int verb_drop_synonyms_size = 1;
const char *verb_drop_synonyms[] = {"drop"};
const int verb_help_synonyms_size = 1;
const char *verb_help_synonyms[] = {"help"};
const int verb_inventory_synonyms_size = 1;
const char *verb_inventory_synonyms[] = {"inventory"};
const int verb_hit_synonyms_size = 1;
const char *verb_hit_synonyms[] = {"hit"};
const int verb_open_synonyms_size = 1;
const char *verb_open_synonyms[] = {"open"};
const int verb_move_synonyms_size = 1;
const char *verb_move_synonyms[] = {"move"};

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
	stripPunctuationLowercase(&cl);
	splitCommandIntoArray(&cl);
	removeStopWords(&cl);
	getVerb(&cl);
	getExit(&cl);
	getFeature(&cl);
	getOtherNouns(&cl);
	
	
	
	
	/* comments for debugging  */ 
	printf("\nFOR DEBUGGING - Parser received: %s", cl.userInput);
	printf("FOR DEBUGGING - Processed string: %s\n", cl.processedInput);
	printf("%d\n", cl.verbIndex);
	
	/* return parsed_command struct with verb and nouns  */ 
	strcpy(pc.verb, cl.verb); 
	strcpy(pc.noun1, cl.inputArray[1]); 
	strcpy(pc.noun2, cl.inputArray[2]);
	return pc;
	
}

/*********************************************************************
 ** Function: void stripPunctuationLowercase(struct command_line* cl)
 ** Description: strip punctuation from user input and lowercase
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.processedInput has all punctuation removed
 ** 	and is lowercased
 *********************************************************************/

void stripPunctuationLowercase(struct command_line* cl) { 
	int i = 0;
    int p = 0;
    for (i = 0; i < 2000; i++) {
        if (! ispunct(cl->processedInput[i])) {
            cl->processedInput[p] = tolower(cl->processedInput[i]);
            p++; 
        }  
    }    
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
 ** Function: void removeStopWords(struct command_line* cl)
 ** Description: remove stop words from user input
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.processedInput has all stop words removed
 *********************************************************************/

void removeStopWords(struct command_line* cl) {
	/* loop through input array and remove words that are on the stop word list */
	int i;
	int j;
	int k;
	for (i = 0; i < cl->inputArraySize; i++) {
		for (j = 0; j < stop_words_size; j++) {
			if (strcmp(cl->inputArray[i], stop_words[j]) == 0) {
				for (k = i; k < cl->inputArraySize; k++) {
					strcpy(cl->inputArray[k], cl->inputArray[k+1]);
				}
				cl->inputArraySize--;
				i--;
				break;
			}
		}
	}

	/* after removing stop words from array, put array back into the processed string */
	memset(cl->processedInput, '\0', sizeof(cl->processedInput));
	for (i = 0; i < cl->inputArraySize; i++) {
		strcat(cl->processedInput, cl->inputArray[i]);
		strcat(cl->processedInput, " ");  
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
	memset(cl->verb, '\0', sizeof(cl->verb));
	int i;
	int j;
	if(strstr(cl->processedInput, "look at") != NULL) {
    	strcpy(cl->verb, "look at");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "at") == 0) {
    			cl->verbIndex = i;
    		}
    	}	
    	return;
	}
	for (i = 0; i < cl->inputArraySize; i++) {
		for (j = 0; j < verb_look_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_look_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_look_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
	}
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