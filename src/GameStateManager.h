#pragma once
#include <map>
#include <string>
#include "Singleton.h"

class GameStateManager : public Singleton<GameStateManager>
{
public:
	std::map<std::string, int> State;
	std::string GetStateString(std::string stateName);
	
	GameStateManager(void);
	void Init();
	void InitWeapons();
	void Update(float deltaTime);
	~GameStateManager(void);
};
