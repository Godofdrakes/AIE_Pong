#include "AIE.h"
#include <iostream>
#include "Paddle.h"
#include "Ball.h"


//Function Protos
float ABCSquared(float a, float b);
char* int_to_string(int value, unsigned int characters);

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

//Functions
float ABCSquared(float a, float b) { //pythagorean theorem
	return ((a*a) + (b*b));
}

char* int_to_string(int value, unsigned int characters) {
	char* buffer = new char[characters];
	itoa(value, buffer, 10);
	return buffer;
}
