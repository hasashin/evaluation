#include "graphics/SDLFrontend.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include <SDL_rotozoom.h>
#include <SDL_gfxPrimitives.h>
#include "main/Game.h"
#include "graphics/Graphics.h"
#include "graphics/ImagesManager.h"
#include "entities/Trigger.h"
#include "entities/Actor.h"
#include "entities/Wall.h"
#include "entities/CustomShell.h"
#include "main/Configuration.h"

/** function used in sorting object
funkcja do sortowania obiektów w grze od "najni¿szych" do "najwy¿szych" ¿eby sie nie zas³ania³y
*/
bool lower(Entity* first, Entity* second) {
	return (first->getPosition() < second->getPosition());
}

/** generates postfix for resource name to get aproperietly directed object on image
*/
std::string getDirectionPostfix(Vector4d direction) {
	
	Vector4d dir( direction.val[0],direction.val[1]);
	dir.normalize();
	const double cosOfPiBy8 = 0.92387953251128675612818318939679;
	Vector4d n(0,-1);
	Vector4d ne(1,-1);
	ne.normalize();
	Vector4d e(1,0);
	Vector4d se(1,1);
	se.normalize();
	Vector4d s(0,1);
	Vector4d sw(-1,1);
	sw.normalize();
	Vector4d w(-1,0);
	Vector4d nw(-1,-1);
	nw.normalize();

	Vector4d directions[8]= { n, nw, w, sw, s, se, e, ne };
	std::string strDirections[8]= { "n", "nw", "w", "sw", "s", "se", "e", "ne" };

	if (direction.val[0] == 0 && direction.val[1] == 0) {
		direction = Vector4d(0, -1);
	}
	for (int j = 0; j < 8; ++j) {
		if (dir.dot(directions[j]) >= cosOfPiBy8) {
			return strDirections[j];
		}
	}
	return "error";
}

