
#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
//#include "planet.h"
#include "ship.h"
#include "enemy.h"
#include "laser.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager backgroundTexture;   // nebula texture
    TextureManager gameTextures;    // game texture
	Ship    ship1;    // spaceships (https://www.pnglot.com/downpng/hTxmTim_first-version-of-my-sprite-sheet-i-have/)
	Enemy enemy; //enemy spaceships
	Laser laser;

    Image   background;         // backdrop image

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
