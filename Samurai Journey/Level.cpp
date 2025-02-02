#include "Level.h"

namespace Levels {

    Managers::GraphicManager* Level::pGraphic = Managers::GraphicManager::getInstance();

	Level::Level(bool isMultiplayer, Managers::States::State_ID id) : pPlayer1(nullptr), pPlayer2(nullptr),
        p1life(nullptr), p2life(nullptr), isMultiplayer(isMultiplayer),
        Managers::States::State(id)
    {
        mapImage = new sf::RectangleShape();
        mapSprite = new GraphicalElements::Animation(mapImage, Math::CoordF(1, 1));

        pCollision = Managers::Collisions::CollisionManager::getInstance();
        pCollision->setLists(movingEntities, staticEntities);
        
        p1life = new Menu::Text("Player 1's HP: ", pGraphic->loadFont("alagard.ttf"), 30);
        p1life->setTextColor(sf::Color(31, 28, 43));
        if (isMultiplayer) {
            p2life = new Menu::Text("Player 2's HP: ", pGraphic->loadFont("alagard.ttf"), 30);
            p2life->setTextColor(sf::Color(31, 28, 43));
        }
    }

    Level::~Level() {
        if (mapImage) {
            delete mapImage;
            mapImage = nullptr;
        }

        if (mapSprite) {
            delete mapSprite;
            mapSprite = nullptr;
        }

        if (pPlayer1) {
            pPlayer1->changeObserverState(false);
        }

        if (isMultiplayer) {
            pPlayer2->changeObserverState(false);
        }

        while (staticEntities.getSize() > 0) {
            Entities::Entity* entity = *staticEntities.begin();
            staticEntities.removeEntity(entity);
        }

        while (movingEntities.getSize() > 0) {
            Entities::Entity* entity = *movingEntities.begin();
            movingEntities.removeEntity(entity);
        }
    }

	void Level::createMap(const char* filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }

        json tmjData;

        try {
            file >> tmjData;
            std::cout << "Arquivo JSON carregado com sucesso!" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Erro ao processar JSON: " << e.what() << std::endl;
            return;
        }

