#ifndef _BALL_H_
#define _BALL_H_

class Ball {
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

	bool up;
	bool right;

	Ball(void);
	~Ball(void);

	void SetPos(float set_x, float set_y);
	void SetPosMax(float set_xMax, float set_yMax);
	void SetSize(float set_w, float set_h);
	void SetSpeed(float set_speed);

	int CheckSide();
	void CheckBounce();

	void Move(float deltaTime);

};

#endif
