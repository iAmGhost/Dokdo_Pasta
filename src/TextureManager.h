#pragma once
#include <map>
#include <string>
#include "Singleton.h"

class TextureManager : public Singleton<TextureManager>
{
protected:
	std::map<std::wstring, LPDIRECT3DTEXTURE9> textures;

public:
	TextureManager(void);
	void Add(std::wstring texturePath);
	LPDIRECT3DTEXTURE9 Get(std::wstring texturePath);
	void Init();
	void Release();
	~TextureManager(void);
};
