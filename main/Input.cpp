#include "main/Input.h"
#include <SDL.h>
#include "main/Misc.h"
#include "graphics/UserInterface.h"
/** process SDL events
*/
bool Input::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// check for messages
		switch (event.type)
		{
			// exit if the window is closed
			case SDL_QUIT:
				return true;
			break;
			case SDL_ACTIVEEVENT:
			break;
			case SDL_MOUSEMOTION:
				ui->mouseMoved(
					event.motion.xrel, event.motion.yrel,
					event.motion.x, event.motion.y);
                break;
			break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.val[0] = event.button.x;
                mouse.val[1] = event.button.y;
				ui->mouseButtonPressed(mouse, event.button.button);
			break;
			case SDL_KEYDOWN:
				ui->keyPressed(event.key.keysym.sym);
			break;
			case SDL_KEYUP:
				ui->keyReleased(event.key.keysym.sym);
			break;
		} // end switch
	} // end of message processing
	return false;
}
