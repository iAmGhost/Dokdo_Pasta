#pragma once
#include <string>
#include "Entity.h"

class Particle : public Entity
{
protected:
	float rotation;
	D3DXMATRIX matrix;
	D3DXVECTOR2 center;
public:
	float RotSpeed;
	Particle(const Particle* particle);
	Particle(std::wstring texturePath, int width, int height);
	void Update(float deltaTime);
	~Particle(void);
};
