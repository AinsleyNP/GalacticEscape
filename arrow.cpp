#include "arrow.h"
#include <stdlib.h>

//  Module:             Falling Paradise
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley
//  Student Number:     S10186606

//=============================================================================
// default constructor
//=============================================================================
Arrow::Arrow() : Entity()
{
	spriteData.width = ArrowNS::WIDTH;           // size of laser
	spriteData.height = ArrowNS::HEIGHT;
	spriteData.x = ArrowNS::X;                   // location on screen
	spriteData.y = ArrowNS::Y;
	spriteData.rect.bottom = ArrowNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = ArrowNS::WIDTH;
	spriteData.scale = 1;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = ArrowNS::ARROW_START_FRAME;     // first frame of bullet animation
	endFrame = ArrowNS::ARROW_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = ArrowNS::WIDTH / 2.0;
	mass = ArrowNS::MASS;
	collisionType = entityNS::BOX;
	edge.bottom = ArrowNS::WIDTH / 2;
	edge.left = ArrowNS::WIDTH / 2;
	edge.right = ArrowNS::WIDTH / 2;
	edge.top = ArrowNS::WIDTH / 2;
	rotationrate = ArrowNS::ROTATION_RATE;
}

//=============================================================================
// Initialize the Laser.
// Post: returns true if successful, false if failed
//=============================================================================
bool Arrow::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the laser
//=============================================================================
void Arrow::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Arrow::update(float frameTime)
{
	/*
	Equation for Range:
	(InitialVelocity)^2 * sin(2*angle) } /gravity
	*/
	float vely = velocity.y;
	float velx = velocity.x;
	float rotrate = getRotationRate();

	deltaV.y -= 0.1; // Force of gravity
	rotrate = pow(rotrate, 5);

	spriteData.angle += frameTime * direction * rotrate;
	spriteData.x += frameTime * velx * direction;
	spriteData.y -= frameTime * vely;
	Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Arrow::damage(WEAPON weapon)
{
}