#include "DXUT.h"
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(void)
{
	for ( int i = 0; i < 150; i++ )
	{
		keyState[i] = 0;
	}
}

KeyboardManager::~KeyboardManager(void)
{
}

void KeyboardManager::Update(UINT keyCode, bool keyDown)
{
	if ( keyDown && keyState[keyCode] < 1000 )
	{
		keyState[keyCode]++;
	}
	else if ( !keyDown )
	{
		keyState[keyCode] = 0;
	}
}

bool KeyboardManager::IsKeyPressed(int keyCode)
{
	return ( keyState[keyCode] > 0 ) ? true : false;
}

bool KeyboardManager::IsKeyPressedN(int keyCode)
{
	if ( keyState[keyCode] == 1 )
	{
		keyState[keyCode]++;

		return true;
	}

	return false;
}