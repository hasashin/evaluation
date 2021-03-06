#pragma once
#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "main/NavigationNode.h"
#include <limits>
#include <vector>
#include <algorithm>
#include "boost/tuple/tuple.hpp"
#include "main/RandomGenerator.h"

class Trigger;

//aStarNode (index, f, g, h, prevIndex)
typedef boost::tuples::tuple<int, double, double, double, int> AStarNode;

//used in making heap for a*, sorting by f
static bool lowerCost(AStarNode first, AStarNode second) {
	return (first.get<1>() > second.get<1>());
}
/** Navigation class preformes A* path searches throught graph of NavigationNodes
*/
class Navigation {
	friend class GameFactory;
public:
	/**checks if ray colides any solid thing on the way
	*/
	bool anyRayCrateColision(Vector4d displacementVector, Vector4d positionVector);
	Vector4d getNodePosition(int index) {
		return nodes[index].position;
	}

	/**finds shortest way between two points
	*/
	std::vector<int> searchWay(Vector4d from, Vector4d to);
	/** number of triggers such as medkits, ammo packs, armours
	*/
	int getNumberOfTriggers();

	/** number of navigation points
	*/
	int getNumberOfPoints();
	/** get trigger such as medkits, ammo packs, armours
	*/
	Trigger * getTrigger(int index);
	/** number of places where actors apear after respawning
	*/
	int getNumberOfSpawnPoints() {
		return spawns.size();
	}
	/** gets place where actors apear after respawning
	*/
	Vector4d getSpawnPoint(int index) {
		return spawns[index];
	}
protected:
	Navigation(int indexNr) {
		this->indexNr = indexNr;
	}
	/** finds closest navigation node
	*/
	int searchClosestNavigationNode(Vector4d point);

	/**finds shortest way between two navigation nodes
	*/
	std::vector<int> searchWay(int from, int to);

	/**checks if AStarNode has searched index
	*/
	bool hasIndex(AStarNode i, int searchedIndex) {
		return searchedIndex == i.get<0>();
	}
	std::vector<Vector4d> spawns;
	std::vector<NavigationNode> nodes;
	std::vector<Trigger*> triggers;
	int indexNr;
};

#endif //NAVIGATION_H