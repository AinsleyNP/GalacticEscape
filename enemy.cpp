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
	spriteData.angle = 0.5 * PI;
	direction = -1;
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

	//Test movement of enemy ship left and right

	// Movement along X Axis
	if (input->isKeyDown(VK_LEFT)) // Move left
	{
		spriteData.x -= frameTime * 2 * velocity.x;         // move ship along x
	}

	if (input->isKeyDown(VK_RIGHT)) // Move right
	{
		spriteData.x += frameTime * 2 * velocity.x;         // move ship along x

	}

	// Movement along Y Axis

	if (input->isKeyDown(VK_UP))
	{
		spriteData.y += frameTime * 2 * velocity.y;         // move ship along y

	}
	if (input->isKeyDown(VK_DOWN))
	{
		spriteData.y -= frameTime * 2 * velocity.y;         // move ship along y
	}

	// Prevents ship from going outside the boundaries of the screen

	if (spriteData.x > GAME_WIDTH - enemyNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - enemyNS::WIDTH;    // position at right screen edge
		//velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		//velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - enemyNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - enemyNS::HEIGHT;  // position at bottom screen edge
		//velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		//velocity.y = -velocity.y;                   // reverse Y direction
	}
}

//=============================================================================
// damage
//=============================================================================
void Enemy::damage(WEAPON weapon)
{
	
}
