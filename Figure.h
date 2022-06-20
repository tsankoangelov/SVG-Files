#ifndef __Figure_HPP
#define __Figure_HPP

/**
 * @file Figure.h
 * @author Tsanko Angelov
 * @brief Class Figure is abstract class that implements a figure
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>

class Figure
{
private:
    char* color;
    char type;
    double x, y;
    void copy(const Figure&);
    void clean();
public:
    Figure();
    Figure(const char*, const double, const double);
    Figure(const Figure&);
    Figure& operator=(const Figure&);
    virtual ~Figure() = 0;

    void setColor(const char*);
    void setX(const double);
    void setY(const double);
    void setType(const char);

    char* getColor() const { return this->color; }
    double getX() const { return this->x; }
    double getY() const { return this->y; }
    char getType() const { return this->type; }


    virtual void translation(double, double) = 0;
    virtual bool within(const char*, double, double, double, double = 0) = 0;
    virtual char* convertToString() = 0;
    virtual void convertFromString(const char*) = 0;
    friend std::ostream& operator<<(std::ostream&, const Figure&);
};

#endif