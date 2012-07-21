#pragma once
#include "Singleton.h"

class KeyboardManager : public Singleton<KeyboardManager>
{
protected:
	int keyState[150];

public:
	KeyboardManager(void);
	void Update(UINT keyCode, bool keyDown);
	bool IsKeyPressed(int keyCode);
	bool IsKeyPressedN(int keyCode);
	~KeyboardManager(void);
};
