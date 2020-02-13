// This class is the core of the game

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Lim Wei Fu
//  Student Number:     S10189687

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Brannon Chua
//  Student Number:     S10187075

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley Malcolm Pereira
//  Student Number:     S10186606

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:		Dinesh KP
//  Student Number:     S10185976

#include "spaceWar.h"
#include <vector>
#include <time.h>       /* time */

using namespace spaceWarNS;

typedef std::vector<Bullet *> BULLETLIST;
typedef std::vector<Enemy *> ENEMYLIST;
typedef std::vector<Laser *> LASERLIST;
typedef std::vector<Bullet*> ENEMYBULLETLIST;

std::vector<Bullet *> bullet_collection;
std::vector<Enemy *> enemyList;
std::vector<Laser *> laserList;
std::vector<Bullet*> enemyBulletList;

bool respawn = false;
int heart = 5;
int game_height = GAME_HEIGHT;
bool die = false;
bool over = false;
float resettime = 0;
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	mapX = 0;
	mapY = -TEXTURE_SIZE * (MAP_HEIGHT - (game_height / TEXTURE_SIZE));
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

	// main menu textures
	if (!mainMenuTexture.initialize(graphics, MAINMENU_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu textures"));

	// main menu image 
	if (!mainMenu.initialize(graphics, 0, 0, 0, &mainMenuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu"));
	// place main menu in center of screen
	mainMenu.setX(GAME_WIDTH * 0.5f - mainMenu.getWidth() * 0.5f);
	mainMenu.setY(GAME_HEIGHT * 0.5f - mainMenu.getHeight() * 0.5f);



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

	// Game over textures
	if (!gameOverTexture.initialize(graphics, GAMEOVER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu textures"));

	if (!Gameover.initialize(graphics, 0, 0, 0, &gameOverTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error Initializing Game over menu"));

    // ship
    if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH/2);
    ship1.setY(GAME_HEIGHT/1.25);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)

	//=========================================================================
	// enemy initialize
	if (!enemy1.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy1.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemy1.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemy1.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

	
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	// DEFINING VARIABLES
	float shipx;
	float shipy;

	// HUD/MENU =====================================================================================
	// checks for return key press
	// game starts if key pressed
	if (input->wasKeyPressed(VK_RETURN))
	{
		menu = false;
	}
	// checks for escape key press
	// game application quits if key pressed
	if (input->wasKeyPressed(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	if (over == false) {
		Gameover.setVisible(false);
	}

		
	//========================================================================= ENVIRONMENT STUFF
	// SCROLLING STUFF
	if (mapY >= GAME_HEIGHT)
	{
		mapY = -TEXTURE_SIZE*MAP_HEIGHT-128;
	}

	// Vertical "Scrolling"
	shipy = ship1.getY();
	if (shipy < GAME_HEIGHT/2)
	{
		if (input->isKeyDown(VK_UP))
		{
			mapY +=  frameTime * SCROLL_RATE;
		}
		else
		{
			//mapY += frameTime * SCROLL_RATE;
		}
	}
	else
	{
		//mapY +=  frameTime * SCROLL_RATE;
	}

	//=========================================================================
	// Player Control

	// Shoot Bullet
	if (input->isKeyDown(VK_SPACE) && resettime > 0.5)
	{
		Bullet* b = new Bullet();
		bullet_collection.push_back(b);
		if (ship1.getDirection()==1)
		{
			b->setX(ship1.getX() + (shipNS::WIDTH / 2));
			b->setDirection(1);
		}
		else
		{
			b->setX(ship1.getX() - (shipNS::WIDTH / 2));
			b->setDirection(-1);
		}
		b->setY(ship1.getY());
		resettime = 0;
	}

	for (std::vector<Bullet*>::iterator ib = bullet_collection.begin(); ib < bullet_collection.end(); ++ib)
	{
		(*ib)->initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &gameTextures);
		(*ib)->setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
		(*ib)->setCurrentFrame(BulletNS::Bullet_START_FRAME);
		(*ib)->setVelocity(VECTOR2(-BulletNS::SPEED, -BulletNS::SPEED)); // VECTOR2(X, Y)
	}

	if (respawn == true)
	{
		Sleep(500);
		ship1.setVisible(true);
		ship1.setActive(true);
		ship1.setX(GAME_WIDTH / 2);
		ship1.setY(GAME_HEIGHT / 1.5);
		respawn = false;
	}

	
	if (heart == 0)
	{
		Gameover.setVisible(true);
	}

	//Bullet Pointer Update
	for (std::vector<Bullet*>::iterator ib = bullet_collection.begin(); ib < bullet_collection.end(); ++ib)
	{
		(*ib)->update(frameTime);
	}

	//=========================================================================
	resettime += frameTime;
	ship1.update(frameTime);
	enemy1.update(frameTime);
	laser.update(frameTime);
	bullet.update(frameTime);
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
    // if collision between ship and enemy
    if(ship1.collidesWith(enemy1, collisionVector))
    {
		heart = heart - 1;
		ship1.setVisible(false);
		ship1.setActive(false);
		ship1.setX(GAME_WIDTH/1.25);
		ship1.setY(GAME_HEIGHT/1.25);
		
		respawn = true;
    }

	// BULLET COLLISION
	for (std::vector<Bullet *>::iterator ib = bullet_collection.begin(); ib < bullet_collection.end(); ++ib)
	{
		if ((*ib)->collidesWith(enemy1, collisionVector))
		{
			float hp = enemy1.getHealth();
			(*ib)->setVisible(false);
			(*ib)->setActive(false);
			ib = bullet_collection.erase(ib);
			enemy1.setHealth(hp-1);
			break;
		}
	}


		// bounce off ship
		//ship1.bounce(collisionVector, ship2);
		//ship1.damage(SHIP);
		// change the direction of the collisionVector for ship2
		//ship2.bounce(collisionVector*-1, ship1);
		//ship2.damage(SHIP);
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites


	// DRAW "TILES"
	for (int col = 0; col < MAP_WIDTH; col++)       // for each column of map
	{
		tile.setX((float)(col * TEXTURE_SIZE));	// set tile X
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


	if (ship1.getActive())
	{
		ship1.draw();                           // add the spaceship to the scene
	}

    enemy1.draw(); // enemy spaceship draw



	// BULLETS
	for (std::vector<Bullet*>::iterator lb = bullet_collection.begin(); lb < bullet_collection.end(); ++lb)
	{
		(*lb)->draw();
	}


	if (menu) {
		mainMenu.draw(); // main menu draw
	}

	if (over = true) {
		Gameover.draw();
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
	mainMenuTexture.onLostDevice();
	gameOverTexture.onLostDevice();

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
	mainMenuTexture.onResetDevice();
	gameOverTexture.onLostDevice();

    Game::resetAll();
    return;
}
