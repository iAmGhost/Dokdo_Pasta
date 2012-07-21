#pragma once
#include <string>
#include "Animation.h"

class Enemy : public Animation
{
protected:
	bool animChanged;

public:
	Enemy(const Enemy *enemy);
	Enemy(std::wstring texturePath, int width, int height, int rows, int cols);
	void Update(float deltaTime);
	~Enemy(void);
};
