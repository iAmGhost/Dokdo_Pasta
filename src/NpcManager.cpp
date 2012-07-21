#include "DXUT.h"
#include "NpcManager.h"
#include "Helper.h"
#include "GameStateManager.h"

using namespace std;

NpcManager::NpcManager(void)
{
	time = 0;
	RespawnTime = 2.5;
	RespawnTimeMod = 0;
}

NpcManager::~NpcManager(void)
{
}

void NpcManager::Init(std::list<Entity*> *entities)
{
	this->entities = entities;
}

void NpcManager::Add(Enemy *enemy)
{
	npcs.push_back(enemy);
}

void NpcManager::Update(float deltaTime)
{
	if ( npcs.empty() ) return ;
	if ( time >= RespawnTime - RespawnTimeMod )
	{
		random_shuffle(npcs.begin(), npcs.end());
		vector<Enemy*>::iterator it = npcs.begin();

		Enemy *newEnemy = new Enemy(*it);

		if (  Helper::Random(1, 3) == 1 )
		{
			newEnemy->SetPos(800, Helper::Random(0, 30) * 10.0f);
			if ( newEnemy->Params["EnemyType"] == "2" )
			{
				newEnemy->SetSpeed(-230, (float)Helper::Random(10, 20), 0, (float)Helper::Random(10, 20));
			}
		}
		else
		{
			newEnemy->SetPos(800, Helper::Random(30, 40) * 10.0f);
			if ( newEnemy->Params["EnemyType"] == "2" )
			{
				newEnemy->SetSpeed(-200 + -Helper::Random(0, 6) * 10.0f, (float)-Helper::Random(10, 20), 0, (float)-Helper::Random(10, 20));
			}
		}
		
		if ( newEnemy->Params["EnemyType"] == "1" )
		{
			newEnemy->Health = 100;
		}
		else if ( newEnemy->Params["EnemyType"] == "2" )
		{
			newEnemy->Health = 200;
		}

		newEnemy->Init();
		entities->push_back(newEnemy);
		time = 0;
	}

	time += deltaTime;
}

void NpcManager::Release()
{
	vector<Enemy*>::iterator it;

	for ( it = npcs.begin(); it != npcs.end(); ++it )
	{
		SAFE_RELEASE(*it);
		SAFE_DELETE(*it);
	}

	npcs.clear();
}