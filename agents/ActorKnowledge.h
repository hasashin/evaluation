#ifndef ACTOR_KNOWLEDGE_H
#define ACTOR_KNOWLEDGE_H
#include <vector>
#include <set>
#include "agents/ActorInfo.h"

class Actor;
class ObjectInfo;
class Navigation;
/** Self knowlage of actor
*/
class ActorKnowledge// TODO ? derive form ActorInfo ?
{
public:
	ActorKnowledge(Actor * actor);
	void updateSpotting();
	int getAmmo(Enumerations::WeaponType type);
	Vector4d getPosition();
	Vector4d getDirection();
	Navigation * getNavigation();
	unsigned short getTeam();
	int getHealth();
	Enumerations::WeaponType getWeaponType();
	int getArmour();
	bool isMoving();
	bool isLoaded(Enumerations::WeaponType type);
	/** get ActorInfo about oneself
	*/
	ActorInfo getSelf();
	/** get list of friends seen from current position
	*/
	std::vector<ActorInfo> getSeenFriends();
	/** get list of foes seen from current position
	*/
	std::vector<ActorInfo> getSeenFoes();
	/** get list of all actors seen from current position
	*/
	std::vector<ActorInfo> getSeenActors();
	Vector4d getLongDestination();
	Vector4d getShortDestination();
	const char* getName() const;
	int getId() const;
	/**
	*/
	int getEstimatedTimeToReach(Vector4d self, Vector4d target);
	Actor * getActor() {
		return actor;
	}
private:
	std::set<ActorInfo> seenActors;
	std::set<ObjectInfo*> seenObjects;
	Actor * actor;
};

#endif //ACTOR_KNOWLEDGE_H