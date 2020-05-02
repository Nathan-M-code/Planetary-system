#include "Body.h"
#include "OptionBody.h"

using namespace std;

Body::Body(sf::Vector2f pos, sf::Vector2f initialVelocity, double mass, float radius, sf::Texture *texture){
    m_pos = pos;
    m_velocity = initialVelocity;

    m_mass = mass;
    m_radius = radius;

    if(texture == nullptr){ //use cs
        m_textured = false;
        m_cs = sf::CircleShape((float)m_radius);
        m_cs.setFillColor(getARndColor());
        m_cs.setOrigin(m_radius,m_radius);
        m_cs.setPosition(m_pos);
    }else{ //use sprite
        m_textured = true;
        m_sprite.setTexture(*texture);
        m_sprite.setScale((m_radius*2)/(float)texture->getSize().x, (m_radius*2)/(float)texture->getSize().y);
        m_sprite.setOrigin(m_sprite.getGlobalBounds().width/2,m_sprite.getGlobalBounds().height/2);
        m_sprite.setPosition(m_pos);
    }

    m_selected = false;
    m_optionBody = 0;
}
Body::~Body(){
    if(m_optionBody)
        delete m_optionBody;
}

void Body::setSelected(bool select){
    m_selected = select;
}

void Body::addOpionBody(OptionBody* optionBody){
    m_optionBody = optionBody;
}

void Body::removeOpionBody(){
    if(m_optionBody){
        delete m_optionBody;
        m_optionBody = 0;
    }
}

float Body::getMass() const{
    return m_mass;
}

sf::Vector2f Body::getPos() const{
    return m_pos;
}

sf::Vector2f Body::getVel() const{
    return m_velocity;
}

sf::Vector2f Body::getLastPosPrevisu() const{
    return m_listPosPreVisu[m_listPosPreVisu.size()-1];
}

float Body::getRadius() const{
    return m_radius;
}

OptionBody* Body::getOptionBody() const{
    return m_optionBody;
}

void Body::setMass(double mass){
    m_mass = mass;
}
void Body::setRadius(float radius){
    m_radius = radius;
    if(m_textured){
        m_sprite.setScale((m_radius*2)/(float)m_sprite.getTexture()->getSize().x, (m_radius*2)/(float)m_sprite.getTexture()->getSize().y);
        m_sprite.setOrigin(m_sprite.getGlobalBounds().width/2,m_sprite.getGlobalBounds().height/2);
        m_sprite.setPosition(m_pos);
    }else{
        m_cs.setRadius(m_radius);
        m_cs.setOrigin(m_radius,m_radius);
        m_cs.setPosition(m_pos);
    }
}
void Body::setPos(sf::Vector2f pos){
    m_pos = pos;
    if(m_textured){
        m_sprite.setPosition(m_pos);
    }else{
        m_cs.setPosition(m_pos);
    }

}
void Body::setVel(sf::Vector2f vel){
    m_velocity = vel;
}

bool Body::testClick(sf::Vector2f &cooMap){
    if(cooMap.x >= m_pos.x-m_radius && cooMap.x <= m_pos.x+m_radius && cooMap.y >= m_pos.y-m_radius && cooMap.y <= m_pos.y+m_radius){
        return true;
    }
    return false;
}

bool Body::isInCoo(sf::Vector2f &coo1, sf::Vector2f &coo2){
    //cout << m_pos.x << " " << m_pos.y << " "<<coo1.x << " " << coo1.y << " "<<coo2.x << " " << coo2.y<<endl;
    if(coo1.x <= m_pos.x && m_pos.x <= coo2.x && coo1.y <= m_pos.y && m_pos.y <= coo2.y){
        return true;
    }
    return false;
}

bool Body::clickOnOptionBody(sf::Vector2i &mousePos){
    if(m_optionBody){
        return m_optionBody->mouseIsOn(mousePos);
    }
    else{
        return false;
    }
}

