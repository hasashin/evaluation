#ifndef SHOOT_AT_ACTION_H
#define SHOOT_AT_ACTION_H
#include "actions/Action.h"

/** shooting action
*/
class ShootAtAction : public Action
{
public:
	static const bool stopAtTarget[ Enumerations::WeaponType::WeaponSize ];
	static const int numberOfParticles[ Enumerations::WeaponType::WeaponSize ];
	static const double arc[ Enumerations::WeaponType::WeaponSize ];
	static const int ammoPacks[ Enumerations::WeaponType::WeaponSize ];
	static const double radius[ Enumerations::WeaponType::WeaponSize ];
	static const double reloadTime[ Enumerations::WeaponType::WeaponSize ];
	static const double damage[ Enumerations::WeaponType::WeaponSize ];
	static const unsigned int color[ Enumerations::WeaponType::WeaponSize ];
	static const double speed[ Enumerations::WeaponType::WeaponSize ];
	static const double shootTime[ Enumerations::WeaponType::WeaponSize ];

	ShootAtAction(Vector4d target);
	void onEnter(Actor* actor, GameTime gameTime);
	bool execute(Actor* actor, GameTime gameTime);
	void onExit(Actor* actor, GameTime gameTime);
private:
	Vector4d target;
};

#endif //SHOOT_AT_ACTION_H