#include "DXUT.h"
#include "Font.h"
#include "DeviceManager.h"

Font::Font(std::wstring fontFace, int width, int height, int fontHeight, int fontWidth, int fontWeight, bool italic) : Entity(L"", width, height)
{
	Params["Text"] = "";
	D3DXCreateFontW(DeviceManager::GetSingleton().GetDevice(), fontHeight, fontWidth, fontWeight, 1, italic, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontFace.c_str(), &font);
}

Font::~Font(void)
{
}

void Font::Draw(LPDIRECT3DDEVICE9 device)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	font->DrawTextA(sprite, Params["Text"].c_str(), Params["Text"].length(), &Rect, D3DFMT_UNKNOWN, color);
	sprite->End();
}

void Font::Release()
{
	SAFE_RELEASE(font);
	SAFE_DELETE(font);
	Entity::Release();
}