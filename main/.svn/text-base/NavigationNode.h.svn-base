#pragma once
#ifndef NAVIGATION_NODE_H
#define NAVIGATION_NODE_H
#include <map>
#include <vector>
#include "main/Misc.h"

/** Navigation node provides information about position of node and estimated costs of moving to other connected nodes
*/
class NavigationNode {
public:
	NavigationNode(double x, double y, int index) {
		position.val[0] = x;
		position.val[1] = y;
		this->index = index;
	}
	Vector4d position;
	int index;
	typedef std::pair<int, double> Arc;
	std::vector<Arc> arcs;
};

#endif //NAVIGATION_NODE_H