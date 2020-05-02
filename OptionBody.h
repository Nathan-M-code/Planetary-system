#ifndef OPTIONBODY_H_INCLUDED
#define OPTIONBODY_H_INCLUDED

#include "Body.h"
#include "TextBox.h"

class OptionBody{
public:
    OptionBody(Body *bodyTarget, int x, int y, unsigned width, unsigned height);
    ~OptionBody();

    bool isMoving() const;
    bool isScaling() const;

    void setMoving(bool mov);
    void setScaling(bool scal);

    bool mouseIsOnMove(sf::Vector2i &mousePos);
    bool mouseIsOnScale(sf::Vector2i &mousePos);
    bool mouseIsOnDelete(sf::Vector2i &mousePos);

    bool mouseIsOn(sf::Vector2i &mousePos);

    void clickHandlerInside(sf::Vector2i &mousePos);

    void setPositionByButtonMove(sf::Vector2i &mousePos);
    void scaleByButtonScale(sf::Vector2i &mousePos);

    void textEntered(sf::Uint32 &key);

    void update(sf::RenderWindow &window, sf::View &view);
    void updateString();

    void draw(sf::RenderWindow &window);

private:
    unsigned _width;
    unsigned _widthMin;
    unsigned _height;
    unsigned _heightMin;
    int _x;
    int _y;

    bool _scaling;
    bool _moving;

    bool _error;

    sf::RectangleShape _rsBackground;

    sf::Text _text;

    sf::Sprite _spriteMove;
    sf::Sprite _spriteScale;
    sf::Sprite _spriteDelete;

    Body *_bodyTarget;
    sf::VertexArray _line;

    TextBox *_tbFocus;
    std::vector<TextBox*> _listTb;

    void updatePosTB();
};

#endif // OPTIONBODY_H_INCLUDED
