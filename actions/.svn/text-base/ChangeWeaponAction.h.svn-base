#ifndef CHANGE_WEAPON_ACTION_H
#define CHANGE_WEAPON_ACTION_H
#include "actions/Action.h"

/** swap weapon action
*/
class ChangeWeaponAction : public Action
{
public:
	ChangeWeaponAction(Enumerations::WeaponType weapon);
	void onEnter(Actor* actor, GameTime gameTime);
	bool execute(Actor* actor, GameTime gameTime);
	void onExit(Actor* actor, GameTime gameTime);
private:
	Enumerations::WeaponType weapon;
};

#endif //CHANGE_WEAPON_ACTION_H