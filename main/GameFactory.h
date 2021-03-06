#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H
#include <memory>
#include "main/Game.h"

class UserInterface;
/** constructs game instances acording to configuration
*/
class GameFactory 
{
public:
	/** singleton call only one instance allowed
	*/
	static GameFactory& getInstance() 
	{
		//TODO PS L czy to aby napewno jest dobra implementacja wzorca singleton?
		static GameFactory instance;
		return instance;
	}
	/** construct game instance according to configuration
	*/
	void createGame(UserInterface * ui);
	/** returns current game
	*/
	Game * getCurrentGame();
	void addObject(Entity * obj);//TODO this should be moved to private part
private:
	GameFactory() {}
	void createMap();
	void createActors(UserInterface * ui);
	void addActor(Actor * actor);
	std::unique_ptr<Game> game;
};

#endif //GAME_FACTORY_H