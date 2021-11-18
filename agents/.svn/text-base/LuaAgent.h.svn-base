#ifndef LUA_AGENT_H
#define LUA_AGENT_H
#include "PlayerAgent.h"
#include <string>
#include <vector>

struct lua_State;
/** lua script driven agent
*/
class LuaAgent : public PlayerAgent
{
public:
	LuaAgent(std::string filename, lua_State * pL);
	void whatToDo(ActorKnowledge * actorKnowledge, GameTime time);
	void onStart(ActorKnowledge * actorKnowledge, GameTime time);
	
	static lua_State * createLuaEnv();
	static void destroyLuaEnv(lua_State * pL);
protected:
	lua_State * luaEnv;
	std::string whatToName;
	std::string onStartName;
private:
//	ActorInfo* at_wrapper(std::vector<ActorInfo*> &v, int i);
};

#endif //LUA_AGENT_H