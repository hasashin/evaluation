#ifndef GAME_H
#define GAME_H
#include <chrono>
#include <vector>
#include <memory>
#include <map>
#include "main/Misc.h"
//#include "entities/Entity.h"
#include "main/Navigation.h"

class AbstractFrontend;
class Actor;
class Entity;
struct lua_State;

typedef std::map<int, lua_State*> Team2LuaEnvMap;
/** stores all the information about game
*/
class Game 
{
	friend class GameFactory;
public:
	std::unique_ptr<Navigation> navigation;//TODO move to private
	Game();
	/** run one step of game machanics
	*/
	void updateWorld();
	/** runs registred frontends graphics, sound and others
	*/
	void runFrontends();
	/** checks wheter game has finished
	*/
	bool isFinished();
	/** asks agents to update orders to actors
	*/
	void updateAI();
	/** registers frontends
	*/
	void addFrontend(AbstractFrontend * frontend);
	~Game();
	/** inflict damage to actor
	*/
	void inflictDamage(Actor* actor, int damage, GameTime time, Actor* attacker);
	/** returns all the in game objects walls, shells, actors
	*/
	std::vector<Entity*> & getObjects();
	/** returns actors only
	*/
	std::vector<Actor*> & getActors();
	/** prints to std out game results
	*/
	void printResults();
	/** returns abstract game time
	*/
	GameTime getGameTime() { 
		return gameTime;
	}
	/** map height
	*/
	double getHeight() { 
		return height;
	}
	/** map width
	*/
	double getWidth() { 
		return width;
	}

	void startGame() {
		start_game = std::chrono::system_clock::now();
	}

	void endGame() {
		end_game = std::chrono::system_clock::now();
	}

	int getTimeToEnd();

private:
	double height;
	double width;
	GameTime gameTime;
	std::vector<AbstractFrontend*> frontends;
	std::vector<Entity*> objects;
	std::vector<Actor*> actors;
	Team2LuaEnvMap luaTeams;
	std::chrono::time_point<std::chrono::system_clock> start_game;
	std::chrono::time_point<std::chrono::system_clock> end_game;
};

#endif //GAME_H