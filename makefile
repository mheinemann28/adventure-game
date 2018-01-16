default: GameEngine.c RoomLoader.c GameStateLoader.c CommandParser.c
	gcc -o adventure-game GameEngine.c RoomLoader.c GameStateLoader.c CommandParser.c