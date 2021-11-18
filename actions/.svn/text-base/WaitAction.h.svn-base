#ifndef WAIT_ACTION_H
#define WAIT_ACTION_H
#include "actions/Action.h"

/** default action when actor has nothing to do and awaits orders
*/
class WaitAction : public Action
{
public:
	WaitAction() : Action() {
		actionCode = "stopped";
		breakable = true;
		standardCost = 0;
		repeatable = true;
		actionType = Enumerations::ActionType::Waiting;
	}
	bool execute(Actor* actor, GameTime gameTime) {
		return false;
	}
protected:

};

#endif //WAIT_ACTION_H