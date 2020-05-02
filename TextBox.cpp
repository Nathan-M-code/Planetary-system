#include "TextBox.h"

using namespace std;

TextBox::TextBox(float posX, float posY, string message){
    m_pos = sf::Vector2f(posX, posY);

    m_fond.setSize(sf::Vector2f(100,20));
    m_fond.setPosition(m_pos);
    m_fond.setFillColor(sf::Color(220,220,220));
    m_fond.setOutlineThickness(2);
    m_fond.setOutlineColor(sf::Color(120,120,120));

    m_texte.setFont(*TextureLoader::getFont());
    m_texte.setPosition(posX+2, posY);
    m_texte.setCharacterSize(16);
    m_texte.setFillColor(sf::Color(0,0,0));
    m_string = message;
    m_texte.setString(m_string);

    m_focus = false;
}
TextBox::~TextBox(){}

bool TextBox::testClick(int mouseX, int mouseY){
    return (mouseX>=m_pos.x && mouseX<=m_pos.x+m_fond.getSize().x && mouseY>=m_pos.y && mouseY<=m_pos.y+m_fond.getSize().y);
}

sf::Vector2f TextBox::getSize() const{
    return m_fond.getSize();
}

void TextBox::setPos(sf::Vector2f pos){
    m_pos = pos;
    m_fond.setPosition(pos);
    m_texte.setPosition(pos.x+2, pos.y);
}

sf::Vector2f TextBox::getPos() const{
    return m_pos;
}

void TextBox::setFocus(bool act){
    m_focus = act;
    if(m_focus){
        m_fond.setOutlineColor(sf::Color(255,255,255));
    }else{
        m_fond.setOutlineColor(sf::Color(120,120,120));
    }
    m_texte.setString(m_string);
}

std::string TextBox::getString() const{
    return m_texte.getString();
}

bool TextBox::isFocus() const{
    return m_focus;
}

void TextBox::setString(std::string str){
    m_string = str;
    m_texte.setString(m_string);
    if(str == ""){
        m_fond.setSize(sf::Vector2f(200,20));
    }
}

void TextBox::ajouterLettre(sf::Uint32 key){
    m_string += static_cast<char>(key);
    m_texte.setString(m_string);
    if(m_texte.getLocalBounds().width > 200){
        m_fond.setSize(sf::Vector2f(m_texte.getLocalBounds().width+5, m_fond.getSize().y));
    }
}
void TextBox::supprimerLettre(){
    m_string = m_string.substr(0, m_string.size() - 1);
    m_texte.setString(m_string);
    if(m_texte.getLocalBounds().width > 200){
        m_fond.setSize(sf::Vector2f(m_texte.getLocalBounds().width+5, m_fond.getSize().y));
    }
}
void TextBox::draw(sf::RenderWindow &window){
    window.draw(m_fond);
    window.draw(m_texte);
}
