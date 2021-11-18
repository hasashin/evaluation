#include <sstream>
#include <entities/Actor.h>
#include "graphics/UserInterface.h"
#include "graphics/Graphics.h"
#include "agents/ActorKnowledge.h"
/** process mouse button pressed events
*/
void UserInterface::mouseButtonPressed(Vector4d coordinates, Uint8 button) {
	coordinates.val[0] = graphics->transformXToWorldCoordinate(coordinates.val[0]);
	coordinates.val[1] = graphics->transformYToWorldCoordinate(coordinates.val[1]);
	if (agent != NULL) {
		agent->mouseButtonPressed(coordinates, button);
	}
}
/** process mouse moves
*/
void UserInterface::mouseMoved(int xrel, int yrel, int x, int y) {
	Vector4d coordinates;
	coordinates.val[0] = graphics->transformXToWorldCoordinate(x);
	coordinates.val[1] = graphics->transformYToWorldCoordinate(y);
	if (agent != NULL) {
		agent->mouseMoved(coordinates);
	}
}
/** process key released events
*/
void UserInterface::keyReleased(SDLKey key) {
	switch (key) {
	case SDLK_KP_PLUS:
		zooming = 0.0;
		break;
	case SDLK_KP_MINUS:
		zooming = 0.0;
		break;
	case SDLK_KP8:
		movingVertical = 0;
		break;
	case SDLK_KP2:
		movingVertical = 0;
		break;
	case SDLK_KP4:
		movingHorizontal = 0;
		break;
	case SDLK_KP6:
		movingHorizontal = 0;
		break;
	}
}
/** process key pressed events
*/
void UserInterface::keyPressed(SDLKey key) {
	switch (key) {
	case SDLK_KP_PLUS:
		zooming = 0.1;
		break;
	case SDLK_KP_MINUS:
		zooming = -0.1;
		break;
	case SDLK_KP8:
		movingVertical = -10;
		break;
	case SDLK_KP2:
		movingVertical = 10;
		break;
	case SDLK_KP4:
		movingHorizontal = -10;
		break;
	case SDLK_KP6:
		movingHorizontal = 10;
		break;
	case SDLK_KP5:
		/*if (agent != NULL) {
			Vector4d pos = agent->getCurrent()->getPosition();
			graphics->setOOPoint(pos.val[0], pos.val[1]);
		}*/
		break;
	default:
		if (agent != NULL) {
			agent->keyPressed(key);
		}
	}
}

void UserInterface::setOOPoint(double x, double y, double scale) {
	graphics->setOOPoint(x, y, scale);
}

int UserInterface::getHeight() {
	return graphics->getHeight();
}

int UserInterface::getWidth() {
	return graphics->getWidth();
}


