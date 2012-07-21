#pragma once
#include "Stage.h"

class Stage_Title : public Stage
{
public:
	Stage_Title(void);
	void Init();
	void Update(float deltaTime);
	void UpdateEntities(Entity *entity, float deltaTime);
	void Release();
	~Stage_Title(void);
};
