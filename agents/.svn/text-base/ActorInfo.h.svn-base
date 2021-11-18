#ifndef NACTOR_INFO_H
#define NACTOR_INFO_H
#include <string>
#include "main/Misc.h"

class Actor;
/**	Gives acces to information about seen actors
*/
class ActorInfo
{
public:
	ActorInfo() {}
	ActorInfo(Actor * actor);
	Vector4d getPosition() const {
		return position;
	}
	Vector4d getDirection() const {
		return direction;
	}
	void setPosition(Vector4d position) {
		this->position = position;
	}
	void setDirection(Vector4d direction) {
		this->direction = direction;
	}
	unsigned short getTeam() const {
		return team;
	}
	void setTeam(unsigned short team) {
		this->team = team;
	}
	int getHealth() const {
		return health;
	}
	void setHealth(int health) {
		this->health = health;
	}
	int getArmour() const {
		return armour;
	}
	void setArmour(int armour) {
		this->armour = armour;
	}
	const char* getName() const {
		return name.c_str();
	}
	Enumerations::WeaponType getWeaponType() const {
		return weaponType;
	}
	void setWeaponType(Enumerations::WeaponType type) {
		this->weaponType = type;
	}
	virtual ~ActorInfo() {}
	bool operator<(const ActorInfo& q) const {
		return name < q.name;//TODO !!! to inaczej zrobiæ
	}
protected:
	int armour;
	std::string name;
	Vector4d position;
	Vector4d direction;
	unsigned short team;
	int health;
	Enumerations::WeaponType weaponType;
	friend class PlayerAgent;
};

#endif //NACTOR_INFO_H