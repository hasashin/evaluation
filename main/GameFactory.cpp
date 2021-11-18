#include <fstream>
#include "main/GameFactory.h"
#include "entities/Actor.h"
#include "entities/Wall.h"
#include "entities/HealthPack.h"
#include "entities/WeaponPack.h"
#include "entities/ArmourPack.h"
#include "agents/LuaAgent.h"
#include "agents/MouseAgent.h"
//#include "agents/FuzzyAgent.h"
#include "main/RandomGenerator.h"
#include "main/Configuration.h"
#include "main/Navigation.h"
#include "graphics/UserInterface.h"

/**create game instance according to configuration
*/
void GameFactory::createGame(UserInterface * ui) {
	game.reset(new Game());
	createMap();
	createActors(ui);
	double scaleY = ui->getHeight() / game->height;
	double scaleX = ui->getWidth() / game->width;
	ui->setOOPoint(0, 0, (scaleX < scaleY ? scaleX : scaleY));
}

/**returns current game
*/
Game * GameFactory::getCurrentGame() {
	return game.get();
}
/** adds object to the game
*/
void GameFactory::addObject(Entity * obj) {
	obj->navigation = game->navigation.get();
	game->objects.push_back(obj);
}
/** adds actor to the game
*/
void GameFactory::addActor(Actor * actor) {
	game->actors.push_back(actor);
	addObject(actor);
}

void GameFactory::createMap() {
	std::ifstream mapfile;
	mapfile.open(ConfString("map.filename").c_str());
	int indexPointsNr;
	mapfile >> indexPointsNr;
	std::string s1, s2, s3, s4, s5;
	double x, y;
	int indexNr;
	game->navigation.reset(new Navigation(indexPointsNr));
	for (int i = 0; i < indexPointsNr; i++) {
		mapfile >> s1 >> indexNr >> s2 >> x >> s3 >> y;
		game->navigation->nodes.push_back(NavigationNode(x, y, indexNr));
	}
	int transitionsNr;
	mapfile >> transitionsNr;
	int index1, index2, i1, i2, i3;
	double cost;
	for (int i = 0; i < transitionsNr; i++) {
		mapfile >> s1 >> index1 >> s2 >> index2 >> s3 >> cost >> s4 >> i1 >> s5 >> i2;
			game->navigation->nodes[index1].arcs.push_back(NavigationNode::Arc(index2,cost));
	}
	double x1,y1,x2,y2,dim0,dim1;
	int type;
	mapfile >> x1 >> y1;
	game->width = x1;
	game->height = y1;
	Trigger * tr;
	while (mapfile >> type) {
		switch (type) {
			case 0 ://sciana
				{
				mapfile >> x1 >> y1 >> x2 >> y2 >> dim0 >> dim1;
				Vector4d a(x1, y1);
				Vector4d b(x2, y2);
				addObject(new Wall(a, b));
				break;
				}
			case 4 ://apteczka
				mapfile >> i1 >> x1 >> y1 >> i2 >> i3 >> index1;
				tr = new HealthPack(x1, y1, index1);
				game->navigation->triggers.push_back(tr);
				addObject(tr);
				break;
			case 5 ://spawn point
				mapfile >> i1 >> x1 >> y1 >> i2 >> i3;
				game->navigation->spawns.push_back(Vector4d(x1,y1));
				break;
			case 6 ://railgun
				mapfile >> i1 >> x1 >> y1 >> i2 >> index1;
				tr = new WeaponPack(x1, y1, Enumerations::WeaponType::Railgun, index1);
				game->navigation->triggers.push_back(tr);
				addObject(tr);
				break;
			case 7 ://rocket
				mapfile >> i1 >> x1 >> y1 >> i2 >> index1;
				tr = new WeaponPack(x1, y1, Enumerations::WeaponType::RocketLuncher, index1);
				game->navigation->triggers.push_back(tr);
				addObject(tr);
				break;
			case 8 ://shotgun
				mapfile >> i1 >> x1 >> y1 >> i2 >> index1;
				tr = new WeaponPack(x1, y1, Enumerations::WeaponType::Shotgun, index1);
				game->navigation->triggers.push_back(tr);
				addObject(tr);
				break;
			case 9 ://chaingun
				mapfile >> i1 >> x1 >> y1 >> i2 >> index1;
				tr = new WeaponPack(x1, y1, Enumerations::WeaponType::Chaingun, index1);
				game->navigation->triggers.push_back(tr);
				addObject(tr);
				break;
			case 10 ://armour
				mapfile >> i1 >> x1 >> y1 >> i2 >> index1;
				tr = new ArmourPack(x1, y1, index1);
				game->navigation->triggers.push_back(tr);
				addObject(tr);
				break;
		} 
	}
	mapfile.close();
}

void GameFactory::createActors(UserInterface * ui) {
	std::ifstream actorfile;//TODO zabezpieczyæ przed brakiem pliku
	actorfile.open(ConfString("map.actors.file").c_str());
	int team;
	double x,y;
	std::string control;
	std::string resourceName, name;
	Actor * actor;
	AbstractAgent * agent;
	while (actorfile >> name >> control >> team >> x >> y >> resourceName) {//TODO zabezpieczyæ przed nie poprawnymi plikami
		std::string actorType = control.substr(0, 2);
		if (actorType.compare("ms") == 0) {
			agent = new MouseAgent();
			ui->registerAgent(static_cast<MouseAgent*>(agent));
		} else if (actorType.compare("sc") == 0) {
			std::string scriptFile = control.substr(3);
			lua_State * luaEnv = NULL;

			Team2LuaEnvMap::const_iterator luaTeamsIterator;
			luaTeamsIterator = game->luaTeams.find(team);
			if ( luaTeamsIterator == game->luaTeams.end( ) )
			{
				luaEnv = LuaAgent::createLuaEnv();
				game->luaTeams.insert(std::pair <int, lua_State*>(team, luaEnv));
			} else {
				luaEnv = luaTeamsIterator->second;
			}
			agent = new LuaAgent(scriptFile, luaEnv);
		} /*else if (actorType.compare("fz") == 0) {
			agent = new FuzzyAgent();
		}*/
		Vector4d pos(x,y);
		actor = new Actor(agent, team, pos);
		actor->name = name;
		actor->setResourceName(resourceName);
		addActor(actor);
	}
	actorfile.close();
}