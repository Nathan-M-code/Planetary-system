#include "OptionBody.h"
#include "CursorFloat.h"
#include "CursorInt.h"


using namespace std;

sf::Vector2i getScreenSize(){
    return sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
}

int main(){
    srand(time(NULL));

    TextureLoader::init();

    sf::Vector2i tailleEcran = getScreenSize();

    sf::Text text_camera;
    text_camera.setFont(*TextureLoader::getFont());
    text_camera.setFillColor(sf::Color(255,255,255));
    text_camera.setCharacterSize(16);

    sf::Vector2i mousePos;
    sf::Vector2f cooMap;
    sf::View view(sf::FloatRect(0,0,tailleEcran.x,tailleEcran.y));
    view.setSize(tailleEcran.x*10,tailleEcran.y*10);

    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(tailleEcran.x,tailleEcran.y), "Planet Simulation", sf::Style::Fullscreen);

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Uint32 key;

    bool paused = false;
    unsigned int nbPrevisu = 100;
    float timeStep = 1.0;

    bool rightClickPressed = false;

    unsigned int nbSelected = 0;
    bool isSelecting = false; //is true when the left mouse is pressed and there is no optionbody drawn
    sf::Vector2i saveCooScreen;
    sf::RectangleShape visuSelection;
    visuSelection.setFillColor(sf::Color::Transparent);
    visuSelection.setOutlineColor(sf::Color::Blue);
    visuSelection.setOutlineThickness(2);

    vector<Body*> listBody;
    listBody.push_back(new Body({tailleEcran.x/2,tailleEcran.y/2}, {0,0}, 5.9736*pow(10,14), 200)); //earth  5.9736*pow(10,24)
    listBody.push_back(new Body({tailleEcran.x/2-1000,tailleEcran.y/2}, {0,-5}, 7.3477*pow(10,13),50)); //moon 7.3477*pow(10,22)
    listBody.push_back(new Body({tailleEcran.x/2+1000,tailleEcran.y/2}, {0,5}, 7.3477*pow(10,13),50)); //moon 7.3477*pow(10,22)

    CursorFloat csfTimeStep(tailleEcran.x-200-20,20,200,20,0.1,20.0);
    csfTimeStep.setValue(timeStep);
    Cursor csiNbPrevisu(tailleEcran.x-200-20,50,200,20,1,200);
    csiNbPrevisu.setValue(nbPrevisu);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }
                    //-----------------------------------
                    if (event.key.code == sf::Keyboard::Space){
                        paused = !paused;
                    }
                    if (event.key.code == sf::Keyboard::N){
                        paused = true;
                        listBody.push_back(new Body(cooMap, {0,0}, 5.9736*pow(10,13), 50));
                        unsigned int i= listBody.size()-1;
                        sf::Vector2i cooScreen = window.mapCoordsToPixel(listBody[i]->getPos(), view);
                        listBody[i]->addOpionBody(new OptionBody(listBody[i],cooScreen.x,cooScreen.y,300,300));
                        listBody[i]->setSelected(true);
                        nbSelected++;
                    }
                    //------------------test-----------------
                    break;
                /*case sf::Event::KeyReleased:
                    break;*/
                case sf::Event::MouseMoved:
                    if(rightClickPressed){
                        sf::Vector2i newMousePosScreen = sf::Mouse::getPosition(window);
                        sf::Vector2f newCooMap = window.mapPixelToCoords(newMousePosScreen,view);
                        sf::Vector2f delta = cooMap-newCooMap;
                        view.setCenter(view.getCenter().x+delta.x, view.getCenter().y+delta.y);
                    }
                    mousePos = sf::Mouse::getPosition(window);
                    cooMap = window.mapPixelToCoords(mousePos,view);

                    if(isSelecting){
                        visuSelection.setSize(sf::Vector2f(mousePos-saveCooScreen));
                    }

                    if(csiNbPrevisu.isActivated()){
                        csiNbPrevisu.setValue(mousePos);
                        nbPrevisu = csiNbPrevisu.getValue();
                    }else if(csfTimeStep.isActivated()){
                        csfTimeStep.setValue(mousePos);
                        timeStep = csfTimeStep.getValue();
                    }

                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left){
                        if(csfTimeStep.mouseIsOnCursor(mousePos)){
                            csfTimeStep.setActivated(true);
                        }else if(csiNbPrevisu.mouseIsOnCursor(mousePos)){
                            csiNbPrevisu.setActivated(true);
                        }else{
                            bool mouseOnAOptionBody = false;
                            for(unsigned int i=0;i<listBody.size();i++){
                                if(listBody[i]->clickOnOptionBody(mousePos)){
                                    mouseOnAOptionBody = true;
                                    break;
                                }
                            }
                            if(!mouseOnAOptionBody){
                                nbSelected = 0;
                                isSelecting = true;
                                for(unsigned int i=0;i<listBody.size();i++){
                                    listBody[i]->setSelected(false);
                                    listBody[i]->removeOpionBody();
                                }
                                saveCooScreen = mousePos;
                                visuSelection.setPosition(sf::Vector2f(saveCooScreen));
                            }else{
                                for(unsigned int i=0;i<listBody.size();i++){
                                    if(listBody[i]->clickHandlerOptionBody(mousePos, cooMap, true)){ //pressed the delete button
                                        delete listBody[i];
                                        listBody.erase(listBody.begin()+i);
                                        i--;
                                    }
                                }
                            }
                        }
                    }else if(event.mouseButton.button == sf::Mouse::Right){
                        rightClickPressed = true;
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        csfTimeStep.setActivated(false);
                        csiNbPrevisu.setActivated(false);

                        if(isSelecting == true){
                            isSelecting = false;
                            visuSelection.setSize(sf::Vector2f(0,0));
                            sf::Vector2f firstCooMap = window.mapPixelToCoords(saveCooScreen,view);
                            //cout << "debut: " << firstCooMap.x << " " << firstCooMap.y << " fin: " << cooMap.x << " " << cooMap.y << endl;
                            for(unsigned int i=0;i<listBody.size();i++){
                                if(listBody[i]->isInCoo(firstCooMap, cooMap)){
                                    sf::Vector2i cooScreen = window.mapCoordsToPixel(listBody[i]->getPos(), view);
                                    listBody[i]->addOpionBody(new OptionBody(listBody[i],cooScreen.x,cooScreen.y,300,300));
                                    listBody[i]->getOptionBody()->updateString();
                                    listBody[i]->setSelected(true);
                                    nbSelected++;
                                }
                            }
                        }else{
                            for(unsigned int i=0;i<listBody.size();i++){
                                listBody[i]->clickHandlerOptionBody(mousePos, cooMap, false);
                            }
                        }
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right){
                        rightClickPressed = false;
                    }
                    break;

                case sf::Event::MouseWheelMoved:
                    if(event.mouseWheel.delta>0){ //zoom in delta>0
                        view.zoom(0.7);
                    }else if(event.mouseWheel.delta<0){ //zoom out delat<0
                        view.zoom(1.3);
                    }
                    break;
                case sf::Event::TextEntered:
                    key = event.text.unicode;
                    for(int i=0;i<listBody.size();i++){
                        listBody[i]->textEntered(key);
                    }
                    break;
                /*default:
                    break;*/
            }
        }
        //logique
        if(!paused){
            for(int i=0;i<listBody.size();i++){
                listBody[i]->update(timeStep, listBody);
            }
        }

        if(nbSelected>0){
            //PREVISU
            for(int i=0;i<listBody.size();i++){
                listBody[i]->clearlistPrevisu();
            }
            for(int i=0;i<nbPrevisu;i++){
                for(int i=0;i<listBody.size();i++){
                    listBody[i]->updatePosPrevisu(timeStep, listBody);
                }
            }
            //OPTIONBODY
            for(int i=0;i<listBody.size();i++){
                listBody[i]->updateOptionBody(mousePos, window, view, paused);
            }
        }


        //clear
        window.clear();

        //draw
        window.setView(view);
        for(int i=0;i<listBody.size();i++){
            listBody[i]->draw(window);
            listBody[i]->drawPrevisu(window);
        }

        window.setView(window.getDefaultView());
        if(isSelecting){
            window.draw(visuSelection);
        }
        for(int i=0;i<listBody.size();i++){
            listBody[i]->drawOptionBody(window);
        }
        csiNbPrevisu.draw(window);
        csfTimeStep.draw(window);

        //Text
        text_camera.setString("view: center x: "+intToString(view.getCenter().x)+" center y: "+intToString(view.getCenter().y)+" size: "+intToString(view.getSize().x)+" "+intToString(view.getSize().y));
        text_camera.setPosition(0,0);
        window.draw(text_camera);
        text_camera.setString("mouse: x: "+intToString(mousePos.x)+" y: "+intToString(mousePos.y));
        text_camera.setPosition(0,40);
        window.draw(text_camera);
        text_camera.setString("mouseCooMap: x: "+intToString(cooMap.x)+" y: "+intToString(cooMap.y));
        text_camera.setPosition(0,60);
        window.draw(text_camera);

        text_camera.setString("pause (space): "+BoolToString(paused));
        text_camera.setPosition(0,80);
        window.draw(text_camera);
        text_camera.setString("add a body (n)");
        text_camera.setPosition(0,100);
        window.draw(text_camera);

        text_camera.setString("nbSelected: "+intToString(nbSelected));
        text_camera.setPosition(0,140);
        window.draw(text_camera);


        window.display();
    }

    TextureLoader::freeRAM();

    return 0;
}
