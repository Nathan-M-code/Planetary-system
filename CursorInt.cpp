#include "CursorInt.h"

using namespace std;

Cursor::Cursor(int x, int y, unsigned width, unsigned height, int valueMin, int valueMax){
    _x = x;
    _y = y;
    _width = width;
    _height = height;


    _valueMin = valueMin;
    _valueMax = valueMax;
    _value = _valueMin;

    _activated = false;

    _rsBar.setSize(sf::Vector2f(_width,_height/6));
    _rsBar.setPosition(_x, _y+_height/2-_rsBar.getSize().y/2);
    _rsBar.setFillColor(sf::Color(100,100,100));

    _rsCursor.setSize(sf::Vector2f(8,_height));
    _rsCursor.setPosition(_x+(_value-_valueMin)/(_valueMax-_valueMin)*_width,_y);
    _rsCursor.setFillColor(sf::Color(80,80,80));

    _text.setFont(*TextureLoader::getFont());
    _text.setCharacterSize(12);
    _text.setString(std::to_string(_value));
    _text.setPosition(_x+_width/2-_text.getLocalBounds().width/2,_rsCursor.getPosition().y-5);
}
Cursor::~Cursor(){}

sf::Vector2i Cursor::getPosition(){
    return sf::Vector2i(_x,_y);
}

sf::Vector2i Cursor::getSize(){
    return sf::Vector2i(_width,_height);
}

void Cursor::setPosition(int x, int y){
    _x = x;
    _y = y;
    _rsBar.setPosition(_x, _y+_height/2-_rsBar.getSize().y/2);
    _rsCursor.setPosition(_x+(_value-_valueMin)/(float)(_valueMax-_valueMin)*_width,_y);
    _text.setPosition(_x+_width/2-_text.getLocalBounds().width/2,_rsCursor.getPosition().y-5);
}
void Cursor::setValue(int value){
    _value = value;
    if(_value < _valueMin){
        _value = _valueMin;
    }
    if(_value > _valueMax){
        _value = _valueMax;
    }
    _rsCursor.setPosition(_x+(_value-_valueMin)/(float)(_valueMax-_valueMin)*_width,_y);
    _text.setString(std::to_string(_value));
}

void Cursor::setValue(sf::Vector2i &mousePos){
    int x = mousePos.x - _x;
    int value = round((x/(float)_width) * (_valueMax-_valueMin)) + _valueMin;
    setValue(value);
}

bool Cursor::mouseIsOnCursor(sf::Vector2i &mousePos){
    if(mousePos.x >= _rsCursor.getPosition().x && mousePos.x <= _rsCursor.getPosition().x+_rsCursor.getLocalBounds().width){
        if(mousePos.y >= _rsCursor.getPosition().y && mousePos.y <= _rsCursor.getPosition().y+_rsCursor.getLocalBounds().height){
            return true;
        }
    }
    return false;
}

int Cursor::getValue(){
    return _value;
}

bool Cursor::isActivated(){
    return _activated;
}
void Cursor::setActivated(bool act){
    _activated = act;
}

void Cursor::draw(sf::RenderWindow &window){
    window.draw(_rsBar);
    window.draw(_rsCursor);
    window.draw(_text);
}
