#pragma once
#include<math.h>
class Eater{
public:
	double x, y;
	double v, a;
	bool alive = true;
	int collide(int X, int Y, int flag) {
		if (flag == 1) // wall
		{
			if (abs(x - X) < 30 || abs(y - Y) < 30) {
				x = 
			}
			return 0
		}
		else if (flag == 0) // dots
		{
			return 2;
		}
		else if (flag == -1) // enemy
		{
			alive = false;
			return -1;
		}
		return 1;
	}
};