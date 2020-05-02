#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "TextureLoader.h"

class TextBox{
private:
    sf::RectangleShape m_fond;
    sf::Text m_texte;
    std::string m_string;
    bool m_focus;
    sf::Vector2f m_pos;
public:
    TextBox(float posX, float posY, std::string message);
    ~TextBox();

    std::string getString() const;
    sf::Vector2f getSize() const;
    void setPos(sf::Vector2f pos);
    sf::Vector2f getPos() const;
    bool testClick(int mouseX, int mouseY);
    bool isFocus() const;
    void setFocus(bool act);
    void ajouterLettre(sf::Uint32 key);
    void setString(std::string str);
    void supprimerLettre();
    void draw(sf::RenderWindow &window);
};


#endif // TEXTBOX_H

