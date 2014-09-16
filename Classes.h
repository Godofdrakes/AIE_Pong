#include "AIE.h"



/* ================================================ */
/* ======================PADS====================== */
/* ================================================ */



class Paddle {
private:
	int sprite;
	const char* texture = "./images/blob.png";

	float x;
	float y;

	float w;
	float h;

	float speed;

	int keyUp;
	int keyDown;
	int keySlow;

public:

	~Paddle() {}

	void MakeSprite() {
		sprite = CreateSprite(texture, w, h, true);
	}

	void SetPos(float set_x, float set_y) {
		x = set_x;
		y = set_y;
	}

	void SetSize(float set_w, float set_h) {
		w = set_w;
		h = set_h;
	}

	void SetSpeed(float set_speed) {
		speed = set_speed;
	}

	void SetKeys(int set_keyLeft, int set_keyRight, int set_keySlow) {
		keyUp = set_keyLeft;
		keyDown = set_keyRight;
		keySlow = set_keySlow;
	}

	void Move(float deltaTime) {
		if( IsKeyDown(keySlow) && IsKeyDown(keyUp) ) {
			if(y+(h/2) < SCREEN_HEIGHT) { y += (speed/2) * deltaTime; }
		} else if( IsKeyDown(keyUp) ) {
			if(y+(h/2) < SCREEN_HEIGHT) { y += speed * deltaTime; }
		}

		if( IsKeyDown(keySlow) && IsKeyDown(keyDown) ) {
			if(y-(h/2) > 0) { y -= (speed/2) * deltaTime; }
		} else if( IsKeyDown(keyDown) ) {
			if(y-(h/2) > 0) { y -= speed * deltaTime; }
		}

		MoveSprite(sprite, x, y);

	}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetW() { return w; }
	float GetH() { return h; }
	int GetSprite() { return sprite; }

};


/* ================================================ */
/* =====================BALLS====================== */
/* ================================================ */



class Ball {
private:
	int sprite;
	const char* texture = "./images/blob.png";

	float x;
	float y;

	float w;
	float h;

	float speed;

	bool up;
	bool right;

public:

	~Ball() {}

	void MakeSprite() {
		sprite = CreateSprite(texture, w, h, true);
	}

	void SetPos(float set_x, float set_y) {
		x = set_x;
		y = set_y;
	}

	void SetSize(float set_w, float set_h) {
		w = set_w;
		h = set_h;
	}

	void SetSpeed(float set_speed) {
		speed = set_speed;
	}

	void CheckSide() {
		if( x >= SCREEN_WIDTH ) { SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); up = true; right = false; }
		if( x <= 0 ) { SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); up = true; right = true; }
	}

	void CheckBounce() {
		if(y+(h/2) >= SCREEN_HEIGHT) { up = false; }
		else if(y-(h/2) <= 0) { up = true; }
	}

	void CheckBounce( Paddle &pad ) {
		if(x<SCREEN_WIDTH/2) {
			if( (abs(pad.GetX()-(x-(w/2))) <= pad.GetW()/8) && abs(pad.GetY()-y) <= pad.GetH()/2 ) { right = true; }
		} else {
			if( (abs(pad.GetX()-(x+(w/2))) <= pad.GetW()/8) && abs(pad.GetY()-y) <= pad.GetH()/2 ) { right = false; }
		}
	}

	void Move(float deltaTime) {
		if(right) { x += speed * deltaTime; } else { x -= speed * deltaTime; }
		if(up) { y += speed * deltaTime; } else { y -= speed * deltaTime; }\
		MoveSprite(sprite, x, y);
	}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetW() { return w; }
	float GetH() { return h; }
	int GetSprite() { return sprite; }

};
