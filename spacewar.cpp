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

typedef std::vector<Bullet*> BULLETLIST;
typedef std::vector<Arrow*> ARROWLIST;
typedef std::vector<Laser*> LASERLIST;
typedef std::vector<Enemy*> ENEMYLIST;
typedef std::vector<Bullet*> ENEMYBULLETLIST;
typedef std::vector<Tile*> TILELIST;

std::vector<Bullet*> bullet_collection;
std::vector<Arrow*> ArrowCollection;
std::vector<Enemy*> enemyList;
std::vector<Laser*> laserList;
std::vector<Bullet*> enemyBulletList;

std::vector<Tile*> tileslist;

bool respawn = false;
int heart = 5;
int game_height = GAME_HEIGHT;
bool die = false;
bool over = false;
float shotdelaytime = 0;
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
	:
	menu_(input)
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
	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// nebula image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
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

	// Player textures
	if (!playerTexture.initialize(graphics, PLAYER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player textures"));

	// ship
	if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
	ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	ship1.setX(GAME_WIDTH / 2);
	ship1.setY(GAME_HEIGHT / 1.25);
	ship1.setVelocity(VECTOR2(shipNS::SPEED, -shipNS::SPEED)); // VECTOR2(X, Y)

	//=========================================================================
	// enemy initialize
	if (!enemy1.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy1.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemy1.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemy1.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

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

	//==================================================================================================================================================
	// HUD/MENU 
	//==================================================================================================================================================
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
	//==================================================================================================================================================
	// ENVIRONMENT RELATED
	//==================================================================================================================================================
	// SCROLLING STUFF
	if (mapY >= GAME_HEIGHT)
	{
		mapY = -TEXTURE_SIZE * MAP_HEIGHT - 128;
	}

	// Vertical "Scrolling"
	float shipy = ship1.getY();
	if (shipy < GAME_HEIGHT / 2)
	{
		//ship1.setY(GAME_HEIGHT / 2 - 1); // So ship doesnt go past half way(ish)
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
		//mapY -= ship1.getVelocity().y * frameTime * 3;
	}
	
	//Right Horizontal "Scrolling"
	float shipx = ship1.getX();
	if (shipx < GAME_WIDTH )
	{		
		if (input->isKeyDown(VK_RIGHT))
		{
			mapX -= frameTime * SCROLL_RATE;
		}
	}
	
	if (shipx < GAME_WIDTH)
	{
		if (input->isKeyDown(VK_LEFT))
		{
			mapX += frameTime * SCROLL_RATE;
		}
	}

	for (std::vector<Tile*>::iterator t = tileslist.begin(); t < tileslist.end(); ++t)
	{
		(*t)->update(frameTime);
		t = tileslist.erase(t);
		break;
	}

	//==================================================================================================================================================
	// Player Control Related
	//==================================================================================================================================================
	float wep=ship1.getHeldItem();
	// Use Held Item(shooting)
	if (input->isKeyDown(VK_SPACE))
	{
		if (wep == 0 && shotdelaytime > 0.5)
		{
			Bullet* b = new Bullet();
			bullet_collection.push_back(b);
			b->initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &gameTextures);
			b->setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
			b->setCurrentFrame(BulletNS::Bullet_START_FRAME);
			b->setVelocity(VECTOR2(-BulletNS::SPEED, -BulletNS::SPEED)); // VECTOR2(X, Y)
			if (ship1.getDirection() == 1) // Set Location
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
			shotdelaytime = 0;
		}
		else if (wep == 1 && shotdelaytime > 1)
		{
			Arrow* a = new Arrow();
			ArrowCollection.push_back(a);

			a->initialize(this, ArrowNS::WIDTH, ArrowNS::HEIGHT, ArrowNS::TEXTURE_COLS, &gameTextures);
			a->setFrames(ArrowNS::ARROW_START_FRAME, ArrowNS::ARROW_END_FRAME);
			a->setCurrentFrame(ArrowNS::ARROW_START_FRAME);
			a->setVelocity(VECTOR2(1.5 * ArrowNS::SPEED, ArrowNS::SPEED)); // VECTOR2(X, Y)
			a->setY(ship1.getY() - (shipNS::HEIGHT / 2));
			a->setX(ship1.getX() + (shipNS::WIDTH / 2) * ship1.getDirection());

			if (ship1.getDirection() == 1) //Set Location
			{
				a->setDirection(1);
			}
			else
			{
				a->setDirection(-1);
			}
			shotdelaytime = 0;
		}
	}

	for (std::vector<Bullet*>::iterator ib = bullet_collection.begin(); ib < bullet_collection.end(); ++ib)
	{
			(*ib)->update(frameTime);
	}

	for (std::vector<Arrow*>::iterator ar = ArrowCollection.begin(); ar < ArrowCollection.end(); ++ar)
	{
		(*ar)->update(frameTime);
	}


	//==================================================================================================================================================
	// ENEMY CONTROLS
	//==================================================================================================================================================
	for (std::vector<Enemy*>::iterator it = enemyList.begin(); it < enemyList.end(); ++it)
	{
		float xvel = (*it)->getVelocity().x;
		float xloc = (*it)->getX();
		int direction = (*it)->getDirection();
		if (xloc > GAME_WIDTH-enemyNS::WIDTH)
		{
			(*it)->setDirection(1);
		}
		else if (xloc < 0)
		{
			(*it)->setDirection(-1);
		}
		(*it)->setX(xloc += xvel * frameTime * direction);
	}


	//==================================================================================================================================================
	if (heart == 0)
	{
		Gameover.setVisible(true);
	}

	//=========================================================================
	shotdelaytime += frameTime;
	ship1.update(frameTime);
	enemy1.update(frameTime);
	laser.update(frameTime);
	bullet.update(frameTime);
	tile.update(frameTime);
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
	if (ship1.collidesWith(enemy1, collisionVector))
	{
		heart = heart - 1;
		ship1.setVisible(false);
		ship1.setActive(false);
		ship1.setX(GAME_WIDTH / 1.25);
		ship1.setY(GAME_HEIGHT / 1.25);

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
		if ((*ib)->getX() < 0 || (*ib)->getX() > GAME_WIDTH)
		{
			ib = bullet_collection.erase(ib);
			break;
		}
		else if ((*ib)->getY() < 0 || (*ib)->getY() > GAME_HEIGHT)
		{
			ib = bullet_collection.erase(ib);
			break;
		}
	}

	// ARROW COLLISION
	for (std::vector<Arrow*>::iterator ar = ArrowCollection.begin(); ar < ArrowCollection.end(); ++ar)
	{
		if ((*ar)->collidesWith(enemy1, collisionVector))
		{
			float hp = enemy1.getHealth();
			(*ar)->setVisible(false);
			(*ar)->setActive(false);
			ar = ArrowCollection.erase(ar);
			enemy1.setHealth(hp - 2);
			break;
		}
		if ((*ar)->getX() < 0 || (*ar)->getX() > GAME_WIDTH)
		{
			ar = ArrowCollection.erase(ar);
			break;
		}
		else if ((*ar)->getY() < 0 || (*ar)->getY() > GAME_HEIGHT)
		{
			ar = ArrowCollection.erase(ar);
			break;
		}
	}

	//==================================================================================================================================================
	for (std::vector<Tile *>::iterator it = tileslist.begin(); it < tileslist.end(); ++it) 
	{
		if ((*it)->collidesWith(ship1, collisionVector))
		{
			float y = (*it)->getY();
			ship1.setGrounded(true);
			ship1.setY(GAME_HEIGHT / 2);
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

	menu_.draw();

	//==================================================================================================================================================
	// DRAW "TILES"
	for (int col = 0; col < MAP_WIDTH; col++)       // for each column of map
	{
		tile.setX((float)(col * TEXTURE_SIZE) +mapX);	// set tile X
		for (int row = 0; row < MAP_HEIGHT; row++)    // for each row of map
		{
			if (tileMap[row][col] >= 0)          // if tile present
			{
				tile.setCurrentFrame(tileMap[row][col]);    // set tile texture
				tile.setY((float)(row * TEXTURE_SIZE) + mapY);   // set tile Y
				// if tile on screen
				if (tile.getY() > -TEXTURE_SIZE && tile.getY() < GAME_HEIGHT)
				{ 
					tile.draw();                // draw tile

				Tile* t = new Tile();
				tileslist.push_back(t);

				t->initialize(this, tilesNS::WIDTH, tilesNS::HEIGHT, tilesNS::TEXTURE_COLS, &gameTextures);
				t->setFrames(tilesNS::TILES_START_FRAME, tilesNS::TILES_END_FRAME);
				t->setCurrentFrame(tilesNS::TILES_START_FRAME);
				t->setX(tile.getX());
				t->setY(tile.getY());
				t->setScale(4);
				}
			}
		}
	}

	
	//for (std::vector<Tile*>::iterator t = tileslist.begin(); t < tileslist.end(); ++t)
	//{
	//	(*t)->draw();
	//}
	//==================================================================================================================================================

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
	// ARROWS
	for (std::vector<Arrow*>::iterator a = ArrowCollection.begin(); a < ArrowCollection.end(); ++a)
	{
		(*a)->draw();
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
