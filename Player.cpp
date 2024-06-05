#include "Player.h"

void Player::drawPlayer()
{
	DrawCircleAA(coord_player.x, coord_player.y, size, 150, color, 1);
}
void Player::move(int move_x, int move_y)
{
	coord_player = Point(move_x, move_y);

	drawPlayer();
}

bool Player::isLife()
{
	return life;
}
void Player::playerDie()
{
	life = false;
	color = 0b00000000000000001111111100000000;
}
bool Player::isCollision(Bullet* bullet)
{
	Point bullet_pos = bullet -> getPos();
	double distance = fabs(sqrt(pow(bullet_pos.x - coord_player.x, 2)
							+ pow(bullet_pos.y - coord_player.y, 2)));

	if (distance <= size) return true;
	else return false;
}