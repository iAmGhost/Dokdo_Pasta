#pragma once
#include <string>
#include "Entity.h"

class Font : public Entity
{
protected:
	LPD3DXFONT font;

public:
	Font(std::wstring fontFace, int width, int height, int fontHeight, int fontWidth, int fontWeight, bool italic);
	void Draw(LPDIRECT3DDEVICE9 device);
	void Release();
	~Font(void);
};
