#include "health.h"
#include <stdlib.h>

//=============================================================================
// default constructor
//=============================================================================
Health::Health() : Image()
{
	spriteData.width = HealthNS::WIDTH;           // size of laser
	spriteData.height = HealthNS::HEIGHT;
	spriteData.x = HealthNS::X;                   // location on screen
	spriteData.y = HealthNS::Y;
	spriteData.scale = 1;                  // velocity Y
	startFrame = HealthNS::Health_START_FRAME;     // first frame of laser animation
	endFrame = HealthNS::Health_END_FRAME;     // last frame of laser animation
	currentFrame = startFrame;
}

//=============================================================================
// Initialize the healthbar.
// Post: returns true if successful, false if failed
//=============================================================================
bool Health::initialize(Graphics *g, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Image::initialize(g, width, height, ncols, textureM));
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
	Image::update(frameTime);
}

