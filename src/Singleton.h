#pragma once

template <class T> class Singleton
{
protected:
	Singleton(void){};
	virtual ~Singleton(void){};

public:
	static T& GetSingleton()
	{
		static T singleton;
		return singleton;
	}
};
