#pragma once
#include <math.h>
#include "Point.h"

#define PI 3.141592653589793

class Bullet
{
	public:
		Bullet(int x, int y, double a, int c)
			: coord_bullet(x, y), angle(a * PI / 180.0), dir(0, 0)
		{
			bullet_color = 255;

			//if (c % 8 == 0) bullet_color = 0b00000000111111110000000000000000;
			//else bullet_color = 255;

			dir = Vector2(cos(angle), sin(angle));
		};

			void drawBullet();
			void moveBullet();
			Point getPos();

	private:
		double angle;
		Point coord_bullet;
		Vector2 dir;

		unsigned int bullet_color;
};