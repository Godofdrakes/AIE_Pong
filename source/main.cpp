#include "AIE.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Paddle.h"
#include "Ball.h"

using namespace std;


//Function Prototypes
float ABCSquared( float a, float b );
char* int_to_string( int value, unsigned int characters );
void BouncePaddle( Ball &theBall, Paddle &thePaddle );
bool FileExists(const char* name);
void SaveHighscore(char* filename);
void LoadHighscore(char* filename);

/* -==- AUTOPLAY -==-
	NONE: Both paddles will move using player input
	SINGLE: Player2 will move automatically, following the ball. The goal becoms to keep the ball going as long as possible.
	BOTH: Both players move on their own. Score is disbaled.
*/
enum AUTOPLAY {
	NONE,
	SINGLE,
	BOTH,
};
AUTOPLAY AutoPlay = SINGLE;

//System variables
const char* WINDOW_NAME = "That one game with the ball and the blip and the bloop";
const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;
const char* PIXEL_FONT = "./fonts/invaders.fnt";
char* DATA_FILE_NAME = {"data.dat"};
float deltaTime; // Time between frames
bool doExit = false;

//Initial values for objects
//It's all based off the screen's size so the game's sprites scale
float paddleWidth = SCREEN_WIDTH / 30;
float paddleHeight = SCREEN_HEIGHT / 5;
float paddleSpeed = SCREEN_HEIGHT;
float paddleOffset = SCREEN_WIDTH / 50;

float ballWidth = SCREEN_WIDTH / 30;
float ballHeight = ballWidth;
float ballSpeed = ABCSquared( SCREEN_WIDTH, SCREEN_HEIGHT ) / 2000; //Again, basing the speed of the size of the screen

//Variables for score
const int POINTS_OFFSET_X = 50; //Used to posiition the score strings on screen
const int POINTS_OFFSET_Y = 50;
const unsigned int MAX_SCORE = 99; // Don't let it get above this. The char for displaying the score is only [3]. Bad juju.
unsigned int points_p1 = 0;
unsigned int points_p2 = 0;
unsigned int pointsHigh_p1 = 0;
unsigned int pointsHigh_p2 = 0;

enum GAMEMODE { // What stage the game is currently in
	MAINMENU,
	PLAYING,
	GAMEOVER,
};

