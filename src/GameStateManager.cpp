#include "DXUT.h"
#include "GameStateManager.h"
#include "Helper.h"

using namespace std;

GameStateManager::GameStateManager(void)
{
}

GameStateManager::~GameStateManager(void)
{
}

void GameStateManager::InitWeapons()
{
	State["Speed"] = 0;
	State["Power"] = 0;
	State["Addon"] = 0;
	State["Weapon"] = 0;
}
void GameStateManager::Init()
{
	State["AirPanic"] = 0;
	State["PlayerMode"] = 0;
	State["GameOver"] = 0;
	State["Clear"] = 0;
	State["Life"] = 5;

	State["PlayerX"] = -1337;
	State["PlayerY"] = -1337;

	State["MaxHealth"] = 100;
	State["Health"] = 100;

	State["BossHealth"] = 3000;
	State["BossMaxHealth"] = 3000;

	State["Score"] = 0;
	State["Exp"] = 0;
	State["NextExp"] = 1000;
	State["Boss"] = 0;
	State["Level"] = 1;

	State["Shop_Power"] = 15000;
	State["Shop_Speed"] = 10000;
	State["Shop_MoreSpeed"] = 30000;
	State["Shop_Addon"] = 20000;
	State["Shop_Weapon"] = 15000;

	State["1up"] = 0;
	State["1upCounter"] = 0;
	State["1upCount"] = 0;
	State["1upScore"] = 0;

	InitWeapons();

}

void GameStateManager::Update(float deltaTime)
{
	State["Score"] = (int)Helper::Clamp((float)State["Score"], 0, 99999999);

	if ( State["Exp"] >= State["NextExp"] )
	{
		State["Exp"] = 0;
		State["NextExp"] += 800;
		if ( State["Level"] == 15 ) State["NextExp"] += 10000;
		State["Level"]++;
	}

	State["1upCount"] = State["Score"] / 50000;

	if ( State["1upCounter"] != State["1upCount"] && State["Score"] >= State["1upScore"] )
	{
		State["1up"] = 1;
		State["1upCounter"] = State["1upCount"];
		State["1upScore"] = State["Score"];
	}
}

string GameStateManager::GetStateString(string stateName)
{
	char buffer[10];
	_itoa_s(State[stateName], buffer, 10);
	return buffer;
}