#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <iostream>
#include "main/Misc.h"
#include "entities/BoundingBox.h"
#include "main/Game.h"
#include "main/Navigation.h"
#include <limits>

/** base class for every object in game
*/
class Entity //TODO kolizje wywali� st�d?
{
	friend class GameFactory;
	friend void Game::updateWorld();
public:
	Entity();
	virtual ~Entity() = 0 ;
	Vector4d getPosition() { 
		return position;
	}
	virtual void setPosition(Vector4d position) {
		this->position = position; 
	}
	Vector4d getDirection() { 
		return direction; 
	}
	void setDirection( Vector4d direction ) { 
		this->direction = direction;
	}
	double getBoundingRadius() {
		return boundingBox->getRadius();
	}
	//sprawdza czy podany entity nie bedzie kolidowa� z this'em po przesunieciu o distance
	//np z pociskiem nic nie skoliduje wi�c powinien mie� return false
	//natomiast actor powinien mie� to zaimpementowane podobnie jak skrzynka
	virtual bool checkColision(Entity * entity, Vector4d distance) {
		return boundingBox->checkColision(position, entity->boundingBox.get(), entity->position + distance);
	}
	//u�ywane tylko w rysowaniu bbox�w
	std::vector<Vector4d> getBoundingPoints() {
		return boundingBox->getPoints();
	}
	/** sets validity to false indicating that object may be removed
	*/
	void invalidate() {
		valid = false;
	}
	/** indicated wheter object should be still updated or should be removed
	*/
	bool isValid() {
		return valid;
	}
	//sprawdza czy nast�pi�a kolizja na odcinku od rayPosition do (rayPosition + displacementVector)
	virtual bool rayColision(Vector4d displacementVector, Vector4d rayPosition) {
		return boundingBox->rayColision(position, displacementVector, rayPosition);
	}
	//sprawdza gdzie nast�pi�a kolizja na odcinku od rayPosition do (rayPosition + displacementVector)
	virtual double rayColisionDistance(Vector4d displacementVector, Vector4d rayPosition) {
		return boundingBox->rayColisionDistance(position, displacementVector, rayPosition);
	}
	//sprawdza czy nast�pi�a na podanym odcinku kolizja z jakim� solid obiektem
	bool anyRayCrateColision(Vector4d displacementVector, Vector4d positionVector);

	//czy bedzie zas�ania� i chroni� przed od�amkami, u�ywane w anyRayCreateColision
	bool solid;
	unsigned getColor() {
		return color;
	};
protected:
	virtual void update(GameTime time) { 
		std::cerr << "entity->update()\n";
	};
	long id;
	Vector4d position;
	std::unique_ptr<BoundingBox> boundingBox;
	Vector4d direction;
	bool valid;
	Navigation * navigation;
	unsigned int color;
private:
};

#endif //ENTITY_H