#include "Ball.h"

Ball ball;
Ball multiball;

void setBallParameters() {
	ball.ballPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	ball.ballSpeed = { -330.0f, 290.8f };
	ball.ballStop = true;
	ball.ballRadius = 12.0f;
	ball.col = true;

	multiball.ballPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	multiball.ballSpeed = { -7.0f, 5.8f };
	multiball.active = false;
	multiball.ballRadius = 12.0f;
	multiball.col = true;
	
}
void ballMove() {
	if (!ball.ballStop) {
		ball.ballPosition.y += ball.ballSpeed.y*GetFrameTime();
		ball.ballPosition.x += ball.ballSpeed.x*GetFrameTime();
	}

	if (multiball.active) {
		multiball.ballPosition.y += multiball.ballSpeed.y;
		multiball.ballPosition.x += multiball.ballSpeed.x;
	}
}
void ballDraw() {
	DrawCircleV(ball.ballPosition, ball.ballRadius, WHITE);
	if (multiball.active){
		DrawCircleV(multiball.ballPosition, ball.ballRadius, GOLD);
	}
}
