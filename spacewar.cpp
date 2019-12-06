// This class is the core of the game

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

float enemybulletValue = 0;
float resettime = 0;
bool respawn = false;
int heart = 5;
bool die = false;
bool over = false;
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	mapX = 0;
	mapY = -GAME_HEIGHT;
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

	// Enemy Spawning

	//Enemy Coords
	float enemyCoords[21][3] = {
		{ 50,150,0 },{100,150,0},{ 200,100,0 },{ 300,150,0 },{ 400,100,0 },{ 500,150,0 },{600,125,0},
		{ 50,200,0 },{100,225,0},{ 250,250,0 },{ 350,200,0 },{ 400,250,0 },{ 550,200,0 },{600,225,0},
		{ 50,325,0 },{100,300,0},{ 200,350,0 },{ 300,300,0 },{ 400,350,0 },{ 500,300,0 },{600,350,0}
	};

	for (int i = 0; i < 15; i++)
	{
		Enemy * e = new Enemy(); // POINTER
		enemyList.push_back(e); //Adds e into enemyList(vector)
	}

	srand(time(NULL)); // Set RANDOM seed info
	for (std::vector<Enemy *>::iterator it = enemyList.begin(); it < enemyList.end(); ++it)
	{
		(*it)->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures);
		(*it)->setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
		(*it)->setCurrentFrame(enemyNS::ENEMY_START_FRAME);
		(*it)->setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

		//Randomizer Spawn
		int cantspawn = 1;
		int enemyPick = rand() % 21;
		if (enemyCoords[enemyPick][2] == 0)
		{
			(*it)->setX(enemyCoords[enemyPick][0]);
			(*it)->setY(enemyCoords[enemyPick][1]);
			enemyCoords[enemyPick][2] = 1;
		}
		else
		{
			cantspawn = 0;
			while (cantspawn == 0)
			{
				enemyPick = rand() % 15;
				if (enemyCoords[enemyPick][2] == 0)
				{
					(*it)->setX(enemyCoords[enemyPick][0]);
					(*it)->setY(enemyCoords[enemyPick][1]);
					enemyCoords[enemyPick][2] = 1;
					cantspawn = 1;
				}
			}
		}

		Gameover.setX(GAME_WIDTH * 0.5f - Gameover.getWidth() * 0.5f);
		Gameover.setY(GAME_HEIGHT * 0.5f - Gameover.getHeight() * 0.5f);

	}
	
	if (frameTime > 10)
	{

	}
	//=========================================================================
	// LASER STUFF	
	float laserCoords[4][3] =
	{
		{GAME_WIDTH / 3,GAME_HEIGHT/ 3		,	3 * PI / 2} ,
		{GAME_WIDTH * 2/3,GAME_HEIGHT/3		,	3 * PI / 2},
		{GAME_WIDTH / 3,GAME_HEIGHT * 2/3	,	7 * PI / 4},
		{GAME_WIDTH	* 2/3,GAME_HEIGHT * 2/3	,	5 * PI / 4}
	};

	for (int i = 0; i < 4; i++) // Add Laser POINTER to vector 4 times
	{
		Laser * e = new Laser(); // POINTER
		laserList.push_back(e); //Adds e into laserList(vector)
	}

	int l = 0;
	for (std::vector<Laser *>::iterator lz = laserList.begin(); lz < laserList.end(); ++lz)
	{
		(*lz)->initialize(this, LaserNS::WIDTH, LaserNS::HEIGHT, LaserNS::TEXTURE_COLS, &gameTextures);
		(*lz)->setFrames(LaserNS::Laser_START_FRAME, LaserNS::Laser_END_FRAME);
		(*lz)->setCurrentFrame(LaserNS::Laser_START_FRAME);
		(*lz)->setVelocity(VECTOR2(-LaserNS::SPEED, -LaserNS::SPEED)); // VECTOR2(X, Y)
		(*lz)->setX(laserCoords[l][0]);
		(*lz)->setY(laserCoords[l][1]);
		(*lz)->setRadians(laserCoords[l][2]);
		l += 1;
	}

	
	/*bullet.setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
	bullet.setCurrentFrame(BulletNS::Bullet_START_FRAME);
	bullet.setVelocity(VECTOR2(BulletNS::SPEED, -BulletNS::SPEED));*/

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{

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

	//=========================================================================
	float shipx;
	float shipy;

    ship1.update(frameTime);
	enemy1.update(frameTime);
	laser.update(frameTime);
	bullet.update(frameTime);
	resettime += (frameTime);
	enemybulletValue += (frameTime);
		
	//=========================================================================
	// SCROLLING STUFF
	if (mapY >= GAME_HEIGHT)
	{
		mapY = -TEXTURE_SIZE*MAP_HEIGHT-128;
	}

	// Vertical "Scrolling"
	shipy = ship1.getY();
	if (shipy < GAME_HEIGHT/2)
	{
		ship1.setY(GAME_HEIGHT/2 -1); // So ship doesnt go past half way(ish)
		if (input->isKeyDown(VK_UP))
		{
			mapY -= ship1.getVelocity().y * frameTime * 3;
		}
		else
		{
			mapY -= ship1.getVelocity().y * frameTime * 0.5;
		}
	}
	else
	{
		mapY -= ship1.getVelocity().y * frameTime * 0.5;
	}

	//=========================================================================
	// Player Control
	if (respawn == true)
	{
		Sleep(500);
		ship1.setVisible(true);
		ship1.setActive(true);
		ship1.setX(GAME_WIDTH / 2);
		ship1.setY(GAME_HEIGHT / 1.5);
		respawn = false;
	}
	if (over == false) {
		Gameover.setVisible(false);
	}

	if (heart == 0)
	{
		Gameover.setVisible(true);
	}

	//===================================================================================================
	

	//===================================================================================================
	// ENEMY POINTER MOVEMENT CONTROL
	for (std::vector<Enemy*>::iterator it = enemyList.begin(); it < enemyList.end(); ++it)
	{
		float xloc =(*it)->getX();
		(*it)->setX(xloc += 0);
	}


	//===================================================================================================
	// Bullets
	if (input->wasKeyPressed(VK_SPACE) && resettime > 0.5)
	{
		Bullet* b = new Bullet();
		bullet_collection.push_back(b);
		b->setX(ship1.getX());
		b->setY(ship1.getY() - 16);
		resettime = 0;
	}

	for (std::vector<Bullet *>::iterator ib = bullet_collection.begin(); ib < bullet_collection.end(); ++ib)
	{
		if (resettime > 0.1)
		{
			(*ib)->initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &gameTextures);
			(*ib)->setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
			(*ib)->setCurrentFrame(BulletNS::Bullet_START_FRAME);
			(*ib)->setVelocity(VECTOR2(-BulletNS::SPEED, -BulletNS::SPEED)); // VECTOR2(X, Y)
			(*ib)->setY((*ib)->getY()-1);

			

		}
	

	}
	//===================================================================================================
	// Enemy Bullets

	if (enemybulletValue > 1)
	{
		for (std::vector<Enemy*>::iterator e = enemyList.begin(); e < enemyList.end(); ++e)
		{
			float xvalue = (*e)->getX();
			float yvalue = (*e)->getY();
			Bullet* b = new Bullet();
			enemyBulletList.push_back(b);
			b->setX(xvalue);
			b->setY(yvalue + 16);
			enemybulletValue = 0;
		}
	}

	for (std::vector<Bullet*>::iterator ibe = enemyBulletList.begin(); ibe < enemyBulletList.end(); ++ibe)
	{
		(*ibe)->initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &gameTextures);
		(*ibe)->setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
		(*ibe)->setCurrentFrame(BulletNS::Bullet_START_FRAME);
		(*ibe)->setVelocity(VECTOR2(-BulletNS::SPEED, -BulletNS::SPEED)); // VECTOR2(X, Y)
		(*ibe)->setY((*ibe)->getY() + 1.3);
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
	for (std::vector<Bullet *>::iterator ib = bullet_collection.begin(); ib < bullet_collection.end(); ++ib)
	{
		
			for (std::vector<Enemy*>::iterator ie = enemyList.begin(); ie < enemyList.end(); ++ie)
			{
				if ((*ie)->collidesWith(**ib, collisionVector))
				{
					(*ie)->setVisible(false);
					(*ie)->setActive(false);
					break;
				}
			}
			if (!(*ib)->getActive())
				ib = bullet_collection.erase(ib);
			else
				ib++;		

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

	for (std::vector<Enemy *>::iterator it = enemyList.begin(); it < enemyList.end(); ++it)
	{
		(*it)->draw();
	}

	if (input->isKeyDown(VK_BACK)) {
		for (std::vector<Laser*>::iterator lz = laserList.begin(); lz < laserList.end(); ++lz)
		{
			(*lz)->draw();
		}
	}

	// BULLETS
	for (std::vector<Bullet*>::iterator lb = bullet_collection.begin(); lb < bullet_collection.end(); ++lb)
	{
		(*lb)->draw();
	}

	//ENEMY BULLETS
	for (std::vector<Bullet*>::iterator be = enemyBulletList.begin(); be < enemyBulletList.end(); ++be)
	{
		(*be)->draw();
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
