#include "OptionBody.h"

using namespace std;

OptionBody::OptionBody(Body *bodyTarget, int x, int y, unsigned width, unsigned height){
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _heightMin = 300;
    _widthMin = 300;

    _scaling = false;
    _moving = false;

    _error = false;

    _text.setFont(*TextureLoader::getFont());
    _text.setCharacterSize(16);
    _text.setColor(sf::Color::Black);

    _spriteMove.setTexture(*TextureLoader::getTextureMove());
    _spriteMove.setPosition(_x,_y);

    sf::Texture *texture = TextureLoader::getTextureScale();
    sf::Vector2u size = texture->getSize();
    _spriteScale.setTexture(*texture);
    _spriteScale.setPosition(_x+_width-size.x,_y+_height-size.y);

    texture = TextureLoader::getTextureDelete();
    size = texture->getSize();
    _spriteDelete.setTexture(*texture);
    _spriteDelete.setPosition(_x+_width-size.x,_y);

    _bodyTarget = bodyTarget;
    _line = sf::VertexArray(sf::Lines, 2);
    _line[0].position = {_x,_y};

    _rsBackground.setSize(sf::Vector2f(width, height));
    _rsBackground.setFillColor(sf::Color(100,100,100,150));
    _rsBackground.setPosition(x,y);

    _tbFocus = 0;
    _listTb.push_back(new TextBox(_x+_width/4-50, _y+_height/8-10, to_string(_bodyTarget->getPos().x))); //posx
    _listTb.push_back(new TextBox(_x+3*_width/4-50, _y+_height/8-10, to_string(_bodyTarget->getPos().y))); //posy

    _listTb.push_back(new TextBox(_x+_width/4-50, _y+3*_height/8-10, to_string(_bodyTarget->getVel().x))); //velx
    _listTb.push_back(new TextBox(_x+3*_width/4-50, _y+3*_height/8-10, to_string(_bodyTarget->getVel().y))); //vely

    _listTb.push_back(new TextBox(_x+_width/4-50, _y+5*_height/8-10, to_string(_bodyTarget->getMass()))); //mass
    _listTb.push_back(new TextBox(_x+3*_width/4-50, _y+5*_height/8-10, to_string(_bodyTarget->getRadius()))); //radius
}
OptionBody::~OptionBody(){}

bool OptionBody::isMoving() const{
    return _moving;
}
bool OptionBody::isScaling() const{
    return _scaling;
}

void OptionBody::setMoving(bool mov){
    _moving = mov;
}
void OptionBody::setScaling(bool scal){
    _scaling = scal;
}

void OptionBody::clickHandlerInside(sf::Vector2i &mousePos){
    _tbFocus=0;
    for(unsigned int i=0;i<_listTb.size();i++){
        if(_listTb[i]->testClick(mousePos.x, mousePos.y)){
            _listTb[i]->setFocus(true);
            _tbFocus = _listTb[i];
        }else{
            _listTb[i]->setFocus(false);
        }
    }
}

bool OptionBody::mouseIsOnMove(sf::Vector2i &mousePos){
    if(mousePos.x >= _spriteMove.getPosition().x && mousePos.x <= _spriteMove.getPosition().x+_spriteMove.getTextureRect().width){
        if(mousePos.y >= _spriteMove.getPosition().y && mousePos.y <= _spriteMove.getPosition().y+_spriteMove.getTextureRect().height){
            return true;
        }
    }
    return false;
}

bool OptionBody::mouseIsOnScale(sf::Vector2i &mousePos){
    if(mousePos.x >= _spriteScale.getPosition().x && mousePos.x <= _spriteScale.getPosition().x+_spriteScale.getTextureRect().width){
        if(mousePos.y >= _spriteScale.getPosition().y && mousePos.y <= _spriteScale.getPosition().y+_spriteScale.getTextureRect().height){
            return true;
        }
    }
    return false;
}

bool OptionBody::mouseIsOnDelete(sf::Vector2i &mousePos){
    if(mousePos.x >= _spriteDelete.getPosition().x && mousePos.x <= _spriteDelete.getPosition().x+_spriteDelete.getTextureRect().width){
        if(mousePos.y >= _spriteDelete.getPosition().y && mousePos.y <= _spriteDelete.getPosition().y+_spriteDelete.getTextureRect().height){
            return true;
        }
    }
    return false;
}

bool OptionBody::mouseIsOn(sf::Vector2i &mousePos){
    if(mousePos.x >= _x && mousePos.x <= _x+_width){
        if(mousePos.y >= _y && mousePos.y <= _y+_height){
            return true;
        }
    }
    return false;
}


void OptionBody::scaleByButtonScale(sf::Vector2i &mousePos){
    int width = abs(mousePos.x - _x);
    if(width <= _widthMin){
        width = _widthMin;
    }
    int height = abs(mousePos.y - _y);
    if(height <= _heightMin){
        height = _heightMin;
    }
    _width = width;
    _height = height;

    _spriteMove.setPosition(_x,_y);

    sf::Vector2u size = _spriteScale.getTexture()->getSize();
    _spriteScale.setPosition(_x+_width-size.x,_y+_height-size.y);

    size = _spriteDelete.getTexture()->getSize();
    _spriteDelete.setPosition(_x+_width-size.x,_y);

    _rsBackground.setSize(sf::Vector2f(_width, _height));

    updatePosTB();
}

void OptionBody::setPositionByButtonMove(sf::Vector2i &mousePos){
    _x = mousePos.x;
    _y = mousePos.y;

    _spriteMove.setPosition(_x,_y);

    sf::Vector2u size = _spriteScale.getTexture()->getSize();
    _spriteScale.setPosition(_x+_width-size.x,_y+_height-size.y);

    size = _spriteDelete.getTexture()->getSize();
    _spriteDelete.setPosition(_x+_width-size.x,_y);

    _rsBackground.setPosition(_x,_y);

    _line[0].position = {_x,_y};

    updatePosTB();
}

