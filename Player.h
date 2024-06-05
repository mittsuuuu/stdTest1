#pragma once
#include "DxLib.h"
#include "Point.h"
#include "Bullet.h"

class Player
{
	public:

		Player(int x, int y)
			: coord_player(x, y), size(5), life(true)
		{
			color = 0b00000000000000000000000011111111;
			drawPlayer();
		};
		void move(int move_x, int move_y);
		void drawPlayer();
		bool isCollision(Bullet* bullet);

		bool isLife();
		void playerDie();

	private:
		Point coord_player;

		unsigned int color;
		int size;
		bool life;

};