#include "DXUT.h"
#include "TextureManager.h"
#include "DeviceManager.h"

using namespace std;

TextureManager::TextureManager(void)
{
}

TextureManager::~TextureManager(void)
{
}

void TextureManager::Add(wstring texturePath)
{
	if ( !textures[texturePath] )
		textures[texturePath] = NULL;
}

LPDIRECT3DTEXTURE9 TextureManager::Get(std::wstring texturePath)
{
	LPDIRECT3DTEXTURE9 texture = textures[texturePath];
	return ( texture ) ? texture : NULL;
}

void TextureManager::Init()
{
	LPDIRECT3DDEVICE9 device = DeviceManager::GetSingleton().GetDevice();

	map<wstring, LPDIRECT3DTEXTURE9>::iterator it;

	for ( it = textures.begin(); it != textures.end(); ++it )
	{
		D3DXCreateTextureFromFileExW(device, it->first.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
			D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, true, NULL, NULL, &it->second);
	}
}

void TextureManager::Release()
{
	map<wstring, LPDIRECT3DTEXTURE9>::iterator it;

	for ( it = textures.begin(); it != textures.end(); ++it )
	{
		SAFE_RELEASE(it->second);
		SAFE_DELETE(it->second);
	}

	textures.clear();
}