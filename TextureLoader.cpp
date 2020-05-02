#include "TextureLoader.h"

using namespace std;

std::vector<sf::Texture*> TextureLoader::m_listeTexturePlanet = {};
std::vector<sf::Texture*> TextureLoader::m_listeTextureButton = {};
sf::Font TextureLoader::m_font;

void TextureLoader::init(){
    TextureLoader::ajouterTextureButton("data/move.png");
    TextureLoader::ajouterTextureButton("data/scale.png");
    TextureLoader::ajouterTextureButton("data/delete.png");
    m_font.loadFromFile("data/calibri.ttf");
}

sf::Texture* TextureLoader::getTextureScale(){
    return m_listeTextureButton[1];
}
sf::Texture* TextureLoader::getTextureMove(){
    return m_listeTextureButton[0];
}
sf::Texture* TextureLoader::getTextureDelete(){
    return m_listeTextureButton[2];
}

sf::Texture* TextureLoader::getRndTexturePlanet(){
    return m_listeTexturePlanet[rand_a_b(0,m_listeTexturePlanet.size())];
}

sf::Font* TextureLoader::getFont(){
    return &m_font;
}

void TextureLoader::freeRAM(){
    for(unsigned int i=0;i<m_listeTexturePlanet.size();i++){
        delete m_listeTexturePlanet[i];
        m_listeTexturePlanet[i] = 0;
    }
}

void TextureLoader::ajouterTexturePlanet(std::string path){
    sf::Texture *t = new sf::Texture;
    t->loadFromFile(path);
    m_listeTexturePlanet.push_back(t);
}

void TextureLoader::ajouterTextureButton(std::string path){
    sf::Texture *t = new sf::Texture;
    t->loadFromFile(path);
    m_listeTextureButton.push_back(t);
}