//Main loop
int main(int argc, char* argv[]) {

	//Init the framework and make the window
	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false, WINDOW_NAME);
	SetBackgroundColour(SColour(0, 0, 0, 255));
	AddFont(PIXEL_FONT);

	//Setup the highscores
	LoadHighscore(DATA_FILE_NAME);

	//Setup Enum
	GAMEMODE GameMode = MAINMENU;

	//Setup Player 1
	Paddle player1;
	player1.x = paddleOffset; player1.y = SCREEN_HEIGHT / 2;
	player1.SetPosMax(SCREEN_WIDTH, SCREEN_HEIGHT);
	player1.w = paddleWidth; player1.h = paddleHeight;
	player1.sprite = CreateSprite(player1.texture, player1.w, player1.h, true);
	player1.speedBase = paddleSpeed; player1.speed = player1.speedBase;
	player1.keyUp = GLFW_KEY_W; player1.keyDown = GLFW_KEY_S;


	//Setup Player 2
	Paddle player2;
	player2.x = SCREEN_WIDTH - paddleOffset; player2.y = SCREEN_HEIGHT / 2;
	player2.SetPosMax(SCREEN_WIDTH, SCREEN_HEIGHT);
	player2.w = paddleWidth; player2.h = paddleHeight;
	player2.sprite = CreateSprite(player2.texture, player2.w, player2.h, true);
	player2.speedBase = paddleSpeed; player2.speed = player2.speedBase;
	player2.keyUp = GLFW_KEY_UP; player2.keyDown = GLFW_KEY_DOWN;


	//Setup blob
	Ball blob;
	blob.x = SCREEN_WIDTH / 2; blob.y = SCREEN_HEIGHT / 2;
	blob.SetPosMax(SCREEN_WIDTH, SCREEN_HEIGHT);
	blob.w = ballWidth; blob.h = ballHeight;
	blob.sprite = CreateSprite(blob.texture, blob.w, blob.h, true);
	blob.speedBase = paddleSpeed; blob.speed = blob.speedBase*0.75f;



	//Game Loop
	do{

		deltaTime = GetDeltaTime(); //Get the time between this frame and the last
		SetFont(PIXEL_FONT); //Set the font. I don't know why we have to do this every frame.

		switch(GameMode) {

		case MAINMENU:
			DrawString( WINDOW_NAME, 35, SCREEN_HEIGHT - (SCREEN_HEIGHT / 3) ); //The badass title screen.
			DrawString( "Press 'SPACE' or 'ENTER' to begin", 175, SCREEN_HEIGHT - ((SCREEN_HEIGHT / 3)*2) ); //The badass title screen.

			//Let's have the game play itself in the backgorund
			player1.y = blob.y;
			player2.y = blob.y;

			blob.CheckBounce();
			BouncePaddle(blob, player1);
			BouncePaddle(blob, player2);
			blob.Move(deltaTime);

			MoveSprite(blob.sprite, blob.x, blob.y);
			MoveSprite(player1.sprite, player1.x, player1.y);
			MoveSprite(player2.sprite, player2.x, player2.y);

			for(int i = 1; i < 4; i++) { //Look! For loops!
				if(i=1) {DrawSprite(player1.sprite);}
				if(i=2) {DrawSprite(player2.sprite);}
				if(i=3) {DrawSprite(blob.sprite);}
			}

			// Begin the game proper
			if (IsKeyDown(GLFW_KEY_SPACE) || IsKeyDown(GLFW_KEY_ENTER) || IsKeyDown(GLFW_KEY_KP_ENTER)) {
				//We have to reset the positions and speeds of the objects, otherwise we'll be taking control of a game already in progress.
				player1.x = paddleOffset; player1.y = SCREEN_HEIGHT / 2;
				player2.x = SCREEN_WIDTH - paddleOffset; player2.y = SCREEN_HEIGHT / 2;

				blob.speedBase = paddleSpeed; blob.speed = blob.speedBase*0.75f;
				blob.x = SCREEN_WIDTH / 2; blob.y = SCREEN_HEIGHT / 2;
				blob.up = true;
				blob.right = true;

				GameMode = PLAYING; //And begin
			}


			ClearScreen();
			break;

		case PLAYING:
			//Check Player 1 Keys
			switch(AutoPlay) { //IF autoplay is off accept player input, else we don't care about the player
				case NONE:
					if( IsKeyDown(player1.keyUp) ) { player1.MoveUp(deltaTime); }
					if( IsKeyDown(player1.keyDown) ) { player1.MoveDown(deltaTime); }
					break;
				case SINGLE:
					if( IsKeyDown(player1.keyUp) ) { player1.MoveUp(deltaTime); }
					if( IsKeyDown(player1.keyDown) ) { player1.MoveDown(deltaTime); }
					break;
				case BOTH:
					player1.y = blob.y;
					break;
				default:
					if( IsKeyDown(player1.keyUp) ) { player1.MoveUp(deltaTime); }
					if( IsKeyDown(player1.keyDown) ) { player1.MoveDown(deltaTime); }
					break;
			}
			MoveSprite(player1.sprite, player1.x, player1.y);

			//Check Player 2 Keys
			switch(AutoPlay) { //See autoplay case of player 1
				case NONE:
					if (IsKeyDown(player2.keyUp)) { player2.MoveUp(deltaTime); }
					if (IsKeyDown(player2.keyDown)) { player2.MoveDown(deltaTime); }
					break;
				case SINGLE:
					player2.y = blob.y;
					break;
				case BOTH:
					player2.y = blob.y;
					break;
				default:
					if (IsKeyDown(player2.keyUp)) { player2.MoveUp(deltaTime); }
					if (IsKeyDown(player2.keyDown)) { player2.MoveDown(deltaTime); }
					break;
			}
			MoveSprite(player2.sprite, player2.x, player2.y);


			switch( blob.CheckSide() ) { //Which side did the ball go off of, if any.
			case 0:
				break;
			case 1:
				if( AutoPlay == NONE ) { points_p1++; }
				break;
			case 2:
				if( AutoPlay == SINGLE ) { points_p1 = 0; } else { points_p2++; }
				break;
			}
			blob.CheckBounce(); //Bounce off the top/bottom
			BouncePaddle(blob, player1); //Bounce off the paddles
			BouncePaddle(blob, player2);
			blob.Move(deltaTime);
			MoveSprite(blob.sprite, blob.x, blob.y);


			for(int i = 1; i < 4; i++) {
				if(i=1) {DrawSprite(player1.sprite);}
				if(i=2) {DrawSprite(player2.sprite);}
				if(i=3) {DrawSprite(blob.sprite);}
			}

			//Make sure the score doesn't go above a specific ammount
			if( points_p1 > MAX_SCORE ) { points_p1 = MAX_SCORE; }
			if( points_p2 > MAX_SCORE) { points_p2 = MAX_SCORE; }
			//If the score goes above the high score then we need to update accordingly
			if( points_p1 > pointsHigh_p1 ) {pointsHigh_p1 = points_p1;}
			if( points_p2 > pointsHigh_p2 ) {pointsHigh_p2 = points_p2;}

			//Draw Score on screen
			switch(AutoPlay) { //Draw both, one, or neither scores depending on how many players there are
				case NONE:
					DrawString(int_to_string(points_p1, 3), POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);
					DrawString(int_to_string(points_p2, 3), SCREEN_WIDTH - POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);
					DrawString(int_to_string(pointsHigh_p1, 3), POINTS_OFFSET_X, SCREEN_HEIGHT - (POINTS_OFFSET_Y*2));
					DrawString(int_to_string(pointsHigh_p2, 3), SCREEN_WIDTH - POINTS_OFFSET_X, SCREEN_HEIGHT - (POINTS_OFFSET_Y*2));
					break;
				case SINGLE:
					DrawString(int_to_string(points_p1, 3), POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);
					DrawString(int_to_string(pointsHigh_p1, 3), POINTS_OFFSET_X, SCREEN_HEIGHT - (POINTS_OFFSET_Y*2));
					break;
				case BOTH:
					break;
				default:
					DrawString(int_to_string(points_p1, 3), POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);
					DrawString(int_to_string(points_p2, 3), SCREEN_WIDTH - POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);
					DrawString(int_to_string(points_p2, 3), SCREEN_WIDTH - POINTS_OFFSET_X, SCREEN_HEIGHT - POINTS_OFFSET_Y);
					DrawString(int_to_string(pointsHigh_p2, 3), SCREEN_WIDTH - POINTS_OFFSET_X, SCREEN_HEIGHT - (POINTS_OFFSET_Y*2));
					break;
			}

			if (IsKeyDown(GLFW_KEY_ESCAPE)) { GameMode = GAMEOVER; }

			ClearScreen();
			break;

		case GAMEOVER:

			DrawString("Really quit? Y/N", (SCREEN_WIDTH / 2)-100, SCREEN_HEIGHT / 2);


			for(int i = 1; i < 4; i++) {
				if(i = 1) { DrawSprite(player1.sprite); }
				if(i = 2) { DrawSprite(player2.sprite); }
				if(i = 3) { DrawSprite(blob.sprite); }
			}
			ClearScreen();

			if (IsKeyDown(GLFW_KEY_Y)) { doExit = true; }
			else if (IsKeyDown(GLFW_KEY_N)) { GameMode = PLAYING; }
			if (IsKeyDown(GLFW_KEY_R)) { pointsHigh_p1 = 0; pointsHigh_p1 = 0; } //Fancy not-all-that-hidden reset button

			break;

		default:
			GameMode = MAINMENU;
			ClearScreen();
			break;

		}

		//Save the high schore
		SaveHighscore(DATA_FILE_NAME);


		ClearScreen();

	} while (!FrameworkUpdate() && !doExit);

	Shutdown();

	return 0;
}

