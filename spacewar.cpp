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

	// map textures
	if (!tileTextures.initialize(graphics, TILE_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile textures"));

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

	// generate an object at a distance further than 'minradius' but no further than 'maxradius'
	//  from point X,Y
	int distance = rand() % (50 - 5) + 10;
	int angle = rand() % 360;

	int dx = (int)(cos(angle * PI / 180) * distance);
	int dy = (int)(sin(angle * PI / 180) * distance);
	


	if (!enemy.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemy.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	
	enemy.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

	if (!enemy1.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy1.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemy1.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	
	enemy1.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

	// bullet
	if (!bullet.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	bullet.setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
	bullet.setCurrentFrame(BulletNS::Bullet_START_FRAME);
	bullet.setX(GAME_WIDTH / 2);
	bullet.setY(GAME_HEIGHT / 1.25);
	bullet.setVelocity(VECTOR2(BulletNS::SPEED, -BulletNS::SPEED));

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
	bullet.update(frameTime);


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
	laser.draw();

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
	tileTextures.onLostDevice();

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
	tileTextures.onResetDevice();

    Game::resetAll();
    return;
}
