#include "tiles.h"

//=============================================================================
// default constructor
//=============================================================================
Tile::Tile() : Entity()
{
	spriteData.width = spaceWarNS::WIDTH;           // size of Ship1
	spriteData.height = spaceWarNS::HEIGHT;
	spriteData.x = spaceWarNS::X;                   // location on screen
	spriteData.y = spaceWarNS::Y;
	spriteData.rect.bottom = spaceWarNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = spaceWarNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = spaceWarNS::TILES_START_FRAME;     // first frame of ship animation
	endFrame = spaceWarNS::TILES_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = spaceWarNS::WIDTH / 2.0;
	shieldOn = false;
	mass = spaceWarNS::MASS;
	collisionType = entityNS::BOX;

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