//Functions
float ABCSquared( float a, float b ) { //Pythagorean theorem
	return ((a*a) + (b*b));
}

//Self contained way to convert int to char*
//Helpful when turning the score into a string
char* int_to_string( int value, unsigned int characters ) {
	char* buffer = new char[characters];
	itoa(value, buffer, 10);
	return buffer;
}

//This is our check for if the ball has hit a paddle and needs to bounce off it.
void BouncePaddle( Ball &theBall, Paddle &thePaddle ) {
	float modifier = 0;
	if( theBall.x < SCREEN_WIDTH/2 ) { //We check which side of the screen the ball is on so we can easily tell which paddle we should run out bounce check on.
		if( (abs(thePaddle.x-(theBall.x-(theBall.w/2))) <= thePaddle.w/8) && abs(thePaddle.y-theBall.y) <= thePaddle.h/2 ) { //We do a bit of math to make sure it looks like the left/right side of the ball is bouncing
			theBall.right = true; //Flip the direct
			if( AutoPlay == SINGLE ) { points_p1++; }
			theBall.speed = theBall.speedBase;
		}
	} else {
		if( (abs(thePaddle.x-(theBall.x+(theBall.w/2))) <= thePaddle.w/8) && abs(thePaddle.y-theBall.y) <= thePaddle.h/2 ) {
			theBall.right = false;
			theBall.speed = theBall.speedBase;
		}
	}
}

bool FileExists( const char* name ) { ifstream file(name); return (bool)file; }

void LoadHighscore(char* filename) {
	if(FileExists(filename)) {
		fstream file(filename, ios::in | ios::binary);
		file.read((char*)&pointsHigh_p1, sizeof(pointsHigh_p1));
		file.read((char*)&pointsHigh_p2, sizeof(pointsHigh_p2));
		file.close();
	}
}

void SaveHighscore(char* filename) {
	fstream file(filename, ios::out | ios::binary);
	file.write((char*)&pointsHigh_p1, sizeof(pointsHigh_p1));
	file.write((char*)&pointsHigh_p2, sizeof(pointsHigh_p2));
	file.close();
}
