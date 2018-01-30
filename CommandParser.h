/*********************************************************************
 ** Program Filename: CommandParser.h
 ** Author: Adventure Team (Michael Heinemann, Stephen Liu, Heidi Uphoff)
 ** Date: Jan. 15, 2018
 ** Description: Parses command line input using natural language
 **      parsing
 ** Input: a command string
 ** Output: a struct parsed_command with 3 values: verb, noun1, noun2
 *********************************************************************/
 
 /* To prevent compiler from processing contents twice, wrap in a conditional */
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

/* parsed command that is returned by void parseCommand(char command[2000]) */
struct parsed_command {
	char verb[50];
	char noun1[50];
	char noun2[50];
};

/* stores everything needed by the command parser functions */
struct command_line {
	char userInput[2000];
	char processedInput[2000];
	char inputArray[40][50];
	int inputArraySize;
	char verb[50];
	char noun1[50];
	char noun2[50];
	int verbIndex;
	int noun1Index;
	int noun2Index;
};

/* data  */
//char *stop_words[] = {"a", "the"};
//char verb_look_synonyms[1][50] = {""};
//char verb_go_synonyms[1][50] = {""};
//char verb_take_synonyms[1][50] = {""};
//char verb_drop_synonyms[1][50] = {""};
//char verb_help_synonyms[1][50] = {""};
//char verb_inventory_synonyms[1][50] = {""};
//char verb_hit_synonyms[1][50] = {""};
//char verb_open_synonyms[1][50] = {""};
//char verb_move_synonyms[1][50] = {""};

/* function declarations */
struct parsed_command parseCommand(char command[2000]);
void lowercaseCommand(struct command_line* cl);
void stripPunctuation(struct command_line* cl);
void removeStopWords(struct command_line* cl);
void splitCommandIntoArray(struct command_line* cl);
void getVerb(struct command_line* cl);
void getExit(struct command_line* cl);
void getFeature(struct command_line* cl);
void getOtherNouns(struct command_line* cl);

/* Place at end of file - End of header conditional */
#endif
 
