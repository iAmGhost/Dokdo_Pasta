#pragma once
#include "Stage.h"

class Stage_Stage3 : public Stage
{
protected:
	int boatTimer;
	int bulletCount;
	float stageClearTimer;
	float stageOverTimer;
public:
	Stage_Stage3(void);
	void Init();
	void AddNewPlayer();
	void AddNewPlayerBoat();
	void Update(float deltaTime);
	void UpdateEntities(Entity *entity, float deltaTime);
	void CollisionCheck(Entity *entity);
	void OnCollide(Entity *a, Entity *b);
	void Release();
	~Stage_Stage3(void);
};
