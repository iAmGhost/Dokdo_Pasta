#pragma once
#include <string>
#include "Entity.h"

class Animation : public Entity
{
protected:
	int rows, cols;
	float frame, animSpeed;
	bool animLoop;

public:
	int Row, Col;
	Animation(std::wstring texturePath, int width, int height, int rows, int cols);
	Animation(const Animation *animation);
	void Update(float deltaTime);
	void Play(float speed, bool loop);
	void SetAnimPos(int row, int col);
	~Animation(void);
};
