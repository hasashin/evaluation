#include "actions/ReloadAction.h"
#include "main/Configuration.h"
#include "entities/Actor.h"
#include "actions/WaitAction.h"
#include "actions/ChangeWeaponAction.h"

ReloadAction::ReloadAction(int cost) : Action() {
		actionCode = "reload";
		breakable = false;
		//breakable = true;
		standardCost = cost;
		repeatable = true;
		actionType = Enumerations::ActionType::Reloading;
	}
	void ReloadAction::onEnter(Actor* actor, GameTime gameTime) {
		Action::onEnter(actor, gameTime);
		if (actor->getAmmo(actor->getCurrentWeapon()) == 0 || actor->isLoaded(actor->getCurrentWeapon())) {
			actor->resetCurrentAction( new WaitAction() );
			actor->getCurrentAction()->onEnter(actor, gameTime);
			return;
		}
	}
	bool ReloadAction::execute(Actor* actor, GameTime gameTime) {
		if (gameTime - actionStarted >= (standardCost)) {
			return true; 
		}
		return false; 
	}
	void ReloadAction::onExit(Actor* actor, GameTime gameTime) {
		if (actor->getAmmo(actor->getCurrentWeapon()) > 0) {
			actor->loadAmmo(actor->getCurrentWeapon());
		}
	}