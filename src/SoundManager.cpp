#include "DXUT.h"
#include "SoundManager.h"
#include <vector>

using namespace std;

SoundManager::SoundManager(void)
{
	soundManager = new CSoundManager();
}

SoundManager::~SoundManager(void)
{
	SAFE_DELETE(soundManager);
}

void SoundManager::Init()
{
	soundManager->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
}

void SoundManager::Play(string soundName)
{
	if ( sounds[soundName] != NULL )
	{
		sounds[soundName]->Reset();
		sounds[soundName]->Play(0, 0, DSBVOLUME_MAX);
	}
}

void SoundManager::PlayLoop(string soundName)
{
	if ( sounds[soundName] != NULL && !sounds[soundName]->IsSoundPlaying() )
	{
		sounds[soundName]->Reset();
		sounds[soundName]->Play(0, 0, -800);
	}
}

void SoundManager::Add(string soundName, wstring soundPath)
{
	sounds[soundName] = NULL;
	const wchar_t *temp = soundPath.c_str();
	vector<wchar_t> buffer(temp, temp + soundPath.size() + 1);
	wchar_t *buffer_ptr = &buffer[0];

	soundManager->Create(&sounds[soundName], buffer_ptr, DSBCAPS_CTRLVOLUME );
}

void SoundManager::Stop()
{
	map<string, CSound*>::iterator it;

	for ( it = sounds.begin(); it != sounds.end(); ++it )
	{
		if ( it->second )
			it->second->Stop();
	}
}
void SoundManager::Release()
{
	SAFE_DELETE(soundManager);
	sounds.clear();
}