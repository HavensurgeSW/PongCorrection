#pragma once
#include "players.h"
#include <iostream>
using namespace std;
Player players[1];

void setPlayerParameters() {

	cout << GetFrameTime() << endl;
	players[0].paddleSpeed.y = 7;
	players[0].paddleSpeed.x = 3;
	players[0].paddleSize = { 10.0f, 85.0f };

	players[1].paddleSpeed.y = 7;
	players[1].paddleSpeed.x = 3;
	players[1].paddleSize = { 10.0f, 85.0f };

	players[0].rec.width = players[0].paddleSize.x;
	players[0].rec.height = players[0].paddleSize.y;
	players[1].rec.width = players[1].paddleSize.x;
	players[1].rec.height = players[1].paddleSize.y;

	players[0].rec.x = (float)GetScreenWidth() / 20;
	players[0].rec.y = (float)GetScreenHeight() / 2;
	players[1].rec.x = (float)GetScreenWidth() - 40;
	players[1].rec.y = (float)GetScreenHeight() / 2;

	players[0].score = 0;
	players[1].score = 0;
	players[0].powerUp = false;
	players[1].powerUp = false;

	players[0].shield = false;
	players[0].shields.height = GetScreenHeight();
	players[0].shields.width = 5;
	players[0].shields.x = 0;
	players[0].shields.y = 0;

	players[1].shield = false;
	players[1].shields.height = GetScreenHeight();
	players[1].shields.width = 5;
	players[1].shields.x = GetScreenWidth() - 5;
	players[1].shields.y = 0;

	players[0].color = RED;
	players[1].color = BLUE;

}
void setPlayerParameters2() {
	players[0].paddleSpeed.y = 7;
	players[0].paddleSpeed.x = 3;
	players[0].paddleSize = { 10.0f, 85.0f };

	players[1].paddleSpeed.y = 7;
	players[1].paddleSpeed.x = 3;
	players[1].paddleSize = { 10.0f, 85.0f };

	players[0].rec.width = players[0].paddleSize.x;
	players[0].rec.height = players[0].paddleSize.y;
	players[1].rec.width = players[1].paddleSize.x;
	players[1].rec.height = players[1].paddleSize.y;

	players[0].rec.x = (float)GetScreenWidth() / 20;
	players[0].rec.y = (float)GetScreenHeight() / 2;
	players[1].rec.x = (float)GetScreenWidth() - 40;
	players[1].rec.y = (float)GetScreenHeight() / 2;

	players[0].score = 0;
	players[1].score = 0;
	players[0].powerUp = false;
	players[1].powerUp = false;

	players[0].shield = false;
	players[0].shields.height = GetScreenHeight();
	players[0].shields.width = 5;
	players[0].shields.x = 0;
	players[0].shields.y = 0;

	players[1].shield = false;
	players[1].shields.height = GetScreenHeight();
	players[1].shields.width = 5;
	players[1].shields.x = GetScreenWidth() - 5;
	players[1].shields.y = 0;
}
void playerMovement() {
	if (IsKeyDown(KEY_W))players[0].rec.y -= GetFrameTime() * 420;;
	if (IsKeyDown(KEY_S))players[0].rec.y += GetFrameTime() * 420;;
	if (IsKeyDown(KEY_UP))players[1].rec.y -= GetFrameTime() * 420;;
	if (IsKeyDown(KEY_DOWN))players[1].rec.y += GetFrameTime() * 420;;
}
void drawPlayerObjects() {
	DrawRectangleRec(players[0].rec, players[0].color);
	DrawRectangleRec(players[1].rec, players[1].color);

	if (players[0].shield) {
		DrawRectangleRec(players[0].shields, players[0].color);
	}
	if (players[1].shield) {
		DrawRectangleRec(players[1].shields, players[1].color);
	}

	if (players[0].powerUp) {
		DrawLine(GetScreenWidth() / 2 - 20, 0, GetScreenWidth() / 2 - 20, GetScreenHeight(), players[0].color);
	}

	if (players[1].powerUp) {
		DrawLine(GetScreenWidth() / 2 + 20, 0, GetScreenWidth() / 2 + 20, GetScreenHeight(), players[1].color);
	}
}
