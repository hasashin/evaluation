#ifndef ACTION_H
#define ACTION_H
#include <string>
#include "main/Misc.h"

class Actor;
class ActionInfo;
/** custom action class
*/
class Action
{
public:
	/** this method is executed when action is started
	*/
	virtual void onEnter(Actor* actor, GameTime gameTime);
	/** Executes state if it is finished returns true
	*/
	virtual bool execute(Actor* actor, GameTime gameTime) = 0;
	/** this method is executed when action is ended
	*/
	virtual void onExit(Actor* actor, GameTime gameTime) {};
	/** returns action code used to select animation images of character
	*/
	std::string getActionCode() { return actionCode; }
	/** returns whether action can be broke
	*/
	bool isBreakable() { return breakable; }
	/** retruns true if animation should be repeated continiously
	*/
	bool isRepeatable() { return repeatable; }
	/** returns time moment when the action was started
	*/
	GameTime getActionStarted() { return actionStarted; }
	/** returns action registered to be done after finishing current action
	*/
	Action * getNextAction() {
		return nextAction;
	}
	/** registers next action
	*/
	void setNextAction(Action * action) {
		this->nextAction = action;
	}
	Enumerations::ActionType getActionType() {
		return actionType;
	}
	virtual ~Action() = 0;
protected:
	Action();
	Enumerations::ActionType actionType;
	void rotate(Actor * actor, Vector4d direction, GameTime time);
	const double cosOfPiBy8;
	std::string actionCode;
	bool breakable;
	bool repeatable;
	TimeUnit standardCost;
	GameTime actionStarted;
	Action * nextAction;
};

#endif //ACTION_H