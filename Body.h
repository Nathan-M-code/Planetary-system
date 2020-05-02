#ifndef BODY_H
#define BODY_H

#include "TextureLoader.h"

class OptionBody;

class Body{
public:
    Body(sf::Vector2f pos, sf::Vector2f initialVelocity, double mass, float radius, sf::Texture *texture = nullptr);
    ~Body();

    void setSelected(bool select);
    void addOpionBody(OptionBody* optionBody);
    void removeOpionBody();

    float getMass() const;
    sf::Vector2f getPos() const;
    sf::Vector2f getVel() const;
    sf::Vector2f getLastPosPrevisu() const;
    float getRadius() const;
    OptionBody* getOptionBody() const;

    void setMass(double mass);
    void setRadius(float radius);
    void setPos(sf::Vector2f pos);
    void setVel(sf::Vector2f vel);

    void update(float timeStep, std::vector<Body*> &listBody);
    void updatePosPrevisu(float timeStep, std::vector<Body*> &listBody);
    void clearlistPrevisu();

    void updateOptionBody(sf::Vector2i mousePos, sf::RenderWindow &window, sf::View &view, bool pause);

    bool testClick(sf::Vector2f &cooMap);
    bool isInCoo(sf::Vector2f &coo1, sf::Vector2f &coo2);
    bool clickHandlerOptionBody(sf::Vector2i &mousePos, sf::Vector2f &cooMap, bool pressed);
    bool clickOnOptionBody(sf::Vector2i &mousePos);

    void textEntered(sf::Uint32 &key);

    void draw(sf::RenderWindow &window);
    void drawPrevisu(sf::RenderWindow &window);
    void drawOptionBody(sf::RenderWindow &window);

private:
    sf::Sprite m_sprite;
    sf::CircleShape m_cs;
    bool m_textured;

    sf::Vector2f m_pos;
    std::vector<sf::Vector2f> m_listPosPreVisu;

    sf::Vector2f m_veloPrevisu;

    sf::Vector2f m_velocity;

    double m_mass; //en kilo
    float m_radius;

    bool m_selected;
    OptionBody* m_optionBody;
};

#endif // BODY_H
