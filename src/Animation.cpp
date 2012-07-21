#include "DXUT.h"
#include "Animation.h"
#include "Helper.h"

using namespace std;

Animation::Animation(wstring texturePath, int width, int height, int rows, int cols) : Entity(texturePath, width, height)
{
	this->rows = rows;
	this->cols = cols;

	Width = width / cols;
	Height = height / rows;

	Col = 0;
	Row = 0;
	frame = 0;

	animSpeed = 0;
	animLoop = false;
}

Animation::~Animation(void)
{
}

Animation::Animation(const Animation *animation) : Entity(*animation)
{
	rows = animation->rows;
	cols = animation->cols;

	Width = animation->Width;
	Height = animation->Height;

	Col = animation->Col;
	Row = animation->Row;
	frame = animation->frame;

	animSpeed = animation->animSpeed;
	animLoop = animation->animLoop;
}

void Animation::Update(float deltaTime)
{
	

	Col = (int)Helper::Clamp(frame, 0, (float)cols - 1);

	if ( animLoop )
	{
		if ( animSpeed > 0 && frame >= cols )
		{
			frame = 0;
		}
		else if ( animSpeed < 0 && frame <= cols )
		{
			frame = (float)cols - 1;
		}
	}
	else
	{
		if ( Col == cols - 1 && Params["DeleteWhenEnds"] == "True" )
		{
			Params["Delete"] = "True";
		}
	}

	frame += animSpeed * deltaTime;
	frame = Helper::Clamp(frame, 0, (float)cols);

	Entity::Update(deltaTime);

	SetRect(&cropRect, (int)Col*Width, (int)Row*Height, (int)Col*Width+Width, (int)Row*Height+Height);
}

void Animation::Play(float speed, bool loop)
{
	animSpeed = speed;
	animLoop = loop;
}

void Animation::SetAnimPos(int row, int col)
{
	Row = ( row != -1 ) ? row : Row;
	Col = ( col != -1 ) ? col : Col;
}