
#include "ship.h"
#include "bullet.h"


//  Module:             Falling Paradise
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley
//  Student Number:     S10186606

float Yaccel = 0;

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
    collisionType = entityNS::CIRCLE;
	spriteData.angle = 3 * PI / 2;
}
//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ship::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)

{
    shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
    shield.setFrames(shipNS::SHIELD_START_FRAME, shipNS::SHIELD_END_FRAME);
    shield.setCurrentFrame(shipNS::SHIELD_START_FRAME);
    shield.setFrameDelay(shipNS::SHIELD_ANIMATION_DELAY);
    shield.setLoop(false);                  // do not loop animation
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
	float vely;
	vely = velocity.y;
	float velx;
	velx = velocity.x;

	// Screen movement restriction
	//===============================================================================
	if (spriteData.x < 0)
	{
		spriteData.x = 0;
	}
	if (spriteData.x > GAME_WIDTH - spriteData.width)
	{
		spriteData.x = GAME_WIDTH - spriteData.width;
	}

	if (spriteData.y < 0)
	{
		spriteData.y = 0;
		velocity.y = -shipNS::SPEED;
		deltaV.y = 0;
		Yaccel = 0;
		vely = 0;
	}

	if (spriteData.y > GAME_HEIGHT - spriteData.height)
	{
		spriteData.y = GAME_HEIGHT - spriteData.height;
		velocity.y = -shipNS::SPEED;
		deltaV.y = 0;
		Yaccel = 0;
		vely = 0;
	}

	//Horizontal Movement		--- to be changed to changing velocity instead of sprite position -- Ported into states
	//======================================================================================

	if (input->isKeyDown(VK_LEFT)) // Move left
	{
		velx -= 100;         // move player along x
	}
	else if (input->isKeyDown(VK_RIGHT)) // Move right
	{
		velx += 100;         // move player along x
	}
	else
	{
		velx = 0;
	}

	//Vertical Movement / Gravity   --- DeltaV.y = acceleration	 --- Will be ported into states
	//======================================================================================

	if (input->wasKeyPressed(VK_UP))
	{
		Yaccel += 5000 * frameTime;
	}

	if (input->isKeyDown(VK_DOWN))
	{
		Yaccel -= 200 * frameTime;
	}

	if (Yaccel != 0)
	{
		Yaccel -= 1;
		if (velocity.y < -750)	// Terminal Velocity
		{
			vely = -750;
			Yaccel = 0;
		}
		else					//Gravity
		{
			deltaV.y = Yaccel;
		}
	}

//Movement based on velocity
spriteData.x += frameTime * velx;
spriteData.y -= frameTime * (vely);

Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Ship::damage(WEAPON weapon)
{
    shieldOn = true;
}

