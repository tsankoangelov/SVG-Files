#include <cstring>
#include <sstream>
#include <cmath>

#include "Rectangle.h"
#include "Circle.h"

/**
 * @brief Construct a new Rectangle:: Rectangle object
 * 
 */
Rectangle::Rectangle() : Figure(), length(0), width(0) 
{
	setType('r');
}

/**
 * @brief Set Lenght
 * 
 * @param _length 
 */
void Rectangle::setLenght(const double _length) 
{
	length = _length;
}

/**
 * @brief Set Width
 * 
 * @param _width 
 */
void Rectangle::setWidth(const double _width)
{
	width = _width;
}

/**
 * @brief Override operator for output
 * 
 * @param os 
 * @param r 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &os,const Rectangle& r)
{
	os << "Rectangle " << ' ' << r.getX() << ' ' << r.getY() << ' ' << r.length << ' ' << r.width << ' ' << r.getColor();

	return os;
}

/**
 * @brief Translate rectangle by given horizontal and vertical
 * 
 * @param horizontal 
 * @param vertical 
 */
void Rectangle::translation(double horizontal, double vertical)
{
	setX(getX() + horizontal);
	setY(getY() + vertical);
}

/**
 * @brief Check if rectangle is within circle or within rectangle
 * 
 * @param option 
 * @param coord_x 
 * @param coord_y 
 * @param len1 
 * @param len2 
 * @return true 
 * @return false 
 */
bool Rectangle::within(const char* option, double coord_x, double coord_y, double len1, double len2)
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

		if ((this->getX() > r.getX() && this->getX() < r.getX() + r.getWidth()) || (fabs(this->getX() - r.getX()) < eps) || (fabs(this->getX() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() > r.getY() && this->getY() < r.getY() + r.getLength()) || (fabs(this->getY() - r.getY()) < eps) || (fabs(this->getY() - r.getY() - r.getLength()) < eps))
			{
				one = true;
			}
		}

		if ((this->getX() + this->getWidth() > r.getX() && this->getX() + this->getWidth() < r.getX() + r.getWidth()) || (fabs(this->getX() + this->getWidth() - r.getX()) < eps) || (fabs(this->getX() + this->getWidth() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() > r.getY() && this->getY() < r.getY() + r.getLength()) || (fabs(this->getY() - r.getY()) < eps) || (fabs(this->getY() - r.getY() - r.getLength()) < eps))
			{
				two = true;
			}
		}

		if ((this->getX() > r.getX() && this->getX() < r.getX() + r.getWidth()) || (fabs(this->getX() - r.getX()) < eps) || (fabs(this->getX() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() + this->getLength() > r.getY() && this->getY() + this->getLength() < r.getY() + r.getLength()) || (fabs(this->getY() + this->getLength() - r.getY()) < eps) || (fabs(this->getY() + this->getLength() - r.getY() - r.getLength()) < eps))
			{
				three = true;
			}
		}

		if ((this->getX() + this->getWidth() > r.getX() && this->getX() + this->getWidth() < r.getX() + r.getWidth()) || (fabs(this->getX() + this->getWidth() - r.getX()) < eps) || (fabs(this->getX() + this->getWidth() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() + this->getLength() > r.getY() && this->getY() + this->getLength() < r.getY() + r.getLength()) || (fabs(this->getY() + this->getLength() - r.getY()) < eps) || (fabs(this->getY() + this->getLength() - r.getY() - r.getLength()) < eps))
			{
				four = true;
			}
		}

		if (one && two && three && four)
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
		
		if ((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) < c.getRad() * c.getRad())
		{
			one = true;
		}
		else if (fabs((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			one = true;
		}
		if ((this->getX() + this->getWidth() - c.getX()) * (this->getX() + this->getWidth() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) < c.getRad() * c.getRad())
		{
			two = true;
		}
		else if (fabs((this->getX() + this->getWidth() - c.getX()) * (this->getX() + this->getWidth() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			two = true;
		}
		if ((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() + this->getLength() - c.getY()) * (this->getY() + this->getLength() - c.getY()) < c.getRad() * c.getRad())
		{
			three = true;
		}
		else if (fabs((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() + this->getLength() - c.getY()) * (this->getY() + this->getLength() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			three = true;
		}
		if ((this->getX() + this->getWidth() - c.getX()) * (this->getX() + this->getWidth() - c.getX()) + (this->getY() + this->getLength() - c.getY()) * (this->getY() + this->getLength() - c.getY()) < c.getRad() * c.getRad())
		{
			four = true;
		}
		else if (fabs((this->getX() + this->getWidth() - c.getX()) * (this->getX() + this->getWidth() - c.getX()) + (this->getY() + this->getLength() - c.getY()) * (this->getY() + this->getLength() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			four = true;
		}

		if (one && two && three && four)
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
char* Rectangle::convertToString()
{
	//<rect x="5" y="5" width="10" height="10" fill="green" />
	char* temp = new char[1024];
	strcpy(temp, "<rect x=\"");

	char str[100];
    std::stringstream ss;
    ss << this->getX();
    ss >> str;
    
	strcat(temp, str);
	strcat(temp, "\" y=\"");

	ss.clear();
	ss << this->getY();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" width=\"");

	ss.clear();
	ss << this->getWidth();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" height=\"");

	ss.clear();
	ss << this->getLength();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" fill=\"");
	strcat(temp, this->getColor());
	strcat(temp, "\" />\n");

	return temp;
	
}

/**
 * @brief Get data from char array and set it to object of class Rectangle
 * 
 * @param str 
 */
void Rectangle::convertFromString(const char* str)
{
	//<rect x="5" y="5" width="10" height="10" fill="green" />
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
		if((str[i] == 'h') && (str[i+1] == '='))
		{
			for (int j = i + 3; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setWidth(atof(temp));
			index = 0;
		}
		if((str[i] == 't') && (str[i+1] == '='))
		{
			for (int j = i + 3; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setLenght(atof(temp));
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