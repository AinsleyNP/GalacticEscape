

#ifndef _Menu_H             // Prevent multiple definitions if this 
#define _Menu_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace menuNS
{
	const int   WIDTH = 128;                // image width
	const int   HEIGHT = 128;               // image height
}

class Menu : public Entity            // inherits from Entity class
{
private:
	Input* input;
public:
	// constructor
	Menu(Input* input);

	void update();
	//void draw();

};

#endif 

