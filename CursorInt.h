#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include "TextureLoader.h"

class Cursor{
public:
    Cursor(int x, int y, unsigned width, unsigned height, int valueMin, int valueMax);
    ~Cursor();

    sf::Vector2i getPosition();
    sf::Vector2i getSize();

    void setPosition(int x, int y);
    void setValue(int value);
    void setValue(sf::Vector2i &mousePos);
    //void setValueMinMax(int valueMin, int valueMax);

    bool mouseIsOnCursor(sf::Vector2i &mousePos);

    bool isActivated();
    void setActivated(bool act);

    int getValue();

    void draw(sf::RenderWindow &window);
private:
    int _x;
    int _y;
    unsigned _width;
    unsigned _height;

    int _value;
    int _valueMin;
    int _valueMax;

    bool _activated;

    sf::Text _text;
    sf::RectangleShape _rsBar;
    sf::RectangleShape _rsCursor;
};

#endif
