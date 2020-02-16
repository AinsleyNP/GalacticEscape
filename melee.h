#ifndef _MELEE_H                 // Prevent multiple definitions if this 
#define _MELEE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace MeleeNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 3 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 3 - HEIGHT / 2;
	const float SPEED = 0;                // 100 pixels per second
	const float MASS = 2.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   MELEE_START_FRAME = 45;      // laser frames
	const int   MELEE_END_FRAME = 45;        //
	const float MELEE_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Melee : public Entity
{
private:

public:
	// constructor
	Melee();

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