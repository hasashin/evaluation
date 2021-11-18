#pragma once
#ifndef WALL_H
#define WALL_H
#include "entities/Entity.h"

/** wall object
*/
class Wall : public Entity
{
	friend void Game::updateWorld();
public:
	Wall( Vector4d startPoint, Vector4d endPoint ) : Entity() {
		this->startPoint = startPoint;
		this->endPoint = endPoint;
		solid = true;
	}
	friend class GameFactory;
	Vector4d getStartPoint() {
		return startPoint;
	}
	Vector4d getEndPoint() {
		return endPoint;
	}
protected:
	Vector4d startPoint;
	Vector4d endPoint;
	virtual void update(GameTime time) {};
	virtual bool checkColision(Entity * entity, Vector4d distance) {
		return checkIntersection(startPoint, endPoint, entity->getPosition(), entity->getPosition()+distance);
	}
	//sprawdza czy nast¹pi³a kolizja na odcinku od rayPosition do (rayPosition + displacementVector)
	bool rayColision(Vector4d displacementVector, Vector4d rayPosition) {
		return checkIntersection(startPoint, endPoint, rayPosition, rayPosition + displacementVector);
	}
	//TODO zlikwidowaæ t¹ copypaste -> BoundingBox.h
	//sprawdza gdzie nast¹pi³a kolizja na odcinku od rayPosition do (rayPosition + displacementVector)
	double rayColisionDistance(Vector4d rayDisplacment, Vector4d rayPosition) {
		double closest = std::numeric_limits<double>::infinity();
		Vector4d s1p1, s1p2, s2p1, s2p2;
		s2p1 = rayPosition;
		s2p2 = rayPosition + rayDisplacment;
		{
			s1p1 = startPoint;
			s1p2 = endPoint;
			{
				if (checkIntersection(s1p1, s1p2, s2p1, s2p2)) {
					Vector4d crossing = 0;
					if ( (s1p1 - s1p2).val[0] == 0 ) {//TODO dodac obs³uge jak dwa takie s¹!!!
						if ( (s2p1 - s2p2).val[0] == 0 ) {
							assert(false && "Mia³es to obsluzyc");
						}
						Vector4d line = lineCoefficients(s2p1, s2p2);
						crossing.val[0] = s1p1.val[0];
						crossing.val[1] = crossing.val[0] * line.val[0] + line.val[1];
					} else if ( (s2p1 - s2p2).val[0] == 0 ) {
						Vector4d line = lineCoefficients(s1p1, s1p2);
						crossing.val[0] = s2p1.val[0];
						crossing.val[1] = crossing.val[0] * line.val[0] + line.val[1];
					} else {
						Vector4d line1 = lineCoefficients(s1p1, s1p2);
						Vector4d line2 = lineCoefficients(s2p1, s2p2);
						crossing.val[0] = (line1.val[1] - line2.val[1]) / (line2.val[0] - line1.val[0]);
						crossing.val[1] = crossing.val[0] * line1.val[0] + line1.val[1];
					}
					double dist = (crossing - rayPosition).length();
					if (dist < closest) {
						closest = dist;
					}
				}
			}
		}
		return closest;
	}
protected:
	// sprawdza przecinanie siê dwóch odcinków
	bool checkIntersection( Vector4d s1p1, Vector4d s1p2, Vector4d s2p1, Vector4d s2p2) {
		if (lineInteresctsLineSegment(s1p1, s1p2, s2p1, s2p2)
			&& lineInteresctsLineSegment(s2p1, s2p2, s1p1, s1p2)) {
			return true;
		} else {
			return false;
		}
	}

	// sprawdza przecinanie siê lini oraz odcinka
	bool lineInteresctsLineSegment( Vector4d s1p1, Vector4d s1p2, Vector4d s2p1, Vector4d s2p2) {
		double a = s1p1.val[0];
		double b = s1p1.val[1];
		double c = s1p2.val[0];
		double d = s1p2.val[1];
		double x1 = s2p1.val[0];
		double y1 = s2p1.val[1];
		double x2 = s2p2.val[0];
		double y2 = s2p2.val[1];
		return ((b - d) * x1 + (c - a) * y1 + (a * d - b * c))
				* ((b - d) * x2 + (c - a) * y2 + (a * d - b * c)) <= 0;
	}
	Vector4d lineCoefficients(Vector4d p1, Vector4d p2) {
		double a = (p2.val[1] - p1.val[1])/(p2.val[0] - p1.val[0]);
		double b = (-a) * p1.val[0] + p1.val[1];
		return Vector4d(a, b);
	}
private:
};

#endif //WALL_H