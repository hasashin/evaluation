#include "actions/Action.h"
#include "entities/Actor.h"

Action::Action() : cosOfPiBy8(0.92387953251128675612818318939679) {
	nextAction = NULL;
}

void Action::onEnter(Actor* actor, GameTime gameTime) {
	actionStarted = gameTime;
}

void Action::rotate(Actor * actor, Vector4d direction, GameTime time) {
	actor->setDirectionVector(direction);
}

Action::~Action() = default;