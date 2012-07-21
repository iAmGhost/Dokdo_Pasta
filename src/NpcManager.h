#pragma once
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include "Singleton.h"
#include "Enemy.h"

class NpcManager : public Singleton<NpcManager>
{
protected:
	std::list<Entity*> *entities;
	std::vector<Enemy*> npcs;
	float time;

public:
	float RespawnTime, RespawnTimeMod;

	NpcManager(void);
	void Init(std::list<Entity*> *entities);
	void Update(float deltaTime);
	void Add(Enemy *enemy);
	Enemy Get(std::string name);
	void Release();
	~NpcManager(void);
};
