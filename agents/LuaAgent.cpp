#include "agents/LuaAgent.h"
#include <iostream>
#include <string>
//#include <lua.hpp>
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include "agents/ActorKnowledge.h"
#include "agents/ObjectInfo.h"
#include "main/Navigation.h"
#include "entities/Trigger.h"

using namespace luabind;

typedef std::vector<ActorInfo>::reference (std::vector<ActorInfo>:: *AtFunctionType)(std::vector<ActorInfo>::size_type);

LuaAgent::LuaAgent(std::string filename, lua_State * pL) {
	int error = luaL_loadfile(pL, filename.c_str()) || lua_pcall(pL, 0, LUA_MULTRET, 0);
	if (error) {
		std::cerr << "[Lua] Error " << error << ": " << lua_tostring(pL, -1) << " - during execution of script: " << filename << "\n";
		lua_pop(pL, 1);  /* pop error message from the stack */
	}
	this->luaEnv = pL;
    int pos = filename.find("/");
    if (pos >= 0) {
        filename = filename.substr(pos + 1);
    }
    std::string name = filename;
	name.resize(name.length()-4);
	whatToName = std::string(name + "whatTo");
	onStartName = std::string(name + "onStart");
}

lua_State * LuaAgent::createLuaEnv() {
	lua_State * pL = luaL_newstate();
	luaL_openlibs(pL);
	open(pL);
	module(pL)
	[
		class_<Enumerations>("Enumerations")
			.enum_("ActionType")
			[
				value("Moving", 0),
				value("Shooting", 1),
				value("ChangingWeapon", 2),
				value("Dying", 3),
				value("Reloading", 4),
				value("Waiting", 5)
			]
			.enum_("WeaponType")
			[
				value("Chaingun", 0),
				value("Railgun", 1),
				value("RocketLuncher", 2),
				value("Shotgun", 3),
				value("WeaponSize", 4)
			]
		,
		class_<std::vector<ActorInfo> >("vectorOfActorInfo")
			.def("size", &std::vector<ActorInfo>::size)
			.def("at", (AtFunctionType) &std::vector<ActorInfo>::at)
		,
		class_<std::vector<int> >("vectorOfInt")
			.def("size", &std::vector<int>::size)
			.def("at",(int&(std::vector<int>::*)(size_t))&std::vector<int>::at)
		,
		class_<ActorInfo>("ActorInfo")
			.def(constructor<>())

			.def("getHealth", &ActorInfo::getHealth)
			.def("getPosition", &ActorInfo::getPosition)
			.def("getDirection", &ActorInfo::getDirection)
//			.def("getActionType", &ActorInfo::getActionType)
			.def("getTeam", &ActorInfo::getTeam)
			.def("getName", &ActorInfo::getName)
			.def("getWeaponType", &ActorInfo::getWeaponType)

			.def("setHealth", &ActorInfo::setHealth)
			.def("setPosition", &ActorInfo::setPosition)
			.def("setDirection", &ActorInfo::setDirection)
//			.def("setActionType", &ActorInfo::setActionType)
			.def("setTeam", &ActorInfo::setTeam)
			.def("setWeaponType", &ActorInfo::setWeaponType)
		,
		class_<ObjectInfo>("ObjectInfo")
		,
		class_<ActorKnowledge>("ActorKnowledge")
			.def("getName", &ActorKnowledge::getName)
			.def("getPosition", &ActorKnowledge::getPosition)
			.def("getDirection", &ActorKnowledge::getDirection)
//			.def("getActionType", &ActorKnowledge::getActionType)
			.def("getTeam", &ActorKnowledge::getTeam)
			.def("getWeaponType", &ActorKnowledge::getWeaponType)
			.def("getHealth", &ActorKnowledge::getHealth)
			.def("getAmmo", &ActorKnowledge::getAmmo)
			.def("getSeenFriends", &ActorKnowledge::getSeenFriends)
			.def("getSeenFoes", &ActorKnowledge::getSeenFoes)
			.def("getEstimatedTimeToReach", &ActorKnowledge::getEstimatedTimeToReach)
			.def("getSelf", &ActorKnowledge::getSelf)
			.def("getNavigation", &ActorKnowledge::getNavigation)
			.def("getArmour", &ActorKnowledge::getArmour)
			.def("isMoving", &ActorKnowledge::isMoving)
			.def("isLoaded", &ActorKnowledge::isLoaded)
			.def("getLongDestination", &ActorKnowledge::getLongDestination)
			.def("getShortDestination", &ActorKnowledge::getShortDestination)
		,
		class_<Trigger>("Trigger")
			.enum_("TriggerType")
			[
				value("Weapon", 0),
				value("Armour", 1),
				value("Health", 2)
			]
			.def("getType", &Trigger::getType)
			.def("isActive", &Trigger::isActive)
			.def("getPosition", &Trigger::getPosition)
			.def("getBoundingRadius", &Trigger::getBoundingRadius)
		,
		class_<Navigation>("Navigation")
			.def("anyRayCrateColision", &Navigation::anyRayCrateColision)
			.def("getNodePosition", &Navigation::getNodePosition)
			.def("searchWay", (std::vector<int> (Navigation:: *)(Vector4d, Vector4d)) &Navigation::searchWay)
			.def("getNumberOfTriggers", &Navigation::getNumberOfTriggers)
			.def("getTrigger", &Navigation::getTrigger)
			.def("getNumberOfSpawnPoints", &Navigation::getNumberOfSpawnPoints)
			.def("getSpawnPoint", &Navigation::getSpawnPoint)
			.def("getNumberOfPoints", &Navigation::getNumberOfPoints)
		,
		class_<LuaAgent>("LuaAgent")
			.def("randomDouble", &LuaAgent::randomDouble)
			.def("selectWeapon", &LuaAgent::selectWeapon)
			.def("moveDirection", &LuaAgent::moveDirection)
			.def("moveTo", &LuaAgent::moveTo)
			.def("reload", &LuaAgent::reload)
			.def("rotate", &LuaAgent::rotate)
			.def("shootAt", &LuaAgent::shootAt)
			.def("shootAtPoint", &LuaAgent::shootAtPoint)
			.def("wait", &LuaAgent::wait)
			.def("continueAction", &LuaAgent::continueAction)
		,
		class_<Vector4d>("Vector4d")
			.def("value", &Vector4d::value)
			.def(constructor<double, double, double, double>())
			.def("dot", &Vector4d::dot)
			.def("length", &Vector4d::length)
			.def("lengthSquared", &Vector4d::lengthSquared)
			.def("normal", &Vector4d::normal)
			.def("normalize", &Vector4d::normalize)
			.def(self * double())
			.def(self / double())
			.def(self + other<Vector4d>())
			.def(self - other<Vector4d>())
			.def(self == other<Vector4d>())
	];
	return pL;
}

void LuaAgent::whatToDo(ActorKnowledge * actorKnowledge, GameTime time) {
	try {
		call_function<void>(
			luaEnv 
			, whatToName.c_str()
			, this
			, actorKnowledge
			, static_cast<int>(time)
		);
	} catch (error& e) {
		std::cerr << e.what() << std::endl;
		char n;
		std::cin >> n;
	}
}

void LuaAgent::onStart(ActorKnowledge * actorKnowledge, GameTime time) {
	try {
		call_function<void>(
			luaEnv 
			, onStartName.c_str()
			, this
			, actorKnowledge
			, static_cast<int>(time)
		);
	} catch (error& e) {
		std::cerr << e.what() << std::endl;
		char n;
		std::cin >> n;
	}
}

void LuaAgent::destroyLuaEnv(lua_State * pL) {
	lua_close(pL);
}
