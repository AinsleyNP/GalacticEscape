
#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//  Module:             Gameplay Programming
//  Assignment1:        Galactic Escape
//  Student Name:       Lim Wei Fu
//  Student Number:     S10189687

#include "entity.h"
#include "constants.h"

namespace shipNS
{
    const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/4; // radians per second
    const float SPEED = 0;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 8;           // texture has 8 columns
    const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
    const int   SHIP1_END_FRAME = 0;        // ship1 animation frames 0,1,2,3
    const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
    const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
    const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
    const int   SHIELD_START_FRAME = 24;    // shield start frame
    const int   SHIELD_END_FRAME = 27;      // shield end frame
    const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}

// inherits from Entity class
class Ship : public Entity
{
private:
    bool    shieldOn;
    Image   shield;
public:
    // constructor
    Ship();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
    void damage(WEAPON);

	void setVelocityX(float v) { velocity.x = v; }
	void setVelocityY(float v) { velocity.y = v; }

};
#endif

