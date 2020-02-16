
#include "ship.h"
#include "bullet.h"
#include "arrow.h"


//  Module:             Falling Paradise
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley
//  Student Number:     S10186606


//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
    spriteData.width = shipNS::WIDTH;           // size of Ship1
    spriteData.height = shipNS::HEIGHT;
    spriteData.x = shipNS::X;                   // location on screen
    spriteData.y = shipNS::Y;
    spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = shipNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = shipNS::SHIP_ANIMATION_DELAY;
    startFrame = shipNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = shipNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = shipNS::WIDTH/2.0;
    shieldOn = false;
    mass = shipNS::MASS;
    collisionType = entityNS::BOX;
	edge.bottom = shipNS::WIDTH/2;
	edge.left = shipNS::WIDTH / 2;
	edge.right = shipNS::WIDTH / 2;
	edge.top = shipNS::WIDTH / 2;
	health = 100;
	grounded = true;
	direction = 1; // -1 <- Left | Right -> 1
	terminalVel = getTerminalVel();
	helditem = 0;
}
//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ship::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{

    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Ship::draw()
{
    Image::draw();              // draw ship
    if(shieldOn)
        // draw shield using colorFilter 50% alpha
        shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}
//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ship::update(float frameTime)
{
	float rest = shipNS::SPEED;
	float vely = velocity.y;
	float velx = velocity.x;	

	//Fake state control
	if (grounded)
	{
		startFrame = shipNS::SHIP1_START_FRAME;
		endFrame = shipNS::SHIP1_END_FRAME;
		velocity.y = -rest;
		deltaV.y = 0;
		vely = 0;
	}
	// https://www.grc.nasa.gov/www/k-12/airplane/termv.html
	else if (!grounded) // Not grounded
	{
		if (velocity.y <= -750)	// Terminal Velocity
		{
			velocity.y = -750; //Speed cap
			deltaV.y = 0;
		}
		else
		{
			deltaV.y -= 10; // Force of gravity
		}
	}

	// "Held Item" Control
	if (input->wasKeyPressed(ITEM_SWITCH_KEY))
	{
		if (helditem == 0)
		{
			helditem = 1;
		}
		else if (helditem == 1)
		{
			helditem = 0;
		}
	}

	// Screen movement restriction
	//===============================================================================
	if (spriteData.x < 0) // Left
	{
		spriteData.x = 0;
	}
	if (spriteData.x > GAME_WIDTH - spriteData.width) // Right
	{
		spriteData.x = GAME_WIDTH - spriteData.width;
	}

	if (spriteData.y < 0)
	{
		spriteData.y = GAME_HEIGHT - spriteData.height; // Top
		velocity.y = -rest;
		deltaV.y = 0;
		vely = 0;
	}

	if (spriteData.y > GAME_HEIGHT - spriteData.height) // Bottom
	{
		spriteData.y = GAME_HEIGHT - spriteData.height;
		grounded = true;
	}

	//Horizontal Movement		--- to be changed to changing velocity instead of sprite position directly
	//======================================================================================

	if (input->isKeyDown(VK_RIGHT)) // Move right
	{
		startFrame = shipNS::RUN_START_FRAME;
		endFrame = shipNS::RUN_END_FRAME;
		velx += 200;         // move player along x
		flipHorizontal(false); // Sprite defaults "facing" right
		direction = 1;
	}

	else if (input->isKeyDown(VK_LEFT)) // Move left
	{
		startFrame = shipNS::RUN_START_FRAME;
		endFrame = shipNS::RUN_END_FRAME;
		velx -= 200;         // move player along x
		flipHorizontal(true); // Sprite flips default, "facing" left
		direction = -1;
	}

	else
	{
		startFrame = shipNS::SHIP1_START_FRAME;
		endFrame = shipNS::SHIP1_END_FRAME;
		velx = 0;
	}

	//Vertical Movement / Gravity   --- DeltaV.y = vertical acceleration
	//======================================================================================

	if (grounded && input->wasKeyPressed(VK_UP)) // IF "GROUNDED" , can Jump
	{
		velocity.y = 1500; // Set Velocity to 1000, jumping highest vel = right when leave ground
		startFrame = shipNS::JUMP_START_FRAME;
		endFrame = shipNS::JUMP_END_FRAME;
		grounded = false;
	}


//Movement based on velocity
spriteData.x += frameTime * velx;
spriteData.y -= frameTime * vely;

Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Ship::damage(WEAPON weapon)
{
    shieldOn = true;
}
