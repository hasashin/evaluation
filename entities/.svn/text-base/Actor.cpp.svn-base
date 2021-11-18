#include "entities/Actor.h"
#include <cmath>
#include <iostream>
#include <limits>
#include "main/Configuration.h"
#include "actions/WaitAction.h"
#include "actions/DieAction.h"
#include "agents/AbstractAgent.h"
#include "agents/ActorKnowledge.h"
#include "main/GameFactory.h"
#include "entities/Trigger.h"

Actor::Actor(AbstractAgent * agent, unsigned int team, Vector4d position) : Entity() {
	reset(position, 0);
	kills = 0;
	killed = 0;
	friendkills = 0;
	resourceName = "";
	this->agent = agent;
	this->team = team;
	actorKnowledge.reset( new ActorKnowledge(this) );
}

void Actor::reset(Vector4d position, GameTime time) {
	loaded[ Enumerations::WeaponType::Chaingun ] = false;
	ammo[ Enumerations::WeaponType::Chaingun ] = ConfInt("weapon.chaingun.ammo");
	loaded[ Enumerations::WeaponType::Railgun ] = false;
	ammo[ Enumerations::WeaponType::Railgun ] = ConfInt("weapon.railgun.ammo");
	loaded[ Enumerations::WeaponType::RocketLuncher ] = false;
	ammo[ Enumerations::WeaponType::RocketLuncher ] = ConfInt("weapon.rocket.ammo");
	loaded[ Enumerations::WeaponType::Shotgun ] = false;
	ammo[ Enumerations::WeaponType::Shotgun ] = ConfInt("weapon.shotgun.ammo");
	moveVector = Vector4d();
	directionVector = direction;//TODO spradz OCB?
	armour = 0;
	speed = ConfDouble("actor.speed");
	currentWeapon = Enumerations::WeaponType::Chaingun;
	health = ConfInt("actor.maxHealth");
	resetCurrentAction( new WaitAction() );
	this->position = position; 
	longDestination = position; 
	shortDestination = position;
	currentAction->onEnter(this, time);
	started = false;
}

void Actor::update(GameTime time) {

	if (isDead()) {
		return;
	}
	move();
	rotate();

	if (currentAction.get() == NULL) {
		currentAction.reset( new WaitAction() );
		currentAction->onEnter(this, time);
	}
	if (currentAction->execute(this, time)) {
		currentAction->onExit(this, time);
		currentAction.reset(currentAction->getNextAction());
		if (currentAction.get() == NULL) {
			currentAction.reset( new WaitAction() );
		}
		currentAction->onEnter(this, time);
	}
}

void Actor::act(GameTime time) {
	actorKnowledge->updateSpotting();
	if (!started) {
		agent->start(this->getActorKnowledge(), time);
		started = true;
	}
	if (currentAction.get() != NULL && currentAction->isBreakable()) {
		Action * action = agent->whatToDoNow(this->getActorKnowledge(), time);
		if (action != NULL) {
			currentAction.reset( action );
			currentAction->onEnter(this, time);
		}
	}
}

GameTime Actor::getActionStarted() {
	if (currentAction.get() != NULL) {
		return currentAction->getActionStarted();
	}
	return GameFactory::getInstance().getCurrentGame()->getGameTime();
}

void Actor::move() {
	//skracanie drogi
	if (!(shortDestination == longDestination)) {
		if (way.size() > 0) {
			Vector4d fetchWayPoint = navigation->getNodePosition(way.back());
			if (!anyRayCrateColision( (fetchWayPoint - position), position)) {
				shortDestination = navigation->getNodePosition(way.back());
				way.pop_back();
				moveVector = (shortDestination - position).normal();
			}
		} else {
			Vector4d fetchWayPoint = longDestination;
			if (!anyRayCrateColision( (fetchWayPoint - position), position)) {
				shortDestination = longDestination;
				moveVector = (shortDestination - position).normal();
			}			
		}
	}
	Vector4d distance = moveVector * getSpeed() / GAME_TIME_BY_SECOND;
	Vector4d malyprostopadly = moveVector * 10;
	malyprostopadly.rotateZ(PI_CONST/2, true);
	if (checkIntersection(position, position + distance, shortDestination - malyprostopadly, shortDestination + malyprostopadly)) {
		distance = moveVector * (shortDestination - position).length();
		if (way.size() > 0) {
			shortDestination = navigation->getNodePosition(way.back());
			way.pop_back();
			moveVector = (shortDestination - position).normal();
		} else {
			if (!(shortDestination == longDestination)) {
				shortDestination = longDestination;
				moveVector = (shortDestination - position).normal();
			} else {
				moveVector = Vector4d();
			}
		}
	}
	std::vector<Entity*> & objects = GameFactory::getInstance().getCurrentGame()->getObjects();
	for (std::vector<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		Actor * isActor = dynamic_cast<Actor*>( (*it) );
		if (isActor && (isActor->getHealth() <= 0)) {
			continue;
		}
		if (((*it) != this) && ((*it)->checkColision(this, distance))) {
			distance = Vector4d();
			moveVector = Vector4d();
			break;
		}
	}
	position += distance;
}

void Actor::rotate() {
	double cosOfPiBy8 = 0.92387953251128675612818318939679;
	if (directionVector.dot(getDirection()) < cosOfPiBy8) {
		Vector4d currentVector = direction;
		if (direction.val[1] * directionVector.val[0] - direction.val[0] * directionVector.val[1] > 0) {
			currentVector.rotateZ(-(PI_CONST/8), true);
		} else {
			currentVector.rotateZ((PI_CONST/8), true);
		}
		setDirection(currentVector.normal());
	} else {
		setDirection(directionVector.normal());
	}
}

void Actor::setDestination(Vector4d vect) {
	if (vect == position) {
		moveVector = Vector4d();
		return;
	}
	if (!anyRayCrateColision( (vect - position), position)) {
		longDestination = vect;
		shortDestination = vect;
		way.clear();
		moveVector = (shortDestination - position).normal();
		return;
	}
	way = navigation->searchWay(position, vect);
	if (way.size() > 0) {
		longDestination = vect;
		shortDestination = navigation->getNodePosition(way.back());
		way.pop_back();
		moveVector = (shortDestination - position).normal();
	} else {
		moveVector = Vector4d();
	}
}

bool Actor::lineInteresctsLineSegment( Vector4d s1p1, Vector4d s1p2, Vector4d s2p1, Vector4d s2p2) {
	double a = s1p1.val[0];
	double b = s1p1.val[1];
	double c = s1p2.val[0];
	double d = s1p2.val[1];
	double x1 = s2p1.val[0];
	double y1 = s2p1.val[1];
	double x2 = s2p2.val[0];
	double y2 = s2p2.val[1];
	return ((b - d) * x1 + (c - a) * y1 + (a * d - b * c))
		* ((b - d) * x2 + (c - a) * y2 + (a * d - b * c)) <= 0;
}

bool Actor::checkIntersection( Vector4d s1p1, Vector4d s1p2, Vector4d s2p1, Vector4d s2p2) {
	if (lineInteresctsLineSegment(s1p1, s1p2, s2p1, s2p2)
		&& lineInteresctsLineSegment(s2p1, s2p2, s1p1, s1p2)) {
			return true;
	} else {
		return false;
	}
}