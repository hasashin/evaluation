#pragma once
#ifndef PLAYER_AGENT_H
#define PLAYER_AGENT_H
#include "agents/AbstractAgent.h"
#include <memory>
#include "main/Misc.h"
#include "agents/ActorInfo.h"
#include "actions/Action.h"

class ActorInfo;

/** PlayerAgent classes give orders to actors
*/
class PlayerAgent : public AbstractAgent
{
public:
	PlayerAgent() {
		current = NULL;
	}
	/** called on every order update
	*/
	/*final*/ Action * whatToDoNow(ActorKnowledge * actorKnowledge, GameTime time);
	/** called on spawn of actor
	*/
	/*final*/ void start(ActorKnowledge * actorKnowledge, GameTime time);
	/** returns random double
	*/
	double randomDouble();
	/** gives order to select chosen weapon
	*/
	void selectWeapon(Enumerations::WeaponType weapon);
	/** gives order to move in chosen direction
	*/
	void moveDirection(Vector4d direction);
	/** gives order to move to a certain point
	*/
	void moveTo(Vector4d target);
	/** gives order to reload current weapon
	*/
	void reload();
	/** gives order to change facing direciton
	*/
	void rotate(Vector4d direction);
	void shootAt(ActorInfo enemy); //TODO do usuniecia
	/** gives order to shoot at given point
	*/
	void shootAtPoint(Vector4d vect);
	/** gives order to do nothing
	*/
	void wait();
	/** gives order to continue current action
	*/
	void continueAction();
protected:
	ActorKnowledge * current;
	std::unique_ptr<Action> nextAction;
	virtual void whatToDo(ActorKnowledge * actorKnowledge, GameTime time) = 0;
	virtual void onStart(ActorKnowledge * actorKnowledge, GameTime time) = 0;
};

#endif //PLAYER_AGENT_H