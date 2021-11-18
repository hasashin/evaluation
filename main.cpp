/***************************************************************************
 *   Copyright (C) 2007 by Piotr Sienkowski				                   *
 *   piotr.sienkowski (at) gmail.com                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <iostream>
#include <SDL.h>
#include "graphics/Graphics.h"
#include "main/Input.h"
#include "main/Game.h"
#include "main/GameFactory.h"
#include "graphics/UserInterface.h"
#include "graphics/SDLFrontend.h"
#include "main/Configuration.h"
#include <csignal>

unsigned int maxFrames = 30;
Uint32 ticks = 0;
unsigned int frames = 0;
char caption[100];
bool done = false;
//TODO lynx dodac logger
//TODO doadaj pauze
/** keeps framerate at set level
*/
void keepFramerate() {
		Uint32 currTicks = SDL_GetTicks();
        if (currTicks - ticks > 1000) {
            snprintf(caption, 100, "Framerate %d", frames);
            SDL_WM_SetCaption(caption, 0);
            frames = 0;
            ticks = currTicks;
        }

        if (currTicks - ticks < frames * 1000 / maxFrames) {
            int time = frames * 1000 / maxFrames - (currTicks - ticks);
			SDL_Delay(time);
		}
		frames++;
}

static void term_handler(int i)
{
	done = true;
}

int main ( int argc, char** argv )
{
	std::signal(SIGINT, term_handler);
	//configuration
	Configuration::getInstance().addOptions(argc, argv);
	Configuration::getInstance().addOptions(ConfString("config-file"));

	//component initialization
	Graphics graphics;
	Input input;
	UserInterface ui(&graphics);
	input.setUserInterface(&ui);
	SDLFrontend * sdlFrontend = new SDLFrontend(&graphics);

	//buidling game instance from configuration
	GameFactory::getInstance().createGame(&ui);
	Game * game = GameFactory::getInstance().getCurrentGame();
	game->addFrontend(sdlFrontend);

	//game main loop
	game->startGame();
    int countdown = 20;
	while (countdown > 0 || done)
    {
		keepFramerate();
		game->updateWorld();

		game->runFrontends();
		bool tempdone = input.update();
		done = done ? tempdone : done;
		ui.update( game->getActors());
		
		ui.showTime(game->getTimeToEnd());
		graphics.update();

		game->updateAI();

        if (game->isFinished())
            countdown--;
    }
	game -> endGame();

	game->printResults();
	std::cerr << "Exit ok .\n";
	return 0;
}
