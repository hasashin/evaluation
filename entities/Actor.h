#pragma once
#ifndef ACTOR_H
#define ACTOR_H
#include "entities/Entity.h"
#include <memory>
#include <string>
#include "actions/Action.h"
#include "agents/ActorKnowledge.h"
#include "main/RandomGenerator.h"
#include "main/Configuration.h"


class AbstractAgent;
class Trigger;

/** class representing single character in the game
*/
class Actor : public Entity
{
	friend class GameFactory;
public:
	Actor(AbstractAgent * agent, unsigned int team, Vector4d postion);
	/** continues current action or choses new one
	*/
	virtual void act(GameTime time);
	/** retruns time moment when last action was started
	*/
	GameTime getActionStarted();
	/** returns currently wielded weapon
	*/
	Enumerations::WeaponType getCurrentWeapon() { 
		return currentWeapon;
	}
	/** set new weapon
	*/
	void setCurrentWeapon(Enumerations::WeaponType weapon) { 
		currentWeapon = weapon;
	}
	/** current action
	*/
	Action * getCurrentAction() { 
		return currentAction.get(); 
	}
	/** method runned after spawning character
	*/
	void reset(Vector4d position, GameTime time);
	/**	destroy's current action ptr and sets new
	used when we dont want to use old action any more
	*/
	void resetCurrentAction(Action * action) {
		currentAction.reset(action);
	}
	/**	releases's current action ptr and sets new
	used when we want to use old action somewhere else
	*/
	void setCurrentAction(Action * action) {
		currentAction.release();
		currentAction.reset(action);
	}
	/** checks if character is dead
	*/
	bool isDead() {
		return (getCurrentAction() != NULL ? getCurrentAction()->getActionType() == Enumerations::ActionType::Dying : false);
	}
	/** return team number where actor belongs
	*/
	unsigned int getTeam() {
		return team;
	}
	int getHealth() {
		return health;
	}
	void setHealth(int health) {
		this->health = health;
	}
	void setSpeed( double speed )
	{
		this->speed = speed;
	}
	double getSpeed() {
		return speed;
	}
	/** provides compact information about actor
	*/
	ActorInfo getActorInfo() {
		return ActorInfo(this);
	}
	/** provides full information about actor
	*/
	ActorKnowledge * getActorKnowledge() {
		return actorKnowledge.get();
	}
	/** returns how much actor still has ammo
	*/
	int getAmmo(Enumerations::WeaponType type) {
		return ammo[type];
	}
	/** loads ammo into barrel
	*/
	void loadAmmo(Enumerations::WeaponType type) {
		ammo[type]--;
		loaded[type] = true;
	}
	/** resource name which represents this actor
	*/
	std::string getResourceName()
	{
		return resourceName;
	}
	void setResourceName( std::string name)
	{
		this->resourceName = name;
	}
	/** direction where actor is moving
	*/
	void setMoveVector(Vector4d vect) {
		moveVector = vect.normal();
	}
	/** direction where actor is facing
	*/
	void setDirectionVector(Vector4d vect) {
		directionVector = vect.normal();
	}
	/** checks if actor is currently moving
	*/
	bool isMoving() {
		Vector4d vect;
		if (moveVector == vect) {
			return false;
		} else {
			return true;
		}
	}
	void setDestination(Vector4d vect);

	void addHealth(int h) {
		health = ( (ConfInt("actor.maxHealth") < (health + h)) ? ConfInt("actor.maxHealth") : health + h);
	}
	void addArmour(int a) {
		armour = ( (ConfInt("actor.maxArmour") < (armour + a)) ? ConfInt("actor.maxArmour") : armour + a);
	}
	void setArmour(int a) {
		armour = a;
	}
	void addAmmo(Enumerations::WeaponType type, int a) {
		ammo[type] += a;
	}
	/** check if gun is loaded
	*/
	bool isLoaded(Enumerations::WeaponType type) {
		return loaded[type];
	}
	/** returns how much actor still has ammo
	*/
	int ammoLeft(Enumerations::WeaponType type) {//TODO this method is duplicaded -> getAmmo
		return ammo[type];
	}
	void bulletFired() {
		loaded[currentWeapon] = false;
	}
	/** returns actor name
	*/
	const char* getName() {
		return name.c_str();
	}
	int getArmour() {
		return armour;
	}
	int getNumberOfTriggers() {
		return navigation->getNumberOfTriggers();
	}
	Trigger * getTrigger(int index) {
		return navigation->getTrigger(index);
	}
	Navigation * getNavigation() {
		return navigation;
	}
	/** updates what actor can see from current position
	*/
	void updateSpotting() {
		actorKnowledge->updateSpotting();
	}
	/** long term destination
	*/
	Vector4d getLongDestination() {
		return longDestination;
	}
	/** short term destination
	*/
	Vector4d getShortDestination() {
		return shortDestination;
	}
	int getKills() {
		return kills;
	}
	int getKilled() {
		return killed;
	}
	int getFriendKills() {
		return friendkills;
	}
	void incrementKills() {
		kills++;
	}
	void incrementKilled() {
		killed++;
	}
	void incrementFriendsKilled() {
		friendkills++;
	}
/*	bool isStarted() {
		return started;
	}
	bool setStarted(bool started) {
		this->started = started;
	}*/
protected:
	bool loaded[ Enumerations::WeaponType::WeaponSize ];
	int ammo[ Enumerations::WeaponType::WeaponSize ];
	int armour;
	std::string name;
	int health;
	bool started;
	void rotate();
	void move();
	virtual void update(GameTime time);
	/** sprawdza przecinanie si??? dw???ch odcink???w
	*/
	bool checkIntersection( Vector4d s1p1, Vector4d s1p2, Vector4d s2p1, Vector4d s2p2);

	/** sprawdza przecinanie si??? lini oraz odcinka
	*/
	bool lineInteresctsLineSegment( Vector4d s1p1, Vector4d s1p2, Vector4d s2p1, Vector4d s2p2);

	Vector4d longDestination;
	Vector4d shortDestination;
	std::vector<int> way;

	Vector4d moveVector;
	Vector4d directionVector;

	std::unique_ptr<ActorKnowledge> actorKnowledge;
	AbstractAgent * agent;
	double speed;

	std::string resourceName;
	
	unsigned int team;

	Enumerations::WeaponType currentWeapon;
	int kills;
	int killed;
	int friendkills;
	std::unique_ptr<Action> currentAction;
};

#endif //ACTOR_H