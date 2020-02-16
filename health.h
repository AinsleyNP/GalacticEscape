
#ifndef _HEALTH_H                 // Prevent multiple definitions if this 
#define _HEALTH_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "constants.h"

namespace HealthNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   Health_START_FRAME = 5;      // laser frames
	const int   Health_END_FRAME = 0;        //
	const float Health_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Health : public Image
{
private:

public:
	// constructor
	Health();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Graphics* g, int width, int height, int ncols,
		TextureManager* textureM);
	void update(float frameTime);
	void damage(WEAPON);
};
#endif