#include "DXUT.h"
#include "StageManager.h"

using namespace std;

StageManager::StageManager(void)
{
	currentStage = NULL;
	NextStage = "";
}

StageManager::~StageManager(void)
{
}

void StageManager::Add(std::string stageName, Stage *stage)
{
	stages[stageName] = stage;
}

Stage* StageManager::Get(std::string stageName)
{
	return stages[stageName];
}

void StageManager::Update(float deltaTime)
{
	if ( NextStage != "" )
	{
		if ( currentStage )
			currentStage->Release();

		currentStage = Get(NextStage);
		NextStage = "";
	}
	else if ( currentStage != NULL )
		currentStage->Update(deltaTime);
	
}

void StageManager::Draw(LPDIRECT3DDEVICE9 device)
{
	if ( currentStage )
		currentStage->Draw(device);
}

void StageManager::Release()
{
	map<string, Stage*>::iterator it;

	for ( it = stages.begin(); it != stages.end(); ++it )
	{
		SAFE_RELEASE(it->second);
		SAFE_DELETE(it->second);
	}

	stages.clear();
}