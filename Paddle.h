#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle {
private:

public:
	int sprite;
	char* texture = "./images/blob.png";

	float w;
	float h;

	float x;
	float y;
	float xMax;
	float yMax;

	float speed;

	int keyUp;
	int keyDown;

	Paddle(void);
	~Paddle(void);

	void SetPos(float set_x, float set_y);
	void SetPosMax(float set_xMax, float set_yMax);
	void SetSize(float set_w, float set_h);
	void SetSpeed(float set_speed);
	void SetKeys(int set_keyLeft, int set_keyRight);

	void Paddle::MoveUp(float deltaTime);
	void Paddle::MoveDown(float deltaTime);

};

#endif
