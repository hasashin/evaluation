#include "entities/CustomShell.h"
#include "entities/Actor.h"
#include "main/Configuration.h"
#include "main/GameFactory.h"
#include "main/RandomGenerator.h"

CustomShell::CustomShell(Entity * src, Vector4d destination, bool stopAtDestination, GameTime fireTime, int timeToInvalidate, double speed, double damage, double radius, unsigned int color) : Entity() {
	std::vector<Vector4d> bbox;
	bbox.push_back(Vector4d(0.05, 0.05));
	bbox.push_back(Vector4d(-0.05, 0.05));
	bbox.push_back(Vector4d(-0.05, -0.05));
	bbox.push_back(Vector4d(0.05, -0.05));
//TODO odkomentowac	boundingBox.reset(new BoundingBox(bbox));
	position = src->getPosition();
	this->source = src;
	this->destination = destination;
	this->stopAtDestination = stopAtDestination;
	this->invalidateTime = fireTime + timeToInvalidate;
	this->speed = speed;
	this->damage = damage;
	this->radius = radius;
	this->color = color;
	direction = (destination - position).normal();
	this->prevPosition = position;
}
void CustomShell::update(GameTime time) {
	Vector4d previousPosition = getPosition();
	Vector4d moveVector = (destination-previousPosition).normal();
	Vector4d displacementVector = direction * speed / GAME_TIME_BY_SECOND;
	Vector4d nextPosition = previousPosition + displacementVector;
	std::vector<Entity*> & objects = GameFactory::getInstance().getCurrentGame()->getObjects();
	Entity * hit = NULL;
	Vector4d a = (destination - previousPosition);
	Vector4d b = (destination - nextPosition);
	if (time >= invalidateTime) {
		invalidate();
		return;
	}
	if (stopAtDestination && (a.val[0] * b.val[0] < 0 || a.val[1] * b.val[1] < 0 || a.val[2] * b.val[2] < 0 || a.val[3] * b.val[3] < 0)) {
		nextPosition = destination;
		invalidateTime = time +1;
	}
	for (std::vector <Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it) == this || (*it) == source) {
			continue;
		}
		Actor * isActor = dynamic_cast<Actor*>( (*it) );
		if ((*it)->rayColision(displacementVector, position) && ((*it)->solid || (isActor && (isActor->getHealth() > 0)) )) {
			invalidateTime = time +1;
			double distance = (*it)->rayColisionDistance(displacementVector, position);
			double length = (nextPosition - previousPosition).length(); //to "musi" byæ za ka¿dym razem wyliczone bo updatujemy nextPosition
			if (distance < length) {
				hit = (*it);
				nextPosition = previousPosition + (direction * distance);
			}
		}
	}
	this->prevPosition = position;
	position = nextPosition;
	if (radius == 0) {
		Actor * actor = dynamic_cast<Actor*>( hit );
		if (actor != NULL) {
			GameFactory::getInstance().getCurrentGame()->inflictDamage(actor, damage, time, static_cast<Actor*>(this->source));
		}
	} else {
		if (invalidateTime == time + 1) {
			explode(time);
		}
	}
}
//czy entity (np actor) wszed³ na shell
bool CustomShell::checkColision(Entity * entity, Vector4d distance) {
	return false;
}

void CustomShell::explode(GameTime time) {
	std::vector<Actor*> & actors = GameFactory::getInstance().getCurrentGame()->getActors();
	for (std::vector<Actor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
		Vector4d particleVector = Vector4d((*it)->getPosition() - position);
		double distance = particleVector.length();
		if (distance < radius) {
			if (!anyRayCrateColision(particleVector, position)) {
				int damage = this->damage * (radius - distance) / radius;
				GameFactory::getInstance().getCurrentGame()->inflictDamage((*it), damage, time, static_cast<Actor*>(this->source));
			}
		}
	}
}