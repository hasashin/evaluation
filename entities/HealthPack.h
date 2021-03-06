#pragma once
#ifndef HEALTH_PACK_H
#define HEALTH_PACK_H
#include "entities/Trigger.h"
#include "main/Configuration.h"
/** health providing trigger
*/
class HealthPack : public Trigger
{
public:
	HealthPack(double x, double y, int index, int health = 25) : Trigger(x, y, index) {
		color = 0xFFFFFFFF;
		this->health = Configuration::getInstance().getInt("trigger.addHealth");
	}
	virtual TriggerType getType() {
		return Health;
	}
protected:
	int health;
	virtual void trigger(Actor * actor) {
		actor->addHealth(health);
	}
};

#endif //HEALTH_PACK_H