bool Body::clickHandlerOptionBody(sf::Vector2i &mousePos, sf::Vector2f &cooMap, bool pressed){
    if(m_optionBody){
        if(pressed){
            if(m_optionBody->mouseIsOnDelete(mousePos)){
                return true;
            }else if(m_optionBody->mouseIsOnMove(mousePos)){
                m_optionBody->setMoving(true);
            }else if(m_optionBody->mouseIsOnScale(mousePos)){
                m_optionBody->setScaling(true);
            }else{ //click inside the ioptionBody
                m_optionBody->clickHandlerInside(mousePos);
            }
        }else{
            m_optionBody->setMoving(false);
            m_optionBody->setScaling(false);
        }
    }
    return false;
}

void Body::update(float timeStep, std::vector<Body*> &listBody){
    for(unsigned int i = 0;i<listBody.size();i++){
        if(listBody[i] != this){
            sf::Vector2f otherPos = listBody[i]->getPos();
            float sqrDst = pow(otherPos.x-m_pos.x,2)+pow(otherPos.y-m_pos.y,2); //en pxl
            sf::Vector2f dir = otherPos - m_pos;
            sf::Vector2f forceDir = normalize(dir);
            sf::Vector2f force = forceDir * (float)(6.674*pow(10,-11)) * (float)m_mass * listBody[i]->getMass() / sqrDst;
            sf::Vector2f acceleration = force / (float)m_mass;
            m_velocity += acceleration * timeStep;
        }
    }

    sf::Vector2f savePos = m_pos;

    //cout << m_velocity.x << " " << m_velocity.y << endl;
    m_pos += m_velocity*timeStep;
    //cout << m_pos.x << " " << m_pos.y << endl;

    //test collision
    for(unsigned int i = 0;i<listBody.size();i++){
        if(listBody[i] != this){
            sf::Vector2f otherPos = listBody[i]->getPos();

            sf::Vector2f vecDir = m_pos-savePos;
            float b = -vecDir.x;
            float a = vecDir.y;
            float c = -(a*savePos.x+b*savePos.y);
            //cout << a*otherPos.x+b*otherPos.y+c << " " << sqrt(pow(otherPos.x-savePos.x,2)+pow(otherPos.y-savePos.y,2)) << " " << sqrt(pow(otherPos.x-m_pos.x,2)+pow(otherPos.y-m_pos.y,2)) << endl;

            if(sqrt(pow(otherPos.x-m_pos.x,2)+pow(otherPos.y-m_pos.y,2)) <= m_radius+listBody[i]->getRadius()){
                //cout << "explosion" << endl;
                //remove the both body
                delete listBody[i];
                listBody.erase(listBody.begin()+i);
                for(unsigned int j=0;j<listBody.size();j++){
                    if(listBody[j] == this){
                        delete listBody[j];
                        listBody.erase(listBody.begin()+j);
                    }
                }
            }/*else if(a*otherPos.x+b*otherPos.y+c == 0 && sqrt(pow(otherPos.x-savePos.x,2)+pow(otherPos.y-savePos.y,2)) < sqrt(pow(otherPos.x-m_pos.x,2)+pow(otherPos.y-m_pos.y,2))){
                cout << "explosion" << endl;
                //remove the both body
                delete listBody[i];
                listBody.erase(listBody.begin()+i);
                for(unsigned int j=0;j<listBody.size();j++){
                    if(listBody[j] == this){
                        delete listBody[j];
                        listBody.erase(listBody.begin()+j);
                    }
                }
            }*/
        }
    }

    if(m_textured){
        m_sprite.setPosition(m_pos);
    }else{
        m_cs.setPosition(m_pos);
    }
}

