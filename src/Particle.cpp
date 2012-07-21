#include "DXUT.h"
#include "Particle.h"

using namespace std;

Particle::Particle(wstring texturePath, int width, int height) : Entity(texturePath, width, height)
{
	rotation = 0;
	RotSpeed = 0;
	AutoRemove = true;
}

Particle::~Particle(void)
{
}

Particle::Particle(const Particle *particle) : Entity(*particle)
{
	rotation = particle->rotation;
	RotSpeed = particle->RotSpeed;
}

void Particle::Update(float deltaTime)
{
	center.x = X + Width / 2.0f;
	center.y = Y + Height / 2.0f;

	rotation += RotSpeed * deltaTime;
	D3DXMatrixTransformation2D(&matrix, NULL, NULL, NULL, &center, rotation, NULL);
	sprite->SetTransform(&matrix);
	Entity::Update(deltaTime);
}