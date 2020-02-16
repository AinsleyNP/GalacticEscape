#include "melee.h"
#include <stdlib.h>

//  Module:             Falling Paradise
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley
//  Student Number:     S10186606

//=============================================================================
// default constructor
//=============================================================================
Melee::Melee() : Entity()
{
	spriteData.width = MeleeNS::WIDTH;           // size of laser
	spriteData.height = MeleeNS::HEIGHT;
	spriteData.x = MeleeNS::X;                   // location on screen
	spriteData.y = MeleeNS::Y;
	spriteData.rect.bottom = MeleeNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = MeleeNS::WIDTH;
	spriteData.scale = 1;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = MeleeNS::MELEE_START_FRAME;     // first frame of bullet animation
	endFrame = MeleeNS::MELEE_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = MeleeNS::WIDTH / 2.0;
	mass = MeleeNS::MASS;
	collisionType = entityNS::BOX;
	edge.bottom = MeleeNS::WIDTH / 4;
	edge.left = MeleeNS::WIDTH / 4;
	edge.right = MeleeNS::WIDTH / 4;
	edge.top = MeleeNS::WIDTH / 4;
}

//=============================================================================
// Initialize the Laser.
// Post: returns true if successful, false if failed
//=============================================================================
bool Melee::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the laser
//=============================================================================
void Melee::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Melee::update(float frameTime)
{
	Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Melee::damage(WEAPON weapon)
{
}