#pragma once
class Point //ç¿ïWÇàµÇ§ÉNÉâÉX
{
	public:
		Point(double x, double y) : x(x), y(y) {}

		double x;
		double y;

		Point operator+(const Point& other) const {
			return Point(x + other.x, y + other.y);
		}
		Point operator-(const Point& other) const {
			return Point(x - other.x, y - other.y);
		}

	private:
};

class Vector2
{
	public:
		double _x;
		double _y;

		Vector2(double x, double y) :_x(x), _y(y) {};

		double x();
		double y();

		Vector2 operator+(const Vector2& other) const
		{
			return Vector2(_x + other._x, _y + other._y);
		}
		Vector2 operator-(const Vector2& other) const
		{
			return Vector2(_x - other._x, _y - other._y);
		}

		Vector2 operator+(const double z)
		{
			return Vector2(_x + z, _y + z);
		}

	private:
};
//
//double Vector2::x()
//{
//	return _x;
//}
//double Vector2::y()
//{
//	return _y;
//}
