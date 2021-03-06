#include "main/Navigation.h"
#include "main/GameFactory.h"
#include "entities/Trigger.h"

bool Navigation::anyRayCrateColision(Vector4d displacementVector, Vector4d positionVector) {
		std::vector<Entity*> & objects = GameFactory::getInstance().getCurrentGame()->getObjects();
		for (std::vector<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			if ((*it)->solid && (*it)->rayColision(displacementVector, positionVector)) {
				return true;
			}
		}
		return false;
	}

	int Navigation::getNumberOfTriggers() {
		return triggers.size();
	}

	int Navigation::getNumberOfPoints() {
		return nodes.size();
	}

	Trigger * Navigation::getTrigger(int index) {
		return triggers[index];
	}

	std::vector<int> Navigation::searchWay(int from, int to) {
		std::vector<int> result;

		std::vector<AStarNode> open;
		std::vector<AStarNode> closed;
		std::vector<AStarNode>::iterator it;

		// Dodajemy pole startowe (lub w?ze?) do Listy Otwartych.
		double g = 0;
		double h = (nodes[from].position - nodes[to].position).length();
		open.push_back(AStarNode(from, g + h, g, h, from));
		make_heap (open.begin(),open.end(), lowerCost);

		while (true) {
			// Zatrzymujemy si?, gdy, Lista Otwartych jest pusta. W tym przypadku nie znaleziono pola docelowego, a ?cie?ka nie istnieje.   
			if (open.size() == 0) {
				break;
			}
			
			// Szukamy pola o najni?szej warto?ci F na Li?cie Otwartych. Czynimy je aktualnym polem.
			AStarNode actual = open.front();
			pop_heap (open.begin(),open.end(), lowerCost);
			open.pop_back();

			// Aktualne pole przesuwamy do Listy Zamkni?tych.
			closed.push_back(actual);

			// Zatrzymujemy si?, gdy Dodano pole docelowe do Listy Zamkni?tych. W tym przypadku ?cie?ka zosta?a odnaleziona (popatrzcie na notk? poni?ej)
			if (actual.get<0>() == to) {
				// Zapisujemy ?cie?k?
				AStarNode current = actual;
				int inserted, prev;
				do {
					inserted = current.get<0>();
					prev = current.get<4>();
					result.push_back(inserted);
				    for (it = closed.begin() ; it!=closed.end() ; it++ ) if ( hasIndex(*it, prev) ) break;
					current = *it;
				} while (inserted != prev);
				break;
			}

			// Przetwarzamy s?siad?w aktualnego pola
			NavigationNode current = nodes[actual.get<0>()];
			for (unsigned int i = 0; i < current.arcs.size(); i++) {
				int nextIndex = current.arcs[i].first;
				double toNextCost = current.arcs[i].second;


				for (it = closed.begin() ; it!=closed.end() ; it++ ) if ( hasIndex(*it, nextIndex) ) break;
				// Je?li jest na li?cie zamkni?tych, ignorujemy je
				if (it == closed.end()) {						
					g = actual.get<2>() + toNextCost;
					h = (nodes[to].position - nodes[nextIndex].position).length();

					for (it = open.begin() ; it!=open.end() ; it++ ) if ( hasIndex(*it, nextIndex) ) break;
					// Je?li pole nie jest jeszcze na Li?cie Otwartych, dodajemy je do niej
					if (it == open.end()) {
						open.push_back(AStarNode(nextIndex, g + h, g, h, actual.get<0>() ));
						push_heap (open.begin(),open.end(), lowerCost);

					} else {
						// Je?li pole by?o ju? na Li?cie Otwartych, sprawdzamy czy aktualna ?cie?ka do tego pola jest lepsza
						if ( g < (*it).get<2>() ) {
							boost::tuples::get<1>(*it) = g + (*it).get<3>();
							boost::tuples::get<2>(*it) = g;
							boost::tuples::get<4>(*it) = actual.get<0>();
							make_heap (open.begin(),open.end(), lowerCost);
						}
					}
				}
			}
		}
		return result;
	}

	int Navigation::searchClosestNavigationNode(Vector4d point) {
		int result = -1;
		double minDistance = std::numeric_limits<double>::infinity( );
		for(unsigned int i = 0; i < nodes.size(); i++) {
			double dist = (nodes[i].position - point).length();
			if (nodes[i].index != -1 && dist < minDistance && !anyRayCrateColision( (nodes[i].position - point), point)) {
				minDistance = dist;
				result = nodes[i].index;
			}
		}
		return result;
	}

	std::vector<int> Navigation::searchWay(Vector4d from, Vector4d to) {
		int start = searchClosestNavigationNode(from);
		int end = searchClosestNavigationNode(to);
		if (start == -1 || end == -1) {
			std::vector<int> out;
			return out;
		} else {
			return searchWay(start, end);
		}
	}