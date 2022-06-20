#ifndef __Rectangle_HPP
#define __Rectangle_HPP

/**
 * @file Rectangle.h
 * @author Tsanko Angelov
 * @brief The rectangle is a kind of figure. Class Rectangle inherits class Figure
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Figure.h"

class Rectangle : public Figure
{
private:
    double width, length;

public:
    Rectangle();

    double getWidth() const { return this->width; }
    double getLength() const { return this->length; }
    void setWidth(const double);
    void setLenght(const double);

    friend std::ostream& operator<<(std::ostream&, const Rectangle&);
    virtual void translation(double, double) override;
    virtual bool within(const char*, double, double, double, double = 0) override;
    virtual char* convertToString() override;
    virtual void convertFromString(const char*) override;

};

#endif