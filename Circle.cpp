#include <cstring>
#include <sstream>
#include <cmath>

#include "Circle.h"
#include "Rectangle.h"

/**
 * @brief Construct a new Circle:: Circle object
 * 
 */
Circle::Circle() : Figure(), r(0) 
{
	setType('c');
}

/**
 * @brief Set radius
 * 
 * @param _r 
 */
void Circle::setRad(const double _r)
{
	r = _r;
}

/**
 * @brief Override operator for output
 * 
 * @param os 
 * @param c 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &os, const Circle &c)
{
	os << "Circle " << " radius = " << c.r << ' ' << c.getX() << ' ' << c.getY() << " color: " << c.getColor() << std::endl;

	return os;
}

/**
 * @brief Translate circle by given horizontal and vertical
 * 
 * @param horizontal 
 * @param vertical 
 */
void Circle::translation(double horizontal, double vertical)
{
	setX(getX() + horizontal);
	setY(getY() + vertical);
}

/**
 * @brief Check if circle is within circle or within rectangle
 * 
 * @param option 
 * @param coord_x 
 * @param coord_y 
 * @param len1 
 * @param len2 
 * @return true 
 * @return false 
 */
bool Circle::within(const char* option, double coord_x, double coord_y, double len1, double len2)
{
	if (strcmp(option, "rectangle") == 0)
	{
		Rectangle r;
		r.setX(coord_x);
		r.setY(coord_y);
		r.setWidth(len1);
		r.setLenght(len2);

		const double eps = 0.0001;
		bool one = false;
		bool two = false;
		bool three = false;
		bool four = false;
		bool five = false;

		if ((this->getX() > r.getX() && this->getX() < r.getX() + r.getWidth()) || (fabs(this->getX() - r.getX()) < eps) || (fabs(this->getX() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() > r.getY() && this->getY() < r.getY() + r.getLength()) || (fabs(this->getY() - r.getY()) < eps) || (fabs(this->getY() - r.getY() - r.getLength()) < eps))
			{
				one = true;
			}
		}

		if ((this->getX() + this->getRad() > r.getX() && this->getX() + this->getRad() < r.getX() + r.getWidth()) || (fabs(this->getX() + this->getRad() - r.getX()) < eps) || (fabs(this->getX() + this->getRad() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() > r.getY() && this->getY() < r.getY() + r.getLength()) || (fabs(this->getY() - r.getY()) < eps) || (fabs(this->getY() - r.getY() - r.getLength()) < eps))
			{
				two = true;
			}
		}

		if ((this->getX() - this->getRad() > r.getX() && this->getX() - this->getRad() < r.getX() + r.getWidth()) || (fabs(this->getX() - this->getRad() - r.getX()) < eps) || (fabs(this->getX() - this->getRad() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() > r.getY() && this->getY() < r.getY() + r.getLength()) || (fabs(this->getY() - r.getY()) < eps) || (fabs(this->getY() - r.getY() - r.getLength()) < eps))
			{
				three = true;
			}
		}

		if ((this->getX() > r.getX() && this->getX() < r.getX() + r.getWidth()) || (fabs(this->getX() - r.getX()) < eps) || (fabs(this->getX() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() + this->getRad() > r.getY() && this->getY() + this->getRad() < r.getY() + r.getLength()) || (fabs(this->getY() + this->getRad() - r.getY()) < eps) || (fabs(this->getY() + this->getRad() - r.getY() - r.getLength()) < eps))
			{
				four = true;
			}
		}

		if ((this->getX() > r.getX() && this->getX() < r.getX() + r.getWidth()) || (fabs(this->getX() - r.getX()) < eps) || (fabs(this->getX() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() - this->getRad() > r.getY() && this->getY() - this->getRad() < r.getY() + r.getLength()) || (fabs(this->getY() - this->getRad() - r.getY()) < eps) || (fabs(this->getY() - this->getRad() - r.getY() - r.getLength()) < eps))
			{
				five = true;
			}
		}

		if (one && two && three && four && five)
		{
			return true;
		}

		return false;
	}
	else if (strcmp(option, "circle") == 0)
	{
		Circle c;
		c.setRad(len1);
        c.setX(coord_x);
        c.setY(coord_y);
		const double eps = 0.0001;
		bool one = false;
		bool two = false;
		bool three = false;
		bool four = false;
		bool five = false;
		
		if ((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) < c.getRad() * c.getRad())
		{
			one = true;
		}
		else if (fabs((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			one = true;
		}
		if ((this->getX() + this->getRad() - c.getX()) * (this->getX() + this->getRad() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) < c.getRad() * c.getRad())
		{
			two = true;
		}
		else if (fabs((this->getX() + this->getRad() - c.getX()) * (this->getX() + this->getRad() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			two = true;
		}

		if ((this->getX() - this->getRad() - c.getX()) * (this->getX() - this->getRad() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) < c.getRad() * c.getRad())
		{
			three = true;
		}
		else if (fabs((this->getX() - this->getRad() - c.getX()) * (this->getX() - this->getRad() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			three = true;
		}
		if ((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() + this->getRad() - c.getY()) * (this->getY() + this->getRad() - c.getY()) < c.getRad() * c.getRad())
		{
			four = true;
		}
		else if (fabs((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() + this->getRad() - c.getY()) * (this->getY() + this->getRad() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			four = true;
		}
		if ((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - this->getRad() - c.getY()) * (this->getY() - this->getRad() - c.getY()) < c.getRad() * c.getRad())
		{
			five = true;
		}
		else if (fabs((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - this->getRad() - c.getY()) * (this->getY() - this->getRad() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			five = true;
		}

		if (one && two && three && four && five)
		{
			return true;
		}

		return false;
	}
}

/**
 * @brief Convert line from SVG file to char array
 * 
 * @return char* 
 */
char* Circle::convertToString()
{
	//<<circle cx="5" cy="5" r="10" fill="blue" />
	char* temp = new char[1024];
	strcpy(temp, "<circle cx=\"");

	char str[100];
    std::stringstream ss;
    ss << this->getX();
    ss >> str;
    
	strcat(temp, str);
	strcat(temp, "\" cy=\"");

	ss.clear();
	ss << this->getY();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" r=\"");

	ss.clear();
	ss << this->getRad();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" fill=\"");
	strcat(temp, this->getColor());
	strcat(temp, "\" />\n");

	return temp;
}

/**
 * @brief Get data from char array and set it to object of class Circle
 * 
 * @param str 
 */
void Circle::convertFromString(const char* str)
{
	//<<circle cx="5" cy="5" r="10" fill="blue" />
	int len = strlen(str);
	char* temp = new char[10];
	int index = 0;
	for (int i = 0; i < len; i++) 
	{
		if((str[i] == 'x') && (str[i+1] == '='))
		{
			for (int j = i + 3; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setX(atof(temp));
			index = 0;
		}
		if((str[i] == 'y') && (str[i+1] == '='))
		{
			for (int j = i + 3; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setY(atof(temp));
			index = 0;
		}
		if((str[i] == 'r') && (str[i+1] == '='))
		{
			for (int j = i + 3; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setRad(atof(temp));
			index = 0;
		}
		if((str[i] == 'l') && (str[i+1] == '='))
		{
			for (int j = i + 3; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setColor(temp);
			index = 0;
		}
	}
	delete[] temp;
}