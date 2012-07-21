#pragma once
#include <map>
#include <string>
#include "Stage.h"
#include "Singleton.h"

class StageManager : public Singleton<StageManager>
{
protected:
	std::map<std::string, Stage*> stages;
	Stage *currentStage;

public:
	std::string NextStage;

	StageManager(void);
	void Add(std::string stageName, Stage *stage);
	Stage* Get(std::string stageName);
	void Update(float deltaTime);
	void Draw(LPDIRECT3DDEVICE9 device);
	void Release();
	~StageManager(void);
};
