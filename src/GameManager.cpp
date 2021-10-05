#pragma once
#include "GameManager.h"

screenID screenId;

bool launchDirec;
bool gamemode = true;
int winner = 0;
Color winColor = WHITE;
int randomPU = 0;
int colFix = 0;


/////GAME LOOP//////
void drawGame() {
	BeginDrawing();

	ClearBackground(BLACK);

	DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), LIGHTGRAY);
	DrawText(FormatText("%i", players[0].score), (GetScreenWidth() / 2) - 60, 20, 40, players[0].color);
	DrawText(FormatText("%i", players[1].score), (GetScreenWidth() / 2) + 40, 20, 40, players[1].color);
	ballDraw();
	drawPlayerObjects();

	if (ball.ballStop) {
		DrawText("PRESS ENTER to LAUNCH", GetScreenWidth() / 2 - 120, GetScreenHeight() - 25, 20, LIGHTGRAY);
		if (!launchDirec)
			DrawTriangleLines({ GetScreenWidth() / 2 - 60.0f, GetScreenHeight() / 2.0f }, { GetScreenWidth() / 2 - 30.0f, GetScreenHeight() / 2 + 15.0f }, { GetScreenWidth() / 2 - 30.0f, GetScreenHeight() / 2 - 15.0f }, players[0].color);
		if (launchDirec)
			DrawTriangleLines({ GetScreenWidth() / 2 + 60.0f, GetScreenHeight() / 2.0f }, { GetScreenWidth() / 2 + 30.0f, GetScreenHeight() / 2 + 15.0f }, { GetScreenWidth() / 2 + 30.0f, GetScreenHeight() / 2 - 15.0f }, players[1].color);
	}

	EndDrawing();

}
void collisions() {
	//Scoring collisions
	if (multiball.ballPosition.x >= (GetScreenWidth() - ball.ballRadius)) {
		players[0].score++;
		multiball.ballPosition.x = (GetScreenWidth() / 2);
		multiball.ballPosition.y = (GetScreenHeight() / 2);
		multiball.active = false;
	}
	if (ball.ballPosition.x >= (GetScreenWidth() - ball.ballRadius)) {
		players[0].score++;
		ball.ballPosition.x = (GetScreenWidth() / 2);
		ball.ballPosition.y = (GetScreenHeight() / 2);

		ball.ballStop = true;
		multiball.active = false;
		launchDirec = true;
		players[0].powerUp = true;
		randomPU = 0;
		players[1].shield = true;

	}
	if (multiball.ballPosition.x <= (0 - multiball.ballRadius)) {
		players[1].score++;
		multiball.ballPosition.x = (GetScreenWidth() / 2);
		multiball.ballPosition.y = (GetScreenHeight() / 2);
		multiball.active = false;
	}

	if (ball.ballPosition.x <= (0 - ball.ballRadius)) {
		players[1].score++;
		ball.ballPosition.x = (GetScreenWidth() / 2);
		ball.ballPosition.y = (GetScreenHeight() / 2);

		ball.ballStop = true;
		launchDirec = false;
		multiball.active = false;
		players[1].powerUp = true;
		players[0].shield = true;
		randomPU = 0;


	}
	// Check walls collision for bouncing
	if ((ball.ballPosition.y >= (GetScreenHeight() - ball.ballRadius)) || (ball.ballPosition.y <= ball.ballRadius)) ball.ballSpeed.y *= -1.0f;
	if ((multiball.ballPosition.y >= (GetScreenHeight() - multiball.ballRadius)) || (multiball.ballPosition.y <= multiball.ballRadius)) multiball.ballSpeed.y *= -1.0f;


	// Ball v Paddles
	if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, players[0].rec) && ball.col) {
		ball.ballSpeed.x *= -1.0f;
		if (players[0].rec.x != GetScreenWidth() / 20) players[0].rec.x = GetScreenWidth() / 20;
		randomPU++;
		ball.col = false;
	}

	if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, players[0].shields) && players[0].shield) {
		ball.ballSpeed.x *= -1.0f;
		players[0].shield = false;
	}

	if (CheckCollisionCircleRec(multiball.ballPosition, multiball.ballRadius, players[0].shields) && players[0].shield) {
		multiball.ballSpeed.x *= -1.0f;
		players[0].shield = false;
	}

	if (CheckCollisionCircleRec(multiball.ballPosition, multiball.ballRadius, players[0].rec) && multiball.col) {
		multiball.ballSpeed.x *= -1.0f;
		multiball.col = false;
	}


	if (CheckCollisionCircleRec(multiball.ballPosition, multiball.ballRadius, players[1].rec) && multiball.col) {
		multiball.ballSpeed.x *= -1.0f;
		multiball.col = false;
	}

	if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, players[1].shields) && players[1].shield) {
		ball.ballSpeed.x *= -1.0f;
		players[1].shield = false;
	}
	if (CheckCollisionCircleRec(multiball.ballPosition, multiball.ballRadius, players[1].shields) && players[1].shield) {
		multiball.ballSpeed.x *= -1.0f;
		players[1].shield = false;
	}
	if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, players[1].rec) && ball.col) {
		ball.ballSpeed.x *= -1.0f;

		if (players[1].rec.x != GetScreenWidth() - 40) {
			players[1].rec.x = GetScreenWidth() - 40;
		}
		randomPU++;
		ball.col = false;
	}


	//player vs wall Collisions
	if (players[0].rec.y <= 0)players[0].rec.y = 0;
	if (players[0].rec.y >= GetScreenHeight() - players[0].paddleSize.y)players[0].rec.y = (GetScreenHeight() - players[0].paddleSize.y);
	if (players[1].rec.y <= 0)players[1].rec.y = 0;
	if (players[1].rec.y >= GetScreenHeight() - players[1].paddleSize.y)players[1].rec.y = (GetScreenHeight() - players[1].paddleSize.y);

}
void timePU(int id) {
	float timer = 0.0f;
	Vector2 ballPosTemp = ball.ballPosition;
	float ballSXTemp = ball.ballSpeed.x;
	float ballSYTemp = ball.ballSpeed.y;
	ball.ballSpeed.x = 0;
	ball.ballSpeed.y = 0;

	SetMusicVolume(gameMusic, 0.05f);

	if (id == 0) {
		bool warudoBool0 = true;
		if (players[0].powerUp == true) {
			do {

				UpdateMusicStream(gameMusic);

				if (IsKeyDown(KEY_W)) players[0].rec.y -= players[0].paddleSpeed.y;
				if (IsKeyDown(KEY_S)) players[0].rec.y += players[0].paddleSpeed.y;
				if (IsKeyDown(KEY_A)) players[0].rec.x -= GetFrameTime() * 270.0f;
				if (IsKeyDown(KEY_D)) players[0].rec.x += GetFrameTime() * 270.0f;
				if (players[0].rec.y <= 0) {
					players[0].rec.y = 1;
				}
				if (players[0].rec.y >= GetScreenHeight() - players[0].paddleSize.y) {
					players[0].rec.y = GetScreenHeight() - players[0].paddleSize.y - 0.1f;
				}

				if (players[0].rec.x <= 0) {
					players[0].rec.x = 1;
				}
				if (players[0].rec.x >= GetScreenWidth() / 2 - 20) {
					players[0].rec.x = GetScreenWidth() / 2 - 21;
				}

				drawGame();
				timer += GetFrameTime();
				if (timer >= 2.5f) {
					warudoBool0 = false;
				}


			} while (warudoBool0);
			players[0].powerUp = false;
		}
	}
	if (id == 1) {
		bool warudoBool1 = true;
		if (players[1].powerUp == true) {
			do {
				UpdateMusicStream(gameMusic);

				if (IsKeyDown(KEY_UP)) players[1].rec.y -= players[1].paddleSpeed.y;
				if (IsKeyDown(KEY_DOWN)) players[1].rec.y += players[1].paddleSpeed.y;
				if (IsKeyDown(KEY_LEFT)) players[1].rec.x -= players[1].paddleSpeed.x;
				if (IsKeyDown(KEY_RIGHT)) players[1].rec.x += players[1].paddleSpeed.x;
				if (players[1].rec.y <= 0) {
					players[1].rec.y = 1;
				}
				if (players[1].rec.y >= GetScreenHeight() - players[1].paddleSize.y) {
					players[1].rec.y = GetScreenHeight() - players[1].paddleSize.y - 0.1f;
				}

				if (players[1].rec.x <= 0) {
					players[1].rec.x = 1;
				}
				if (players[1].rec.x <= GetScreenWidth() / 2 + 20) {
					players[1].rec.x = GetScreenWidth() / 2 + 21;
				}

				drawGame();
				timer += GetFrameTime();
				if (timer >= 2.5f) {
					warudoBool1 = false;
				}


			} while (warudoBool1);
			players[1].powerUp = false;
		}
	}
	ball.ballPosition = ballPosTemp;
	ball.ballSpeed.x = ballSXTemp;
	ball.ballSpeed.y = ballSYTemp;
	SetMusicVolume(gameMusic, 0.2f);
}
void input() {
	//MOVEMENT
	if (IsKeyDown(KEY_W))players[0].rec.y -= players[0].paddleSpeed.y;
	if (IsKeyDown(KEY_S))players[0].rec.y += players[0].paddleSpeed.y;

	if (gamemode) {
		if (IsKeyDown(KEY_UP))players[1].rec.y -= players[1].paddleSpeed.y;
		if (IsKeyDown(KEY_DOWN))players[1].rec.y += players[1].paddleSpeed.y;
		if (IsKeyPressed(KEY_L) && players[1].powerUp) {
			timePU(1);
		}
	}
	if (!gamemode) {
		if (ball.ballPosition.y > players[1].rec.y) {
			players[1].rec.y += players[1].paddleSpeed.y - 2;
		}
		if (ball.ballPosition.y < players[1].rec.y) {
			players[1].rec.y -= players[1].paddleSpeed.y - 2;
		}
	}
	if (ball.ballStop) {
		if (IsKeyPressed(KEY_ENTER)) ball.ballStop = false;
	}
	if (IsKeyPressed(KEY_G) && players[0].powerUp) {
		timePU(0);
	}
	if (WindowShouldClose())
		screenId = screenID::exit;
}
void hazards() {
	switch (GetRandomValue(1, 1)) {
	case 1:
		multiball.active = true;
		cout << multiball.ballSpeed.x << endl;
		break;

	}
}
void update() {
	ballMove();
	if (randomPU >= 6) {
		hazards();
		randomPU = 0;
	}

	if (!ball.col){
		colFix++;
		if (colFix > GetFrameTime()*300){
			ball.col = true;
			colFix = 0;
		}
	}

	if (!multiball.col) {
		colFix++;
		if (colFix > GetFrameTime() * 300){ 
			multiball.col = true;
			colFix = 0;
		}
	}


	if (players[1].score >= 10 || players[0].score >= 10) {
		if (players[1].score>=10){
			winner = 1;
			winColor = players[1].color;
		}
		if (players[0].score >= 10) {
			winner = 2;
			winColor = players[0].color;
		}
		screenId = screenID::menu;
	}
}

