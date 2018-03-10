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
const int verb_look_synonyms_size = 5;
const char *verb_look_synonyms[] = {"look", "see", "describe", "examine", "look at"};
const int verb_go_synonyms_size = 3;
const char *verb_go_synonyms[] = {"go","depart","exit"};
const int verb_take_synonyms_size = 4;
const char *verb_take_synonyms[] = {"take","grab","pick","get"};
const int verb_drop_synonyms_size = 5;
const char *verb_drop_synonyms[] = {"drop","leave","use","place","put"};
const int verb_help_synonyms_size = 2;
const char *verb_help_synonyms[] = {"help","actions"};
const int verb_inventory_synonyms_size = 4;
const char *verb_inventory_synonyms[] = {"inventory","items","bag","objects"};
const int verb_hit_synonyms_size = 10;
const char *verb_hit_synonyms[] = {"hit","smack","fight","attack","charge","punch","kick","hurt","swing","give"};
const int verb_open_synonyms_size = 1;
const char *verb_open_synonyms[] = {"open"};
const int verb_move_synonyms_size = 2;
const char *verb_move_synonyms[] = {"move","push"};
const int exit_northeast_synonyms_size = 3;
const char *exit_northeast_synonyms[] = {"northeast","ne","northeastern"};
const int exit_northwest_synonyms_size = 3;
const char *exit_northwest_synonyms[] = {"northwest","nw","northwestern"};
const int exit_southeast_synonyms_size = 3;
const char *exit_southeast_synonyms[] = {"southeast","se","southeastern"};
const int exit_southwest_synonyms_size = 3;
const char *exit_southwest_synonyms[] = {"southwest","sw","southwestern"};
const int exit_north_synonyms_size = 3;
const char *exit_north_synonyms[] = {"north","n","northern"};
const int exit_west_synonyms_size = 3;
const char *exit_west_synonyms[] = {"west","w","western"};
const int exit_east_synonyms_size = 3;
const char *exit_east_synonyms[] = {"east","e","eastern"};
const int exit_south_synonyms_size = 3;
const char *exit_south_synonyms[] = {"south","s","southern"};

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
	cl.verbIndex = -1;
	cl.noun1Index = -1; 
	cl.noun2Index = -1;
	
	/* parse command  */  
	stripPunctuationLowercase(&cl);
	splitCommandIntoArray(&cl);
	removeStopWords(&cl);
	getVerb(&cl);
	getExit(&cl);
	getObjectFeaturePhrase(&cl);
	getObjectFeatureWord(&cl);
	getOtherNouns(&cl);
	
	/* return parsed_command struct with verb and nouns  */ 
	strcpy(pc.verb, cl.verb); 
	strcpy(pc.noun1, cl.noun1); 
	strcpy(pc.noun2, cl.noun2);
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
	if(strstr(cl->processedInput, "save") != NULL) {
    	strcpy(cl->verb, "save");	
    	
    	return;
	}
	if(strstr(cl->processedInput, "look at") != NULL) {
    	strcpy(cl->verb, "look");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "at") == 0) {
    			cl->verbIndex = i;
    		}
    	}	
    	return;
	}
