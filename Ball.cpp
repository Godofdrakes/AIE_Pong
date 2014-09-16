#include <Ball.h>

Ball::Ball(void) {}
Ball::~Ball(void) {}

void Ball::SetPos(float set_x, float set_y) {
	x = set_x;
	y = set_y;
}

void Ball::SetPosMax(float set_xMax, float set_yMax) {
	xMax = set_xMax;
	yMax = set_yMax;
}

void Ball::SetSize(float set_w, float set_h) {
	w = set_w;
	h = set_h;
}

void Ball::SetSpeed(float set_speed) { speed = set_speed; }

int Ball::CheckSide() {
	if( x >= xMax ) { SetPos(xMax / 2, yMax / 2); up = true; right = false; return 1; }
	else if( x <= 0 ) { SetPos(xMax / 2, yMax / 2); up = true; right = true; return 2; }
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
