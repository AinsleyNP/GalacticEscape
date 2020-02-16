#include "Trap.h"
#include <stdlib.h>

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley Malcolm Pereira
//  Student Number:     S10186606

//=============================================================================
// default constructor
//=============================================================================
Trap::Trap() : Entity()
{
	spriteData.width = TrapNS::WIDTH;           // size of laser
	spriteData.height = TrapNS::HEIGHT;
	spriteData.x = TrapNS::X;                   // location on screen
	spriteData.y = TrapNS::Y;
	spriteData.rect.bottom = TrapNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = TrapNS::WIDTH;
	spriteData.scale = 1;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = TrapNS::Laser_START_FRAME;     // first frame of laser animation
	endFrame = TrapNS::Laser_END_FRAME;     // last frame of laser animation
	currentFrame = startFrame;
	radius = TrapNS::WIDTH / 2.0;
	mass = TrapNS::MASS;
	collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the Laser.
// Post: returns true if successful, false if failed
//=============================================================================
bool Trap::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the laser
//=============================================================================
void Trap::draw()
{
		Image::draw();		           // draw laser
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Trap::update(float frameTime)
{
	Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Trap::damage(WEAPON weapon)
{
}