#ifndef ABSTRACT_AGENT_H
#define ABSTRACT_AGENT_H
#include "main/Misc.h"

class ActorKnowledge;
class Action;
/**
	Represents agent which sters actor / actors
*/
class AbstractAgent
{
public:
	/**
		Function called when actor has nothing to do or the action is breakable
		Implementation should return action to be performed.
		If there should be no change of current action NULL should be returned
	*/
	virtual Action * whatToDoNow(ActorKnowledge * actorKnowledge, GameTime time) = 0;
	virtual void start(ActorKnowledge * actorKnowledge, GameTime time) = 0;
	virtual ~AbstractAgent () = default;
private:

};

#endif //ABSTRACT_AGENT_H