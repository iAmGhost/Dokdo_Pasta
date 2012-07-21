#pragma once
#include <map>
#include <string>
#include "Singleton.h"
#include "SDKsound.h"

class SoundManager : public Singleton<SoundManager>
{
protected:
	CSoundManager *soundManager;
	std::map<std::string, CSound*> sounds;

public:
	SoundManager(void);
	void Init();
	void Play(std::string soundName);
	void PlayLoop(std::string soundName);
	void Stop();
	void Add(std::string soundName, std::wstring soundPath);
	void Release();
	~SoundManager(void);
};
