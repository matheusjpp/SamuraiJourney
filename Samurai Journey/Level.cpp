#include "Level.h"

namespace Levels {

    Managers::GraphicManager* Level::pGraphic = Managers::GraphicManager::getInstance();

	Level::Level(bool isMultiplayer, Managers::States::State_ID id) : pPlayer1(nullptr), isMultiplayer(isMultiplayer), Managers::States::State(id) {
        mapImage = new sf::RectangleShape();
        mapSprite = new GraphicalElements::Animation(mapImage, Math::CoordF(1, 1));

        pCollision = Managers::Collisions::CollisionManager::getInstance();
        pCollision->setLists(movingEntities, staticEntities);
        
    }

	Level::~Level() {
        if (mapImage) delete mapImage;
        if (mapSprite) delete mapSprite;
        // clear nas listas
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
                        pPlayer1 = new Entities::Characters::Player(Math::CoordF(posx, posy), true);
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
                        // fire to do
                        break;
                    }

                    case 8: {
                        // fire rand to do
                        break;
                    }

                    case 9: {
                        if (isMultiplayer) {
                            Entities::Characters::Player* p2 = new Entities::Characters::Player(Math::CoordF(posx, posy), false);
                            if (p2) {
                                movingEntities.addEntity(p2);
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
                        Entities::Characters::DemonSamurai * demon = new Entities::Characters::DemonSamurai(Math::CoordF(posx, posy));
                        if (demon) {
                            movingEntities.addEntity(demon);
                        }
                        break;
                    }

                    case 12: {
                        // bush to do
                        break;
                    }

                    case 13: {
                        // bush or demon samurai
                        break;
                    }
                }


            }
        }

        for (auto itM = (&movingEntities)->begin(); itM != (&movingEntities)->end(); ++itM) {
            if (*itM) {
                if ((*itM)->getID() == ID::wolf || (*itM)->getID() == ID::archer || (*itM)->getID() == ID::demonsamurai ) {
                    if (auto* enemy = dynamic_cast<Entities::Characters::Enemy*>(*itM)) {
                        enemy->setPlayer(pPlayer1);
                        //fazer pra p2
                    }
                }

            }
        }

	}

}