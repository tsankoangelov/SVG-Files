#include <cstring>

#include "Figure.h"

void Figure::copy(const Figure &other)
{
	color = new char[strlen(other.color) + 1];
	strcpy(color, other.color);
	x = other.x;
	y = other.y;
}

void Figure::clean()
{
	delete[] color;
}

/**
 * @brief Construct a new Figure:: Figure object
 * 
 */

Figure::Figure()
{
	x = 0;
	y = 0;
	color = new char[9];
	strcpy(color, "No color");
}

/**
 * @brief Construct a new Figure:: Figure object
 * 
 * @param _color 
 * @param _x 
 * @param _y 
 */

Figure::Figure(const char *_color, const double _x, const double _y) : Figure()
{
	setX(_x);
	setY(_y);
	setColor(_color);
}

/**
 * @brief Construct a new Figure:: Figure object
 * 
 * @param other 
 */

Figure::Figure(const Figure &other)
{
	copy(other);
}

/**
 * @brief Override operator=
 * 
 * @param other 
 * @return Figure& 
 */

Figure &Figure::operator=(const Figure &other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}

	return *this;
}

/**
 * @brief Destroy the Figure:: Figure object
 * 
 */

Figure::~Figure()
{
	clean();
}

/**
 * @brief Set color
 * 
 * @param _color 
 */

void Figure::setColor(const char * _color)
{
	delete[] color;
	color = new char[strlen(_color) + 1];
	strcpy(color, _color);
}

/**
 * @brief Set X
 * 
 * @param _x 
 */

void Figure::setX(const double _x) 
{
	x = _x;
}

/**
 * @brief Set y
 * 
 * @param _y 
 */

void Figure::setY(const double _y)
{
	y = _y;
}

/**
 * @brief Set Type
 * 
 * @param t 
 */

void Figure::setType(const char t)
{
	type = t;
}

/**
 * @brief Override operator for output
 * 
 * @param os 
 * @param f 
 * @return std::ostream& 
 */

std::ostream &operator<<(std::ostream &os, const Figure &f)
{
	os << "color: " << f.color << ' ' << f.x << ' ' << f.y << std::endl;

	return os;
}