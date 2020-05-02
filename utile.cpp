#include "utile.h"

std::string intToString(int i) {
     std::ostringstream oss;
     oss << i;
     return oss.str();
}

std::string floatToString(float i) {
     std::ostringstream oss;
     oss << i;
     return oss.str();
}

std::string doubleToString(double i) {
     std::ostringstream oss;
     oss << i;
     return oss.str();
}

// On suppose a<b
int rand_a_b(int a,int b){ //[a,b[
    return rand()%(b-a)+a;
}

std::string const BoolToString(bool b)
{
  return b ? "true" : "false";
}

sf::Color getARndColor(){
    int r = rand_a_b(0,8);
    switch(r){
    case 0:
        return sf::Color::White;
    case 1:
        return sf::Color(150,150,150);
    case 2:
        return sf::Color::Magenta;
    case 3:
        return sf::Color::Blue;
    case 4:
        return sf::Color::Red;
    case 5:
        return sf::Color::Green;
    case 6:
        return sf::Color::Yellow;
    case 7:
        return sf::Color::Cyan;
    }
}

sf::Vector2f normalize(sf::Vector2f &vec){
    return vec/getNorme(vec);
}

float getNorme(sf::Vector2f &vec){
    return sqrt(vec.x*vec.x+vec.y*vec.y);
}

float roundPrecisionFloat(float nb, int prec){
    return roundf(nb * pow(10,prec)) / pow(10,prec);
}
