#pragma once
#include "Stage.h"

class Stage_Menu : public Stage
{
protected:
	int menuPos;
public:
	Stage_Menu(void);
	void Init();
	void Update(float deltaTime);
	void UpdateEntities(Entity *entity, float deltaTime);
	void Release();
	~Stage_Menu(void);
};

enum MENU_LIST
{
	MENU_STAGE1, MENU_STAGE2, MENU_STAGE3, MENU_EXIT
};