        int width = tmjData["width"];
        int height = tmjData["height"];
        int indice = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int value = tmjData["layers"][0]["data"][indice++];
                float posx = 10 * x;
                float posy = 10 * y;
                switch (value) {
                    case 0: {
                        break;
                    }

                    case 1: {
                        Entities::Obstacles::Platform* tmp = new Entities::Obstacles::Platform(Math::CoordF(posx/*-5*/, posy + 8), Math::CoordF(10.0f, 10.0f), false);
                        if (tmp) {
                            staticEntities.addEntity(tmp);
                        }
                        break;
                    }

                    case 2: {
                        pPlayer1 = new Entities::Characters::Player(Math::CoordF(posx, posy), true, this);
                        if (pPlayer1) {
                            movingEntities.addEntity(pPlayer1);
                        }
                        break;
                    }

                    case 3: {
                        Entities::Characters::Wolf* w = new Entities::Characters::Wolf(Math::CoordF(posx, posy));
                        if (w) {
                            movingEntities.addEntity(w);
                        }
                        break;
                    }

                    case 4: {
                        int aux = rand() % 2;
                        if (aux == 1) {
                            Entities::Characters::Wolf* w1 = new Entities::Characters::Wolf(Math::CoordF(posx, posy));
                            if (w1) {
                                movingEntities.addEntity(w1);
                            }
                        }
                        break;
                    }

                    case 5: {
                        Entities::Characters::Archer* a = new Entities::Characters::Archer(Math::CoordF(posx, posy), &movingEntities);
                        if (a) {
                            movingEntities.addEntity(a);
                        }
                        break;
                    }

                    case 6: {
                        int aux = rand() % 2;
                        if (aux == 1) {
                            Entities::Characters::Archer* a1 = new Entities::Characters::Archer(Math::CoordF(posx, posy), &movingEntities);
                            if (a1) {
                                movingEntities.addEntity(a1);
                            }
                        }
                        break;
                    }

                    case 7: {
                        Entities::Obstacles::Fire* fire = new Entities::Obstacles::Fire(Math::CoordF(posx, posy));
                        if (fire) {
                            staticEntities.addEntity(fire);
                        }
                        break;
                    }

                    case 8: {
                        int aux = rand() % 2;
                        if (aux == 1) {
                            Entities::Obstacles::Fire* fire = new Entities::Obstacles::Fire(Math::CoordF(posx, posy));
                            if (fire) {
                                staticEntities.addEntity(fire);
                            }
                        }
                        break;
                    }

                    case 9: {
                        if (isMultiplayer) {
                            pPlayer2 = new Entities::Characters::Player(Math::CoordF(posx, posy), false, this);
                            if (pPlayer2) {
                                movingEntities.addEntity(pPlayer2);
                            }
                        }
                        break;
                    }

                    case 10: {
                        Entities::Obstacles::Platform* fake = new Entities::Obstacles::Platform(Math::CoordF(posx, posy), Math::CoordF(10.0f, 10.0f), true);
                        if (fake) {
                            staticEntities.addEntity(fake);
                        }
                        break;
                    }

                    case 11: {
                        Entities::Characters::DemonSamurai* demon = new Entities::Characters::DemonSamurai(Math::CoordF(posx, posy));
                        if (demon) {
                            movingEntities.addEntity(demon);
                        }
                        break;
                    }

                    case 12: {
                        Entities::Obstacles::Bush* bush = new Entities::Obstacles::Bush(Math::CoordF(posx, posy - 15));
                        if (bush) {
                            staticEntities.addEntity(bush);
                        }
                        break;
                    }

                    case 13: {
                        int aux = rand() % 2;

                        if (aux == 1) {
                            Entities::Characters::DemonSamurai* demon = new Entities::Characters::DemonSamurai(Math::CoordF(posx, posy - 250));
                            if (demon) {
                                movingEntities.addEntity(demon);
                            }
                        }
                        else {
                            Entities::Obstacles::Bush* bush = new Entities::Obstacles::Bush(Math::CoordF(posx + 20, posy - 5));
                            if (bush) {
                                staticEntities.addEntity(bush);
                            }
                        }
                        break;
                    }
                }


            }
        }

        for (auto itM = (&movingEntities)->begin(); itM != (&movingEntities)->end(); ++itM) {
            if (*itM) {
                if ((*itM)->getID() == ID::wolf || (*itM)->getID() == ID::archer || (*itM)->getID() == ID::demonsamurai ) {
                    if (auto* enemy = dynamic_cast<Entities::Characters::Enemy*>(*itM)) {
                        enemy->setPlayers(pPlayer1, pPlayer2);
                    }
                }

            }
        }
	}

    void Level::updateCamera(float cameraLimit) {
        if (pPlayer1->getIsActive()) {
            if (pPlayer1->getPosition().x >= cameraLimit && pPlayer1->getPosition().x <= mapImage->getSize().x - cameraLimit) {
                pPlayer1->centerCamera();
            }
            else if (pPlayer1->getPosition().x < mapImage->getSize().x / 2.0f) {
                pGraphic->centerView(Math::CoordF(cameraLimit, pGraphic->getWindowSize().y / 2.0f));
            }

            else {
                pGraphic->centerView(Math::CoordF(mapImage->getSize().x - cameraLimit, pGraphic->getWindowSize().y / 2.0f));
            }
        }

        else if (isMultiplayer && pPlayer2->getIsActive()) {
            if (pPlayer2->getPosition().x >= cameraLimit && pPlayer2->getPosition().x <= mapImage->getSize().x - cameraLimit) {
                pPlayer2->centerCamera();
            }
            else if (pPlayer2->getPosition().x < mapImage->getSize().x / 2.0f) {
                pGraphic->centerView(Math::CoordF(cameraLimit, pGraphic->getWindowSize().y / 2.0f));
            }
            else {
                pGraphic->centerView(Math::CoordF(mapImage->getSize().x - cameraLimit, pGraphic->getWindowSize().y / 2.0f));
            }
        }
    }

    void Level::render() {
        pGraphic->render(mapImage);

        std::string hpStr = std::to_string(static_cast<int>(pPlayer1->getHP()));
        p1life->setText("Player 1's HP: " + hpStr);
        p1life->setTextPos(Math::CoordF(pGraphic->getCenterView().x - 930, 15));
        sf::Text shadow = p1life->getText();
        shadow.setFillColor(sf::Color(255, 255, 255, 80));
        shadow.move(1.f, 1.f);
        pGraphic->render(shadow);
        pGraphic->render(p1life->getText());

        if (isMultiplayer) {
            std::string hpStr2 = std::to_string(static_cast<int>(pPlayer2->getHP()));
            p2life->setText("Player 2's HP: " + hpStr2);
            p2life->setTextPos(Math::CoordF(pGraphic->getCenterView().x - 930, 65));
            sf::Text shadow2 = p2life->getText();
            shadow2.setFillColor(sf::Color(255, 255, 255, 80));
            shadow2.move(1.f, 1.f);
            pGraphic->render(shadow2);
            pGraphic->render(p2life->getText());
        }
    }

    List::EntitiesList* Level::getEntitiesList() {
        return &movingEntities;
    }

    void Level::setPlayerPoints(int points) {
        pPlayer1->setPoints(points);
    }
}