void OptionBody::updatePosTB(){
    _listTb[0]->setPos(sf::Vector2f(_x+_width/4-50, _y+_height/8-10));
    _listTb[1]->setPos(sf::Vector2f(_x+3*_width/4-50, _y+_height/8-10));
    _listTb[2]->setPos(sf::Vector2f(_x+_width/4-50, _y+3*_height/8-10));
    _listTb[3]->setPos(sf::Vector2f(_x+3*_width/4-50, _y+3*_height/8-10));
    _listTb[4]->setPos(sf::Vector2f(_x+_width/4-50, _y+5*_height/8-10));
    _listTb[5]->setPos(sf::Vector2f(_x+3*_width/4-50, _y+5*_height/8-10));
}

void OptionBody::update(sf::RenderWindow &window, sf::View &view){
    sf::Vector2f cooScreen = sf::Vector2f(window.mapCoordsToPixel(_bodyTarget->getPos(), view));
    //cout << cooScreen.x <<" "<< cooScreen.y << endl;
    //cout << _bodyTarget->getPos().x <<" "<< _bodyTarget->getPos().y << endl;
    _line[1].position = cooScreen;
}

void OptionBody::updateString(){
    _listTb[0]->setString(floatToString(roundPrecisionFloat(_bodyTarget->getPos().x,2)));
    _listTb[1]->setString(floatToString(roundPrecisionFloat(_bodyTarget->getPos().y,2)));

    _listTb[2]->setString(floatToString(roundPrecisionFloat(_bodyTarget->getVel().x,2)));
    _listTb[3]->setString(floatToString(roundPrecisionFloat(_bodyTarget->getVel().y,2)));

    _listTb[4]->setString(doubleToString(_bodyTarget->getMass()));
    _listTb[5]->setString(intToString(roundPrecisionFloat(_bodyTarget->getRadius(),2)));
}

void OptionBody::textEntered(sf::Uint32 &key){
    if(_tbFocus && ((key>=48 && key<=57) || key == 45 || key == 46 || key == 8)){
        if(key != 8){
            _tbFocus->ajouterLettre(key);
        }else{
            _tbFocus->supprimerLettre();
        }

        _error = false;

        float posX;
        try{
            posX = stof(_listTb[0]->getString());
        }catch(invalid_argument e){
            posX = 1.0;
            _error = true;
        }
        float posY;
        try{
            posY = stof(_listTb[1]->getString());
        }catch(invalid_argument e){
            posY = 1.0;
            _error = true;
        }
        _bodyTarget->setPos(sf::Vector2f(posX, posY));

        float velX;
        try{
            velX = stof(_listTb[2]->getString());
        }catch(invalid_argument e){
            velX = 1.0;
            _error = true;
        }
        float velY;
        try{
            velY = stof(_listTb[3]->getString());
        }catch(invalid_argument e){
            velY = 1.0;
            _error = true;
        }
        _bodyTarget->setVel(sf::Vector2f(velX, velY));

        double mass;
        try{
            mass = stof(_listTb[4]->getString());
        }catch(invalid_argument e){
            mass = 5.9736*pow(10,14);
            _error = true;
        }catch(out_of_range e){
            mass = 5.9736*pow(10,14);
            _error = true;
        }
        _bodyTarget->setMass(mass);

        int radius;
        try{
            radius = stoi(_listTb[5]->getString());
        }catch(invalid_argument e){
            radius = 20;
            _error = true;
        }
        _bodyTarget->setRadius(radius);
    }
}

void OptionBody::draw(sf::RenderWindow &window){
    window.draw(_rsBackground);
    window.draw(_line);

    for(unsigned int i=0;i<_listTb.size();i++){
        _listTb[i]->draw(window);
    }

    _text.setString("Menu");
    _text.setPosition(_x+_width/2-_text.getLocalBounds().width/2,_y);
    window.draw(_text);

    _text.setString("posX");
    _text.setPosition(_listTb[0]->getPos().x+_listTb[0]->getSize().x/2-_text.getLocalBounds().width/2,_listTb[0]->getPos().y-2*_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("posY");
    _text.setPosition(_listTb[1]->getPos().x+_listTb[1]->getSize().x/2-_text.getLocalBounds().width/2,_listTb[1]->getPos().y-2*_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("veloX");
    _text.setPosition(_listTb[2]->getPos().x+_listTb[2]->getSize().x/2-_text.getLocalBounds().width/2,_listTb[2]->getPos().y-2*_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("veloY");
    _text.setPosition(_listTb[3]->getPos().x+_listTb[3]->getSize().x/2-_text.getLocalBounds().width/2,_listTb[3]->getPos().y-2*_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("mass: Kg");
    _text.setPosition(_listTb[4]->getPos().x+_listTb[4]->getSize().x/2-_text.getLocalBounds().width/2,_listTb[4]->getPos().y-2*_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("radius: Pxl");
    _text.setPosition(_listTb[5]->getPos().x+_listTb[5]->getSize().x/2-_text.getLocalBounds().width/2,_listTb[5]->getPos().y-2*_text.getLocalBounds().height);
    window.draw(_text);

    if(_error){
       _text.setString("error while setting up parameters");
        _text.setPosition(_x+_width/2-_text.getLocalBounds().width/2,_y+_height-_text.getLocalBounds().height*2);
        window.draw(_text);
    }

    window.draw(_spriteMove);
    window.draw(_spriteScale);
    window.draw(_spriteDelete);
}
