#include "bullet.h"
#include <stdlib.h>

//  Module:             Falling Paradise
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley
//  Student Number:     S10186606

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
{
	spriteData.width = BulletNS::WIDTH;           // size of laser
	spriteData.height = BulletNS::HEIGHT;
	spriteData.x = BulletNS::X;                   // location on screen
	spriteData.y = BulletNS::Y;
	spriteData.rect.bottom = BulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = BulletNS::WIDTH;
	spriteData.scale = 1;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = BulletNS::Bullet_START_FRAME;     // first frame of bullet animation
	endFrame = BulletNS::Bullet_END_FRAME;     // last frame of bullet animation
	currentFrame = startFrame;
	radius = BulletNS::WIDTH / 2.0;
	mass = BulletNS::MASS;
	collisionType = entityNS::BOX;
	edge.bottom	= BulletNS::WIDTH / 4;
	edge.left	= BulletNS::WIDTH / 4;
	edge.right	= BulletNS::WIDTH / 4;
	edge.top	= BulletNS::WIDTH / 4;
}

//=============================================================================
// Initialize the Laser.
// Post: returns true if successful, false if failed
//=============================================================================
bool Bullet::initialize(Game* gamePtr, int width, int height, int ncols,
	TextureManager* textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the laser
//=============================================================================
void Bullet::draw()
{
	Image::draw();		     
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime)
{
	spriteData.x -= frameTime * velocity.x * direction; //Simple move bullet straight on X-axis depending direction facing when bullet shot
	Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Bullet::damage(WEAPON weapon)
{
}