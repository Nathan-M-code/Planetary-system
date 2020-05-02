#include "CursorFloat.h"

using namespace std;

CursorFloat::CursorFloat(int x, int y, unsigned width, unsigned height, float valueMin, float valueMax){
    _x = x;
    _y = y;
    _width = width;
    _height = height;


    _valueMin = valueMin;
    _valueMax = valueMax;
    _value = _valueMin;

    _activated = false;

    _rsBar.setSize(sf::Vector2f(_width,_height/6));
    _rsBar.setPosition(_x, _y+_height/2.0-_rsBar.getSize().y/2.0);
    _rsBar.setFillColor(sf::Color(100,100,100));

    _rsCursor.setSize(sf::Vector2f(8,_height));
    _rsCursor.setPosition(_x+(_value-_valueMin)/(float)(_valueMax-_valueMin)*_width,_y);
    _rsCursor.setFillColor(sf::Color(80,80,80));

    _text.setFont(*TextureLoader::getFont());
    _text.setCharacterSize(12);
    _text.setString(std::to_string(_value));
    _text.setPosition(_x+_width/2.0-_text.getLocalBounds().width/2.0,_rsCursor.getPosition().y-5);
}
CursorFloat::~CursorFloat(){}

sf::Vector2i CursorFloat::getPosition(){
    return sf::Vector2i(_x,_y);
}

sf::Vector2i CursorFloat::getSize(){
    return sf::Vector2i(_width,_height);
}

void CursorFloat::setPosition(int x, int y){
    _x = x;
    _y = y;
    _rsBar.setPosition(_x, _y+_height/2.0-_rsBar.getSize().y/2.0);
    _rsCursor.setPosition(_x+(_value-_valueMin)/(float)(_valueMax-_valueMin)*_width,_y);
    _text.setPosition(_x+_width/2.0-_text.getLocalBounds().width/2.0,_rsCursor.getPosition().y-5);
}
void CursorFloat::setValue(float value){
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

void CursorFloat::setValue(sf::Vector2i &mousePos){
    int x = mousePos.x - _x;
    float value = (x/(float)_width) * (_valueMax-_valueMin) + _valueMin;
    setValue(value);
}

bool CursorFloat::mouseIsOnCursor(sf::Vector2i &mousePos){
    if(mousePos.x >= _rsCursor.getPosition().x && mousePos.x <= _rsCursor.getPosition().x+_rsCursor.getLocalBounds().width){
        if(mousePos.y >= _rsCursor.getPosition().y && mousePos.y <= _rsCursor.getPosition().y+_rsCursor.getLocalBounds().height){
            return true;
        }
    }
    return false;
}

float CursorFloat::getValue(){
    return _value;
}

bool CursorFloat::isActivated(){
    return _activated;
}
void CursorFloat::setActivated(bool act){
    _activated = act;
}

void CursorFloat::draw(sf::RenderWindow &window){
    window.draw(_rsBar);
    window.draw(_rsCursor);
    window.draw(_text);
}

