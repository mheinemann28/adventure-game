# Adventure Team Final Project for CS 467 Capstone Course

#### Team Members
* Michael Heinemann
* Stephen Liu
* Heidi Uphoff

This is an escape game. Users will be placed in a starting room and must navigate through the
maze of rooms to the end room. Within each room users will be presented with descriptions,
options, and an enemy or obstacle to defeat. Failure to defeat the enemy or overcome the
obstacle will result in the game ending. Users interact with the room using natural language
commands such as “look out window,” “open up chest,” or “go through north door.”

Throughout the rooms there are eight objects that users can pick up and place in their inventory.
They can dispose of objects in the inventory in any room. Objects must remain in rooms in
which they are disposed. Some objects can be used to overcome specific room
enemies/obstacles.

In order to defeat the room’s enemy or overcome the room’s obstacle, users are given three
choices: try to flee, fight back, or use an object from their inventory. If they try to flee or fight
back, the game rolls a dice to see if they succeed. If successful in fleeing, users are randomly
placed in an adjacent room. If successful in fighting back, a user remains in the room and can
decide what to do next. Items from the inventory may or may not work to defeat the enemy
depending on the room.

#### Instructions to Run Game
git clone https://github.com/endtoendpaper/adventure-game.git

make

adventure-game

