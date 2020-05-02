#ifndef CURSORF_H_INCLUDED
#define CURSORF_H_INCLUDED

#include "TextureLoader.h"

class CursorFloat{
public:
    CursorFloat(int x, int y, unsigned width, unsigned height, float valueMin, float valueMax);
    ~CursorFloat();

    sf::Vector2i getPosition();
    sf::Vector2i getSize();

    void setPosition(int x, int y);
    void setValue(float value);
    void setValue(sf::Vector2i &mousePos);
    //void setValueMinMax(int valueMin, int valueMax);

    bool mouseIsOnCursor(sf::Vector2i &mousePos);

    bool isActivated();
    void setActivated(bool act);

    float getValue();

    void draw(sf::RenderWindow &window);
private:
    int _x;
    int _y;
    unsigned _width;
    unsigned _height;

    float _value;
    float _valueMin;
    float _valueMax;

    bool _activated;

    sf::Text _text;
    sf::RectangleShape _rsBar;
    sf::RectangleShape _rsCursor;
};

#endif

