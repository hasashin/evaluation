
CC=g++
CFLAGS= -g -std=c++11 -I. -I/usr/local/include/SDL -I/usr/local/include/lua5.1/ -Wnarrowing -Wreturn-local-addr `sdl-config --static-libs` /usr/local/lib/libSDL_ttf.a /usr/local/lib/libSDL_image.a /usr/local/lib/libSDL_gfx.a /usr/local/lib/libboost_program_options.a /usr/local/lib/libfreetype.a /usr/local/lib/libjpeg.a /usr/local/lib/libwebp.a /usr/local/lib/libtiff.a /usr/local/lib/libpng.a /usr/local/lib/libluabind.a -llua5.1 -lbz2 -lz

all: evaLUAtion

clean:
	rm -rf *.o
	rm evaLUAtion

evaLUAtion: main.o Entity.o Actor.o Action.o Graphics.o UserInteface.o Configuration.o GameFactory.o \
	    Game.o Input.o SDLFrontend.o ImagesManager.o MouseAgent.o  \
	    ActorKnowledge.o LuaAgent.o Misc.o ResourceInfo.o \
	    PlayerAgent.o ActorInfo.o Navigation.o ChangeWeaponAction.o \
	    ReloadAction.o ShootAtAction.o CustomShell.o
	$(CC) -o evaLUAtion main.o Entity.o Actor.o Action.o Configuration.o Graphics.o UserInteface.o GameFactory.o Game.o \
		Input.o SDLFrontend.o ImagesManager.o MouseAgent.o ActorKnowledge.o LuaAgent.o \
		Misc.o ResourceInfo.o PlayerAgent.o ActorInfo.o Navigation.o \
		ChangeWeaponAction.o ReloadAction.o ShootAtAction.o CustomShell.o  \
		 $(CFLAGS)

main.o: main.cpp graphics/Graphics.h 
	$(CC) -c main.cpp $(CFLAGS)

Graphics.o: graphics/Graphics.cpp 
	$(CC) -c graphics/Graphics.cpp $(CFLAGS)

UserInteface.o: graphics/UserInteface.cpp 
	$(CC) -c graphics/UserInteface.cpp $(CFLAGS)

Configuration.o: main/Configuration.cpp
	$(CC) -c main/Configuration.cpp $(CFLAGS)

GameFactory.o: main/GameFactory.cpp  
	$(CC) -c main/GameFactory.cpp $(CFLAGS) 

Game.o: main/Game.cpp
	$(CC) -c main/Game.cpp  $(CFLAGS)

Input.o: main/Input.cpp
	$(CC) -c main/Input.cpp $(CFLAGS)

SDLFrontend.o: graphics/SDLFrontend.cpp
	$(CC) -c graphics/SDLFrontend.cpp $(CFLAGS)

ImagesManager.o: graphics/ImagesManager.cpp
	$(CC) -c graphics/ImagesManager.cpp $(CFLAGS)

MouseAgent.o: agents/MouseAgent.cpp
	$(CC) -c agents/MouseAgent.cpp $(CFLAGS)

ActorKnowledge.o: agents/ActorKnowledge.cpp
	$(CC) -c agents/ActorKnowledge.cpp $(CFLAGS)

LuaAgent.o: agents/LuaAgent.cpp
	$(CC) -c agents/LuaAgent.cpp $(CFLAGS)

Misc.o: main/Misc.cpp
	$(CC) -c main/Misc.cpp $(CFLAGS)

Actor.o: entities/Actor.cpp
	$(CC) -c entities/Actor.cpp $(CFLAGS)

Entity.o: entities/Entity.cpp entities/WeaponPack.h
	$(CC) -c entities/Entity.cpp $(CFLAGS)

ResourceInfo.o: graphics/ResourceInfo.cpp 
	$(CC) -c graphics/ResourceInfo.cpp $(CFLAGS)

ActorInfo.o: agents/ActorInfo.cpp
	$(CC) -c agents/ActorInfo.cpp $(CFLAGS)

PlayerAgent.o: agents/PlayerAgent.cpp 
	$(CC) -c agents/PlayerAgent.cpp $(CFLAGS)

Navigation.o: main/Navigation.cpp
	$(CC) -c main/Navigation.cpp $(CFLAGS)

Action.o: actions/Action.cpp
	$(CC) -c actions/Action.cpp $(CFLAGS)

ChangeWeaponAction.o: actions/ChangeWeaponAction.cpp
	$(CC) -c actions/ChangeWeaponAction.cpp $(CFLAGS)

ReloadAction.o: actions/ReloadAction.cpp
	$(CC) -c actions/ReloadAction.cpp $(CFLAGS)

ShootAtAction.o: actions/ShootAtAction.cpp
	$(CC) -c actions/ShootAtAction.cpp $(CFLAGS)

CustomShell.o: entities/CustomShell.cpp
	$(CC) -c entities/CustomShell.cpp $(CFLAGS)
