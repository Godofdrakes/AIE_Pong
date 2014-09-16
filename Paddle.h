#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle {
private:
	int sprite;
	const char* texture = "./images/blob.png";

	float x;
	float y;

	float w;
	float h;

	float speed;

	int keyUp;
	int keyDown;
	int keySlow;

public:

	Paddle(void);
	~Paddle(void);

	void MakeSprite();

	void SetPos(float set_x, float set_y);

	void SetSize(float set_w, float set_h);

	void SetSpeed(float set_speed);

	void SetKeys(int set_keyLeft, int set_keyRight, int set_keySlow);

	void Move(float deltaTime);

	float GetX();
	float GetY();
	float GetW();
	float GetH();
	int GetSprite();

};

#endif
