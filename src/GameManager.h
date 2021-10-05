#pragma once
#include "raylib.h"
#include "objects/players.h"
#include "objects/Ball.h"
#include <iostream>
#include  "Music.h"
using namespace std;

enum class screenID {
	splash,
	menu,
	game,
	options,
	pause,
	credits,
	exit
};


void drawGame();
void collisions();
void timePU(int id);
void input();
void hazards();
void update();

void gameScreen();

void initGameObjects();
void splashScreen();
void menuScreen();
void optionsScreen();
void gameLoop();
void initGame();