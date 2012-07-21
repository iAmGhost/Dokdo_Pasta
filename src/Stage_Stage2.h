#pragma once
#include "Stage.h"

class Stage_Stage2 : public Stage
{
protected:
	int bulletCount;
	float stageClearTimer;
	float stageOverTimer;
public:
	Stage_Stage2(void);
	void Init();
	void AddNewPlayer();
	void Update(float deltaTime);
	void UpdateEntities(Entity *entity, float deltaTime);
	void CollisionCheck(Entity *entity);
	void OnCollide(Entity *a, Entity *b);
	void Release();
	~Stage_Stage2(void);
};
