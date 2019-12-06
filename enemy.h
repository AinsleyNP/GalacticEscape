
#ifndef _ENEMY_H                 // Prevent multiple definitions if this 
#define _ENEMY_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Brannon Chua
//  Student Number:     S10187075

#include "entity.h"
#include "constants.h"

namespace enemyNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI / 4; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   ENEMY_START_FRAME = 8;      // ship2 starts at frame 8
	const int   ENEMY_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
	const float ENEMY_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Enemy : public Entity
{
private:
	
public:
	// constructor
	Enemy();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);
};
#endif