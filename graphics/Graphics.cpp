#include "graphics/Graphics.h"
#include "graphics/GraphicsException.h"
#include "graphics/ImagesManager.h"
#include "main/Configuration.h"
#include <SDL.h>

/** initializes SDL, creates screen surface
*/
Graphics::Graphics() {
	
	// initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
		char * errorTxt = NULL;
        snprintf( errorTxt, 50, "Unable to init SDL: %s\n", SDL_GetError() );
		throw GraphicsException(errorTxt);
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
	height = ConfInt("height");
	width = ConfInt("width");
    screen = SDL_SetVideoMode(width, height, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
		char * errorTxt = NULL;
        snprintf( errorTxt, 50, "Unable to set %dx%d video: %s\n", width, height, SDL_GetError() );
		throw GraphicsException(errorTxt);
    }

	ooPoint.reset(new Vector4d(0,0,4));

	ImagesManager::getInstance().loadResourceFile("images/skel.txt");
	ImagesManager::getInstance().loadResourceFile("images/staff.txt");
	ImagesManager::getInstance().loadResourceFile("images/other.txt");
}
/** returns used screen surface
*/
SDL_Surface * Graphics::getScreen() {
	return screen;
}
/** cleans up, releases sreen surface
*/
Graphics::~Graphics() {
	SDL_FreeSurface(screen);
}
/** flips doublebuffered screen
*/
void Graphics::update() {
	// finally, update the screen :)
    SDL_Flip(screen);
	// clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
}
/** transforms world coordinate x to view coordinate
* used when printing to screen
*/
double Graphics::transformXToViewCoordinate(double x) {
	return ((x - ooPoint->val[0]) * ooPoint->val[2]);
}
/** transforms world coordinate y to view coordinate
* used when printing to screen
*/
double Graphics::transformYToViewCoordinate(double y) {
	return ((y - ooPoint->val[1]) * ooPoint->val[2]);
}
/** transforms view coordinate x to world coordinate
* used when getting mouse clicks
*/
double Graphics::transformXToWorldCoordinate(double x) {
	return (x / ooPoint->val[2]) + ooPoint->val[0];
}
/** transforms view coordinate y to world coordinate
* used when getting mouse clicks
*/
double Graphics::transformYToWorldCoordinate(double y) {
	return (y / ooPoint->val[2]) + ooPoint->val[1];
}