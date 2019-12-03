// This class is the core of the game

#include "spaceWar.h"
#include <vector>
#include <time.h>       /* time */

using namespace spaceWarNS;

typedef std::vector<Bullet *> BULLETLIST;
typedef std::vector<Enemy *> ENEMYLIST;

std::vector<Bullet *> bullet_collection;
std::vector<Enemy *> enemyList;


float resettime = 0;
bool respawn = false;
int heart = 5;
bool die = false;
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	mapX = 1;
	mapY = 10;
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

	// tile image
	if (!tile.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, &tileTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
	tile.setFrames(0, 0);
	tile.setCurrentFrame(0);


    // ship
    if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH/2);
    ship1.setY(GAME_HEIGHT/1.25);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y

	
	for (std::vector<Bullet*>::iterator it = bullet_collection.begin(); it < bullet_collection.end(); ++it)
	{
		(*it)->update(frameTime);
	}


	// enemy
	if (!enemy1.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy1.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemy1.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemy1.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)
	
	float enemyCoords[15][3] = {
		{ 100,100,0 },{ 200,100,0 },{ 300,100,0 },{ 400,100,0 },{ 500,100,0 },
		{ 100,200,0 },{ 200,200,0 },{ 300,200,0 },{ 400,200,0 },{ 500,200,0 },
		{ 100,300,0 },{ 200,300,0 },{ 300,300,0 },{ 400,300,0 },{ 500,300,0 }
	};
	
	
	Enemy * e = new Enemy(); // POINTER
	enemyList.push_back(e);
	e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures);
	e->setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	e->setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	e->setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

	srand(time(NULL)); // Set RANDOM seed info
	int enemyPick = rand() % 15;
	if (enemyCoords[enemyPick][2] == 0)
	{
		e->setX(enemyCoords[enemyPick][0]);
		e->setY(enemyCoords[enemyPick][1]);
		enemyCoords[enemyPick][2] = 1;
	}


	// LASER STUFF
	int laserpick = rand()%4;

	float laserCoords[4][2] = { {100,100} ,{300,200},{100,250},{200,400} };

	// Initialize
	if (!laser.initialize(this, LaserNS::WIDTH, LaserNS::HEIGHT, LaserNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing laser"));

	// Set ANIMATION frames
	laser.setFrames(LaserNS::Laser_START_FRAME, LaserNS::Laser_END_FRAME);
	laser.setCurrentFrame(LaserNS::Laser_START_FRAME);

	// Set Location
	laser.setX(laserCoords[laserpick][0]);
	laser.setY(laserCoords[laserpick][1]);

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
	enemy1.update(frameTime);
	laser.update(frameTime);
	bullet.update(frameTime);
	resettime += (frameTime);
	

	// SCROLLING STUFF
	shipx = ship1.getX();
	if (shipx < 0)                  // if ship off screen left
	{
		mapX -= ship1.getVelocity().x * frameTime;  // scroll map right
		ship1.setX(0);              // put ship at left edge
	}

	// if ship off screen right
	else if (shipx > GAME_WIDTH - ship1.getWidth())
	{
		mapX -= ship1.getVelocity().x * frameTime;  // scroll map left
		// put ship at right edge
		ship1.setX((float)(GAME_WIDTH - ship1.getWidth()));
	}

	// Vertical "Scrolling"
	shipy = ship1.getY();
	if (shipy < GAME_HEIGHT/2)
	{
		ship1.setY(GAME_HEIGHT/2 -1); // So ship doesnt go past half way(ish)
		ship1.setActive(true);
		ship1.setVisible(true);
	}

	if (shipy > GAME_HEIGHT - ship1.getHeight())
	{
		ship1.setY(GAME_HEIGHT - ship1.getHeight()+1);
		mapY -= ship1.getVelocity().y * frameTime;
	}
	if (respawn == true)
	{
		ship1.setVisible(true);
		ship1.setActive(true);
		ship1.setX(GAME_WIDTH / 2);
		ship1.setY(GAME_HEIGHT / 1.5);
		respawn = false;
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
    if(ship1.collidesWith(enemy1, collisionVector))
    {
		heart = heart - 1;
		ship1.setVisible(false);
		ship1.setActive(false);
		ship1.setX(GAME_WIDTH/1.25);
		ship1.setY(GAME_HEIGHT/1.25);
		
		respawn = true;


		
			
		
		if (heart == 0)
		{
			PostQuitMessage(0);
		}
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
    //planet.draw();
	// add the planet to the scene
	if (ship1.getActive())
	{
		ship1.draw();                           // add the spaceship to the scene
	}
    enemy1.draw(); // enemy spaceship draw
	
	laser.draw();							// add lasers

	// BULLETS
	if (input->isKeyDown(VK_SPACE) && ship1.getActive())
	{
		bullet.draw();
		//bullet.setX(ship1.getX());
		//bullet.setY(ship1.getY());
		bullet_collection.push_back(new Bullet());
		bullet.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures);
		bullet.setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
		bullet.setCurrentFrame(BulletNS::Bullet_START_FRAME);
		bullet.setVelocity(VECTOR2(BulletNS::SPEED, -BulletNS::SPEED));
	} 
	// DRAW "TILES"
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
