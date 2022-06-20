#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <sstream>

#include "Figure.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "SVG.h"

/**
 * @brief Interactive menu
 *
 */

void CommandPrompt()
{
    SVG svg;
    char word[100];
    char filename[100];
    std::fstream file;
    std::stringstream buff;
    std::cout << "Welcome to your SVG file editor! What do you need? " << std::endl;

    while (true)
    {
        std::cin.getline(word, 100);

        if (strcmp(word, "EXIT") == 0)
        {
            if (filename == nullptr)
            {
                std::cout << "Exiting program...." << std::endl;
                return;
            }

            std::cout << "You have an open file with unsaved changes, please select close or save or save as first!" << std::endl;

            bool exit = false;

            do
            {
                std::cin.getline(word, 100);
                if (strcmp(word, "CLOSE") == 0)
                {
                    file.close();
                    std::cout << "Successfully closed " << filename << std::endl;
                    exit = true;
                }
                else if (strcmp(word, "SAVE") == 0)
                {
                    std::ofstream temp("temp.svg");
                    std::ifstream in(filename);
                    char buffer[1024];
                    while (in.getline(buffer, sizeof(buffer), '>'))
                    {
                        if (strstr(buffer, "<svg"))
                        {
                            temp << buffer;
                            temp << ">\n";
                            for (int i = 0; i < svg.getSize(); i++)
                            {
                                temp << svg.getfigures()[i]->convertToString();
                            }

                            while (in.getline(buffer, sizeof(buffer), '>'))
                            {
                                if (strstr(buffer, "</svg") != nullptr)
                                {
                                    temp << buffer;
                                    temp << ">\n";
                                    break;
                                }
                            }
                        }
                        else
                        {
                            temp << buffer;
                        }
                    }

                    std::cout << "Successfully saved the changes to " << filename << ' ' << std::endl;
                    in.close();
                    temp.close();
                    exit = true;
                }
                else if (strstr(word, "SAVEAS") != nullptr)
                {
                    buff.clear();
                    unsigned int len = strlen(word);
                    char *new_word = new char[len - 7 + 1];
                    for (int i = 7, j = 0; i <= len; i++, j++)
                    {
                        new_word[j] = word[i];
                    }
                    buff << new_word;
                    char filename1[100];
                    buff >> filename1;

                    std::ofstream file1(filename1);
                    std::ifstream in(filename);
                    char buffer[1024];
                    while (in.getline(buffer, sizeof(buffer), '>'))
                    {
                        if (strstr(buffer, "<svg"))
                        {
                            file1 << buffer;
                            file1 << ">\n";
                            for (int i = 0; i < svg.getSize(); i++)
                            {
                                file1 << svg.getfigures()[i]->convertToString();
                            }

                            while (in.getline(buffer, sizeof(buffer), '>'))
                            {
                                if (strstr(buffer, "</svg"))
                                {
                                    file1 << buffer;
                                    file1 << ">\n";
                                    break;
                                }
                            }
                        }
                        else
                        {
                            file1 << buffer;
                        }
                    }

                    file1.close();
                    in.close();

                    std::cout << "Successfully saved another " << filename1 << ' ' << std::endl;
                    delete[] new_word;
                    exit = true;
                }

                if (!exit)
                {
                    std::cout << "Please select close or save or save as!" << std::endl;
                }

            } while (!exit);

            std::cout << "Exiting program...." << std::endl;
            return;
        }
        else if (strstr(word, "OPEN") != nullptr)
        {
            unsigned int len = strlen(word);
            char *new_word = new char[len - 5];
            for (int i = 5, j = 0; i <= len; i++, j++)
            {
                new_word[j] = word[i];
            }
            buff << new_word;
            buff >> filename;
            buff.clear();

            int num_of_figure = 0;
            std::ifstream in(filename);
            char buffer[1024];
            while (in.getline(buffer, sizeof(buffer), '>'))
            {
                if (strstr(buffer, "<svg"))
                {
                    while ((in.getline(buffer, sizeof(buffer), '>')) && (strstr(buffer, "</svg") == nullptr))
                    {
                        if (strstr(buffer, "rect") != nullptr)
                        {
                            Figure *f = new Rectangle();
                            f->convertFromString(buffer);
                            svg.create(f);
                            num_of_figure++;
                        }
                        if (strstr(buffer, "circle") != nullptr)
                        {
                            Figure *f = new Circle();
                            f->convertFromString(buffer);
                            svg.create(f);
                            num_of_figure++;
                        }
                        if (strstr(buffer, "line") != nullptr)
                        {
                            Figure *f = new Line();
                            f->convertFromString(buffer);
                            svg.create(f);
                            num_of_figure++;
                        }
                    }
                }
            }

            in.close();
            std::cout << "Successfully opened " << filename << std::endl;
            delete[] new_word;
        }
        else if (strcmp(word, "CLOSE") == 0)
        {
            file.close();
            std::cout << "Successfully closed " << filename << std::endl;
        }
        else if (strcmp(word, "SAVE") == 0)
        {
            std::ofstream temp("temp.svg");
            std::ifstream in(filename);
            char buffer[1024];
            while (in.getline(buffer, sizeof(buffer), '>'))
            {
                if (strstr(buffer, "<svg"))
                {
                    temp << buffer;
                    temp << ">\n";
                    for (int i = 0; i < svg.getSize(); i++)
                    {
                        temp << svg.getfigures()[i]->convertToString();
                    }

                    while (in.getline(buffer, sizeof(buffer), '>'))
                    {
                        if (strstr(buffer, "</svg") != nullptr)
                        {
                            temp << buffer;
                            temp << ">\n";
                            break;
                        }
                    }
                }
                else
                {
                    temp << buffer;
                }
            }

            std::cout << "Successfully saved the changes to " << filename << ' ' << std::endl;
            in.close();
            temp.close();
        }
        else if (strstr(word, "SAVEAS") != nullptr)
        {
            buff.clear();
            unsigned int len = strlen(word);
            char *new_word = new char[len - 7 + 1];
            for (int i = 7, j = 0; i <= len; i++, j++)
            {
                new_word[j] = word[i];
            }
            buff << new_word;
            char filename1[100];
            buff >> filename1;

            std::ofstream file1(filename1);
            std::ifstream in(filename);
            char buffer[1024];
            while (in.getline(buffer, sizeof(buffer), '>'))
            {
                if (strstr(buffer, "<svg"))
                {
                    file1 << buffer;
                    file1 << ">\n";
                    for (int i = 0; i < svg.getSize(); i++)
                    {
                        file1 << svg.getfigures()[i]->convertToString();
                    }

                    while (in.getline(buffer, sizeof(buffer), '>'))
                    {
                        if (strstr(buffer, "</svg"))
                        {
                            file1 << buffer;
                            file1 << ">\n";
                            break;
                        }
                    }
                }
                else
                {
                    file1 << buffer;
                }
            }

            file1.close();
            in.close();

            std::cout << "Successfully saved another " << filename1 << ' ' << std::endl;
            delete[] new_word;
        }
        else if (strcmp(word, "HELP") == 0)
        {
            std::cout << "The following commands are supported: " << std::endl;
            std::cout << "Open <file> - Opens <file> " << std::endl;
            std::cout << "close - closes currently opened file " << std::endl;
            std::cout << "save - saves the currently open file " << std::endl;
            std::cout << "saveas <file> - saves the currently open file in <file> " << std::endl;
            std::cout << "help - prints this information " << std::endl;
            std::cout << "exit - exits the program " << std::endl;
            std::cout << "create - creates a new figure " << std::endl;
            std::cout << "erase - erases a figure " << std::endl;
            std::cout << "within - print figures within circle or rectangle " << std::endl;
            std::cout << "print - print all figures " << std::endl;
            std::cout << "translate - translate figure by given number " << std::endl;
            std::cout << "translate all - translate all figures " << std::endl;
        }
        else if (strstr(word, "CREATE") != nullptr)
        {
            unsigned int len = strlen(word);
            char *new_word = new char[len - 7 + 1];
            for (int i = 7, j = 0; i <= len; i++, j++)
            {
                new_word[j] = word[i];
            }
            len = strlen(new_word);
            if (strstr(new_word, "line") != nullptr)
            {
                char *_new_word = new char[len - 5];
                for (int i = 5, j = 0; i <= len; i++, j++)
                {
                    _new_word[j] = new_word[i];
                }
                double a, b, c, d;
                char col[100];
                buff << _new_word;
                buff >> a >> b >> c >> d >> col;
                Line line;
                line.setX(a);
                line.setY(b);
                line.setX1(c);
                line.setY1(d);
                line.setColor(col);
                Figure *f = &line;
                svg.create(f);
                buff.clear();
                delete[] _new_word;
            }
            else if (strstr(word, "circle") != nullptr)
            {
                char *_new_word = new char[len - 7];
                for (int i = 7, j = 0; i <= len; i++, j++)
                {
                    _new_word[j] = new_word[i];
                }
                double a, b, c;
                char col[100];
                buff << _new_word;
                buff >> a >> b >> c >> col;
                Circle circle;
                circle.setX(a);
                circle.setY(b);
                circle.setRad(c);
                circle.setColor(col);
                Figure *f = &circle;
                svg.create(f);
                buff.clear();
                delete[] _new_word;
            }
            else if (strstr(word, "rectangle") != nullptr)
            {
                char *_new_word = new char[len - 10];
                for (int i = 10, j = 0; i <= len; i++, j++)
                {
                    _new_word[j] = new_word[i];
                }
                double a, b, c, d;
                char col[100];
                buff << _new_word;
                buff >> a >> b >> c >> d >> col;
                Rectangle rectangle;
                rectangle.setX(a);
                rectangle.setY(b);
                rectangle.setWidth(c);
                rectangle.setLenght(d);
                rectangle.setColor(col);
                Figure *f = &rectangle;
                svg.create(f);
                buff.clear();
                delete[] _new_word;
            }
            else
            {
                std::cout << "Didn't support that type of figure!" << std::endl;
                buff.clear();
            }
            std::cout << "Successfully created " << ' ';
            if (svg.getfigures()[svg.getSize() - 1]->getType() == 'r')
            {
                std::cout << "rectangle ";
            }
            else if (svg.getfigures()[svg.getSize() - 1]->getType() == 'l')
            {
                std::cout << "line ";
            }
            else if (svg.getfigures()[svg.getSize() - 1]->getType() == 'c')
            {
                std::cout << "circle ";
            }

            std::cout << '(' << svg.getSize() << ')' << std::endl;

            delete[] new_word;
        }
        else if (strstr(word, "ERASE") != nullptr)
        {
            int n;
            unsigned int len = strlen(word);
            char *_new_word = new char[len - 6];
            for (int i = 6, j = 0; i <= len; i++, j++)
            {
                _new_word[j] = word[i];
            }
            buff << _new_word;
            buff >> n;
            buff.clear();
            if (svg.getfigures()[n - 1]->getType() == 'r')
            {
                std::cout << "Erased a "
                          << "rectangle " << '(' << n << ')' << std::endl;
                svg.remove(n);
            }
            else if (svg.getfigures()[n - 1]->getType() == 'c')
            {
                std::cout << "Erased a "
                          << "circle " << '(' << n << ')' << std::endl;
                svg.remove(n);
            }
            else if (svg.getfigures()[n - 1]->getType() == 'l')
            {
                std::cout << "Erased a "
                          << "line " << '(' << n << ')' << std::endl;
                svg.remove(n);
            }

            delete[] _new_word;
        }
        else if (strstr(word, "TRANSLATE") != nullptr)
        {
            int n = 0;
            double vertical, horizontal;
            unsigned int len = strlen(word);
            char *_new_word = new char[len - 10 + 1];
            for (int i = 10, j = 0; i <= len; i++, j++)
            {
                _new_word[j] = word[i];
            }
            len = len - 10;
            if (_new_word[0] >= '0' && _new_word[0] <= '9')
            {
                buff << _new_word;
                buff >> n >> vertical >> horizontal;
                buff.clear();
                svg.translate(n, horizontal, vertical);
                std::cout << "Translate " << *svg.getfigures()[n - 1] << std::endl;
            }

            delete[] _new_word;
        }
        else if (strstr(word, "TRANSLATE ALL") != nullptr)
        {
            double vertical, horizontal;
            unsigned int len = strlen(word);
            char *_new_word = new char[len - 14 + 1];
            for (int i = 14, j = 0; i <= len; i++, j++)
            {
                _new_word[j] = word[i];
            }
            buff >> vertical >> horizontal;
            svg.translateAll(horizontal, vertical);
            std::cout << "Translated all figures " << std::endl;
            delete[] _new_word;
        }
        else if (strstr(word, "WITHIN") != nullptr)
        {
            char n[100];
            buff.clear();
            unsigned int len = strlen(word);
            char *new_word = new char[len - 7 + 1];
            for (int i = 7, j = 0; i <= len; i++, j++)
            {
                new_word[j] = word[i];
            }
            buff << new_word;
            buff >> n;
            buff.clear();
            len -= 7;
            if (strstr(n, "rectangle") != nullptr)
            {
                char *__new_word = new char[len - 10 + 1];
                for (int i = 10, j = 0; i <= len; i++, j++)
                {
                    __new_word[j] = new_word[i];
                }
                buff << __new_word;
                double a, b, c, d;
                char s[100];
                buff >> a >> b >> c >> d;

                svg.within("rectangle", a, b, c, d);
                delete[] __new_word;
            }
            else if (strstr(n, "circle") != nullptr)
            {
                char *__new_word = new char[len - 7 + 1];
                for (int i = 7, j = 0; i <= len; i++, j++)
                {
                    __new_word[j] = new_word[i];
                }
                buff << __new_word;
                double a, b, c;
                buff >> a >> b >> c;

                svg.within("circle", a, b, c);
                delete[] __new_word;
            }

            delete[] new_word;
        }
        else if (strcmp(word, "PRINT") == 0)
        {
            svg.print();
            buff.clear();
        }
        else
        {
            std::cout << "Invalid command! Try again!" << std::endl;
            buff.clear();
        }
    }
}

int main()
{
    CommandPrompt();

    return 0;
}