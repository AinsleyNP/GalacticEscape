#include "laser.h"

//=============================================================================
// default constructor
//=============================================================================
Laser::Laser() : Entity()
{
	spriteData.width = LaserNS::WIDTH;           // size of laser
	spriteData.height = LaserNS::HEIGHT;
	spriteData.x = LaserNS::X;                   // location on screen
	spriteData.y = LaserNS::Y;
	spriteData.rect.bottom = LaserNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = LaserNS::WIDTH;
	spriteData.scale = 1;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = LaserNS::Laser_START_FRAME;     // first frame of laser animation
	endFrame = LaserNS::Laser_END_FRAME;     // last frame of laser animation
	currentFrame = startFrame;
	radius = LaserNS::WIDTH / 2.0;
	mass = LaserNS::MASS;
	collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the Laser.
// Post: returns true if successful, false if failed
//=============================================================================
bool Laser::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the laser
//=============================================================================
void Laser::draw()
{
	Image::draw();              // draw laser

}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Laser::update(float frameTime)
{
	if (input->isKeyDown(VK_BACK))
	{
		spriteData.angle = 1.5;
		spriteData.x += 0.2;
		spriteData.scale += 0.5;
	}
	Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Laser::damage(WEAPON weapon)
{
}