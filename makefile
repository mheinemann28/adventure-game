default: GameEngine.c RoomLoader.c GameStateLoader.c CommandParser.c
	gcc -o adventure-game GameEngine.c RoomLoader.c GameStateLoader.c CommandParser.c
	
test-CommandParser: CommandParser.c CommandParser-tester.c
	gcc -o test-CommandParser CommandParser.c CommandParser-tester.c

gameEngine: GameEngine.c GameEngine.h GameEngine_helpers.h RoomLoader.c RoomLoader.h
	gcc -g -o gameEngine GameEngine.c GameEngine.h GameEngine_helpers.h RoomLoader.c RoomLoader.h

clean:
	rm -f adventure-game test-CommandParser gameEngine