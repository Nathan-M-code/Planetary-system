#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED

#include "utile.h"

class TextureLoader{
public:
    static void init();
    static void ajouterTexturePlanet(std::string path);
    static void ajouterTextureButton(std::string path);

    static sf::Texture* getRndTexturePlanet();
    static sf::Texture* getTextureScale();
    static sf::Texture* getTextureMove();
    static sf::Texture* getTextureDelete();
    static sf::Font* getFont();

    static void freeRAM();

private:
    static std::vector<sf::Texture*> m_listeTexturePlanet;
    static std::vector<sf::Texture*> m_listeTextureButton;
    static sf::Font m_font;
};

#endif // TEXTURELOADER_H_INCLUDED
