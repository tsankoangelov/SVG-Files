#ifndef __Circle_HPP
#define __Circle_HPP

/**
 * @file Circle.h
 * @author Tsanko Angelov
 * @brief The circle is a kind of figure. Class Circle inherits class Figure
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Figure.h"

class Circle : public Figure
{
private:
    double r;
public:
    Circle();
   
    double getRad() const { return this->r; }
    void setRad(const double);

    friend std::ostream& operator<<(std::ostream&, const Circle&);
    virtual void translation(double, double) override;
    virtual bool within(const char*, double, double, double, double = 0) override;
    virtual char* convertToString() override;
    virtual void convertFromString(const char*) override;

};

#endif