#pragma once
#include "Stage.h"

class Stage_Ending : public Stage
{
protected:
	float timer;
public:
	Stage_Ending(void);
	void Init();
	void Update(float deltaTime);
	void Release();
	~Stage_Ending(void);
};
