#pragma once
#include "Singleton.h"

class DeviceManager : public Singleton<DeviceManager>
{
protected:
	LPDIRECT3DDEVICE9 device;
	RECT screenRect;

public:
	DeviceManager(void);
	void Init(LPDIRECT3DDEVICE9 device);
	LPDIRECT3DDEVICE9 GetDevice();
	LPD3DXSPRITE GetSprite();
	RECT GetScreenRect();
	~DeviceManager(void);
};
