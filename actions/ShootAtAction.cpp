#include "actions/ShootAtAction.h"
#include "entities/Actor.h"
#include "main/Configuration.h"
#include "entities/CustomShell.h"
#include "main/GameFactory.h"
#include "actions/ReloadAction.h"
#include "actions/WaitAction.h"
#include "main/RandomGenerator.h"

const bool ShootAtAction::stopAtTarget[ Enumerations::WeaponType::WeaponSize ] = {false, false, true, false};
const int ShootAtAction::numberOfParticles[ Enumerations::WeaponType::WeaponSize ] = { 1, 1, 1, 10 };
const double ShootAtAction::arc[ Enumerations::WeaponType::WeaponSize ] = { 0.7, 0.1, 0.3, 3.0 };
const int ShootAtAction::ammoPacks[ Enumerations::WeaponType::WeaponSize ] = { 100, 5, 10, 15 };
const double ShootAtAction::radius[ Enumerations::WeaponType::WeaponSize ] = { 0, 0, 50, 0 };
const double ShootAtAction::reloadTime[ Enumerations::WeaponType::WeaponSize ] = { 0, 3, 1.5, 1 };
const double ShootAtAction::damage[ Enumerations::WeaponType::WeaponSize ] = { 5, 100, 50, 15 };
const unsigned int ShootAtAction::color[ Enumerations::WeaponType::WeaponSize ] = { 0x00FF00FF, 0x0000FFFF, 0xFF0000FF, 0x000000FF };
const double ShootAtAction::speed[ Enumerations::WeaponType::WeaponSize ] = { 500, 15000, 350, 1000 };
const double ShootAtAction::shootTime[ Enumerations::WeaponType::WeaponSize ] = { 1, 5, 1.5, 1 };

ShootAtAction::ShootAtAction(Vector4d target) : Action() {
	actionCode = "shooting";
	breakable = false;
//	standardCost = 1;//zale�nie od broni
	repeatable = false;

	this->target = target;
	actionType = Enumerations::ActionType::Shooting;
}
void ShootAtAction::onEnter(Actor* actor, GameTime gameTime) {
	actionStarted = gameTime;
	rotate(actor, (target - actor->getPosition()), gameTime);
	if (!actor->isLoaded(actor->getCurrentWeapon())) {
		ReloadAction * ra = new ReloadAction(reloadTime[actor->getCurrentWeapon()]);
		actor->setCurrentAction( ra );
		ra->setNextAction(this);
		actor->getCurrentAction()->onEnter(actor, gameTime);
		return;
	}
}
bool ShootAtAction::execute(Actor* actor, GameTime gameTime) {
	double cosOfPiBy8 = 0.92387953251128675612818318939679;
	Vector4d directionVector(target - actor->getPosition());
	actor->setDirectionVector(directionVector.normal());
	if (gameTime - actionStarted >= (shootTime[actor->getCurrentWeapon()])) {
		if (directionVector.dot(actor->getDirection()) < cosOfPiBy8) {
			return false;
		} else {
			return true;
		}
	}
	return false; 
}
void ShootAtAction::onExit(Actor* actor, GameTime gameTime) {
	//TODO
	Vector4d direction(target - actor->getPosition());
	actor->setDirection(direction.normal());
	Enumerations::WeaponType wp = actor->getCurrentWeapon();

	for (int i = 0; i < numberOfParticles[wp]; i++) {
		Vector4d direction = target - actor->getPosition();
		double missArc = RandomNormal() * arc[wp];
		direction.rotateZ(missArc, false);
		Vector4d missTarget = actor->getPosition() + direction;
		GameFactory::getInstance().addObject(new CustomShell(actor, missTarget, stopAtTarget[wp], gameTime, 2 * GAME_TIME_BY_SECOND, speed[wp], damage[wp], radius[wp], color[wp]));
	}
	actor->bulletFired();

	ReloadAction * ra = new ReloadAction(reloadTime[wp] * 30);
	if (this->nextAction == NULL) {
		this->setNextAction(ra);
	} else {
		ra->setNextAction(this->nextAction);
		this->setNextAction(ra);
	}
}