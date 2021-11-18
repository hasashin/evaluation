#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "main/Misc.h"
#include "agents/MouseAgent.h"
//TODO externalize to file keyboard settings
//TODO let register other agents

class Graphics;
/** process and dispath input
*/
class UserInterface
{
public:
	enum textquality {
		solid,
		shaded,
		blended
	};

	UserInterface(Graphics * graphics) {
		this->graphics = graphics;
		this->agent = NULL;
		zooming = 0;
		movingVertical = 0;
		movingHorizontal = 0;
		TTF_Init();
		defaultFont = TTF_OpenFont("fonts/Vera.ttf", 12);
		if (defaultFont == NULL){//TODO zabezpieczy� to jako� porz�dnie
			std::cerr << "Couldnt load font" << std::endl;
		}
		smallFont = TTF_OpenFont("fonts/Vera.ttf", 10);
		if (smallFont == NULL){
			std::cerr << "Couldn't load font" << std::endl;
		}
	}
	~UserInterface() {
		TTF_CloseFont( defaultFont );
		TTF_Quit();
	}
	/** sets point (0,0) of view and scale
	*/
	void setOOPoint(double x, double y, double scale);
	/** processes input and prints ui elements to the screen
	*/
	void update( std::vector<Actor*> allActors);

	void showTime(int timeToEnd);
	
	/** event dispathers
	*/
	void mouseButtonPressed(Vector4d coordinates, Uint8 button);
    void mouseMoved(int xrel, int yrel, int x, int y);
	void keyPressed(SDLKey key);
	void keyReleased(SDLKey key);
	/** register user controled agent 
	apropriet input events will be dispathed to this agent
	*/
	void registerAgent(MouseAgent * mouseAgent) {
		this->agent = mouseAgent;
	}
	/** window height
	*/
	int getHeight();
	/** window width
	*/
	int getWidth();
protected:
	Graphics * graphics;
	SDL_Surface * drawtext(const char * text, Vector4d color, textquality quality = shaded, int useDefaultFont = 1);

	MouseAgent * agent;
	TTF_Font * defaultFont;
	TTF_Font * smallFont;

	double zooming;
	double movingVertical;
	double movingHorizontal;
};

#endif //USER_INTERFACE_H