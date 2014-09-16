#include "AIE.h"
#include <iostream>
#include "Paddle.h"
#include "Ball.h"


//Function Protos
float ABCSquared(float a, float b);
char* int_to_string(int value, unsigned int characters);

//Constants
const char* WINDOW_NAME = "That one game with the ball and the blip and the "; // Awwwwww yeah
const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;
const char* PIXEL_FONT = "./fonts/invaders.fnt";

//Variables
float paddleWidth = SCREEN_WIDTH / 30; // Base the paddle sizes of the initial size of the window
float paddleHeight = SCREEN_HEIGHT / 5;
float paddleSpeed = SCREEN_HEIGHT;
float paddleOffset = SCREEN_WIDTH / 50;

float ballWidth = SCREEN_WIDTH / 30; // Base the ball size of the initial size of the window
float ballHeight = ballWidth;
float ballSpeed = ABCSquared(SCREEN_WIDTH, SCREEN_HEIGHT) / 2500;

float deltaTime; // Time between frames

const int POINTS_OFFSET_X = 50;
const int POINTS_OFFSET_Y = 50;
unsigned int points_p1 = 0;
unsigned int points_p2 = 0;

enum GAMEMODE { // What stage the game is currently in
	MAINMENU,
	PLAYING,
	GAMEOVER,
};

//Main loop
int main(int argc, char* argv[]) {

	//Init the framework
	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false, WINDOW_NAME);
	SetBackgroundColour(SColour(0, 0, 0, 255));
	AddFont(PIXEL_FONT);

	//Setup Enum
	GAMEMODE eGameMode = MAINMENU;

	//Setup Player 1
	Paddle player1;
	player1.SetPos(paddleOffset, SCREEN_HEIGHT / 2);
	player1.SetSize(paddleWidth, paddleHeight);
	player1.MakeSprite();
	player1.SetSpeed(paddleSpeed);
	player1.SetKeys(87, 83, 68); //W, S, D


	//Setup Player 2
	Paddle player2;
	player2.SetPos(SCREEN_WIDTH - paddleOffset, SCREEN_HEIGHT / 2);
	player2.SetSize(paddleWidth, paddleHeight);
	player2.MakeSprite();
	player2.SetSpeed(paddleSpeed);
	player2.SetKeys(73, 75, 74); //I, K, J


	//Setup Ball
	Ball blob;
	blob.SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	blob.SetSize(ballWidth, ballHeight);
	blob.MakeSprite();
	blob.SetSpeed(ballSpeed);



	//Game Loop
	do {

		deltaTime = GetDeltaTime();
		SetFont(PIXEL_FONT);

		switch (eGameMode) {

		case MAINMENU:

			DrawString(WINDOW_NAME, 0, SCREEN_HEIGHT / 2);

			if (IsKeyDown(257) || IsKeyDown(KEY_SPACE)) { eGameMode = PLAYING; }

			ClearScreen();
			break;

		case PLAYING:

			//Check Player 1 Keys
			player1.Move(deltaTime);

			//Check Player 2 Keys
			player2.Move(deltaTime);


			blob.CheckSide();
			blob.CheckBounce();
			blob.CheckBounce(player1);
			blob.CheckBounce(player2);
			blob.Move(deltaTime);


			DrawSprite(player1.GetSprite());
			DrawSprite(player2.GetSprite());
			DrawSprite(blob.GetSprite());

			if( points_p1 > 99 ) { points_p1 = 99; }
			if( points_p2 > 99 ) { points_p2 = 99; }
			DrawString(int_to_string(points_p1, 3), POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);
			DrawString(int_to_string(points_p2, 3), SCREEN_WIDTH - POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);

			ClearScreen();
			break;

		case GAMEOVER:

			ClearScreen();
			break;

		default:

			eGameMode = MAINMENU;
			ClearScreen();
			break;

		}

		ClearScreen();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}

//Class Functions

//Functions
float ABCSquared(float a, float b) { //pythagorean theorem
	return ((a*a) + (b*b));
}

char* int_to_string(int value, unsigned int characters) {
	char* buffer = new char[characters];
	itoa(value, buffer, 10);
	return buffer;
}

//Paddle Functions
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

//Ball Functions
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
