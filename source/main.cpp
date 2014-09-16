#include "AIE.h"
#include <iostream>
#include "Paddle.h"
#include "Ball.h"


//Function Prototypes
float ABCSquared(float a, float b);
char* int_to_string(int value, unsigned int characters);
void BouncePaddle(Ball &theBall, Paddle &thePaddle);

//Constants
const char* WINDOW_NAME = "That one game with the ball and the blip and the bloop"; // Awwwwww yeah
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
const unsigned int MAX_SCORE = 99;
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
	player1.SetPosMax(SCREEN_WIDTH, SCREEN_HEIGHT);
	player1.SetSize(paddleWidth, paddleHeight);
	player1.sprite = CreateSprite(player1.texture, player1.w, player1.h, true);
	player1.SetSpeed(paddleSpeed);
	player1.SetKeys(GLFW_KEY_W, GLFW_KEY_S); //W, S


	//Setup Player 2
	Paddle player2;
	player2.SetPos(SCREEN_WIDTH - paddleOffset, SCREEN_HEIGHT / 2);
	player2.SetPosMax(SCREEN_WIDTH, SCREEN_HEIGHT);
	player2.SetSize(paddleWidth, paddleHeight);
	player2.sprite = CreateSprite(player2.texture, player2.w, player2.h, true);
	player2.SetSpeed(paddleSpeed);
	player2.SetKeys(GLFW_KEY_UP, GLFW_KEY_DOWN); //I, K


	//Setup Ball
	Ball blob;
	blob.SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	blob.SetPosMax(SCREEN_WIDTH, SCREEN_HEIGHT);
	blob.SetSize(ballWidth, ballHeight);
	blob.sprite = CreateSprite(blob.texture, blob.w, blob.h, true);
	blob.SetSpeed(ballSpeed);



	//Game Loop
	do {

		deltaTime = GetDeltaTime();
		SetFont(PIXEL_FONT);

		switch (eGameMode) {

		case MAINMENU:
			DrawString(WINDOW_NAME, 0, SCREEN_HEIGHT / 2);

			if (IsKeyDown(GLFW_KEY_SPACE) || IsKeyDown(GLFW_KEY_ENTER) || IsKeyDown(GLFW_KEY_KP_ENTER)) { eGameMode = PLAYING; }

			ClearScreen();
			break;

		case PLAYING:
			//Check Player 1 Keys
			if (IsKeyDown(player1.keyUp)) { player1.MoveUp(deltaTime); }
			if (IsKeyDown(player1.keyDown)) { player1.MoveDown(deltaTime); }
			MoveSprite(player1.sprite, player1.x, player1.y);

			//Check Player 2 Keys
			if (IsKeyDown(player2.keyUp)) { player2.MoveUp(deltaTime); }
			if (IsKeyDown(player2.keyDown)) { player2.MoveDown(deltaTime); }
			MoveSprite(player2.sprite, player2.x, player2.y);


			switch( blob.CheckSide() ) {
			case 0:
				break;
			case 1:
				points_p1++;
				break;
			case 2:
				points_p2++;
				break;
			}
			blob.CheckBounce();
			BouncePaddle(blob, player1);
			BouncePaddle(blob, player2);
			blob.Move(deltaTime);
			MoveSprite(blob.sprite, blob.x, blob.y);


			DrawSprite(player1.sprite);
			DrawSprite(player2.sprite);
			DrawSprite(blob.sprite);

			if( points_p1 > MAX_SCORE ) { points_p1 = MAX_SCORE; }
			if( points_p2 > MAX_SCORE ) { points_p2 = MAX_SCORE; }
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

//Functions
float ABCSquared(float a, float b) { //pythagorean theorem
	return ((a*a) + (b*b));
}

char* int_to_string(int value, unsigned int characters) {
	char* buffer = new char[characters];
	itoa(value, buffer, 10);
	return buffer;
}

void BouncePaddle(Ball &theBall, Paddle &thePaddle) {
	if( theBall.x < theBall.xMax/2 ) {
		if( (abs(thePaddle.x-(theBall.x-(theBall.w/2))) <= thePaddle.w/8) && abs(thePaddle.y-theBall.y) <= thePaddle.h/2 ) { theBall.right = true; }
	} else {
		if( (abs(thePaddle.x-(theBall.x+(theBall.w/2))) <= thePaddle.w/8) && abs(thePaddle.y-theBall.y) <= thePaddle.h/2 ) { theBall.right = false; }
	}
}
