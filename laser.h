
#ifndef _LASER_H                 // Prevent multiple definitions if this 
#define _LASER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley Malcolm Pereira
//  Student Number:     S10186606
#include "entity.h"
#include "constants.h"

namespace LaserNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   Laser_START_FRAME = 16;      // laser frames
	const int   Laser_END_FRAME = 16;        //
	const float LASER_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Laser : public Entity
{
private:

public:
	// constructor
	Laser();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game* gamePtr, int width, int height, int ncols,
		TextureManager* textureM);
	void update(float frameTime);
	void damage(WEAPON);
};
#endif