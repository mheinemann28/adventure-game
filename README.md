# Adventure Team Final Project for CS 467 Capstone Course

#### Team Members
* Michael Heinemann
* Stephen Liu
* Heidi Uphoff

This is an escape game. Users will be placed in a starting room and must navigate through the maze of rooms to the end room. Within each room users will be presented with descriptions, options, and sometimes an enemy or obstacle to defeat. Users interact with the rooms using natural language commands such as “look out window,” “open up chest,” or “go through north door.” Throughout the rooms there are objects that users can pick up and place in their inventory. They can dispose of objects in the inventory in any room. Some objects can be used to overcome specific room enemies/obstacles.

#### Supported Verb Commands 
* look - repeats the long description of a room
* look at - takes a closer look at specified room feature
* go - moves user through specified exit
* take - adds specified object to user's inventory
* drop - removes specified object from user's inventory
* help - displays list of supported actions to user
* inventory - lists user's current inventory
* hit - hits specified object or feature
* open - opens specified object or feature
* move - moves specified object or feature 

#### Instructions to Run Game
* git clone https://github.com/endtoendpaper/adventure-game.git
* make gameEngine 
* gameEngine

#### Instructions to Run Testing Program for Command Line Parser 
* make test-CommandParser
* test-CommandParser