void gameScreen() {
	bool pauseBool = false;
	setPlayerParameters2();
	while (!WindowShouldClose() && screenId == screenID::game && gamemode) {
		UpdateMusicStream(gameMusic);


		if (!pauseBool) {
			input();
			if (IsKeyPressed(KEY_P)) {
				pauseBool = true;
				fflush(stdin);
			}
			update();
			if (WindowShouldClose())
				screenId = screenID::exit;
			collisions();
			drawGame();
		}
		else {
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText(FormatText("%i", players[0].score), (GetScreenWidth() / 2) - 60, 20, 40, players[0].color);
			DrawText(FormatText("%i", players[1].score), (GetScreenWidth() / 2) + 40, 20, 40, players[1].color);
			DrawRectangleLines(players[0].rec.x, players[0].rec.y, players[0].rec.width, players[0].rec.height, players[0].color);
			DrawRectangleLines(players[1].rec.x, players[1].rec.y, players[1].rec.width, players[1].rec.height, players[1].color);
			DrawCircleLines(ball.ballPosition.x, ball.ballPosition.y, ball.ballRadius, WHITE);

			DrawText("PAUSED", GetScreenWidth() / 3.0f + 20, GetScreenHeight() / 3.0f, 60, WHITE);
			DrawText("RESUME [P]", GetScreenWidth() / 3.0f + 50, GetScreenHeight() / 3.0f + 120, 30, WHITE);
			DrawText("MENU [M]", GetScreenWidth() / 3.0f + 70, GetScreenHeight() - 60.0f, 30, WHITE);
			EndDrawing();

			if (IsKeyPressed(KEY_P)) {
				pauseBool = false;
			}
			if (IsKeyPressed(KEY_M)) {
				screenId = screenID::menu;
			}
			if (WindowShouldClose())
				screenId = screenID::exit;
		}

	}
	while (!WindowShouldClose() && screenId == screenID::game && !gamemode) {
		UpdateMusicStream(gameMusic);
		if (!pauseBool) {
			input();
			if (IsKeyReleased(KEY_P)) {
				pauseBool = true;
				fflush(stdin);
			}
			update();
			if (WindowShouldClose())
				screenId = screenID::exit;
			collisions();
			drawGame();
		}
		else {
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText(FormatText("%i", players[0].score), (GetScreenWidth() / 2) - 60, 20, 40, players[0].color);
			DrawText(FormatText("%i", players[1].score), (GetScreenWidth() / 2) + 40, 20, 40, players[1].color);
			DrawRectangleLines(players[0].rec.x, players[0].rec.y, players[0].rec.width, players[0].rec.height, players[0].color);
			DrawRectangleLines(players[1].rec.x, players[1].rec.y, players[1].rec.width, players[1].rec.height, players[1].color);
			DrawCircleLines(ball.ballPosition.x, ball.ballPosition.y, ball.ballRadius, WHITE);

			DrawText("PAUSED", GetScreenWidth() / 3.0f + 20, GetScreenHeight() / 3.0f, 60, WHITE);
			DrawText("RESUME [P]", GetScreenWidth() / 3.0f + 70, GetScreenHeight() / 3.0f + 120, 30, WHITE);
			DrawText("MENU [M]", GetScreenWidth() / 3.0f + 90, GetScreenHeight() - 60.0f, 30, WHITE);
			EndDrawing();

			if (IsKeyReleased(KEY_P)) {
				pauseBool = false;
				fflush(stdin);
			}
			if (IsKeyPressed(KEY_M)) {
				screenId = screenID::menu;
			}

			if (WindowShouldClose())
				screenId = screenID::exit;
		}

	}

}

