default: GameEngine.c RoomLoader.c GameStateLoader.c CommandParser.c
	gcc -o adventure-game GameEngine.c RoomLoader.c GameStateLoader.c CommandParser.c
	
test-CommandParser: CommandParser.c CommandParser-tester.c
	gcc -o test-CommandParser CommandParser.c CommandParser-tester.c
