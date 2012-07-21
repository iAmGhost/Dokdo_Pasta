#include "DXUT.h"
#include "DeviceManager.h"

DeviceManager::DeviceManager(void)
{
	SetRect(&screenRect, -50, -50, 850, 650);
}

DeviceManager::~DeviceManager(void)
{
	//SAFE_DELETE(device);
}

void DeviceManager::Init(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
}

LPDIRECT3DDEVICE9 DeviceManager::GetDevice()
{
	return device;
}

RECT DeviceManager::GetScreenRect()
{
	return screenRect;
}

LPD3DXSPRITE DeviceManager::GetSprite()
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(device, &sprite);

	return sprite;
}