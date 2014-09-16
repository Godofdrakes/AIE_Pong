#include <Paddle.h>

Paddle::Paddle(void) {}
Paddle::~Paddle(void) {}

void Paddle::SetPos(float set_x, float set_y) {
	x = set_x;
	y = set_y;
}

void Paddle::SetPosMax(float set_xMax, float set_yMax) {
	xMax = set_xMax;
	yMax = set_yMax;
}

void Paddle::SetSize(float set_w, float set_h) {
	w = set_w;
	h = set_h;
}

void Paddle::SetSpeed(float set_speed) { speed = set_speed; }

void Paddle::SetKeys(int set_keyLeft, int set_keyRight) {
	keyUp = set_keyLeft;
	keyDown = set_keyRight;
}

void Paddle::MoveUp(float deltaTime) {
	if(y+(h/2) < yMax) { y += speed * deltaTime; }
}

void Paddle::MoveDown(float deltaTime) {
	if(y-(h/2) > 0) { y -= speed * deltaTime; }
}
