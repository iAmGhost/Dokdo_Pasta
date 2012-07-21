#include "DXUT.h"
#include "Enemy.h"
#include "Helper.h"

using namespace std;

Enemy::Enemy(wstring texturePath, int width, int height, int rows, int cols) : Animation(texturePath, width, height, rows, cols)
{
	animChanged = false;
	AutoRemove = true;
	Power = 50;
}

Enemy::~Enemy(void)
{
}

Enemy::Enemy(const Enemy *enemy) : Animation(*enemy)
{
	animChanged = false;
}


void Enemy::Update(float deltaTime)
{
	if ( ySpeed < -25 && !animChanged )
	{
		SetAnimPos(1, 0);
		Play(15.0f, false);
		animChanged = true;
	}
	else if ( ySpeed > 25 && !animChanged )
	{
		SetAnimPos(0, 0);
		Play(15.0f, false);
		animChanged = true;
	}

	if ( Params["EnemyType"] == "2" )
	{
		if ( Helper::Random(1, 40) <= 1 )
		{
			Params["OnFire"] = "True";
		}
		else
		{
			Params["OnFire"] = "False";
		}
	}

	Animation::Update(deltaTime);
}