void Body::updatePosPrevisu(float timeStep, std::vector<Body*> &listBody){
    sf::Vector2f myPos = m_listPosPreVisu[m_listPosPreVisu.size()-1];
    for(unsigned int i = 0;i<listBody.size();i++){
        if(listBody[i] != this){
            sf::Vector2f otherPos = listBody[i]->getLastPosPrevisu();
            float sqrDst = pow(otherPos.x-myPos.x,2)+pow(otherPos.y-myPos.y,2); //en pxl
            sf::Vector2f dir = otherPos - myPos;
            sf::Vector2f forceDir = normalize(dir);
            sf::Vector2f force = forceDir * (float)(6.674*pow(10,-11)) * (float)m_mass * listBody[i]->getMass() / sqrDst;
            sf::Vector2f acceleration = force / (float)m_mass;
            m_veloPrevisu += acceleration * timeStep;
        }
    }

    //sf::Vector2f savePos = myPos;

    //cout << m_veloPrevisu.x << " " << m_veloPrevisu.y << endl;
    m_listPosPreVisu.push_back(myPos + (m_veloPrevisu*timeStep));
    //cout << m_pos.x << " " << m_pos.y << endl;

    /*
    //test collision
    for(unsigned int i = 0;i<listBody.size();i++){
        if(listBody[i] != this){
            sf::Vector2f otherPos = listBody[i]->getPos();

            sf::Vector2f vecDir = m_pos-savePos;
            float b = -vecDir.x;
            float a = vecDir.y;
            float c = -(a*savePos.x+b*savePos.y);
            //cout << a*otherPos.x+b*otherPos.y+c << " " << sqrt(pow(otherPos.x-savePos.x,2)+pow(otherPos.y-savePos.y,2)) << " " << sqrt(pow(otherPos.x-m_pos.x,2)+pow(otherPos.y-m_pos.y,2)) << endl;

            if(sqrt(pow(otherPos.x-m_pos.x,2)+pow(otherPos.y-m_pos.y,2)) <= m_radius+listBody[i]->getRadius()){
                cout << "explosion" << endl;
                //remove the both body
                delete listBody[i];
                listBody.erase(listBody.begin()+i);
                for(unsigned int j=0;j<listBody.size();j++){
                    if(listBody[j] == this){
                        delete listBody[j];
                        listBody.erase(listBody.begin()+j);
                    }
                }
            }else if(a*otherPos.x+b*otherPos.y+c == 0 && sqrt(pow(otherPos.x-savePos.x,2)+pow(otherPos.y-savePos.y,2)) < sqrt(pow(otherPos.x-m_pos.x,2)+pow(otherPos.y-m_pos.y,2))){
                cout << "explosion" << endl;
                //remove the both body
                delete listBody[i];
                listBody.erase(listBody.begin()+i);
                for(unsigned int j=0;j<listBody.size();j++){
                    if(listBody[j] == this){
                        delete listBody[j];
                        listBody.erase(listBody.begin()+j);
                    }
                }
            }
        }
    }*/
}

void Body::clearlistPrevisu(){
    m_listPosPreVisu.clear();
    m_listPosPreVisu.push_back(sf::Vector2f(m_pos));
    m_veloPrevisu = m_velocity;
}

void Body::updateOptionBody(sf::Vector2i mousePos, sf::RenderWindow &window, sf::View &view, bool pause){
    if(m_optionBody){
        if(m_optionBody->isMoving()){
            m_optionBody->setPositionByButtonMove(mousePos);
        }else if(m_optionBody->isScaling()){
            m_optionBody->scaleByButtonScale(mousePos);
        }
        m_optionBody->update(window, view);
        if(!pause){
            m_optionBody->updateString();
        }
    }
}

void Body::textEntered(sf::Uint32 &key){
    if(m_optionBody){
        m_optionBody->textEntered(key);
    }
}

void Body::draw(sf::RenderWindow &window){
    if(m_textured){
        window.draw(m_sprite);
    }else{
        window.draw(m_cs);
    }
}

void Body::drawPrevisu(sf::RenderWindow &window){
    if(m_selected){
        sf::CircleShape csPreVisu(m_radius/2.0);
        csPreVisu.setFillColor(sf::Color(m_cs.getFillColor().r, m_cs.getFillColor().g, m_cs.getFillColor().b, 150));
        csPreVisu.setOrigin(m_radius/2.0,m_radius/2.0);

        sf::VertexArray lines(sf::LinesStrip, m_listPosPreVisu.size());

        for(unsigned int i=0;i<m_listPosPreVisu.size();i++){
            csPreVisu.setPosition(m_listPosPreVisu[i]);
            lines[i].position = m_listPosPreVisu[i];
            lines[i].color = m_cs.getFillColor();
            window.draw(csPreVisu);
        }

        window.draw(lines);
    }
}

void Body::drawOptionBody(sf::RenderWindow &window){
    if(m_optionBody){
        m_optionBody->draw(window);
    }
}
