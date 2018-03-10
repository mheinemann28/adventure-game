default: GameEngine.c RoomLoader.c ObjectLoader.c GameStateLoader.c CommandParser.c
	gcc -o adventure-game GameEngine.c RoomLoader.c ObjectLoader.c GameStateLoader.c CommandParser.c
	
test-CommandParser: CommandParser.c CommandParser-tester.c
	gcc -o test-CommandParser CommandParser.c CommandParser-tester.c

gameEngine: CommandParser.c CommandParser.h GameEngine.c GameEngine.h RoomLoader.c RoomLoader.h ObjectLoader.c ObjectLoader.h SaveGame.c SaveGame.h
	gcc -g -o gameEngine CommandParser.c CommandParser.h GameEngine.c GameEngine.h RoomLoader.c RoomLoader.h ObjectLoader.c ObjectLoader.h SaveGame.c SaveGame.h

clean:
	rm -f adventure-game test-CommandParser gameEngine
