#include "DXUT.h"
#include "EnemyBoss.h"
#include "Helper.h"
#include "KeyboardManager.h"
#include "GameStateManager.h"

using namespace std;

EnemyBoss::EnemyBoss(wstring texturePath, int width, int height, int rows, int cols) : Animation(texturePath, width, height, rows, cols)
{
	behavior = 0;
	behaviorTime = 0;
	onlyOnce = false;
}

EnemyBoss::~EnemyBoss(void)
{
}

void EnemyBoss::Update(float deltaTime)
{
	if (KeyboardManager::GetSingleton().IsKeyPressedN(VK_F4) )
	{
		Health = 0;
	}
	Animation::Update(deltaTime);

	GameStateManager& gameState = GameStateManager::GetSingleton();
	if ( X > 500 )
	{
		X += -100 * deltaTime;
	}

	if ( behaviorTime <= 0 )
	{
		behavior = Helper::Random(0, 5);
		behaviorTime = 2.0f + Helper::Random(1, 4);
		onlyOnce = true;
	}


	if ( Params["BossType"] == "1" )
	{
		if ( behavior >= 2 )
		{
			behavior = 0;
		}
		if ( behavior == 0 )
		{
			if ( onlyOnce )
			{
				if ( Helper::Random(0, 2) > 1 )
				{
					SetSpeed(-1, 150, -1, Helper::Random(10, 30) * 10.0f);
				}
				else
				{
					SetSpeed(-1, -150, -1, Helper::Random(10, 30) * 10.0f);
				}

				onlyOnce = false;
			}

			if ( Y <= 10 )
			{
				SetSpeed(-1, 150, -1, Helper::Random(10, 30) * 10.0f);
			}
			else if ( Y >= 550 - Height )
			{
				SetSpeed(-1, -150, -1, -Helper::Random(10, 30) * 10.0f);
			}

		}
		if ( behavior == 1 )
		{
			if ( gameState.State["PlayerY"] >= Y + Height / 2 - 50)
			{
				SetSpeed(-1, 100, -1, 0);
			}
			else if ( gameState.State["PlayerY"] <= Y + Height / 2 - 50)
			{
				SetSpeed(-1, -100, -1, 0);
			}
		}
		if ( Helper::Random(0, 100) >= 95 )
		{
			Params["OnFire"] = "True";
		}
		else
		{
			Params["OnFire"] = "";
		}
	}
	else if ( Params["BossType"] == "2" )
	{
		if ( behavior >= 3 )
		{
			behavior = 0;
		}

		if ( behavior == 0 )
		{

			if ( onlyOnce )
			{
				if ( Helper::Random(0, 2) > 1 )
				{
					SetSpeed(-1, 150, -1, Helper::Random(10, 30) * 10.0f);
				}
				else
				{
					SetSpeed(-1, -150, -1, Helper::Random(10, 30) * 10.0f);
				}

				onlyOnce = false;
			}

			if ( Y <= 10 )
			{
				SetSpeed(-1, 150, -1, Helper::Random(10, 30) * 10.0f);
			}
			else if ( Y >= 550 - Height )
			{
				SetSpeed(-1, -150, -1, -Helper::Random(10, 30) * 10.0f);
			}

		}
		else if ( behavior == 1 )
		{
			if ( gameState.State["PlayerY"] >= Y + Height / 2 - 50)
			{
				SetSpeed(-1, 100, -1, 0);
			}
			else if ( gameState.State["PlayerY"] <= Y + Height / 2 - 50)
			{
				SetSpeed(-1, -100, -1, 0);
			}
		}
		else if ( behavior == 2 )
		{
			SetSpeed(-170, 0, 0, 0);
		}

		if ( X <= -600 )
			X = 800;

		if ( behavior != 2 && X > 500 )
			SetSpeed(0, -1, 0, -1);

		if ( Helper::Random(0, 100) >= 95 )
		{
			Params["OnFire"] = "True";
		}
		else
		{
			Params["OnFire"] = "";
		}
	}

	behaviorTime -= deltaTime;

	
}