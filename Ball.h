#ifndef _BALL_H_
#define _BALL_H_

class Ball {
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

	bool up;
	bool right;

	Ball(void);
	~Ball(void);

	void SetPosMax(float set_xMax, float set_yMax);

	int CheckSide();
	void CheckBounce();

	void Move(float deltaTime);

};

#endif
