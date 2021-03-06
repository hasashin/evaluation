#include "entities/Entity.h"
#include "main/RandomGenerator.h"
#include "main/GameFactory.h"

/**checks if ray colides any solid thing on the way //kopi pasta!!!! TODO
*/
bool Entity::anyRayCrateColision(Vector4d displacementVector, Vector4d positionVector) {
	return navigation->anyRayCrateColision(displacementVector, positionVector);
}

Entity::Entity() {
		//TODO zmie� to
		Vector4d dest( RandomDouble() - 0.500001, RandomDouble() - 0.5);
		direction = dest.normal();
		solid = false;
		std::vector<Vector4d> bbox;
		bbox.push_back(Vector4d(-2.5, -2.5));
		bbox.push_back(Vector4d(2.5, -2.5));
		bbox.push_back(Vector4d(2.5, 2.5));
		bbox.push_back(Vector4d(-2.5, 2.5));
		boundingBox.reset(new BoundingBox(bbox));
		valid = true;
		position = Vector4d();
		static long idIterator = 0;
		id = idIterator++;
	}

	Entity::~Entity() = default;