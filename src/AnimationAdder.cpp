#include "DXUT.h"
#include "AnimationAdder.h"

using namespace std;

AnimationAdder::AnimationAdder(void)
{
	currentAnim = NULL;
}

AnimationAdder::~AnimationAdder(void)
{
}

void AnimationAdder::Init(std::list<Entity*> *entities)
{
	this->entities = entities;
}

void AnimationAdder::Add(string animationName, Animation *entity)
{
	anims[animationName] = entity;
}

Animation* AnimationAdder::Prepare(string animationName)
{
	currentAnim = new Animation(anims[animationName]);
	return currentAnim;
}

void AnimationAdder::Fire()
{
	if ( currentAnim )
	{
		currentAnim->Init();
		entities->push_back(currentAnim);
		currentAnim = NULL;
	}
}

void AnimationAdder::Release()
{
	map<string,Animation*>::iterator it;

	for ( it = anims.begin(); it != anims.end(); ++it )
	{
		SAFE_RELEASE(it->second);
		SAFE_DELETE(it->second);
	}

	anims.clear();
}