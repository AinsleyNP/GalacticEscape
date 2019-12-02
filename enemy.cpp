// Enemy Class

#include "enemy.h"

//=============================================================================
// default constructor
//=============================================================================
Enemy::Enemy() : Entity()
{
	spriteData.width = enemyNS::WIDTH;           // size of enemy
	spriteData.height = enemyNS::HEIGHT;
	spriteData.x = enemyNS::X;                   // location on screen
	spriteData.y = enemyNS::Y;
	spriteData.rect.bottom = enemyNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = enemyNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = enemyNS::ENEMY_ANIMATION_DELAY;
	startFrame = enemyNS::ENEMY_START_FRAME;     // first frame of ship animation
	endFrame = enemyNS::ENEMY_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = enemyNS::WIDTH / 2.0;
	mass = enemyNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Enemy.
// Post: returns true if successful, false if failed
//=============================================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the enemy
//=============================================================================
void Enemy::draw()
{
	
	Image::draw();              // draw enemy
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Enemy::update(float frameTime)
{
	Entity::update(frameTime);
}

//=============================================================================
// damage
//=============================================================================
void Enemy::damage(WEAPON weapon)
{
	
}
