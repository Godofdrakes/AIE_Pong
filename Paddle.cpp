#include <Paddle.h>

Paddle::Paddle(void) {}
Paddle::~Paddle(void) {}

void Paddle::SetPosMax(float set_xMax, float set_yMax) {
	xMax = set_xMax;
	yMax = set_yMax;
}

void Paddle::MoveUp(float deltaTime) { if(y+(h/2) < yMax) { y += speed * deltaTime; } }

void Paddle::MoveDown(float deltaTime) { if(y-(h/2) > 0) { y -= speed * deltaTime; } }