/** function prints world on the screen surface
all world drawing should go here
*/
void SDLFrontend::run(Game * game) {
	SDL_Surface * screen = graphics->getScreen();

	//narysowanie pod³ogi zupe³nie nie potrzebne, ale brzydko bez tego narazie wygl¹da
	int height = game->getHeight();
	int width = game->getWidth();
	boxColor(screen, graphics->transformXToViewCoordinate(0), graphics->transformYToViewCoordinate(0), graphics->transformXToViewCoordinate(width), graphics->transformYToViewCoordinate(height), 0xAAAAAAFF);

	std::vector<Entity*> & objects = game->getObjects();
	sort( objects.begin(), objects.end(), lower );

	SDL_Rect prect;
	for (unsigned int i = 0; i < objects.size(); ++i) {
		Entity* obj = objects[i];
		prect.x = graphics->transformXToViewCoordinate(static_cast<int>(obj->getPosition().val[0]));
		prect.y = graphics->transformYToViewCoordinate(static_cast<int>(obj->getPosition().val[1]));

		std::string surfaceName = "nieNadano";
		if( Actor* actor = dynamic_cast<Actor*>(obj))
		{

			Vector4d corner00 = actor->getPosition() - actor->getBoundingPoints().at(0);
			Vector4d corner11 = actor->getPosition() + actor->getBoundingPoints().at(0);
			int showHealthBar = Configuration::getInstance().getBool("graphics.showHealthBar");
			if (showHealthBar)
			{
			
				Vector4d pos11 = actor->getPosition() - actor->getBoundingPoints().at(0) - actor->getBoundingPoints().at(0) - Vector4d(0, +20, 0, 0);
				Vector4d pos00 = actor->getPosition() + actor->getBoundingPoints().at(0) + actor->getBoundingPoints().at(0) - Vector4d(0, +12, 0, 0);
				int healthPoint = actor->getHealth();
				int maxHealth = Configuration::getInstance().getInt("actor.maxHealth");
				int val = pos11.val[0] - pos00.val[0];
				val *= (float) healthPoint / (float) maxHealth;
				pos11.val[0] = pos00.val[0] + val;
				Uint32 color = 0x00FF00FF;

			
				if (((float) healthPoint / (float) maxHealth) < 0.5f)
				{
					color = 0xFF8850FF;
				}
				else if ((float) healthPoint / (float) maxHealth < 0.2f)
				{
					color = 0xFF0000FF;
				}
				boxColor(screen, graphics->transformXToViewCoordinate(pos00.val[0]), graphics->transformYToViewCoordinate(pos00.val[1]),
					graphics->transformXToViewCoordinate(pos11.val[0]), graphics->transformYToViewCoordinate(pos11.val[1]), color);
			}
			boxColor(screen, graphics->transformXToViewCoordinate(corner00.val[0]), graphics->transformYToViewCoordinate(corner00.val[1]), graphics->transformXToViewCoordinate(corner11.val[0]), graphics->transformYToViewCoordinate(corner11.val[1]), 0xDDDDDDFF);
			
			surfaceName = actor->getResourceName();
			if ( surfaceName.compare("") != 0)
			{
				int alpha = 255;
				surfaceName += actor->getCurrentAction()->getActionCode();
				surfaceName += ".";
				surfaceName += getDirectionPostfix(actor->getDirection());

				ResourceInfo ri = ImagesManager::getInstance().getResourceInfo(surfaceName);
				int frame = ri.getFrames();
				Action * currentAction = actor->getCurrentAction();
				if (frame > 0) {
					if (currentAction->isRepeatable()) {
						frame = ((game->getGameTime() - currentAction->getActionStarted())/2) % frame;
					} else {
						frame = std::min((int)((game->getGameTime() - currentAction->getActionStarted())/2), (int)(frame-1));
					}
				}

				Vector4d scale(0.25 * graphics->getZoomFactor(), 0.25 * graphics->getZoomFactor());
				const SDL_Surface * out = ImagesManager::getInstance().getSurface(surfaceName, scale, frame);
				SDL_SetAlpha (const_cast<SDL_Surface*>(out), SDL_SRCALPHA, alpha);
				prect.x -= out->w * 0.5;
				prect.y -= out->h * (68.0/96.0);
				SDL_BlitSurface(const_cast<SDL_Surface*>(out), 0, screen, &prect);
			}
		}
		if( Trigger* trigger = dynamic_cast<Trigger*>(obj))
		{
			circleColor(screen, graphics->transformXToViewCoordinate(trigger->getPosition().val[0]),  graphics->transformYToViewCoordinate(trigger->getPosition().val[1]), trigger->getBoundingRadius() * 1.5 * graphics->getZoomFactor(), trigger->getColor());
			if (trigger->isActive()) {
				Vector4d corner00 = trigger->getPosition() - trigger->getBoundingPoints().at(0);
				Vector4d corner11 = trigger->getPosition() + trigger->getBoundingPoints().at(0);
				boxColor(screen, graphics->transformXToViewCoordinate(corner00.val[0]), graphics->transformYToViewCoordinate(corner00.val[1]), graphics->transformXToViewCoordinate(corner11.val[0]), graphics->transformYToViewCoordinate(corner11.val[1]), trigger->getColor());
			}
		}
		if( Wall* wall = dynamic_cast<Wall*>(obj))
		{
			lineColor(screen, graphics->transformXToViewCoordinate(wall->getStartPoint().val[0]),  graphics->transformYToViewCoordinate(wall->getStartPoint().val[1]),
					graphics->transformXToViewCoordinate(wall->getEndPoint().val[0]), graphics->transformYToViewCoordinate(wall->getEndPoint().val[1]), 0x000000FF);
		}
		if( CustomShell* customShell = dynamic_cast<CustomShell*>(obj))
		{
			if (game->getGameTime() + 1 == customShell->getInvalidateTime()) {
				circleColor(screen, graphics->transformXToViewCoordinate(customShell->getPosition().val[0]),  graphics->transformYToViewCoordinate(customShell->getPosition().val[1]), customShell->getRadius() * graphics->getZoomFactor(), customShell->getColor());
			} else {
				lineColor(screen, graphics->transformXToViewCoordinate(customShell->getPosition().val[0]),  graphics->transformYToViewCoordinate(customShell->getPosition().val[1]),
					graphics->transformXToViewCoordinate(customShell->getPrevPosition().val[0]), graphics->transformYToViewCoordinate(customShell->getPrevPosition().val[1]), customShell->getColor());
			}
		}
	}
}