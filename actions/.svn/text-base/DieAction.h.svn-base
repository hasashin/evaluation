#ifndef DIE_ACTION_H
#define DIE_ACTION_H
#include "actions/Action.h"

/** action which is set after death of actor
*/
class DieAction : public Action
{
public:
	DieAction() : Action() {
		actionCode = "dying";
		breakable = false;
		standardCost = 0;
		repeatable = false;
		actionType = Enumerations::ActionType::Dying;
	}
	void onEnter(Actor* actor, GameTime gameTime) {
		Action::onEnter(actor, gameTime);
		//drop equipent
	}
	bool execute(Actor* actor, GameTime gameTime) { 
		Vector4d vect;
		actor->setMoveVector(vect);
		return false; 
	}
protected:

};

#endif //DIE_ACTION_H