#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

#include "SVG.h"
#include "Rectangle.h"
#include "Line.h"
#include "Circle.h"

void SVG::copy(const SVG &other)
{
    size = other.size;
    capacity = other.capacity;
    delete[] figures;
    figures = new Figure *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        figures[i] = other.figures[i];
    }
}

void SVG::clean()
{
    delete[] figures;
}

void SVG::resize()
{
    capacity = capacity * 2;
    Figure **temp = new Figure *[capacity];
    for (int i = 0; i < size; i++)
    {
        temp[i] = figures[i];
    }
    delete[] figures;
    figures = temp;
}

/**
 * @brief Construct a new SVG::SVG object
 * 
 */
SVG::SVG() : capacity(10), size(0)
{
    figures = new Figure *[capacity];
}

/**
 * @brief Construct a new SVG::SVG object
 * 
 * @param other 
 */
SVG::SVG(const SVG &other)
{
    copy(other);
}

/**
 * @brief Override operator=
 * 
 * @param other 
 * @return SVG& 
 */
SVG &SVG::operator=(const SVG &other)
{
    if (this != &other)
    {
        clean();
        copy(other);
    }

    return *this;
}

/**
 * @brief Destroy the SVG::SVG object
 * 
 */
SVG::~SVG()
{
    clean();
}

/**
 * @brief Creates and adds a new figure to the array of figures
 * 
 * @param e 
 */
void SVG::create(Figure* &e)
{
    if (size == capacity)
    {
        resize();
    }

    figures[size] = e;
    size++;
}

/**
 * @brief Translate figure <n> from the array of figures by given horizontal and vertical
 * 
 * @param n 
 * @param horizontal 
 * @param vertical 
 */
void SVG::translate(unsigned int n, double horizontal, double vertical)
{
    if (n - 1 > size)
    {
        std::cout << "Wrong index! Try again!" << std::endl;
        return;
    }
    figures[n - 1]->translation(horizontal, vertical);
}

/**
 * @brief Translate all figures from the array
 * 
 * @param horizontal 
 * @param vertical 
 */
void SVG::translateAll(double horizontal, double vertical)
{
    for(int i = 0; i < size; i++)
    {
        figures[i]->translation(horizontal, vertical);
    }
}

/**
 * @brief Erase figure <n> from the array
 * 
 * @param n 
 */
void SVG::remove(unsigned int n)
{
    if (n - 1 > size)
    {
        std::cout << "Wrong index! Please, try again!" << std::endl;
        return;
    }
    Figure **temp = new Figure *[capacity];
    for (int i = 0; i < n - 1; i++)
    {
        temp[i] = figures[i];
    }
    for (int i = n; i < size; i++)
    {
        temp[i - 1] = figures[i];
    }
    delete[] figures;
    size--;
    figures = temp;
}

/**
 * @brief Check if the figures from the array are within circle or within rectangle
 * 
 * @param option 
 * @param coord_x 
 * @param coord_y 
 * @param len1 
 * @param len2 
 */
void SVG::within(const char* option, double coord_x, double coord_y, double len1, double len2)
{
    if ((strcmp(option, "rectangle")) ||(strcmp(option, "circle")) )
    {
        for (int i = 0; i < size; i++)
        {
            if (figures[i]->within(option, coord_x, coord_y, len1, len2))
            {
                std::cout << i+1 << ". " << *figures[i] << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Wrong choice of option! Please trgetY() again!" << std::endl;
        return;
    }
}

/**
 * @brief Print all figures from the array
 * 
 */
void SVG::print()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << i+1 << ". " << *figures[i] << std::endl;
    }
}
