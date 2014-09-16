Ball::Ball(void) {}
Ball::~Ball(void) {}

void Ball::MakeSprite() {
	sprite = CreateSprite(texture, w, h, true);
}

void Ball::SetPos(float set_x, float set_y) {
	x = set_x;
	y = set_y;
}

void Ball::SetSize(float set_w, float set_h) {
	w = set_w;
	h = set_h;
}

void Ball::SetSpeed(float set_speed) {
	speed = set_speed;
}

void Ball::CheckSide() {
	if( x >= SCREEN_WIDTH ) { SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); up = true; right = false; points_p1++; }
	if( x <= 0 ) { SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); up = true; right = true; points_p2++; }
}

void Ball::CheckBounce() {
	if(y+(h/2) >= SCREEN_HEIGHT) { up = false; }
	else if(y-(h/2) <= 0) { up = true; }
}

void Ball::CheckBounce( Paddle &pad ) {
	if(x<SCREEN_WIDTH/2) {
		if( (abs(pad.GetX()-(x-(w/2))) <= pad.GetW()/8) && abs(pad.GetY()-y) <= pad.GetH()/2 ) { right = true; }
	} else {
		if( (abs(pad.GetX()-(x+(w/2))) <= pad.GetW()/8) && abs(pad.GetY()-y) <= pad.GetH()/2 ) { right = false; }
	}
}

void Ball::Move(float deltaTime) {
	if(right) { x += speed * deltaTime; } else { x -= speed * deltaTime; }
	if(up) { y += speed * deltaTime; } else { y -= speed * deltaTime; }\
	MoveSprite(sprite, x, y);
}

float Ball::GetX() { return x; }
float Ball::GetY() { return y; }
float Ball::GetW() { return w; }
float Ball::GetH() { return h; }
int Ball::GetSprite() { return sprite; }
