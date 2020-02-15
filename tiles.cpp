#include "tiles.h"

//=============================================================================
// default constructor
//=============================================================================
Tile::Tile() : Entity()
{
	spriteData.width = tilesNS::WIDTH;           // size of Ship1
	spriteData.height = tilesNS::HEIGHT;
	spriteData.x = tilesNS::X;                   // location on screen
	spriteData.y = tilesNS::Y;
	spriteData.rect.bottom = tilesNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = tilesNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = tilesNS::TILES_START_FRAME;     // first frame of ship animation
	endFrame = tilesNS::TILES_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = tilesNS::WIDTH / 2.0;
	shieldOn = false;
	mass = tilesNS::MASS;
	collisionType = entityNS::CIRCLE;

}
bool Tile::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)

{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Tile::draw()
{
	Image::draw();              // draw ship
}
void Tile::update(float frameTime)
{

Entity::update(frameTime);
}