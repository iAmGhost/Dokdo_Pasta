#include "DXUT.h"
#include "ParticleAdder.h"

using namespace std;

ParticleAdder::ParticleAdder(void)
{
	currentAnim = NULL;
}

ParticleAdder::~ParticleAdder(void)
{
}

void ParticleAdder::Init(std::list<Entity*> *entities)
{
	this->entities = entities;
}

void ParticleAdder::Add(string ParticleName, Particle *entity)
{
	anims[ParticleName] = entity;
}

Particle* ParticleAdder::Prepare(string ParticleName)
{
	currentAnim = new Particle(anims[ParticleName]);
	return currentAnim;
}

void ParticleAdder::Fire()
{
	if ( currentAnim )
	{
		currentAnim->Init();
		entities->push_back(currentAnim);
		currentAnim = NULL;
	}
}

void ParticleAdder::Release()
{
	map<string,Particle*>::iterator it;

	for ( it = anims.begin(); it != anims.end(); ++it )
	{
		SAFE_RELEASE(it->second);
		SAFE_DELETE(it->second);
	}

	anims.clear();
}