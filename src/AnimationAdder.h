#pragma once
#include <map>
#include <list>
#include <string>
#include "Animation.h"
#include "Singleton.h"

class AnimationAdder : public Singleton<AnimationAdder>
{
protected:
	std::list<Entity*> *entities;
	std::map<std::string, Animation*> anims;

	Animation *currentAnim;

public:
	AnimationAdder(void);
	void Init(std::list<Entity*> *entities);
	void Add(std::string animationName, Animation *entity);
	Animation* Prepare(std::string animationName);
	void Fire();
	void Release();
	~AnimationAdder(void);
};
