#pragma once
#include <map>
#include <string>

class Entity
{
protected:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 position;
	D3DXCOLOR color;
	RECT cropRect;

	

	std::wstring texturePath;
	

public:
	float xSpeed, ySpeed, xMod, yMod;
	bool AutoRemove;
	RECT Rect, HitRect, HitMod;
	std::map<std::string, std::string> Params;
	float X, Y;
	float XSpeedEmergencyModder;
	int Width, Height, TextureWidth, TextureHeight;
	int Health, Damage, Power;

	Entity(const Entity *entity);
	Entity(std::wstring texturePath, int width, int height);
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Draw(LPDIRECT3DDEVICE9 device);
	virtual void SetPos(float x, float y);
	virtual void SetColor(D3DXCOLOR color);
	virtual void SetSpeed(float xspeed, float yspeed, float xmod, float ymod);
	virtual void Release();
	~Entity(void);
};
