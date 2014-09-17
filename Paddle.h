#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle {
private:
	float xMax;
	float yMax;

public:
	int sprite;
	char* texture = "./images/blob.png";

	float w;
	float h;

	float x;
	float y;

	float speed;
	float speedBase;

	int keyUp;
	int keyDown;

	Paddle(void);
	~Paddle(void);

	void SetPosMax(float set_xMax, float set_yMax);

	void Paddle::MoveUp(float deltaTime);
	void Paddle::MoveDown(float deltaTime);

};

#endif
