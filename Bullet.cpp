#include "DxLib.h"
#include "Bullet.h"

void Bullet::drawBullet() 
{
	DrawCircleAA(coord_bullet.x, coord_bullet.y, 5, 150, bullet_color, 1);
}

void Bullet::moveBullet()
{
	coord_bullet.x += dir._x;
	coord_bullet.y += dir._y;

	drawBullet();
}

Point Bullet::getPos()
{
	return coord_bullet;
}