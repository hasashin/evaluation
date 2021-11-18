#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H
#include "entities/Entity.h"
#include "main/GameFactory.h"
#include "entities/Actor.h"
/** custom trigger class
*/
class Trigger : public Entity
{
	friend void Game::updateWorld();
	friend class GameFactory;
public:
	enum TriggerType {
		Weapon,
		Armour,
		Health
	};
	virtual TriggerType getType() = 0;
	/** returns state of trigger (if effect can be triggered)
	*/
	bool isActive() {
		return active;
	};
protected:
	Trigger(double x, double y, int index) : Entity() {
		activateTime = 0;
		timeToActivate = 60 * GAME_TIME_BY_SECOND;
		active = true;
		position.val[0] = x;
		position.val[1] = y;
		this->index = index;
	}
	/** reactivates trigger after some time
	*/
	virtual void update(GameTime time) {
		if (active) {
			Vector4d distance;
			std::vector<Entity*> & objects = GameFactory::getInstance().getCurrentGame()->getObjects();
			for (std::vector<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
				Actor * isActor = dynamic_cast<Actor*>( (*it) );
				if ( isActor && ((*it) != this) && ((*it)->checkColision(this, distance))) {
					trigger(isActor);
					active = false;
					activateTime = time + timeToActivate;
				}
			}
		} else {
			if (time > activateTime) {
				active = true;
			}
		}
	};
	int index;
	GameTime activateTime;
	int timeToActivate;
	bool active;
	virtual bool checkColision(Entity * entity, Vector4d distance) {
		return false;
	}
	bool rayColision(Vector4d displacementVector, Vector4d rayPosition) {
		return false;
	}
	/** triggers effects
	*/
	virtual void trigger(Actor * actor) = 0;
};

#endif //TRIGGER_H