#ifndef __SVG_HPP
#define __SVG_HPP

/**
 * @file SVG.h
 * @author Tsanko Angelov
 * @brief Main functions are implemented in class SVG
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Figure.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"

class SVG
{
private:
    Figure** figures;
    unsigned int capacity, size;

    void copy(const SVG&);
    void clean();
    void resize();
    

public:
    SVG();
    SVG(const SVG&);
    SVG& operator=(const SVG&);
    ~SVG();

    Figure** getfigures() const { return this->figures;  }
	int getCapacity() const { return this->capacity; }
	int getSize() const { return this->size; }

    void create(Figure*&);
	void remove(unsigned int);
    void translate(unsigned int, double, double);
    void translateAll(double, double);
    void within(const char*, double, double, double, double = 0);
    void print();

	friend std::ostream& operator<<(std::ostream&, const SVG&);
};


#endif