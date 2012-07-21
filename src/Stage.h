#pragma once
#include <list>
#include "Entity.h"

class Stage
{
protected:
	std::list<Entity*> entities;

public:
	Stage(void);
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void UpdateEntities(Entity *entity, float deltaTime);
	virtual void Draw(LPDIRECT3DDEVICE9 device);
	virtual void Release();
	~Stage(void);
};
