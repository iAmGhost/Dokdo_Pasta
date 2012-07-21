#pragma once
#include <string>
#include "Animation.h"

class EnemyBoss : public Animation
{
protected:
	int behavior;
	float behaviorTime;
	bool onlyOnce;
public:
	EnemyBoss(std::wstring texturePath, int width, int height, int rows, int cols);
	void Update(float deltaTime);
	~EnemyBoss(void);
};