void initGameObjects() {
	setPlayerParameters();
	setBallParameters();
	launchDirec = false;
	InitAudioDevice();
	loadMusic();
}
void splashScreen() {
	int framesCounter = 0;

	while (screenId == screenID::splash && !WindowShouldClose())
	{
		framesCounter++;

		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("HSS Presents", GetScreenWidth() / 3, GetScreenHeight() / 2 - (GetScreenHeight() / 10), GetScreenWidth() / 24, WHITE);

		EndDrawing();

		if (((framesCounter / 180) % 3) == 1) { //60 fps on 5 seconds
			screenId = screenID::menu;
		}

		if (WindowShouldClose())
			screenId = screenID::exit;

	}


}
void menuScreen() {
	bool menuBool = true;
	bool creditsBool = false;


	Rectangle playButton;
	playButton.x = GetScreenWidth() / 100 * 2.5f;
	playButton.y = GetScreenHeight() / 2;
	playButton.height = 30;
	playButton.width = 65;
	Rectangle optionsButton;
	optionsButton.x = GetScreenWidth() / 100 * 2.5f;
	optionsButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 11.1f);
	optionsButton.height = 30;
	optionsButton.width = 113;

	Rectangle creditsButton;
	creditsButton.x = GetScreenWidth() / 100 * 2.5f;
	creditsButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 22.2f);
	creditsButton.height = 30;
	creditsButton.width = 113;
	Rectangle closeButton;
	closeButton.x = GetScreenWidth() / 100 * 2.5f;
	closeButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 37.3f);
	closeButton.height = 30;
	closeButton.width = 81.25f;

	PlayMusicStream(gameMusic);
	SetMusicVolume(gameMusic, 0.2f);



	while (!WindowShouldClose() && screenId == screenID::menu) {
		UpdateMusicStream(gameMusic);
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(FormatText("PONG"), 20, GetScreenHeight() / 10, 120, winColor);

		if (CheckCollisionPointRec(GetMousePosition(), playButton))
			DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, RED);
		else
			DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), optionsButton))
			DrawText(FormatText("Options"), 20, (GetScreenHeight() / 2) + 50, 30, RED);
		else
			DrawText(FormatText("Options"), 20, (GetScreenHeight() / 2) + 50, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, RED);
		else
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), closeButton))
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, RED);
		else
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, WHITE);



		DrawText(FormatText("v 1.0"), GetScreenWidth() - 50, 1, 20, WHITE);


		if (CheckCollisionPointRec(GetMousePosition(), playButton)) {
			DrawText(FormatText("GAME DETAILS"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 20, 30, WHITE);
			DrawText(FormatText("Gamemode: "), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 60, 20, WHITE);
			if (gamemode) {
				DrawText(FormatText("PvP"), (GetScreenWidth() / 2 + 150), (GetScreenHeight() / 4) + 60, 20, WHITE);
			}
			else {
				DrawText(FormatText("PvAI"), (GetScreenWidth() / 2 + 150), (GetScreenHeight() / 4) + 60, 20, WHITE);
			}

			DrawText(FormatText("Player 1"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 100, 20, players[0].color);
			DrawText(FormatText("[W/S] [G]"), (GetScreenWidth() / 2 + 130), (GetScreenHeight() / 4) + 100, 20, players[0].color);
			DrawText(FormatText("Player 1"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 140, 20, players[1].color);
			DrawText(FormatText("[UP/DOWN] [L]"), (GetScreenWidth() / 2 + 130), (GetScreenHeight() / 4) + 140, 20, players[1].color);

			DrawText(FormatText("[P]ause"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 180, 20, WHITE);


		}

		if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			screenId = screenID::game;
		}

		if (CheckCollisionPointRec(GetMousePosition(), optionsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			screenId = screenID::options;
		}


		if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) {
			DrawText(FormatText("Engine: Raylib 3.7"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 20, 30, WHITE);
			DrawText(FormatText("Created by:"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 100, 30, WHITE);
			DrawText(FormatText("Matias P. Karplus"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 130, 30, WHITE);
		}


		if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			exit(0);
		}

		EndDrawing();

		if (WindowShouldClose())
			screenId = screenID::exit;
	}
}
void optionsScreen() {
	Rectangle backButton;
	backButton.x = 20;
	backButton.y = 20;
	backButton.height = 30;
	backButton.width = 70;
	Rectangle PvPButton;
	PvPButton.x = 20;
	PvPButton.y = GetScreenHeight() / 4 + 40;
	PvPButton.height = 30;
	PvPButton.width = 48.75f;
	Rectangle PvAIButton;
	PvAIButton.x = 20;
	PvAIButton.y = GetScreenHeight() / 4 + 80;
	PvAIButton.height = 30;
	PvAIButton.width = 65;

	Rectangle invPaddle0;
	invPaddle0.x = GetScreenWidth() / 2 + 90;
	invPaddle0.y = PvPButton.y + 10;
	invPaddle0.height = 10;
	invPaddle0.width = 85;
	Rectangle invPaddle1;
	invPaddle1.x = GetScreenWidth() / 2 + 90;
	invPaddle1.y = PvAIButton.y + 10;
	invPaddle1.height = 10;
	invPaddle1.width = 85;

	int color0 = 0;
	int color1 = 1;

	while (!WindowShouldClose() && screenId == screenID::options) {
		UpdateMusicStream(gameMusic);

		BeginDrawing();
		ClearBackground(BLACK);

		if (CheckCollisionPointRec(GetMousePosition(), backButton))
			DrawText(FormatText("Back"), 20, 20, 30, RED);
		else
			DrawText(FormatText("Back"), 20, 20, 30, WHITE);

		DrawText(FormatText("|PADDLE COLORS|"), GetScreenWidth() / 2, GetScreenHeight() / 4, 30, WHITE);
		DrawRectangle(GetScreenWidth() / 2 + 90, PvPButton.y + 10, 85, 10, players[0].color);
		DrawRectangle(GetScreenWidth() / 2 + 90, PvAIButton.y + 10, 85, 10, players[1].color);


		//--------------------
		DrawText(FormatText("|GAMEMODE|"), 20, GetScreenHeight() / 4, 30, WHITE);
		if (CheckCollisionPointRec(GetMousePosition(), PvPButton))
			DrawText(FormatText("PvP"), 20, PvPButton.y, 30, RED);
		else
			DrawText(FormatText("PvP"), 20, PvPButton.y, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), PvAIButton))
			DrawText(FormatText("PvAI"), 20, PvAIButton.y, 30, RED);
		else
			DrawText(FormatText("PvAI"), 20, PvAIButton.y, 30, WHITE);
		//--------------------

		EndDrawing();


		if (CheckCollisionPointRec(GetMousePosition(), PvPButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			gamemode = true;
		}
		if (CheckCollisionPointRec(GetMousePosition(), PvAIButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			gamemode = false;
		}


		if (CheckCollisionPointRec(GetMousePosition(), backButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			screenId = screenID::menu;
		}

		if (CheckCollisionPointRec(GetMousePosition(), invPaddle0) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			color0++;
			if (color0 > 5)
				color0 = 0;

			switch (color0) {
			case 0:
				players[0].color = RED;
				break;
			case 1:
				players[0].color = BLUE;
				break;
			case 2:
				players[0].color = YELLOW;
				break;
			case 3:
				players[0].color = GREEN;
				break;
			case 4:
				players[0].color = VIOLET;
				break;
			case 5:
				players[0].color = BROWN;
				break;
			}
		}

		if (CheckCollisionPointRec(GetMousePosition(), invPaddle1) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			color1++;
			if (color1 > 5)
				color1 = 0;

			switch (color1) {
			case 0:
				players[1].color = RED;
				break;
			case 1:
				players[1].color = BLUE;
				break;
			case 2:
				players[1].color = YELLOW;
				break;
			case 3:
				players[1].color = GREEN;
				break;
			case 4:
				players[1].color = VIOLET;
				break;
			case 5:
				players[1].color = BROWN;
				break;
			}
		}

		if (WindowShouldClose())
			screenId = screenID::exit;

	}
}
void gameLoop() {
	while (!WindowShouldClose()) {
		switch (screenId) {
		case screenID::splash:
			splashScreen();
			break;
		case screenID::menu:
			menuScreen();
			break;
		case screenID::game:
			gameScreen();
			break;
		case screenID::options:
			optionsScreen();
			break;
		case screenID::exit:
			CloseWindow();
			break;
		
		}
	}
}
void initGame() {
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Pong 2021");
	SetTargetFPS(60);
	screenId = screenID::splash;
	initGameObjects();
	SetExitKey(KEY_NUM_LOCK);

	gameLoop();
}