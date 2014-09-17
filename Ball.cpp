#include <Ball.h>

Ball::Ball(void) {}
Ball::~Ball(void) {}

void Ball::SetPosMax(float set_xMax, float set_yMax) {
	xMax = set_xMax;
	yMax = set_yMax;
}

int Ball::CheckSide() {
	if (x >= xMax) { x = xMax / 2; y = yMax / 2; up = true; right = false; speed = speedBase*0.75f; return 1; }
	else if (x <= 0) { x = xMax / 2; y = yMax / 2; up = true; right = true; speed = speedBase*0.75f; return 2; }
	else { return 0; }
}

void Ball::CheckBounce() {
	if(y+(h/2) >= yMax) { up = false; }
	else if(y-(h/2) <= 0) { up = true; }
}

void Ball::Move(float deltaTime) {
	if(right) { x += speed * deltaTime; } else { x -= speed * deltaTime; }
	if(up) { y += speed * deltaTime; } else { y -= speed * deltaTime; }
}
