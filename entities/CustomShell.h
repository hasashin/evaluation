#ifndef CUSTOM_SHELL_H
#define CUSTOM_SHELL_H
#include "entities/Entity.h"

/** represents a shell rocket etc
*/
class CustomShell : public Entity
{
	friend void Game::updateWorld();
public:
	CustomShell(Entity * src, Vector4d destination, bool stopAtDestination,	GameTime fireTime, int timeToInvalidate, double speed, double damage, double radius, unsigned int color);
	/** procedure called on hit
	*/
	void explode(GameTime time);
	bool checkColision(Entity * entity, Vector4d distance);
	double getRadius() {
		return radius;
	};
	/** time after with object will invalidate and will be removed
	*/
	double getInvalidateTime() {
		return invalidateTime;
	};
	Vector4d getPrevPosition() {
		return prevPosition;
	}
private:
	void update(GameTime time);
	double radius;
	GameTime invalidateTime;
	Vector4d prevPosition;

	Entity * source;
	Vector4d destination;
	bool stopAtDestination;
	double speed;
	double damage;
};


#endif //CUSTOM_SHELL_H