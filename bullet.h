#ifndef _BULLET_H                 // Prevent multiple definitions if this 
#define _BULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Lim Wei Fu
//  Student Number:     S10189687

#include "entity.h"
#include "constants.h"

namespace BulletNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 3 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 3 - HEIGHT / 2;
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   Bullet_START_FRAME = 41;      // laser frames
	const int   Bullet_END_FRAME = 44;        //
	const float Bullet_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Bullet : public Entity
{
private:

public:
	// constructor
	Bullet();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
		TextureManager* textureM);
	void update(float frameTime);
	void damage(WEAPON);

	void setVelocityX(float v) { velocity.x = v; }
	void setVelocityY(float v) { velocity.y = v; }
};
#endif