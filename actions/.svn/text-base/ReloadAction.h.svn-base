#ifndef RELOAD_ACTION_H
#define RELOAD_ACTION_H
#include "actions/Action.h"

/** reload current weapon  action
*/
class ReloadAction : public Action
{
public:
	ReloadAction(int cost);
	void onEnter(Actor* actor, GameTime gameTime);
	bool execute(Actor* actor, GameTime gameTime);
	void onExit(Actor* actor, GameTime gameTime);
private:
};

#endif //RELOAD_ACTION_H