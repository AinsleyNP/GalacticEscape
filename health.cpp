#include "health.h"
#include <stdlib.h>

//=============================================================================
// default constructor
//=============================================================================
Health::Health() : Entity()
{
	spriteData.width = HealthNS::WIDTH;           // size of laser
	spriteData.height = HealthNS::HEIGHT;
	spriteData.x = HealthNS::X;                   // location on screen
	spriteData.y = HealthNS::Y;
	spriteData.rect.bottom = HealthNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = HealthNS::WIDTH;
	spriteData.scale = 1;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = HealthNS::Health_START_FRAME;     // first frame of laser animation
	endFrame = HealthNS::Health_END_FRAME;     // last frame of laser animation
	currentFrame = startFrame;
	radius = HealthNS::WIDTH / 2.0;
	mass = HealthNS::MASS;
	collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the healthbar.
// Post: returns true if successful, false if failed
//=============================================================================
bool Health::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the healthbar
//=============================================================================
void Health::draw()
{
	Image::draw();		           // draw laser
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Health::update(float frameTime)
{
	Entity::update(frameTime);
}

