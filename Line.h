#ifndef __Line_HPP
#define __Line_HPP

/**
 * @file Line.h
 * @author Tsanko Angelov
 * @brief The line is a kind of figure. Class Line inherits class Figure
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Figure.h"

class Line : public Figure
{
private:
    double x1, y1;

public:
    Line();

    double getX1() const { return this->x1; }
    double getY1() const { return this->y1; }
    void setX1(const double);
    void setY1(const double);

    friend std::ostream& operator<<(std::ostream&, const Line&);
    virtual void translation(double, double) override;
    virtual bool within(const char*, double, double, double, double = 0) override;
    virtual char* convertToString() override;
    virtual void convertFromString(const char*) override;

};

#endif