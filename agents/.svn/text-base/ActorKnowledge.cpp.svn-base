#include "agents/ActorKnowledge.h"
#include <set>
#include "main/Configuration.h"
#include "entities/Actor.h"
#include "main/GameFactory.h"
#include "main/RandomGenerator.h"

Navigation * ActorKnowledge::getNavigation() {
	return actor->getNavigation();
}

int ActorKnowledge::getAmmo(Enumerations::WeaponType type) {
	return actor->getAmmo(type);
}
void ActorKnowledge::updateSpotting() {
	std::vector<Actor*> & actors = GameFactory::getInstance().getCurrentGame()->getActors();
	seenActors.clear();
	for (std::vector<Actor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
		if (!(*it)->isDead() && (*it)->getPosition() != this->getPosition() && !((*it)->anyRayCrateColision(((*it)->getPosition() - this->getPosition()), this->getPosition())) ) {//TODO inaczej zrobiæ sprawdzanie czy to nie ten w³asnie aktor
			seenActors.insert((*it)->getActorInfo());
		}
	}
}
//std::vector<ObjectInfo> ActorKnowledge::getSeenObjects();
std::vector<ActorInfo> ActorKnowledge::getSeenActors() {
	std::vector<ActorInfo> actors;
	for (std::set<ActorInfo>::iterator it = seenActors.begin(); it != seenActors.end(); ++it) {
		actors.push_back(*it);
	}
	return actors;
}

ActorKnowledge::ActorKnowledge(Actor * actor) : actor(actor) {
}

/*-----new interface part-----*/

ActorInfo ActorKnowledge::getSelf() {
	return actor->getActorInfo();
}
std::vector<ActorInfo> ActorKnowledge::getSeenFriends() {
	std::vector<ActorInfo> friends;
	for (std::set<ActorInfo>::iterator it = seenActors.begin(); it != seenActors.end(); ++it) {
		if ((*it).getTeam() == this->getTeam()) {
			friends.push_back(*it);
		}
	}
	return friends;
}

std::vector<ActorInfo> ActorKnowledge::getSeenFoes() {
	std::vector<ActorInfo> foes;
	for (std::set<ActorInfo>::iterator it = seenActors.begin(); it != seenActors.end(); ++it) {
		if ((*it).getTeam() != this->getTeam()) {
			foes.push_back(*it);
		}
	}
	return foes;
}

int ActorKnowledge::getEstimatedTimeToReach(Vector4d self, Vector4d target) {
	Vector4d moveVector(target - self);
	double time = moveVector.length() / ((ConfDouble("actor.speed")) / GAME_TIME_BY_SECOND);
	return time;
}

Vector4d ActorKnowledge::getPosition() {
	return actor->getPosition();
}
Vector4d ActorKnowledge::getDirection() {
	return actor->getDirection();
}
Enumerations::WeaponType ActorKnowledge::getWeaponType() {
	return actor->getCurrentWeapon();
}
unsigned short ActorKnowledge::getTeam() {
	return actor->getTeam();
}
	const char* ActorKnowledge::getName() const {
		return actor->getName();
	}
int ActorKnowledge::getHealth() {
	return actor->getHealth();
}
int ActorKnowledge::getArmour() {
	return actor->getArmour();
}
bool ActorKnowledge::isMoving(){
	return actor->isMoving();
}
bool ActorKnowledge::isLoaded(Enumerations::WeaponType type){
	return actor->isLoaded(type);
}
	Vector4d ActorKnowledge::getLongDestination() {
		return actor->getLongDestination();
	}
	Vector4d ActorKnowledge::getShortDestination() {
		return actor->getShortDestination();
	}