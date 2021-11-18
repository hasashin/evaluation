#include "agents/PlayerAgent.h"
#include "entities/Actor.h"
#include "agents/ActorKnowledge.h"
#include "actions/ChangeWeaponAction.h"
#include "actions/ReloadAction.h"
#include "actions/ShootAtAction.h"
#include "actions/WaitAction.h"
#include "main/RandomGenerator.h"

double PlayerAgent::randomDouble() {
	return RandomDouble();
}

Action * PlayerAgent::whatToDoNow(ActorKnowledge * actorKnowledge, GameTime time) {
		current = actorKnowledge;
		whatToDo(actorKnowledge, time);
		return nextAction.release();
	}

void PlayerAgent::start(ActorKnowledge * actorKnowledge, GameTime time) {
		current = actorKnowledge;
		onStart(actorKnowledge, time);
	}

	void PlayerAgent::selectWeapon(Enumerations::WeaponType weapon) {
		nextAction.reset(new ChangeWeaponAction(weapon));
	}
	void PlayerAgent::moveDirection(Vector4d direction) {
		current->getActor()->setMoveVector(direction);
	}
	void PlayerAgent::moveTo(Vector4d target) {
		current->getActor()->setDestination(target);
	}
	void PlayerAgent::reload() {
		nextAction.reset(new ReloadAction(0));
	}
	void PlayerAgent::rotate(Vector4d direction) {
		current->getActor()->setDirectionVector(direction);
	}
	void PlayerAgent::shootAt(ActorInfo enemy) {
		nextAction.reset(new ShootAtAction(enemy.getPosition()));
	}
	void PlayerAgent::shootAtPoint(Vector4d vect) {
		nextAction.reset(new ShootAtAction(vect));
	}
	void PlayerAgent::wait() {
		Vector4d direction;
		current->getActor()->setMoveVector(direction);
		nextAction.reset(new WaitAction());
	}
	void PlayerAgent::continueAction() {
		nextAction.reset();
	}
