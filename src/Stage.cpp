#include "DXUT.h"
#include "Stage.h"
#include "SoundManager.h"

using namespace std;

Stage::Stage(void)
{
}

Stage::~Stage(void)
{
}

void Stage::Init()
{

}

void Stage::Update(float deltaTime)
{
	if ( entities.empty() )
	{
		Init();
		return ;
	}

	list<Entity*> temp;
	temp.resize(entities.size());
	copy(entities.begin(), entities.end(), temp.begin());

	list<Entity*>::iterator it;

	for ( it = temp.begin(); it != temp.end(); ++it )
	{
		(*it)->Update(deltaTime);
		UpdateEntities(*it, deltaTime);
	}
}

void Stage::UpdateEntities(Entity *entity, float deltaTime)
{
	if ( entity->Params["Delete"] == "True" )
	{
		entities.remove(entity);
		SAFE_RELEASE(entity);
		SAFE_DELETE(entity);
	}
}

void Stage::Draw(LPDIRECT3DDEVICE9 device)
{
	if ( entities.empty() )
	{
		Init();
		return ;
	}

	list<Entity*>::iterator it;

	for ( it = entities.begin(); it != entities.end(); ++it )
	{
		if ( (*it)->Params["DrawLater"] != "True" )
		{
			(*it)->Draw(device);
		}
	}

	for ( it = entities.begin(); it != entities.end(); ++it )
	{
		if ( (*it)->Params["DrawLater"] == "True" )
		{
			(*it)->Draw(device);
		}
	}

}

void Stage::Release()
{
	list<Entity*>::iterator it;

	for ( it = entities.begin(); it != entities.end(); ++it )
	{
		SAFE_RELEASE(*it);
		SAFE_DELETE(*it);
	}
	SoundManager::GetSingleton().Stop();
	entities.clear();
}