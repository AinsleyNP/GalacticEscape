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
typedef std::vector<Trap*> LASERLIST;
typedef std::vector<Enemy*> ENEMYLIST;
typedef std::vector<Bullet*> ENEMYBULLETLIST;
typedef std::vector<Tile*> TILELIST;

std::vector<Bullet*> bullet_collection;
std::vector<Arrow*> ArrowCollection;
std::vector<Enemy*> enemyList;
std::vector<Trap*> laserList;
std::vector<Bullet*> enemyBulletList;

std::vector<Tile*> tileslist;

bool respawn = false;
int game_height = GAME_HEIGHT;
bool die = false;
bool over = false;
float shotdelaytime = 0;
float attackdelaytime = 0;
float playermeleetimer;
float monstermeleetimer;
float monstermeleelength;
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

	// background textures 
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing background textures"));

	

	// sky image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
		//background.setScale(3.5);
		float bgheight = background.getHeight();
		float scale = game_height / bgheight;
		background.setScale(scale);

		// trap
		if (!trap.initialize(this, TrapNS::WIDTH, TrapNS::HEIGHT, TrapNS::TEXTURE_COLS, &gameTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing trap"));
		trap.setFrames(TrapNS::Laser_START_FRAME, TrapNS::Laser_END_FRAME);
		trap.setCurrentFrame(TrapNS::Laser_START_FRAME);
		trap.setX(GAME_WIDTH / 3 );
		trap.setY(GAME_HEIGHT / 1.2);


	// tile image
	if (!tile.initialize(graphics, TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_COLS, &tileTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
	tile.setFrames(0, 0);
	tile.setCurrentFrame(0);

	// Health Bar textures
	if (!healthTexture.initialize(graphics, HEALTHBAR_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health bar textures"));

	//Health Bar HUD
	if(!HealthBar.initialize(graphics, HealthNS::WIDTH  , HealthNS::HEIGHT , HealthNS::TEXTURE_COLS , &healthTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health bar"));
	HealthBar.setFrames(HealthNS::Health_START_FRAME, HealthNS::Health_END_FRAME);
	HealthBar.setCurrentFrame(HealthNS::Health_START_FRAME);
	HealthBar.setX(GAME_WIDTH / 16);
	HealthBar.setY(GAME_HEIGHT / 20);

	//Enemy Texture
	if (!enemyTexture.initialize(graphics, ENEMY_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy textures"));

	// Game over textures
	if (!gameOverTexture.initialize(graphics, GAMEOVER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing main menu textures"));

	if (!Gameover.initialize(graphics, 0, 0, 0, &gameOverTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error Initializing Game over menu"));
	Gameover.setX(GAME_WIDTH * 0.5f - Gameover.getWidth() * 0.5f);
	Gameover.setY(GAME_HEIGHT * 0.5f - Gameover.getHeight() * 0.5f);

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

	if (!playerMelee.initialize(this, MeleeNS::WIDTH, MeleeNS::HEIGHT, MeleeNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player Melee"));
	playerMelee.setFrames(MeleeNS::MELEE_START_FRAME, MeleeNS::MELEE_END_FRAME);
	playerMelee.setCurrentFrame(MeleeNS::MELEE_START_FRAME);
	playerMelee.setRadians(PI / 2);
	playerMelee.setActive(false);

	//=========================================================================
	// enemy initialize
	if (!enemy1.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy1.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemy1.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemy1.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

	// Enemy Goomba - No Attacks, walks around, dmgs player on collision
	if (!enemyGoomba.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemyGoomba.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemyGoomba.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemyGoomba.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)
	enemyGoomba.setX(GAME_WIDTH / 1.5);
	enemyGoomba.setY(GAME_HEIGHT / 1.25);
	enemyGoomba.setRadians(2 * PI);
	enemyGoomba.flipHorizontal(90);

	// Enemy Plant - Mario piranha plant
	if (!enemyPlant.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemyPlant.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemyPlant.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemyPlant.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)
	enemyPlant.setX(50);
	enemyPlant.setY(50);

	// Enemy Monster - Walks around, Has Melee attack
	if (!enemyMonster.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemyMonster.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemyMonster.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemyMonster.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)
	enemyMonster.setX(200);
	enemyMonster.setY(200);

	if (!enemyMelee.initialize(this, MeleeNS::WIDTH, MeleeNS::HEIGHT, MeleeNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player Melee"));
	enemyMelee.setFrames(MeleeNS::MELEE_START_FRAME, MeleeNS::MELEE_END_FRAME);
	enemyMelee.setCurrentFrame(MeleeNS::MELEE_START_FRAME);
	enemyMelee.setRadians(PI / 2);
	enemyMelee.setActive(false);

	// Enemy Bomber - Shoots bombs/bullets
	if (!enemyBomber.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemyBomber.setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	enemyBomber.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemyBomber.setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)
	enemyBomber.setX(25);
	enemyBomber.setY(25);

	

	////======================================================================================================
	////Enemy Spawning (Fixed Locations)
	//float enemyCoords[2][3] = {
	//	{50,50,0},{100,100,0}
	//};

	////Choose <2 enemy to spawn and add to enemyList
	//for (int i = 0; i < 2; i++)
	//{
	//	Enemy* e = new Enemy(); //Pointer
	//	enemyList.push_back(e); //Adds e into the enemyList vector
	//}

	////For all the enemies in list spawn them at the locations set in enemycoords
	//for (std::vector<Enemy*>::iterator it = enemyList.begin(); it < enemyList.end(); ++it)
	//{
	//	(*it)->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &gameTextures);
	//	(*it)->setFrames(enemyNS::ENEMY_START_FRAME, enemyNS::ENEMY_END_FRAME);
	//	(*it)->setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	//	(*it)->setVelocity(VECTOR2(-enemyNS::SPEED, -enemyNS::SPEED)); // VECTOR2(X, Y)

	//	int enemyPick = rand() % 21;
	//	if (enemyCoords[enemyPick][2] == 0)
	//	{
	//		(*it)->setX(enemyCoords[enemyPick][0]);
	//		(*it)->setY(enemyCoords[enemyPick][1]);
	//	}
	//}


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

	menu_.update();

	if (menu_.menu1 == true)
	{
		menu = false;
	}

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

	if (ship1.getHealth()<=0)
	{
		Gameover.setVisible(true);
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
	if (shipy < TEXTURE_SIZE * 2)
	{
		//ship1.setY(GAME_HEIGHT / 2 - 1); // So ship doesnt go past half way(ish)
		if (input->isKeyDown(VK_UP))
		{
			mapY += frameTime * SCROLL_RATE;
		}
	}
	
	// Vertical "Scrolling"
	if (ship1.getY() < GAME_HEIGHT + TEXTURE_SIZE * 2)
	{
		//ship1.setY(GAME_HEIGHT / 2 - 1); // So ship doesnt go past half way(ish)
		if (input->isKeyDown(VK_DOWN))
		{
			mapY -= frameTime * SCROLL_RATE;
		}
	}

	//Right Horizontal "Scrolling"
	float shipx = ship1.getX();
	if (input->isKeyDown(VK_RIGHT))
	{
		mapX -= frameTime * SCROLL_RATE;
	}

	
	//Left Horizontal "Scrolling"

	if (input->isKeyDown(VK_LEFT))
	{
		mapX += frameTime * SCROLL_RATE;
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
	// Use Held Item(shooting)
	float wep=ship1.getHeldItem();
	// "wep" -> array of items, 0==gun, 1==bow
	if (input->isKeyDown(VK_SPACE))
	{
		float shipx = ship1.getX();
		float shipy = ship1.getY();
		float shipdir = ship1.getDirection();
		if (wep == 0 && shotdelaytime > 0.5)
		{
			Bullet* b = new Bullet();
			bullet_collection.push_back(b);
			b->initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &gameTextures);
			b->setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
			b->setCurrentFrame(BulletNS::Bullet_START_FRAME);
			b->setVelocity(VECTOR2(-BulletNS::SPEED, -BulletNS::SPEED)); // VECTOR2(X, Y)
			if (shipdir == 1) // Set Location
			{
				b->setX(shipx + (shipNS::WIDTH / 2));
				b->setDirection(1);
			}
			else
			{
				b->setX(shipx - (shipNS::WIDTH / 2));
				b->setDirection(-1);
			}
			b->setY(shipy); 
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
			a->setY(shipy - (shipNS::HEIGHT / 2));
			a->setX(shipx + (shipNS::WIDTH / 2) * shipdir);

			// MATH TO CALCULATE SHOT ANGLE
			float opp = a->getVelocity().y;
			float hyp = hypot(a->getVelocity().x, opp);
			float rad = asin(opp / hyp);
			a->setRadians(rad* ship1.getDirection());
			a->setRotationRate(ArrowNS::ROTATION_RATE);

			if (shipdir == 1) //Set Location
			{
				a->setDirection(1);
			}
			else
			{
				a->setDirection(-1);
			}
			shotdelaytime = 0;
		}
		else if (wep == 2 && shotdelaytime > 0.3)
		{
			playermeleetimer = 0;
			if (shipdir == 1)
			{
				playerMelee.flipHorizontal(false);
			}
			else if (shipdir == -1)
			{
				playerMelee.flipHorizontal(true);
			}
			playerMelee.setX(shipx+shipNS::WIDTH*shipdir);
			playerMelee.setY(shipy);
			playerMelee.setVisible(true);
			playerMelee.setActive(true);
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

	if (playermeleetimer > 1)
	{
		playerMelee.setVisible(false);
		playerMelee.setActive(false);
	}
	if (playerMelee.getActive())
	{
		playermeleetimer += frameTime;
	}

	// AN EXPERIMENT WITH FINDING ANGLES BETWEEN POINTS GONE WRONG BECAUSE ASIN() DOESNT WORK
	if (input->isKeyDown(VK_DOWN))
	{
		float mousex = input->getMouseX();
		float mousey = input->getMouseY();

	// FINDING ANGLE BETWEEN WHERE ITS SHOT FROM & MOUSE
		float adj = mousex - ship1.getX();
		float opp = mousey - ship1.getY();
		float hyp = hypot(adj, opp);
		float anglediff = asin(opp/hyp);

		// sin(anglediff) * vel ->set velocity.y
		// cos(anglediff) * vel ->set velocity.x
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

	if (monstermeleetimer > 5)
	{
		enemyMelee.setX(enemyMonster.getX() + enemyNS::WIDTH);
		enemyMelee.setY(enemyMonster.getY());
		enemyMelee.setVisible(true);
		enemyMelee.setActive(true);
		monstermeleetimer = 0;
	}
	if (enemyMelee.getActive())
	{
		monstermeleelength += frameTime;
	}
	if (monstermeleelength > 1)
	{
		enemyMelee.setVisible(false);
		enemyMelee.setActive(false);
	}
	//==================================================================================================================================================
	if (ship1.getHealth() <= 0)
	{
		Gameover.setVisible(true);
	}

	//=========================================================================
	if (attackdelaytime > 3)
	{
		float xvalue = enemyGoomba.getX();
		float yvalue = enemyGoomba.getY();
		Bullet* b = new Bullet();
		enemyBulletList.push_back(b);
		b->initialize(this, BulletNS::WIDTH, BulletNS::HEIGHT, BulletNS::TEXTURE_COLS, &gameTextures);
		b->setFrames(BulletNS::Bullet_START_FRAME, BulletNS::Bullet_END_FRAME);
		b->setCurrentFrame(BulletNS::Bullet_START_FRAME);
		b->setVelocity(VECTOR2(-BulletNS::SPEED, -BulletNS::SPEED)); // VECTOR2(X, Y)
		b->setX(xvalue-16);
		b->setY(yvalue);
		b->setDirection(-1);

		attackdelaytime = 0;
	}

	for (std::vector<Bullet*>::iterator ib = enemyBulletList.begin(); ib < enemyBulletList.end(); ++ib)
	{
		(*ib)->update(frameTime);
	}

	shotdelaytime += frameTime;
	ship1.update(frameTime);
	enemy1.update(frameTime);
	playerMelee.update(frameTime);
	//enemyGoomba.update(frameTime);
	attackdelaytime += (frameTime);
	trap.update(frameTime);
	bullet.update(frameTime);
	tile.update(frameTime);
	enemyGoomba.update(frameTime);
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
		ship1.setHealth(ship1.getHealth() - 20);
		ship1.setVisible(false);
		ship1.setActive(false);
		ship1.setX(GAME_WIDTH / 1.25);
		ship1.setY(GAME_HEIGHT / 1.25);

		respawn = true;
    }

	if (ship1.getHealth() == 100)
	{
		HealthBar.setCurrentFrame(0);
	}
	else if (ship1.getHealth() == 80)
	{
		HealthBar.setCurrentFrame(1);
	}
	else if (ship1.getHealth() == 60)
	{
		HealthBar.setCurrentFrame(2);
	}
	else if (ship1.getHealth() == 40)
	{
		HealthBar.setCurrentFrame(3);
	}
	else if (ship1.getHealth() == 20)
	{
		HealthBar.setCurrentFrame(4);
	}
	else
	{
		HealthBar.setCurrentFrame(6);
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
	//Tiles Collision
	//==================================================================================================================================================
	for (std::vector<Tile *>::iterator it = tileslist.begin(); it < tileslist.end(); ++it) 
	{
		if ((*it)->collidesWith(ship1, collisionVector))
		{
			float y = (*it)->getY();
			ship1.setGrounded(true);
			ship1.setY((*it)->getX() + (*it)->getHeight() + 1);
			ship1.setVelocityX(-ship1.getVelocity().x);
			ship1.setVelocityY(-ship1.getVelocity().y);

		}
		
	}

	//Total Enemy collision
	if (ship1.collidesWith(enemyGoomba, collisionVector))
	{
		ship1.setHealth(ship1.getHealth() - 20);
			// bounce off ship
			ship1.bounce(collisionVector, enemyGoomba);
	}

	if (ship1.collidesWith(enemyPlant, collisionVector))
	{
		ship1.setHealth(ship1.getHealth() - 20);
	}

	if (ship1.collidesWith(enemyMonster, collisionVector))
	{
		ship1.setHealth(ship1.getHealth() - 20);
	}

	if (ship1.collidesWith(enemyBomber, collisionVector))
	{
		ship1.setHealth(ship1.getHealth() - 20);
	}

	//Trap Collision
	if (ship1.collidesWith(trap, collisionVector))
	{
		ship1.setHealth(ship1.getHealth() - 10);
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
	background.draw();
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


	//Enemy

	enemy1.draw(); // enemy spaceship draw

	//Enemy Variants draw
	enemyGoomba.draw();
	enemyPlant.draw();
	enemyMonster.draw();
	enemyBomber.draw();
	trap.draw();

	if (enemyMelee.getActive())
	{
		enemyMelee.draw();
	}
	
	// ATTACK-RELATED RENDERING
	for (std::vector<Bullet*>::iterator ibe = enemyBulletList.begin(); ibe < enemyBulletList.end(); ++ibe)
	{
		(*ibe)->draw();
	}


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
	// PLAYER MELEE
	if (playerMelee.getActive())
	{
		playermeleetimer = 0;
		playerMelee.draw();
	}

	if (menu) {
		mainMenu.draw(); // main menu draw
	}

	if (over = true) {
		Gameover.draw();
	}

	HealthBar.draw();
	

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
	healthTexture.onLostDevice();

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
	gameOverTexture.onResetDevice();
	healthTexture.onResetDevice();

	Game::resetAll();
	return;
}
