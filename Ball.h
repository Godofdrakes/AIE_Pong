#ifndef _BALL_H_
#define _BALL_H_

class Ball {
private:
	int sprite;
	const char* texture = "./images/blob.png";

	float x;
	float y;

	float w;
	float h;

	float speed;

	bool up;
	bool right;

public:

	Ball(void);
	~Ball(void);

	void MakeSprite();

	void SetPos(float set_x, float set_y);

	void SetSize(float set_w, float set_h);

	void SetSpeed(float set_speed);

	void CheckSide();

	void CheckBounce();

	void CheckBounce( Paddle &pad );

	void Move(float deltaTime);

	float GetX();
	float GetY();
	float GetW();
	float GetH();
	int GetSprite();

};

#endif
