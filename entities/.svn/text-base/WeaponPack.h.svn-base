#pragma once
#ifndef WEAPON_PACK_H
#define WEAPON_PACK_H
#include "entities/Trigger.h"
#include "actions/ShootAtAction.h"

/** custom weapon pack
*/
class WeaponPack : public Trigger
{
public:
	WeaponPack(double x, double y, Enumerations::WeaponType type, int index) : Trigger(x, y, index) {
		this->type = type;
		color = ShootAtAction::color[type];
	}
	/** ammo type provided in this pack
	*/
	virtual TriggerType getType() {
		return Weapon;
	}
protected:
	Enumerations::WeaponType type;
	/** triggers add ammo effect
	*/
	virtual void trigger(Actor * actor) {
		actor->addAmmo(type, ShootAtAction::ammoPacks[type]);
	}
};

#endif //WEAPON_PACK_H