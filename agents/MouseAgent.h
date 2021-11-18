#ifndef MOUSE_AGENT_H
#define MOUSE_AGENT_H
#include "agents/PlayerAgent.h"
#include <SDL.h>

/** mouse driven agent
*/
class MouseAgent : public PlayerAgent
{
public:
	void whatToDo(ActorKnowledge * actorKnowledge, GameTime time);
	void onStart(ActorKnowledge * actorKnowledge, GameTime time) {}

	/** event handlers
	*/
	void mouseButtonPressed(Vector4d coordinates, Uint8 button);
	void mouseMoved(Vector4d coordinates);
	void keyPressed(SDLKey key);

	ActorKnowledge * getCurrent() {
		return current;
	}
private:

};

#endif //MOUSE_AGENT_H