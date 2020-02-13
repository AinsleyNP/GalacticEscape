
#ifndef _TILE_H                 // Prevent multiple definitions if this 
#define _TILE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//  Module:             Falling Paradise
//  Assignment1:        Galactic Escape
//  Student Name:       Lim Wei Fu
//  Student Number:     S10189687

#include "entity.h"
#include "constants.h"

namespace tilesNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI / 4; // radians per second
	const float SPEED = 0;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   TILES_START_FRAME = 5;      // ship1 starts at frame 0
	const int   TILES_END_FRAME = 5;        // ship1 animation frames 0,1,2,3
}

// inherits from Entity class
class Tile : public Entity
{
private:
	bool    shieldOn;
	Image   shield;
public:
	// constructor
	Tile();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);

};
#endif

