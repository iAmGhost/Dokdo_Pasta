#include "DXUT.h"
#include "Stage_Menu.h"
#include "Include_Managers.h"

#define T_BACKGROUND_1 L"data\\menu\\background_1.png"
#define T_BACKGROUND_2 L"data\\menu\\background_2.png"
#define T_BACKGROUND_3 L"data\\menu\\background_3.png"
#define T_MENU_BAR L"data\\menu\\menu_bar.png"
#define T_CURSOR L"data\\menu\\cursor.png"


Stage_Menu::Stage_Menu(void)
{
	menuPos = 0;
}

Stage_Menu::~Stage_Menu(void)
{
}

void Stage_Menu::Init()
{
	TextureManager& tm = TextureManager::GetSingleton();
	tm.Add(T_BACKGROUND_1);
	tm.Add(T_BACKGROUND_2);
	tm.Add(T_BACKGROUND_3);
	tm.Add(T_MENU_BAR);
	tm.Add(T_CURSOR);
	tm.Init();

	Entity *newEntity = new Entity(T_BACKGROUND_1, 800, 600);
	newEntity->Params["Name"] = "BG1";
	newEntity->SetPos(0, 0);
	entities.push_back(newEntity);

	newEntity = new Entity(T_BACKGROUND_2, 800, 600);
	newEntity->Params["Name"] = "BG2";
	entities.push_back(newEntity);

	newEntity = new Entity(T_BACKGROUND_3, 800, 600);
	newEntity->Params["Name"] = "BG3";
	entities.push_back(newEntity);

	newEntity = new Entity(T_MENU_BAR, 800, 600);
	newEntity->SetPos(0, 0);
	entities.push_back(newEntity);

	newEntity = new Entity(T_CURSOR, 204, 79);
	newEntity->Params["Name"] = "Cursor";
	newEntity->SetPos(30, 470);
	entities.push_back(newEntity);
	
}

void Stage_Menu::Update(float deltaTime)
{
	SoundManager::GetSingleton().PlayLoop("BGM0");
	KeyboardManager& keyboard = KeyboardManager::GetSingleton();

	if ( keyboard.IsKeyPressedN(VK_LEFT) && menuPos != MENU_STAGE1 )
		menuPos--;
	else if ( keyboard.IsKeyPressedN(VK_RIGHT) && menuPos != MENU_EXIT )
		menuPos++;
	else if ( keyboard.IsKeyPressedN(VK_RETURN) )
	{
		StageManager& sm = StageManager::GetSingleton();
		switch ( menuPos )
		{
		case MENU_STAGE1:
			sm.NextStage = "Stage1";
			break;

		case MENU_STAGE2:
			sm.NextStage = "Stage2";
			break;

		case MENU_STAGE3:
			sm.NextStage = "Stage3";
			break;

		default:
			DXUTShutdown();
		}
	}
	else if ( keyboard.IsKeyPressedN(VK_ESCAPE) )
	{
		DXUTShutdown();
	}

	Stage::Update(deltaTime);
}

void Stage_Menu::UpdateEntities(Entity *entity, float deltaTime)
{
	if ( entity->Params["Name"] == "BG1" )
	{
		if ( menuPos == MENU_STAGE1 )
			entity->SetPos(0, 0);
		else
			entity->SetPos(800, 0);
	}
	else if ( entity->Params["Name"] == "BG2" )
	{
		if ( menuPos == MENU_STAGE2 )
			entity->SetPos(0, 0);
		else
			entity->SetPos(800, 0);
	}
	else if ( entity->Params["Name"] == "BG3" )
	{
		if ( menuPos == MENU_STAGE3 || menuPos == MENU_EXIT )
			entity->SetPos(0, 0);
		else
			entity->SetPos(800, 0);
	}
	else if ( entity->Params["Name"] == "Cursor" )
	{
		entity->SetPos((float)30 + menuPos * 185, (float)470);
	}

	Stage::UpdateEntities(entity, deltaTime);
}

void Stage_Menu::Release()
{
	TextureManager::GetSingleton().Release();
	Stage::Release();
}