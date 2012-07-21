#include "DXUT.h"
#include "Player.h"
#include "KeyboardManager.h"
#include "GameStateManager.h"
#include "Helper.h"

Player::Player(std::wstring texturePath, int width, int height, int rows, int cols) : Animation(texturePath, width, height, rows, cols)
{
	MoveSpeed = 100;
	MoveSpeedMod = 0;
	Power = 100;
	Params["Switching"] = "True";
}

Player::~Player(void)
{
}

void Player::Update(float deltaTime)
{

	if ( GameStateManager::GetSingleton().State["Clear"] )
	{
		Health = 110;
	}
	KeyboardManager& keyboard = KeyboardManager::GetSingleton();


	if ( Params["Switching"] == "True" )
	{
		Params["OnFire"] = "";
		if ( X > -100 )
		{
			X -= 200 * deltaTime;
			Params["Type"] = "";
			
		}
	}
	else if ( Params["Switching"] != "True" && X <= -1 )
	{
		X += 150 * deltaTime;
		Power = 0;
		Damage = 0;
	}
	else if ( Params["Switching"] != "True" )
	{
		Params["Type"] = "Player";
		Power = 100;

		if ( Params["Name"] != "PlayerBoat" )
		{
			if ( keyboard.IsKeyPressedN(VK_UP) )
			{
				SetAnimPos(1, 0);
				Play(20.0f, false);
			}
			else if ( keyboard.IsKeyPressedN(VK_DOWN) )
			{
				SetAnimPos(0, 0);
				Play(20.0f, false);
			}
			else if ( !keyboard.IsKeyPressed(VK_UP) && !keyboard.IsKeyPressed(VK_DOWN) )
			{
				Play(-20.0f, false);
			}

			if ( keyboard.IsKeyPressed(VK_UP) && Y > 0 )
			{
				Y -= (MoveSpeed + MoveSpeedMod) * deltaTime;
				Y = Helper::Clamp(Y, 0, (float)600 - Height + 40 - 100);
			}
			else if ( keyboard.IsKeyPressed(VK_DOWN) && Y < 600 - Height + 40 - 100)
			{
				Y += (MoveSpeed + MoveSpeedMod) * deltaTime;
				Y = Helper::Clamp(Y, 0, (float)600 - Height + 40 - 100);
			}
		}

		if ( keyboard.IsKeyPressed(VK_LEFT) && X > 0 )
		{
			X -= (MoveSpeed + MoveSpeedMod) * deltaTime;
			X = Helper::Clamp(X, 0, (float)800 - Width);
		}
		else if ( keyboard.IsKeyPressed(VK_RIGHT) && X < 800 - Width)
		{
			X += (MoveSpeed + MoveSpeedMod) * deltaTime;
			X = Helper::Clamp(X, 0, (float)800 - Width);
		}


		if ( keyboard.IsKeyPressedN('D') )
		{
			Params["OnFire"] = "True";
		}
		else if ( !keyboard.IsKeyPressedN('D') )
		{
			Params["OnFire"] = "";
		}

	}
	Animation::Update(deltaTime);
}