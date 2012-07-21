#pragma once

class Helper
{
public:
	Helper(void){};
	~Helper(void){};

	static float Clamp(float num, float min, float max)
	{
		return ( num < min ) ? min : ( ( num > max ) ? max : num );
	}

	static bool HitTest(RECT a, RECT b)
	{
		RECT dummy;
		return ( IntersectRect(&dummy, &a, &b) ) ? true : false;
	}

	static int Random(int min, int max)
	{
		return rand() % (max-min) + min; 
	}
};
