#pragma once
#include <map>
#include <list>
#include <string>
#include "Particle.h"
#include "Singleton.h"

class ParticleAdder : public Singleton<ParticleAdder>
{
protected:
	std::list<Entity*> *entities;
	std::map<std::string, Particle*> anims;

	Particle *currentAnim;

public:
	ParticleAdder(void);
	void Init(std::list<Entity*> *entities);
	void Add(std::string ParticleName, Particle *entity);
	Particle* Prepare(std::string ParticleName);
	void Fire();
	void Release();
	~ParticleAdder(void);
};
