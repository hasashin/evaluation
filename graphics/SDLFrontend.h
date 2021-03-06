#ifndef SDL_FRONTEND_H
#define SDL_FRONTEND_H
#include "graphics/GraphicsFrontend.h"
#include "main/Misc.h"
#include <SDL_ttf.h>
class Graphics;
/** SDL based graphics frontend
*/
class SDLFrontend : public GraphicsFrontend
{
public:
	SDLFrontend(Graphics * igraphics) : graphics(igraphics) {}
	void run(Game * game);
private:
	Graphics * graphics;
};

#endif //SDL_FRONTEND_H