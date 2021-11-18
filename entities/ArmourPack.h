#pragma once
#ifndef ARMOUR_PACK_H
#define ARMOUR_PACK_H
#include "entities/Trigger.h"

/** armour providing trigger
*/
class ArmourPack : public Trigger
{
public:
	ArmourPack(double x, double y, int index, int armour = 50) : Trigger(x, y, index) {
		color = 0xF00FFFFF;
		this->armour = armour;
	}
	virtual TriggerType getType() {
		return Armour;
	}
protected:
	int armour;
	virtual void trigger(Actor * actor) {
		actor->addArmour(armour);
	}
};

#endif //ARMOUR_PACK_H