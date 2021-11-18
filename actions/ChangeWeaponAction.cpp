#include "actions/ChangeWeaponAction.h"
#include "entities/Actor.h"

ChangeWeaponAction::ChangeWeaponAction(Enumerations::WeaponType weapon) : Action() {
		actionCode = "reload";
		breakable = false;
		standardCost = 4;
		repeatable = false;
		actionType = Enumerations::ActionType::ChangingWeapon;
		this->weapon = weapon;
	}
	void ChangeWeaponAction::onEnter(Actor* actor, GameTime gameTime) {
		Action::onEnter(actor, gameTime);
	}
	bool ChangeWeaponAction::execute(Actor* actor, GameTime gameTime) {
		if (gameTime - actionStarted >= (standardCost)) {
			return true; 
		}
		return false; 
	}
	void ChangeWeaponAction::onExit(Actor* actor, GameTime gameTime) {
		actor->setCurrentWeapon(weapon);
	}