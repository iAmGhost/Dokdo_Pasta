#include "DXUT.h"
#include "Stage_Ending.h"
#include "Include_Managers.h"
#include "Include_Entities.h"

Stage_Ending::Stage_Ending(void)
{

}

Stage_Ending::~Stage_Ending(void)
{
}

void Stage_Ending::Init()
{
	timer = 0;
	TextureManager::GetSingleton().Add(L"data\\ending\\background.png");
	TextureManager::GetSingleton().Add(L"data\\ending\\flag.png");
	TextureManager::GetSingleton().Init();

	Entity *newEntity = new Entity(L"data\\ending\\background.png", 800, 600);
	newEntity->SetPos(0, 0);
	entities.push_back(newEntity);

	Animation *newAnimation = new Animation(L"data\\ending\\flag.png", 2000, 120, 1, 20);
	newAnimation->SetPos(236, 200);
	newAnimation->Play(15.0f, true);
	entities.push_back(newAnimation);
}

void Stage_Ending::Update(float deltaTime)
{
	SoundManager::GetSingleton().PlayLoop("BGM4");
	if ( timer > 10 )
	{
		StageManager::GetSingleton().NextStage = "Menu";
	}
	timer += deltaTime;

	Stage::Update(deltaTime);
}

void Stage_Ending::Release()
{
	TextureManager::GetSingleton().Release();
	Stage::Release();
}