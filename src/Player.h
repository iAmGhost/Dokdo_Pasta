#pragma once
#include <string>
#include "Animation.h"

class Player : public Animation
{
protected:

public:
	float MoveSpeed;
	float MoveSpeedMod;
	Player(std::wstring texturePath, int width, int height, int rows, int cols);
	void Update(float deltaTime);
	~Player(void);
};
