
#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//  Module:             Falling Paradise
//  Assignment1:        Galactic Escape
//  Student Name:       Ainsley
//  Student Number:     S10186606

#include "entity.h"
#include "constants.h"

namespace shipNS
{
    const int WIDTH = 50;                   // image width
    const int HEIGHT = 37;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/4; // radians per second
    const float SPEED = 0;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 7;           // texture has 8 columns
    const int   SHIP1_START_FRAME = 0;      // Idle starts at frame
    const int   SHIP1_END_FRAME = 3;        // Idle animation frames
    const int   RUN_START_FRAME = 8;      // Run animation Frames
    const int   RUN_END_FRAME = 13;       // Run animation frames
    const int   JUMP_START_FRAME = 14;      // Jump animation Frames
    const int   JUMP_END_FRAME = 17;       // Jump animation frames
    const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
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