/** draws ui elements on screen surface, and also process long lasting input actions
for example if something should happen durring all time some key is beeing pressed
*/
void UserInterface::update(std::vector<Actor*> allActors) {
	ActorKnowledge * ak = NULL;

	if (agent != NULL)
		ak = agent->getCurrent();
	std::ostringstream ss;
	SDL_Rect rcDest;
	SDL_Surface * sText;

	Vector4d red(255, 0, 0);
	Vector4d green(0, 255, 0);

	if (ak != NULL) {
		std::string weaponStr;
		switch (ak->getWeaponType()) {
		case Enumerations::WeaponType::Chaingun:
			weaponStr = "Machinegun";
			break;
		case Enumerations::WeaponType::Railgun:
			weaponStr = "Railgun";
			break;
		case Enumerations::WeaponType::RocketLuncher:
			weaponStr = "RocketLuncher";
			break;
		case Enumerations::WeaponType::Shotgun:
			weaponStr = "Shotgun";
			break;
		};

		
		ss << "Health: " << ak->getHealth() << "Armour: " << ak->getActor()->getArmour() << " Weapon: " << weaponStr << " Ammo: " << ak->getAmmo(ak->getWeaponType());

		Vector4d white(255, 255, 255);
		sText = drawtext(ss.str().c_str(), white, blended);
		rcDest = { 1,0,0,0 };
		SDL_BlitSurface(sText, NULL, graphics->getScreen(), &rcDest);
		SDL_FreeSurface(sText);

		ss.str("");
		for (int i = 0; i < Enumerations::WeaponType::WeaponSize; i++) {
			switch (i) {
			case Enumerations::WeaponType::Chaingun:
				weaponStr = "Machinegun";
				break;
			case Enumerations::WeaponType::Railgun:
				weaponStr = "Railgun";
				break;
			case Enumerations::WeaponType::RocketLuncher:
				weaponStr = "RocketLuncher";
				break;
			case Enumerations::WeaponType::Shotgun:
				weaponStr = "Shotgun";
				break;
			};
			ss << weaponStr << (ak->getActor()->isLoaded(static_cast<Enumerations::WeaponType>(i)) ? " [:] " : " [ ] ") << ak->getAmmo(static_cast<Enumerations::WeaponType>(i)) << " ";
		}
		sText = drawtext(ss.str().c_str(), white, blended);
		rcDest.y = getHeight() - 12 - 1;
		SDL_BlitSurface(sText, NULL, graphics->getScreen(), &rcDest);
		SDL_FreeSurface(sText);
		ss.str("");

		
		std::vector<ActorInfo> actors = ak->getSeenActors();
		for (unsigned int i = 0; i < actors.size(); i++) {
			ActorInfo actr = actors[i];
			Vector4d color = (ak->getTeam() != actr.getTeam() ? red : green);

			sText = drawtext(actr.getName(), color, blended);
			rcDest.x = graphics->transformXToViewCoordinate(actr.getPosition().val[0]);
			rcDest.y = graphics->transformYToViewCoordinate(actr.getPosition().val[1]);
			SDL_BlitSurface(sText, NULL, graphics->getScreen(), &rcDest);
			SDL_FreeSurface(sText);
			ss.str("");

			switch (actr.getWeaponType()) {
			case Enumerations::WeaponType::Chaingun:
				weaponStr = "MG";
				break;
			case Enumerations::WeaponType::Railgun:
				weaponStr = "RG";
				break;
			case Enumerations::WeaponType::RocketLuncher:
				weaponStr = "RL";
				break;
			case Enumerations::WeaponType::Shotgun:
				weaponStr = "SG";
				break;
			};
			ss << "H:" << actr.getHealth() << " A:" << actr.getArmour() << " W:" << weaponStr;
			sText = drawtext(ss.str().c_str(), color, blended);
			rcDest.x = graphics->transformXToViewCoordinate(actr.getPosition().val[0]);
			rcDest.y = graphics->transformYToViewCoordinate(actr.getPosition().val[1]) + 12;
			SDL_BlitSurface(sText, NULL, graphics->getScreen(), &rcDest);
			SDL_FreeSurface(sText);
			ss.str("");
		}

	}
	
	int showHealthNumber = Configuration::getInstance().getBool("graphics.showHealthNumber");

	if (showHealthNumber)
	{

		for (unsigned int i = 0; i < allActors.size(); ++i)
		{
			Actor* actor = allActors[i];
			int healthPoint = actor->getHealth();
			int maxHealth = Configuration::getInstance().getInt("actor.maxHealth");
			float health = (float)healthPoint / maxHealth * 100;

			if (healthPoint > 0)
			{
				ss << ((float)(int)(health*10.0f)) / 10.0f << "%";
				rcDest.x = graphics->transformXToViewCoordinate(actor->getPosition().val[0]) - 15;
				rcDest.y = graphics->transformYToViewCoordinate(actor->getPosition().val[1]) - 30;
				sText = drawtext(ss.str().c_str(), red, blended, 1);
				SDL_BlitSurface(sText, NULL, graphics->getScreen(), &rcDest);
				SDL_FreeSurface(sText);
				ss.str("");
			}
		}
	}


	graphics->zoom(zooming);
	graphics->moveVertical(movingVertical);
	graphics->moveHorizontal(movingHorizontal);
}

void UserInterface::showTime(int timeToEnd)
{
	std::ostringstream ss;
	SDL_Rect rcDest;
	SDL_Surface * sText;
	rcDest = { 1,0,0,0 };
	ss << "Time left: " << timeToEnd;
	Vector4d black(255, 0, 0);
	sText = drawtext(ss.str().c_str(), black, blended);
	rcDest.x = 350; 
	rcDest.y = 0;// getHeight() - 12 - 1;
	SDL_BlitSurface(sText, NULL, graphics->getScreen(), &rcDest);
	SDL_FreeSurface(sText);
}

SDL_Surface * UserInterface::drawtext(const char * text, Vector4d color, textquality quality, int useDefaultFont)
{
	SDL_Color tmpfontcolor = { (Uint8)color.val[0],(Uint8)color.val[1],(Uint8)color.val[2],128 };
	//  SDL_Color tmpfontcolor = {255,255,255,128};
	SDL_Color tmpfontbgcolor = { 0, 0, 0, 128 };
	SDL_Surface *resulting_text;
	TTF_Font * font = useDefaultFont ? defaultFont : smallFont;

	if (quality == solid) resulting_text = TTF_RenderText_Solid(font, text, tmpfontcolor);
	else if (quality == shaded) resulting_text = TTF_RenderText_Shaded(font, text, tmpfontcolor, tmpfontbgcolor);
	else if (quality == blended) resulting_text = TTF_RenderText_Blended(font, text, tmpfontcolor);

	return resulting_text;
}