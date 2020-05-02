#ifndef UTILE_H_INCLUDED
#define UTILE_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

std::string intToString(int i);
std::string floatToString(float i);
std::string doubleToString(double i);
int rand_a_b(int a,int b);
std::string const BoolToString(bool b);
sf::Color getARndColor();
sf::Vector2f normalize(sf::Vector2f &vec);
float getNorme(sf::Vector2f &vec);
float roundPrecisionFloat(float nb, int prec);



#endif // UTILE_H_INCLUDED
