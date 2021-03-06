#include "main/Game.h"
#include "main/AbstractFrontend.h"
#include "entities/Entity.h"
#include "entities/Actor.h"
#include "actions/DieAction.h"
#include "actions/WaitAction.h"
#include "main/Configuration.h"
#include "agents/LuaAgent.h"
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <fstream>

/** returns all objects in game world
*/
std::vector<Entity*> & Game::getObjects() {
	return objects;
}

/** returns all active object in game world
*/
std::vector<Actor*> & Game::getActors() {
	return actors;
}
/** constructor
*/
Game::Game() {
	gameTime = 0;
}
void Game::printResults() {
	std::chrono::duration<double> diff = end_game - start_game;
	std::ofstream result_file;
	result_file.open("result.txt");

	std::cout << "TIME: " << diff.count() << " s." << std::endl;
	result_file << "TIME: " << diff.count() << " s." << std::endl;
	std::unordered_map<int, int> team_points;

	for (unsigned int i = 0; i < actors.size(); ++i) {
		std::cout << actors[i]->getName() << " Kills: " << actors[i]->getKills() << " Killed: " << actors[i]->getKilled() << " Friend kills: " << actors[i]->getFriendKills() << std::endl;
		int team_id = actors[i]->getTeam();

		if (team_points.find(team_id) == team_points.end())
			team_points[team_id] = 0;
		if (!actors[i]->isDead())
			team_points[team_id]++;
	}
	std::ostringstream final_s;
	std::ostringstream score_s;
	final_s << "RESULT: ";

	for (const auto &myPair : team_points) {
		final_s << myPair.first << " ";
		score_s << myPair.second << " ";
	}

	std::cout << final_s.str() << score_s.str() << std::endl;
	result_file << final_s.str() << score_s.str() << std::endl;
	result_file.close();
}

/** cleans up
*/
Game::~Game() {
	for (unsigned int i = 0; i < frontends.size(); ++i) {
		delete frontends[i];
	}
	frontends.clear();
	for (unsigned int i = 0; i < objects.size(); ++i) {
		delete objects[i];
	}
	Team2LuaEnvMap::iterator it;
	for (it = luaTeams.begin(); it != luaTeams.end(); ++it)
	{
		LuaAgent::destroyLuaEnv(it->second);
	}
	luaTeams.clear();
	objects.clear();
	actors.clear();
}
/** adds game frontend
*/
void Game::addFrontend(AbstractFrontend * frontend) {
	frontends.push_back(frontend);
}
/** updates game world
*/
void Game::updateWorld() {
	gameTime++;//TODO PS L co jak przepelnienie, po kilku latach :D
	for (int i = objects.size() - 1; i >= 0; --i) {
		if (objects[i]->isValid()) {
			objects[i]->update(gameTime);
		}
		else {
			objects.erase(objects.begin() + i);
		}
	}
}
/** runs frontends (graphics now only)
*/
void Game::runFrontends() {
	for (unsigned int i = 0; i < frontends.size(); ++i) {
		frontends[i]->run(this);
	}
}

/** checks if game is finnished
*/
bool Game::isFinished() {

	std::chrono::duration<double> diff = std::chrono::system_clock::now() - start_game;
	if (diff.count() > Configuration::getInstance().getInt("time"))
		return true;

	for (unsigned int i = 0; i < actors.size(); ++i) {
		for (unsigned int j = i; j < actors.size(); ++j) {
			if ((actors[i]->getTeam() != actors[j]->getTeam()) && (actors[i]->getHealth() > 0 && actors[j]->getHealth() > 0)) {
				return false;
			}
		}
	}
	return true;
}
/** gets new commands for actors
*/
void Game::updateAI() {
	for (unsigned int i = 0; i < actors.size(); ++i) {
		Action * currentAction = actors[i]->getCurrentAction();
		actors[i]->updateSpotting();
		if (currentAction == NULL || currentAction->isBreakable()) {
			actors[i]->act(gameTime);
		}
	}

}

void Game::inflictDamage(Actor* actor, int damage, GameTime time, Actor* attacker) {
	int absorb = 0;
	int armour = actor->getArmour();
	if (armour > 0) {
		absorb = (damage / 2 > armour ? armour : damage / 2);
		armour -= absorb;
	}
	actor->setHealth(actor->getHealth() - (damage - absorb));
	actor->setArmour(armour);
	if (actor->getHealth() <= 0) {
		if (!ConfIsSet("respawns")) {
			if (actor->isDead()) {
				return;
			}
			actor->resetCurrentAction(new DieAction());
			actor->getCurrentAction()->onEnter(actor, time);
		}
		else {
			Vector4d random(40 * RandomDouble() - 20, 40 * RandomDouble() - 20);
			int sw = navigation->getNumberOfSpawnPoints() * RandomDouble();
			actor->reset(navigation->getSpawnPoint(sw) + random, time);
		}
		if (actor->getTeam() != attacker->getTeam()) {
			attacker->incrementKills();
		}
		else {
			actor->incrementFriendsKilled();
		}
		actor->incrementKilled();
	}
}

int Game::getTimeToEnd()
{
	std::chrono::duration<double> diff = std::chrono::system_clock::now() - start_game;
	int game_time = Configuration::getInstance().getInt("time");
	return game_time - (int)diff.count();
}