/*	if(strstr(cl->processedInput, "describe") != NULL) {
    	strcpy(cl->verb, "look at");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "describe") == 0) {
    			cl->verbIndex = i;
    		}
    	}	
    	return;
	}*/
	for (i = 0; i < cl->inputArraySize; i++) {
		for (j = 0; j < verb_look_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_look_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_look_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_go_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_go_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_go_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_take_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_take_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_take_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_drop_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_drop_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_drop_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_help_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_help_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_help_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_inventory_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_inventory_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_inventory_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_hit_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_hit_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_hit_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_open_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_open_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_open_synonyms[0]);
    			cl->verbIndex = i;
    			return;
    		}
		}
		for (j = 0; j < verb_move_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], verb_move_synonyms[j]) == 0) {
				strcpy(cl->verb, verb_move_synonyms[0]);
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
	memset(cl->noun1, '\0', sizeof(cl->noun1));
	int i;
	int j;
	if(strstr(cl->processedInput, "bright lights") != NULL) {
    	strcpy(cl->noun1, "bright lights");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "lights") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "animal hair") != NULL) {
    	strcpy(cl->noun1, "animal hair");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "hair") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "fresh air") != NULL) {
    	strcpy(cl->noun1, "fresh air");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "air") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "bar music") != NULL) {
    	strcpy(cl->noun1, "bar music");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "music") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "music note") != NULL) {
    	strcpy(cl->noun1, "music note");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "note") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "fluttering noise") != NULL) {
    	strcpy(cl->noun1, "fluttering noise");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "noise") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "car sign") != NULL) {
    	strcpy(cl->noun1, "car sign");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "sign") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "storage sign") != NULL) {
    	strcpy(cl->noun1, "storage sign");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "sign") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "dark and damp") != NULL) {
    	strcpy(cl->noun1, "dark and damp");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "damp") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	if(strstr(cl->processedInput, "smell cookies") != NULL) {
    	strcpy(cl->noun1, "smell cookies");	
    	for (i = 0; i < cl->inputArraySize; i++) {
    		if (strcmp(cl->inputArray[i], "cookies") == 0) {
    			cl->noun1Index = i;
    		}
    	}	
    	return;
	}
	for (i = 0; i < cl->inputArraySize; i++) {
		for (j = 0; j < exit_northeast_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_northeast_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_northeast_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}
		for (j = 0; j < exit_northwest_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_northwest_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_northwest_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}
		for (j = 0; j < exit_southeast_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_southeast_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_southeast_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}
		for (j = 0; j < exit_southwest_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_southwest_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_southwest_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}
		for (j = 0; j < exit_north_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_north_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_north_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}
		for (j = 0; j < exit_west_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_west_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_west_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}
		for (j = 0; j < exit_east_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_east_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_east_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}
		for (j = 0; j < exit_south_synonyms_size; j++) {
			if (strcmp(cl->inputArray[i], exit_south_synonyms[j]) == 0) {
				strcpy(cl->noun1, exit_south_synonyms[0]);
    			cl->noun1Index = i;
    			return;
    		}
		}			
		if (strcmp(cl->inputArray[i], "musty") == 0) {
			strcpy(cl->noun1, "musty");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "bright") == 0) {
			strcpy(cl->noun1, "bright lights");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "lights") == 0) {
			strcpy(cl->noun1, "bright lights");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "creepy") == 0) {
			strcpy(cl->noun1, "creepy");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "hair") == 0) {
			strcpy(cl->noun1, "animal hair");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "fresh") == 0) {
			strcpy(cl->noun1, "fresh air");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "air") == 0) {
			strcpy(cl->noun1, "fresh air");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "noise") == 0) {
			strcpy(cl->noun1, "fluttering noise");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "fluttering") == 0) {
			strcpy(cl->noun1, "fluttering noise");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "pig") == 0) {
			strcpy(cl->noun1, "pig");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "confusion") == 0) {
			strcpy(cl->noun1, "confusing");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "confusing") == 0) {
			strcpy(cl->noun1, "confusing");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "spooky") == 0) {
			strcpy(cl->noun1, "spooky");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "cookie") == 0) {
			strcpy(cl->noun1, "smell cookies");
    		cl->noun1Index = i;
    		return;
    	}
    	if (strcmp(cl->inputArray[i], "cookies") == 0) {
			strcpy(cl->noun1, "smell cookies");
    		cl->noun1Index = i;
    		return;
    	}
	}
}

/*********************************************************************
 ** Function: getObjectFeaturePhrase(struct command_line* cl)
 ** Description: gets object or feature from user input if exists
 ** 	only focuses on the features and objects that are whole
 ** 	phrases so they won't be missed when catching single nouns
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.noun1 or cl.noun2 (if there was a phrase) 
 ** 	contains object/feature if exists in user input
 *********************************************************************/
 
void getObjectFeaturePhrase(struct command_line* cl) {
	int i;
	int j;
	if(strstr(cl->processedInput, "tennis racket") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "tennis racket");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "racket") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "tennis racket") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "tennis racket");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "racket") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "serena williams") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "serena williams");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "williams") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "serena williams") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "serena williams");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "williams") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "book wallpaper") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "book of wallpaper");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "wallpaper") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "book of wallpaper") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "book of wallpaper");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "wallpaper") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "tennis ball") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "tennis ball");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "ball") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "tennis ball") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "tennis ball");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "ball") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "life size barbie") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "life size barbie");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "barbie") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "life size barbie") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "life size barbie");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "barbie") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "baby doll") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "baby doll");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "doll") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "baby doll") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "baby doll");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "doll") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "bar counter") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "bar counter");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "counter") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "bar counter") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "bar counter");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "counter") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "low cabinet") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "low cabinet");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "cabinet") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "low cabinet") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "low cabinet");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "cabinet") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "magical wand") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "magical wand");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "wand") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "magical wand") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "magical wand");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "wand") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "dog") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "dog");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "dog") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "dog") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "dog");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "dog") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "giant spider") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "giant spider");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "spider") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "giant spider") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "giant spider");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "spider") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
	if(strstr(cl->processedInput, "hostile magical beast") != NULL) {
		if (cl->noun1Index == -1) {
			//add to noun1
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, "hostile magical beast");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "beast") == 0) {
    				cl->noun1Index = i;
    			}
    		}
		} else if (cl->noun2Index == -1 && (strcmp(cl->noun1, "hostile magical beast") != 0)) {
			//add to noun2
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, "hostile magical beast");	
    		for (i = 0; i < cl->inputArraySize; i++) {
    			if (strcmp(cl->inputArray[i], "beast") == 0) {
    				cl->noun1Index = 1;
    			}
    		}
		} else {
			return;
		}
	}
}

