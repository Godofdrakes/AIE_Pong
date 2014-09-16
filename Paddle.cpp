Paddle::Paddle(void) {}
Paddle::~Paddle(void) {}

void Paddle::MakeSprite() { sprite = CreateSprite(texture, w, h, true); }

void Paddle::SetPos(float set_x, float set_y) {
	x = set_x;
	y = set_y;
}

void Paddle::SetSize(float set_w, float set_h) {
	w = set_w;
	h = set_h;
}

void Paddle::SetSpeed(float set_speed) { speed = set_speed; }

void Paddle::SetKeys(int set_keyLeft, int set_keyRight, int set_keySlow) {
	keyUp = set_keyLeft;
	keyDown = set_keyRight;
	keySlow = set_keySlow;
}

void Paddle::Move(float deltaTime) {
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

float Paddle::GetX() { return x; }
float Paddle::GetY() { return y; }
float Paddle::GetW() { return w; }
float Paddle::GetH() { return h; }
int Paddle::GetSprite() { return sprite; }
