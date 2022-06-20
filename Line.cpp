#include <cstring>
#include <sstream>
#include <cmath>

#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"

/**
 * @brief Construct a new Line:: Line object
 * 
 */
Line::Line() : x1(0), y1(0) , Figure() 
{
	setType('l');
}

/**
 * @brief Set X1
 * 
 * @param _x 
 */
void Line::setX1(const double _x) 
{
	x1 = _x;
}

/**
 * @brief Set Y1
 * 
 * @param _y 
 */
void Line::setY1(const double _y)
{
	y1 = _y;
}

/**
 * @brief Override operator for output
 * 
 * @param os 
 * @param l 
 * @return std::ostream& 
 */

std::ostream &operator<<(std::ostream &os,const Line& l)
{
	os << "Line:" << " color: " << l.getColor() << ' ' << l.getX() << ' ' << l.getY() << l.x1 << ' ' << l.y1 << ' '  << std::endl;

	return os;
}

/**
 * @brief Translate line by given horizontal and vertical
 * 
 * @param horizontal 
 * @param vertical 
 */

void Line::translation(double horizontal, double vertical)
{
	setX(getX() + horizontal);
	setY(getY() + vertical);
	setX1(x1 + horizontal);
	setY1(y1 + vertical);
}

/**
 * @brief Check if line is within circle or within rectangle
 * 
 * @param option 
 * @param coord_x 
 * @param coord_y 
 * @param len1 
 * @param len2 
 * @return true 
 * @return false 
 */

bool Line::within(const char* option, double coord_x, double coord_y, double len1, double len2)
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
		
		if ((this->getX() > r.getX() && this->getX() < r.getX() + r.getWidth()) || (fabs(this->getX() - r.getX()) < eps) || (fabs(this->getX() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY() > r.getY() && this->getY() < r.getY() + r.getLength()) || (fabs(this->getY() - r.getY()) < eps) || (fabs(this->getY() - r.getY() - r.getLength()) < eps))
			{
				one = true;
			}
		}

		if ((this->getX1() > r.getX() && this->getX1() < r.getX() + r.getWidth()) || (fabs(this->getX1() - r.getX()) < eps) || (fabs(this->getX1() - r.getX() - r.getWidth()) < eps))
		{
			if ((this->getY1() > r.getY() && this->getY1() < r.getY() + r.getLength()) || (fabs(this->getY1() - r.getY()) < eps) || (fabs(this->getY1() - r.getY() - r.getLength()) < eps))
			{
				two = true;
			}
		}

		if (one && two)
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

		if ((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) < c.getRad() * c.getRad())
		{
			one = true;
		}
		else if (fabs((this->getX() - c.getX()) * (this->getX() - c.getX()) + (this->getY() - c.getY()) * (this->getY() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			one = true;
		}

		if ((this->getX1() - c.getX()) * (this->getX1() - c.getX()) + (this->getY1() - c.getY()) * (this->getY1() - c.getY()) < c.getRad() * c.getRad())
		{
			two = true;
		}
		else if (fabs((this->getX1() - c.getX()) * (this->getX1() - c.getX()) + (this->getY1() - c.getY()) * (this->getY1() - c.getY()) - (c.getRad() * c.getRad())) < eps)
		{
			two = true;
		}

		if (one && two)
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
char* Line::convertToString()
{
	//<line x1="0" y1="80" x2="100" y2="20" stroke="black" />
	char* temp = new char[1024];
	strcpy(temp, "<line x1=\"");

	char str[100];
    std::stringstream ss;
    ss << this->getX();
    ss >> str;
    
	strcat(temp, str);
	strcat(temp, "\" y1=\"");

	ss.clear();
	ss << this->getY();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" x2=\"");

	ss.clear();
	ss << this->getX1();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" y2=\"");

	ss.clear();
	ss << this->getY1();
    ss >> str;

	strcat(temp, str);
	strcat(temp, "\" stroke=\"");
	strcat(temp, this->getColor());
	strcat(temp, "\" />\n");

	return temp;
	
}

/**
 * @brief Get data from char array and set it to object of class Line
 * 
 * @param str 
 */
void Line::convertFromString(const char* str)
{
	//<line x1="0" y1="80" x2="100" y2="20" stroke="black" />
	int len = strlen(str);
	char* temp = new char[10];
	int index = 0;
	for (int i = 0; i < len; i++) 
	{
		if((str[i] == 'x') && (str[i+1] == '1') && (str[i+2] == '='))
		{
			for (int j = i + 4; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setX(atof(temp));
			index = 0;
		}
		if((str[i] == 'y') && (str[i+1] == '1') && (str[i+2] == '='))
		{
			for (int j = i + 4; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setY(atof(temp));
			index = 0;
		}
		if((str[i] == 'x') && (str[i+1] == '2') && (str[i+2] == '='))
		{
			for (int j = i + 4; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setX1(atof(temp));
			index = 0;
		}
		if((str[i] == 'y') && (str[i+1] == '2') && (str[i+2] == '='))
		{
			for (int j = i + 4; str[j] != '"'; j++)
			{
				temp[index] = str[j];
				index++;
			}
			temp[index] = '\0';
			setY1(atof(temp));
			index = 0;
		}
		if((str[i] == 'e') && (str[i+1] == '='))
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