/*********************************************************************
 ** Function: void getObjectFeatureWord(struct command_line* cl)
 ** Description: gets feature/object from user input if exists
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.noun1 or cl.noun2 (if there was a feature/object) 
 ** 	contains feature/object if exists in user input
 *********************************************************************/
 
void getObjectFeatureWord(struct command_line* cl) {
	int i;
	int j;
	for (i = 0; i < cl->inputArraySize; i++) {	
		if (strcmp(cl->inputArray[i], "serena") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "serena williams");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "serena williams") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "serena williams");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}		
		if (strcmp(cl->inputArray[i], "williams") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "serena williams");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "serena williams") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "serena williams");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "ball") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "tennis ball");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "tennis ball") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "tennis ball");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "doll") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "baby doll");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "baby doll") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "baby doll");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "barbie") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "life size barbie");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "life size barbie") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "life size barbie");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "cat") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "tabby cat");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "tabby cat") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "tabby cat");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "beast") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "hostile magical beast");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "hostile magical beast") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "hostile magical beast");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "counter") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "bar counter");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "bar counter") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "bar counter");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "bar") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "bar counter");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "bar counter") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "bar counter");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "keypad") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "keypad");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "keypad") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "keypad");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "lion") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "lion");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "lion") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "lion");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "fountain") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "fountain");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "fountain") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "fountain");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "hammock") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "hammock");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "hammock") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "hammock");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "piano") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "piano");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "piano") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "piano");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "cage") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "cage");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "cage") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "cage");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "bat") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "bat");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "bat") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "bat");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "car") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "car");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "car") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "car");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "shelf") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "shelf");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "shelf") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "shelf");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "spider") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "giant spider");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "spider") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "giant spider");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "cabinet") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "low cabinet");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "low cabinet") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "low cabinet");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "chest") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "chest");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "chest") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "chest");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "dog") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "dog");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "dog") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "dog");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "notes") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "notes");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "notes") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "notes");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "desk") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "desk");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "desk") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "desk");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "ghost") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "ghost");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "ghost") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "ghost");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "fountain") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "fountain");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "fountain") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "fountain");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "hammock") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "hammock");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "hammock") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "hammock");	
 				cl->noun2Index = i;
				return;
			}
    	}
    	if (strcmp(cl->inputArray[i], "librarian") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "librarian");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "librarian") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "librarian");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 	
    	if (strcmp(cl->inputArray[i], "bones") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "bones");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "bones") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "bones");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 
    	if (strcmp(cl->inputArray[i], "catnip") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "catnip");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "catnip") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "catnip");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 
    	if (strcmp(cl->inputArray[i], "key") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "key");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "key") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "key");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 
    	if (strcmp(cl->inputArray[i], "crowbar") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "crowbar");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "crowbar") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "crowbar");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 
    	if (strcmp(cl->inputArray[i], "book") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "book");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "book") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "book");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 
    	if (strcmp(cl->inputArray[i], "catnip") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "catnip");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "catnip") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "catnip");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 
    	if (strcmp(cl->inputArray[i], "key1") == 0) {
			if (cl->noun1Index == -1) {
				//add to noun1
				memset(cl->noun1, '\0', sizeof(cl->noun1));
				strcpy(cl->noun1, "key1");	
				cl->noun1Index = i;
			} else if (cl->noun2Index == -1  && (strcmp(cl->noun1, "key1") != 0)) {
				memset(cl->noun2, '\0', sizeof(cl->noun2));
				strcpy(cl->noun2, "key1");	
 				cl->noun2Index = i;
			} else {
				return;
			}
    	} 
	}
}

/*********************************************************************
 ** Function: void getOtherNouns(struct command_line* cl)
 ** Description: gets other nouns from user input if exists
 ** Parameters: struct command_line* cl
 ** Pre-Conditions: none
 ** Post-Conditions: cl.noun1 or cl.noun2 if those were not already
 ** 	taken by a feature or exit
 *********************************************************************/

void getOtherNouns(struct command_line* cl) {
	if (cl->noun1Index == -1) {
		cl->noun1Index = cl->verbIndex + 1;
		if (cl->noun1Index < cl->inputArraySize) {
			memset(cl->noun1, '\0', sizeof(cl->noun1));
			strcpy(cl->noun1, cl->inputArray[cl->noun1Index]);
		}
		else {
			memset(cl->noun1, '\0', sizeof(cl->noun1));
		}
	}
	if (cl->noun2Index == -1) {
		cl->noun2Index = cl->noun1Index + 1;
		if (cl->noun2Index < cl->inputArraySize) {
			memset(cl->noun2, '\0', sizeof(cl->noun2));
			strcpy(cl->noun2, cl->inputArray[cl->noun2Index]);
		}
		else {
			memset(cl->noun2, '\0', sizeof(cl->noun2));
		}
	}
}