#include "DXUT.h"
#include "Stage_Title.h"
#include "Include_Managers.h"

#define T_BACKGROUND L"data\\title\\background.png"

Stage_Title::Stage_Title(void)
{
}

Stage_Title::~Stage_Title(void)
{
}

void Stage_Title::Init()
{
	SoundManager& sm = SoundManager::GetSingleton();
	sm.Init();
	sm.Add("BGM0", L"data\\sound\\bgm0.wav");
	sm.Add("BGM1", L"data\\sound\\bgm1.wav");
	sm.Add("BGM2", L"data\\sound\\bgm2.wav");
	sm.Add("BGM3", L"data\\sound\\bgm3.wav");
	sm.Add("BGM4", L"data\\sound\\bgm4.wav");
	sm.Add("Explode", L"data\\sound\\explode.wav");
	sm.Add("Shoot", L"data\\sound\\shoot.wav");

	TextureManager& tm = TextureManager::GetSingleton();
	tm.Add(T_BACKGROUND);
	tm.Init();

	Entity *newEntity = new Entity(T_BACKGROUND, 800, 600);
	newEntity->SetPos(0, 0);
	entities.push_back(newEntity);
}

void Stage_Title::Update(float deltaTime)
{
	KeyboardManager& keyboard = KeyboardManager::GetSingleton();
	if ( keyboard.IsKeyPressedN(VK_RETURN) )
	{
		StageManager::GetSingleton().NextStage = "Menu";
	}
	else if ( keyboard.IsKeyPressedN(VK_ESCAPE) )
	{
		DXUTShutdown();
	}

	Stage::Update(deltaTime);
}

void Stage_Title::UpdateEntities(Entity *entity, float deltaTime)
{
	Stage::UpdateEntities(entity, deltaTime);
}

void Stage_Title::Release()
{
	TextureManager::GetSingleton().Release();
	Stage::Release();
}