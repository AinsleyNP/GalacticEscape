// This class is the core of the game

#include "spaceWar.h"
#include <vector>
#include <time.h>       /* time */

using namespace spaceWarNS;

typedef std::vector<Bullet *> BULLETLIST;
typedef std::vector<Enemy *> ENEMYLIST;
typedef std::vector<Laser*> LASERLIST;

std::vector<Bullet *> bullet_collection;
std::vector<Enemy *> enemyList;
std::vector<Laser*> laserlist;

float resettime = 0;
bool respawn = false;
int heart = 5;
bool die = false;
int ScreenTileY=GAME_HEIGHT/TEXTURE_SIZE;
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	mapX = 0;
	mapY = -(TEXTURE_SIZE*ScreenTileY*2);
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

	// map textures
	if (!tileTextures.initialize(graphics, TILE_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile textures"));

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// main menu textures
	if (!mainMenuTexture.initialize(graphics, MAINMENU_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu textures"));

	// main menu image 
	if (!mainMenu.initialize(graphics, 0, 0, 0, &mainMenuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu"));
	// place main menu in center of screen
	mainMenu.setX(GAME_WIDTH * 0.5f - mainMenu.getWidth() * 0.5f);
	mainMenu.setY(GAME_HEIGHT * 0.5f - mainMenu.getHeight() * 0.5f);

    // nebula image
    if (!background.initialize(graphics,0,0,0,&backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// tile image
	if (!tile.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, &tileTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
	tile.setFrames(0, 0);
	tile.setCurrentFrame(0);

	//==================================================================================================================
    // ship
    if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH/2);
    ship1.setY(GAME_HEIGHT/1.25);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y
	
	//==================================================================================================================
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

	//==================================================================================================================
	// LASER STUFF

	float laserCoords[4][3] =
	{
		{GAME_WIDTH / 3,GAME_HEIGHT / (4 / 3),3 * PI / 2} ,
		{GAME_WIDTH / 3 * 2,GAME_HEIGHT / (4 / 3),3 * PI / 2},
		{GAME_WIDTH / 3,GAME_HEIGHT / (4 / 3),7 * PI / 4},
		{GAME_WIDTH / 3,GAME_HEIGHT / (4 / 3),5 * PI / 4}
	};

	Laser * l = new Laser();
	for (int i = 0; i > 3; i++)
	{
		laserlist.push_back(l);
		if (l->initialize(this, LaserNS::WIDTH, LaserNS::HEIGHT, LaserNS::TEXTURE_COLS, &gameTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing laser"));
		// Set ANIMATION frames
		l->setFrames(LaserNS::Laser_START_FRAME, LaserNS::Laser_END_FRAME);
		l->setCurrentFrame(LaserNS::Laser_START_FRAME);
		l->setX(laserCoords[i][0]);
		l->setY(laserCoords[i][1]);
	}


	
	//==================================================================================================================
	// Bullets
	bullet.setX(ship1.getX());
	bullet.setY(ship1.getY());

	
	bullet.setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
	bullet.setCurrentFrame(BulletNS::Bullet_START_FRAME);
	bullet.setVelocity(VECTOR2(BulletNS::SPEED, -BulletNS::SPEED));

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

	float shipx;
	float shipy;

    ship1.update(frameTime);
	enemy1.update(frameTime);
	laser.update(frameTime);
	bullet.update(frameTime);
	resettime += (frameTime);

	
//==================================================================================================================
	// SCROLLING STUFF
	if (mapY >= ScreenTileY) // RECURRING SCROLLING
	{
		mapY = -TEXTURE_SIZE*MAP_HEIGHT;
	}
	//						Vertical "Scrolling"
	shipy = ship1.getY();
	if (shipy < GAME_HEIGHT/2)
	{
		ship1.setY(GAME_HEIGHT/2 -1);	// Checks ship at about half GAME_HEIGHT
		if (input->isKeyDown(VK_UP))	// Checks MovementKey(UP) pressed
		{
			mapY -= ship1.getVelocity().y * frameTime;	// Scroll at fastest speed
		}
		else	// If NOT pressing UP while at about half GAME_HEIGHT
		{
			mapY -= ship1.getVelocity().y * frameTime * 0.5; //Scrolls at normal speed
		}
	}
	else		// Scrolls at normal speed all the time
	{
		mapY -= ship1.getVelocity().y * frameTime * 0.5;
	}

	//==================================================================================================================

	if (respawn == true)
	{
		Sleep(500);
		ship1.setVisible(true);
		ship1.setActive(true);
		ship1.setX(GAME_WIDTH / 2);
		ship1.setY(GAME_HEIGHT / 1.5);
		respawn = false;
	}
	for (std::vector<Bullet*>::iterator it = bullet_collection.begin(); it < bullet_collection.end(); ++it)
	{
		(*it)->update(frameTime);
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

	//==================================================================================================================
	if (ship1.getActive())
	{
		ship1.draw();                           // add the spaceship to the scene
	}

	//==================================================================================================================
    enemy1.draw(); // enemy spaceship draw

	if (menu) {
		mainMenu.draw(); // main menu draw
	}
	
	//==================================================================================================================
	for (std::vector<Laser*>::iterator it = laserlist.begin(); it < laserlist.end(); ++it)
	{
		(*it)->draw();
	}

	//==================================================================================================================
	// BULLETS
	if (input->isKeyDown(VK_SPACE) && ship1.getActive())
	{
		bullet.draw();
		bullet_collection.push_back(new Bullet());
		bullet.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures);
	} 

	//==================================================================================================================
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
	mainMenuTexture.onLostDevice();

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

    Game::resetAll();
    return;
}
