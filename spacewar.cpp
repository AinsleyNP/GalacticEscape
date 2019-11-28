// This class is the core of the game

#include "spaceWar.h"
using namespace spaceWarNS;

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	mapX = 0;
	mapY = 0;
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // Background texture
    if (!backgroundTexture.initialize(graphics,BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!background.initialize(graphics,0,0,0,&backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));


    // ship
    if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH/2);
    ship1.setY(GAME_HEIGHT/1.25);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)

	// enemy
	if (!enemy.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));
	enemy.setFrames(shipNS::SHIP2_START_FRAME, shipNS::SHIP2_END_FRAME);
	enemy.setCurrentFrame(shipNS::SHIP2_START_FRAME);
	enemy.setX(GAME_WIDTH - GAME_WIDTH / 4);
	enemy.setY(GAME_HEIGHT / 4);
	enemy.setVelocity(VECTOR2(-shipNS::SPEED, -shipNS::SPEED)); // VECTOR2(X, Y)

	// LASER STUFF
	int laserpick = rand() % 25;

	float Coords[4][2] = { {100,100} ,{300,200},{100,250},{200,400} };

	// Initialize
	if (!laser.initialize(this, LaserNS::WIDTH, LaserNS::HEIGHT, LaserNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing laser"));

	// Set ANIMATION frames
	laser.setFrames(LaserNS::Laser_START_FRAME, LaserNS::Laser_END_FRAME);
	laser.setCurrentFrame(LaserNS::Laser_START_FRAME);

	// Set Location
	laser.setX(Coords[laserpick][0]);
	laser.setY(Coords[laserpick][1]);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	float shipx;
	float shipy;

    ship1.update(frameTime);
	enemy.update(frameTime);
	laser.update(frameTime);


	// SCROLLING STUFF
	shipx = ship1.getX();
	if (shipx < 0)                  // if butterfly off screen left
	{
		mapX -= ship1.getVelocity().x * frameTime;  // scroll map right
		ship1.setX(0);              // put butterfly at left edge
	}

	// if butterfly off screen right
	else if (shipx > GAME_WIDTH - ship1.getWidth())
	{
		mapX -= ship1.getVelocity().x * frameTime;  // scroll map left
		// put butterfly at right edge
		ship1.setX((float)(GAME_WIDTH - ship1.getWidth()));
	}

	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
    VECTOR2 collisionVector;
    // if collision between ships
    //if(ship1.collidesWith(ship2, collisionVector))
    {
        // bounce off ship
        //ship1.bounce(collisionVector, ship2);
        //ship1.damage(SHIP);
        // change the direction of the collisionVector for ship2
        //ship2.bounce(collisionVector*-1, ship1);
        //ship2.damage(SHIP);
    }
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    background.draw();                          // add the to the scene
    //planet.draw();                          // add the planet to the scene
    ship1.draw();                           // add the spaceship to the scene
    enemy.draw();                           // add the spaceship to the scene
	laser.draw();							// add lasers


	// "TILES"
	for (int col = 0; col < MAP_WIDTH; col++)       // for each column of map
	{
		tile.setX((float)(col * TEXTURE_SIZE)); // set tile X
		for (int row = 0; row < MAP_HEIGHT; row++)    // for each row of map
		{
			if (tileMap[row][col] >= 0)          // if tile present
			{
				tile.setCurrentFrame(tileMap[row][col]);    // set tile texture
				tile.setY((float)(row * TEXTURE_SIZE) + mapY);   // set tile Y
				// if tile on screen
				if (tile.getY() > -TEXTURE_SIZE && tile.getY() < GAME_HEIGHT)
					tile.draw();                // draw tile
			}
		}
	}

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    backgroundTexture.onLostDevice();
    gameTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    gameTextures.onResetDevice();
    backgroundTexture.onResetDevice();
    Game::resetAll();
    return;
}
