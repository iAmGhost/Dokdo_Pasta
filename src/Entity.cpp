#include "DXUT.h"
#include "Entity.h"
#include "DeviceManager.h"
#include "TextureManager.h"
#include "Helper.h"

using namespace std;

Entity::Entity(wstring texturePath, int width, int height)
{

	XSpeedEmergencyModder = 0;

	this->texturePath = texturePath;

	texture = NULL;
	sprite = NULL;

	TextureWidth = width;
	TextureHeight = height;

	Width = width;
	Height = height;

	xSpeed = 0;
	ySpeed = 0;
	xMod = 0;
	yMod = 0;

	color = D3DCOLOR_ARGB(255, 255, 255 ,255);

	SetRect(&Rect, 0, 0, 10, 10);
	SetRect(&cropRect, 0, 0, width, height);
	SetRect(&HitRect, 0, 0, 0, 0);
	SetRect(&HitMod, 0, 0, 0, 0);
	position = D3DXVECTOR3(-12345, -12345, 0.0f);

	Health = 13371337;
	Damage = 0;
	Power = 0;

	AutoRemove = false;

	Init();
}

Entity::Entity(const Entity *entity)
{
	this->texturePath = entity->texturePath;

	TextureWidth = entity->TextureWidth;
	TextureHeight = entity->TextureHeight;

	Width = entity->Width;
	Height = entity->Height;

	xSpeed = entity->xSpeed;
	ySpeed = entity->ySpeed;
	xMod = entity->xMod;
	yMod = entity->yMod;

	color = entity->color;

	cropRect = entity->cropRect;
	HitRect = entity->HitRect;
	HitMod = entity->HitMod;
	Rect = entity->Rect;
	position = entity->position;

	Health = entity->Health;
	Damage = entity->Damage;
	Power = entity->Power;

	AutoRemove = entity->AutoRemove;

	Init();
}

Entity::~Entity(void)
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(texture);
}

void Entity::Init()
{
	texture = TextureManager::GetSingleton().Get(texturePath);
	sprite = DeviceManager::GetSingleton().GetSprite();
}

void Entity::Update(float deltaTime)
{
	X += XSpeedEmergencyModder * deltaTime + xSpeed * deltaTime;
	Y += ySpeed * deltaTime;

	xSpeed += xMod * deltaTime;
	ySpeed += yMod * deltaTime;

	position.x = X;
	position.y = Y;

	if ( Damage > 0 )
	{
		Health -= Damage;
		Damage = 0;
		Params["OnDamaged"] = "True";
	}
	else
	{
		Params["OnDamaged"] = "";
	}

	if ( Health <= 0 )
	{
		Params["Crashed"] = "True";
	}

	if ( !Helper::HitTest(Rect, DeviceManager::GetSingleton().GetScreenRect()) && AutoRemove )
	{
		Params["Delete"] = "True";
	}



	SetRect(&cropRect, 0, 0, Width, Height);
	SetRect(&Rect, (int)X, (int)Y, (int)X + Width, (int)Y + Height);
	SetRect(&HitRect, Rect.left - HitMod.left, Rect.top - HitMod.top, Rect.right - HitMod.right, Rect.bottom - HitMod.bottom);
}

void Entity::Draw(LPDIRECT3DDEVICE9 device)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, &cropRect, NULL, &position, color);
	sprite->End();
}

void Entity::SetPos(float x, float y)
{
	X = ( x != -1 ) ? x : X;
	Y = ( y != -1 ) ? y : Y;
}

void Entity::SetColor(D3DXCOLOR color)
{
	this->color = color;
}

void Entity::SetSpeed(float xspeed, float yspeed, float xmod, float ymod)
{
	xSpeed = ( xspeed != -1 ) ? xspeed : xSpeed;
	ySpeed = ( yspeed != -1 ) ? yspeed : ySpeed;
	xMod = ( xmod != -1 ) ? xmod : xMod;
	yMod = ( ymod != -1 ) ? ymod : yMod;
}

void Entity::Release()
{
	SAFE_RELEASE(sprite);
}