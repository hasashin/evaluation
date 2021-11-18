#pragma once
#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H
#include <cmath>
#include <cassert>
#include <vector>
#include <limits>
#include "main/Misc.h"

/** collision box class
*/
class BoundingBox //TODO uporz¹dkowaæ i opisaæ t¹ klasê, zlikwidowaæ copypaste -> Wall.h
{
public:
	//TODO ten konstruktor wywaliæ jak bede mia³ lepsze wyznaczanie œrodka i radiusa
	BoundingBox(std::vector<Vector4d> inPoints) {
		this->points = inPoints;
		radius = 0;
		double currRadius = 0;
		for (std::vector<Vector4d>::iterator it = points.begin(); it != points.end(); it++ ) {
			currRadius = (*it).lengthSquared();
			if (currRadius > radius) {
				radius = currRadius;
			}
		}
		radius = std::sqrt(radius);
	}

	//sprawdza czy podany bbox w pozycji bbposition nie bedzie kolidowa³ z this'em który znajduje siê w position
	//TODO to sprawdzanie jest s³abe bo umo¿liwia przy du¿ych prêdkoœciach przenikniêcie przez przeszkodê
	bool checkColision(Vector4d position, BoundingBox * bbox, Vector4d bbposition) {
		if ((bbox->radius + radius) * (bbox->radius + radius) < Vector4d(position - bbposition).lengthSquared()) {
			return false;
		}
		Vector4d s1p1, s1p2, s2p1, s2p2;
		for (unsigned int i = 0; i < points.size(); i++) {
			s1p1 = points[i] + position;
			s1p2 = points[(i + 1) % points.size()] + position;
			for (unsigned int j = 0; j < bbox->points.size(); j++) {
				s2p1 = bbox->points[j] + bbposition;
				s2p2 = bbox->points[(j + 1) % bbox->points.size()] + bbposition;
				if (checkIntersection(s1p1, s1p2, s2p1, s2p2)) {
					return true;
				}
			}
		}
		//TODO dodaj sprawdzenie czy nie zawiera siê ca³kowicie dla dowolnego punktu
		return false;
	}

	double getRadius() {
		return radius;
	}
	std::vector<Vector4d> getPoints() {
		return points;
	}
	
	bool rayColision(Vector4d position, Vector4d rayDisplacment, Vector4d rayPosition) {
		if ((rayDisplacment.length()/2.0 + radius) * (rayDisplacment.length()/2.0 + radius) < Vector4d(position - (rayPosition + rayDisplacment/2.0)).lengthSquared()) {
			return false;
		}
		Vector4d s1p1, s1p2, s2p1, s2p2;
		s2p1 = rayPosition;
		s2p2 = rayPosition + rayDisplacment;
		for (unsigned int i = 0; i < points.size(); i++) {
			s1p1 = points[i] + position;
			s1p2 = points[(i + 1) % points.size()] + position;
			{
				if (checkIntersection(s1p1, s1p2, s2p1, s2p2)) {
					return true;
				}
			}
		}
		return false;
	}

	double rayColisionDistance(Vector4d position, Vector4d rayDisplacment, Vector4d rayPosition) {
		if ((rayDisplacment.length()/2.0 + radius) * (rayDisplacment.length()/2.0 + radius) < Vector4d(position - (rayPosition + rayDisplacment/2.0)).lengthSquared()) {
			return std::numeric_limits<double>::infinity();
		}
		double closest = std::numeric_limits<double>::infinity();
		Vector4d s1p1, s1p2, s2p1, s2p2;
		s2p1 = rayPosition;
		s2p2 = rayPosition + rayDisplacment;
		for (unsigned int i = 0; i < points.size(); i++) {
			s1p1 = points[i] + position;
			s1p2 = points[(i + 1) % points.size()] + position;
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
	Vector4d lineCoefficients(Vector4d p1, Vector4d p2) {
		double a = (p2.val[1] - p1.val[1])/(p2.val[0] - p1.val[0]);
		double b = (-a) * p1.val[0] + p1.val[1];
		return Vector4d(a, b);
	}
private:
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
	double radius;
	std::vector<Vector4d> points;
};

#endif //BOUNDING_BOX_H