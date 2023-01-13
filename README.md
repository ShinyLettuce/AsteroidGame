# AsteroidGame

CONTROLS
X: start game from main menu 
Z: (hold)charge shot (release)shoot if fully charged
Arrow keys: movement of spaceship

GOAL OF THE GAME
Shoot the asteroids and pick up points to score as high as possible, can you get to 10,000?
(It is possible, I've tried!)

CODE

Where is everything?
main.cpp
Handles main game loop and holds the code that controls the menu states

Entity.h/.cpp
Holds all of the entity classes and their update/render functions.

Level.h/.cpp:
Handles everything in the level with its own update and render function. All particles, rocks, and the player are made as instances here with their own spawn functions
and a function that removes dead entities. Most interactions between entities such as collisions are handled by the update function here. Other that drawing entities
score and combo text is drawn here.

Media.h/.cpp
Holds the assets of the game and media_init() that loads them.

Math.h/.cpp
Holds functions that uses cmath, among other useful math functions.

CREDITS
Sounds from Pixabay and mixkit
My previous team for code inspiration<3
