#include "MouseAgent.h"
#include "ActorKnowledge.h"

void MouseAgent::whatToDo(ActorKnowledge * actorKnowledge, GameTime time) {
}

void MouseAgent::mouseButtonPressed(Vector4d coordinates, Uint8 button) {
	if (current != NULL) {
		if (button == 1) {
			moveTo(coordinates);
		} else {
			shootAtPoint(coordinates);
		}
	}
}

void MouseAgent::mouseMoved(Vector4d coordinates) {
	if (current != NULL) {
		rotate(coordinates - current->getPosition());
	}
}

void MouseAgent::keyPressed(SDLKey key) {
	switch (key) {
		case SDLK_r:
			reload();
			break;
		case SDLK_KP5:
			wait();
			break;
		case SDLK_1:
			selectWeapon(Enumerations::WeaponType::Chaingun);
			break;
		case SDLK_2:
			selectWeapon(Enumerations::WeaponType::Railgun);
			break;
		case SDLK_3:
			selectWeapon(Enumerations::WeaponType::RocketLuncher);
			break;
		case SDLK_4:
			selectWeapon(Enumerations::WeaponType::Shotgun);
			break;
		default:
			break;
	}
}