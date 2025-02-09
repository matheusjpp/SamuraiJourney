#include "Level.h"

namespace Levels {

    Managers::GraphicManager* Level::pGraphic = Managers::GraphicManager::getInstance();

    Entities::Factories::EnemyFactory Level::enemyFactory;
    Entities::Factories::PlayerFactory Level::playerFactory;
    Entities::Factories::ObstacleFactory Level::obstacleFactory;
    Entities::Factories::ArrowFactory Level::arrowFactory;

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

	void Level::createLevel(const char* filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }

        json tmjData;

        try {
            file >> tmjData;
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
                        Entities::Obstacles::Platform* tmp = static_cast<Entities::Obstacles::Platform*>(obstacleFactory.FactoryMethod(Math::CoordF(posx, posy + 8), false, false, nullptr, nullptr, ID::platform));
                            //new Entities::Obstacles::Platform(Math::CoordF(posx/*-5*/, posy + 8), Math::CoordF(10.0f, 10.0f), false);
                        if (tmp) {
                            staticEntities.addEntity(tmp);
                        }
                        break;
                    }

                    case 2: {
                        pPlayer1 = static_cast<Entities::Characters::Player*>(playerFactory.FactoryMethod(Math::CoordF(posx, posy), true, false, nullptr, this, ID::player));
                            //new Entities::Characters::Player(Math::CoordF(posx, posy), true, this);
                        if (pPlayer1) {
                            movingEntities.addEntity(pPlayer1);
                        }
                        break;
                    }

                    case 3: {
                        Entities::Characters::Wolf* w = static_cast<Entities::Characters::Wolf*>(enemyFactory.FactoryMethod(Math::CoordF(posx, posy), false, false, nullptr, nullptr, ID::wolf));
                            //new Entities::Characters::Wolf(Math::CoordF(posx, posy));
                        if (w) {
                            movingEntities.addEntity(w);
                        }
                        break;
                    }

                    case 4: {
                        int aux = rand() % 2;
                        if (aux == 1) {
                            Entities::Characters::Wolf* w1 = static_cast<Entities::Characters::Wolf*>(enemyFactory.FactoryMethod(Math::CoordF(posx, posy), false, false, nullptr, nullptr, ID::wolf));
                                //new Entities::Characters::Wolf(Math::CoordF(posx, posy));
                            if (w1) {
                                movingEntities.addEntity(w1);
                            }
                        }
                        break;
                    }

                    case 5: {
                        Entities::Characters::Archer* a = static_cast<Entities::Characters::Archer*>(enemyFactory.FactoryMethod(Math::CoordF(posx, posy), false, false, &movingEntities, nullptr, ID::archer));
                            //new Entities::Characters::Archer(Math::CoordF(posx, posy), &movingEntities);
                        if (a) {
                            movingEntities.addEntity(a);
                        }
                        break;
                    }

                    case 6: {
                        int aux = rand() % 2;
                        if (aux == 1) {
                            Entities::Characters::Archer* a1 = static_cast<Entities::Characters::Archer*>(enemyFactory.FactoryMethod(Math::CoordF(posx, posy), false, false, &movingEntities, nullptr, ID::archer));
                                //new Entities::Characters::Archer(Math::CoordF(posx, posy), &movingEntities);
                            if (a1) {
                                movingEntities.addEntity(a1);
                            }
                        }
                        break;
                    }

                    case 7: {
                        Entities::Obstacles::Fire* fire = static_cast<Entities::Obstacles::Fire*>(obstacleFactory.FactoryMethod(Math::CoordF(posx, posy - 20), false, false, nullptr, nullptr, ID::fire));
                            //new Entities::Obstacles::Fire(Math::CoordF(posx, posy - 20));
                        if (fire) {
                            staticEntities.addEntity(fire);
                        }
                        break;
                    }

                    case 8: {
                        int aux = rand() % 2;
                        if (aux == 1) {
                            Entities::Obstacles::Fire* fire = static_cast<Entities::Obstacles::Fire*>(obstacleFactory.FactoryMethod(Math::CoordF(posx, posy - 20), false, false, nullptr, nullptr, ID::fire));
                                //new Entities::Obstacles::Fire(Math::CoordF(posx, posy - 20));
                            if (fire) {
                                staticEntities.addEntity(fire);
                            }
                        }
                        break;
                    }

                    case 9: {
                        if (isMultiplayer) {
                            pPlayer2 = static_cast<Entities::Characters::Player*>(playerFactory.FactoryMethod(Math::CoordF(posx, posy), false, false, nullptr, this, ID::player));
                                //new Entities::Characters::Player(Math::CoordF(posx, posy), false, this);
                            if (pPlayer2) {
                                movingEntities.addEntity(pPlayer2);
                            }
                        }
                        break;
                    }

                    case 10: {
                        int aux = rand() % 2;
                        if (aux == 1) {
                            Entities::Obstacles::Platform* fake = static_cast<Entities::Obstacles::Platform*>(obstacleFactory.FactoryMethod(Math::CoordF(posx, posy - 20), false, true, nullptr, nullptr, ID::platform));
                            //new Entities::Obstacles::Platform(Math::CoordF(posx, posy), Math::CoordF(10.0f, 10.0f), true);
                            if (fake) {
                                staticEntities.addEntity(fake);
                            }
                        }
                        break;
                    }

                    case 11: {
                        Entities::Characters::DemonSamurai* demon = static_cast<Entities::Characters::DemonSamurai*>(enemyFactory.FactoryMethod(Math::CoordF(posx, posy), false, false, nullptr, nullptr, ID::demonsamurai));
                            //new Entities::Characters::DemonSamurai(Math::CoordF(posx, posy));
                        if (demon) {
                            movingEntities.addEntity(demon);
                        }
                        break;
                    }

                    case 12: {
                        Entities::Obstacles::Bush* bush = static_cast<Entities::Obstacles::Bush*>(obstacleFactory.FactoryMethod(Math::CoordF(posx, posy - 15), false, false, nullptr, nullptr, ID::bush));
                            //new Entities::Obstacles::Bush(Math::CoordF(posx, posy - 15));
                        if (bush) {
                            staticEntities.addEntity(bush);
                        }
                        break;
                    }

                    case 13: {
                        int aux = rand() % 2;

                        if (aux == 1) {
                            Entities::Characters::DemonSamurai* demon = static_cast<Entities::Characters::DemonSamurai*>(enemyFactory.FactoryMethod(Math::CoordF(posx, posy - 250), false, false, nullptr, nullptr, ID::demonsamurai));
                                //new Entities::Characters::DemonSamurai(Math::CoordF(posx, posy - 250));
                            if (demon) {
                                movingEntities.addEntity(demon);
                            }
                        }
                        else {
                            Entities::Obstacles::Bush* bush = static_cast<Entities::Obstacles::Bush*>(obstacleFactory.FactoryMethod(Math::CoordF(posx + 20, posy - 5), false, false, nullptr, nullptr, ID::bush));
                                //new Entities::Obstacles::Bush(Math::CoordF(posx + 20, posy - 5));
                            if (bush) {
                                staticEntities.addEntity(bush);
                            }
                        }
                        break;
                    }

                    case 14: {
                        Entities::Obstacles::Portal* portal = static_cast<Entities::Obstacles::Portal*>(obstacleFactory.FactoryMethod(Math::CoordF(posx, posy), false, false, nullptr, nullptr, ID::portal));
                            //new Entities::Obstacles::Portal(Math::CoordF(posx, posy));
                        if (portal) {
                            if (pStateM->getCurrentState()->getID() == Managers::States::State_ID::bosslevel_singleplayer || pStateM->getCurrentState()->getID() == Managers::States::State_ID::bosslevel_multiplayer) portal->setDirection(true);
                            staticEntities.addEntity(portal);
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

            if (isMultiplayer) {
                if (fabs(pPlayer1->getPosition().x - pPlayer2->getPosition().x) > 960.0f) {
                    pPlayer2->setPosition(Math::CoordF(pPlayer1->getPosition().x, pPlayer1->getPosition().y - 20));
                }
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
        if (pPlayer1->getHP() < 0) p1life->setText("Player 1's HP: 0");
        else p1life->setText("Player 1's HP: " + hpStr);
        p1life->setTextPos(Math::CoordF(pGraphic->getCenterView().x - 930, 15));
        sf::Text shadow = p1life->getText();
        shadow.setFillColor(sf::Color(255, 255, 255, 80));
        shadow.move(1.f, 1.f);
        pGraphic->render(shadow);
        pGraphic->render(p1life->getText());

        if (isMultiplayer) {
            std::string hpStr2 = std::to_string(static_cast<int>(pPlayer2->getHP()));
            if (pPlayer2->getHP() < 0) p2life->setText("Player 2's HP: 0");
            else p2life->setText("Player 2's HP: " + hpStr2);
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

    void Level::executePortal() {
        for (auto itS = staticEntities.begin(); itS != staticEntities.end(); ++itS) {
            if (*itS) {
                if ((*itS)->getID() == ID::portal) (*itS)->execute();
            }
        }
    }

    void Level::saveLevel(const char* filePath) {
        json j;

        j["GAME"] = pStateM->getPreviousState()->getID();

        if (pPlayer1->getIsActive()) {
            j["Player1"]["position"]["x"] = pPlayer1->getPosition().x;
            j["Player1"]["position"]["y"] = pPlayer1->getPosition().y;
            j["Player1"]["isActive"] = pPlayer1->getIsActive();
            j["Player1"]["isPlayer1"] = pPlayer1->getIsPlayer1();
            j["Player1"]["points"] = pPlayer1->getScorePoints();
            j["Player1"]["isDefending"] = pPlayer1->getIsDefending();
            j["Player1"]["isHealing"] = pPlayer1->getIsHealing();
            j["Player1"]["healTimer"] = pPlayer1->getHealTimer();
            j["Player1"]["hp"] = pPlayer1->getHP();
            j["Player1"]["isDying"] = pPlayer1->getIsDying();
            j["Player1"]["isHurting"] = pPlayer1->getIsHurting();
            j["Player1"]["isAttacking"] = pPlayer1->getIsAttacking();
            j["Player1"]["attackCooldown"] = pPlayer1->getAttackCooldown();
            j["Player1"]["cooldownTimer"] = pPlayer1->getCooldownTimer();
            j["Player1"]["attackTimer"] = pPlayer1->getAttackTimer();
            j["Player1"]["deathTimer"] = pPlayer1->getDeathTimer();
            j["Player1"]["hurtingTimer"] = pPlayer1->getHurtingTimer();
            j["Player1"]["impactTimer"] = pPlayer1->getImpactTimer();
            j["Player1"]["isFacingLeft"] = pPlayer1->getIsFacingLeft();
            j["Player1"]["isMoving"] = pPlayer1->getIsMoving();
        }
        if (isMultiplayer) {
            if (pPlayer2->getIsActive()) {
                j["Player2"]["position"]["x"] = pPlayer2->getPosition().x;
                j["Player2"]["position"]["y"] = pPlayer2->getPosition().y;
                j["Player2"]["isActive"] = pPlayer2->getIsActive();
                j["Player2"]["isPlayer1"] = pPlayer2->getIsPlayer1();
                j["Player2"]["points"] = pPlayer2->getScorePoints();
                j["Player2"]["isDefending"] = pPlayer2->getIsDefending();
                j["Player2"]["isHealing"] = pPlayer2->getIsHealing();
                j["Player2"]["healTimer"] = pPlayer2->getHealTimer();
                j["Player2"]["hp"] = pPlayer2->getHP();
                j["Player2"]["isDying"] = pPlayer2->getIsDying();
                j["Player2"]["isHurting"] = pPlayer2->getIsHurting();
                j["Player2"]["isAttacking"] = pPlayer2->getIsAttacking();
                j["Player2"]["attackCooldown"] = pPlayer2->getAttackCooldown();
                j["Player2"]["cooldownTimer"] = pPlayer2->getCooldownTimer();
                j["Player2"]["attackTimer"] = pPlayer2->getAttackTimer();
                j["Player2"]["deathTimer"] = pPlayer2->getDeathTimer();
                j["Player2"]["hurtingTimer"] = pPlayer2->getHurtingTimer();
                j["Player2"]["impactTimer"] = pPlayer2->getImpactTimer();
                j["Player2"]["isFacingLeft"] = pPlayer2->getIsFacingLeft();
                j["Player2"]["isMoving"] = pPlayer2->getIsMoving();
            }
        }
        //save obstacles
        for (auto itS = staticEntities.begin(); itS != staticEntities.end(); itS++) {
            
            auto& sE = *itS;
 
            json entity;

            entity["type"] = sE->getID();
            entity["position"]["x"] = sE->getPosition().x;
            entity["position"]["y"] = sE->getPosition().y;
            entity["isActive"] = sE->getIsActive();
            entity["isFake"] = static_cast<Entities::Obstacles::Platform*>(sE)->getIsFake();

            j["obstacles"].push_back(entity);
        }
        //save enemies
        for (auto itM = movingEntities.begin(); itM != movingEntities.end(); itM++) {
            auto& sM = *itM;
        
            if ((sM->getID() == ID::wolf || sM->getID()== ID::archer || sM->getID()== ID::demonsamurai) && sM->getIsActive()) {
                json enemy;

                enemy["type"] = sM->getID();
                enemy["position"]["x"] = sM->getPosition().x;
                enemy["position"]["y"] = sM->getPosition().y;
                enemy["isActive"] = sM->getIsActive();
                enemy["isFacingLeft"] = static_cast<Entities::MovingEntity*>(sM)->getIsFacingLeft();
                enemy["isMoving"] = static_cast<Entities::MovingEntity*>(sM)->getIsMoving();
                enemy["counted"] = static_cast<Entities::Characters::Enemy*>(sM)->getCounted();
                enemy["hp"] = static_cast<Entities::Characters::Enemy*> (sM)->getHP();
                enemy["isDying"] = static_cast<Entities::Characters::Enemy*> (sM)->getIsDying();
                enemy["isHurting"] = static_cast<Entities::Characters::Enemy*> (sM)->getIsHurting();
                enemy["isAttacking"] = static_cast<Entities::Characters::Enemy*> (sM)->getIsAttacking();
                enemy["attackCooldown"] = static_cast<Entities::Characters::Enemy*> (sM)->getAttackCooldown();
                enemy["cooldownTimer"] = static_cast<Entities::Characters::Enemy*> (sM)->getCooldownTimer();
                enemy["attackTimer"] = static_cast<Entities::Characters::Enemy*> (sM)->getAttackTimer();
                enemy["deathTimer"] = static_cast<Entities::Characters::Enemy*> (sM)->getDeathTimer();
                enemy["hurtingTimer"] = static_cast<Entities::Characters::Enemy*> (sM)->getHurtingTimer();
                enemy["impactTimer"] = static_cast<Entities::Characters::Enemy*> (sM)->getImpactTimer();

                if (sM->getID() == ID::wolf) {
                   enemy["isFirstAttack"] = static_cast<Entities::Characters::Wolf*>(sM)->getIsFirstAttack();
                   enemy["FirstAttackTimer"] = static_cast<Entities::Characters::Wolf*>(sM)->getFirstAttackTimer();
                }
                if (sM->getID() == ID::archer) {
                   enemy["arrowDelayTimer"] = static_cast<Entities::Characters::Archer*>(sM)->getArrowDelayTimer();
                   enemy["movingDelayTimer"] = static_cast<Entities::Characters::Archer*>(sM)->getMovingDelayTimer();
                }
                if (sM->getID() == ID::demonsamurai) {
                   enemy["cont"] = static_cast<Entities::Characters::DemonSamurai*>(sM)->getCont();
                   enemy["isLastBuffed"] = static_cast<Entities::Characters::DemonSamurai*>(sM)->getIsLastBuffed();
                   enemy["shoutTimer"] = static_cast<Entities::Characters::DemonSamurai*>(sM)->getShoutTimer();
                   enemy["isShouting"] = static_cast<Entities::Characters::DemonSamurai*>(sM)->getIsShouting();
                }
                   j["enemies"].push_back(enemy);
            }
        }

        //save projectile
        for (auto itM = movingEntities.begin(); itM != movingEntities.end(); itM++) {
            auto& sM = *itM;

            if (sM->getID() == ID::arrow && sM->getIsActive()) {
                json projec;
                projec["position"]["x"] = sM->getPosition().x;
                projec["position"]["y"] = sM->getPosition().y;
                projec["isActive"] = sM->getIsActive();
                projec["isFacingLeft"] = static_cast<Entities::MovingEntity*>(sM)->getIsFacingLeft();
                projec["initialX"] = static_cast<Entities::Arrow*>(sM)->getInitialX();
                projec["distanceTraveled"] = static_cast<Entities::Arrow*>(sM)->getDistanceTraveled();

                j["projectiles"].push_back(projec);
            }
        }

        //open file to write

        std::ofstream file(filePath, std::ofstream::trunc);
        if (!file.is_open()) {
            cout << "Error file(save)" << endl;
        }
        file << j.dump(4);
        file.close();
    }

    void Level::loadLevel(const char* filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir o arquivo salvo: " << filePath << std::endl;
            return;
        }

        json j;
        try {
            file >> j;
        }
        catch (const std::exception& e) {
            std::cerr << "Erro ao processar JSON: " << e.what() << std::endl;
            return;
        }

        if (j.contains("Player1")) {
            pPlayer1 = static_cast<Entities::Characters::Player*>(playerFactory.FactoryMethod(Math::CoordF(0, 0), true, false, nullptr, this, ID::player));
            if (pPlayer1) {
                pPlayer1->setPosition(Math::CoordF(j["Player1"]["position"]["x"], j["Player1"]["position"]["y"]));
                pPlayer1->setIsActive(j["Player1"]["isActive"]);
                pPlayer1->setPoints(j["Player1"]["points"]);
                pPlayer1->setIsDefending(j["Player1"]["isDefending"]);
                pPlayer1->setIsHealing(j["Player1"]["isHealing"]);
                pPlayer1->setHealTimer(j["Player1"]["healTimer"]);
                pPlayer1->setHP(j["Player1"]["hp"]);
                pPlayer1->setIsDying(j["Player1"]["isDying"]);
                pPlayer1->setIsHurting(j["Player1"]["isHurting"]);
                pPlayer1->setIsAttacking(j["Player1"]["isAttacking"]);
                pPlayer1->setAttackCooldown(j["Player1"]["attackCooldown"]);
                pPlayer1->setCooldownTimer(j["Player1"]["cooldownTimer"]);
                pPlayer1->setAttackTimer(j["Player1"]["attackTimer"]);
                pPlayer1->setDeathTimer(j["Player1"]["deathTimer"]);            
                pPlayer1->setHurtingTimer(j["Player1"]["hurtingTimer"]);
                pPlayer1->setImpactTimer(j["Player1"]["impactTimer"]);
                pPlayer1->setIsFacingLeft(j["Player1"]["isFacingLeft"]);
                pPlayer1->setAttackTimer(j["Player1"]["attackTimer"]);

                movingEntities.addEntity(pPlayer1);
            }
        }

        if (isMultiplayer) {
            if (j.contains("Player2")) {
                pPlayer2 = static_cast<Entities::Characters::Player*>(playerFactory.FactoryMethod(Math::CoordF(0, 0), false, false, nullptr, this, ID::player));
                if (pPlayer2) {
                    pPlayer2->setPosition(Math::CoordF(j["Player2"]["position"]["x"], j["Player2"]["position"]["y"]));
                    pPlayer2->setIsActive(j["Player2"]["isActive"]);
                    pPlayer2->setPoints(j["Player2"]["points"]);
                    pPlayer2->setIsDefending(j["Player2"]["isDefending"]);
                    pPlayer2->setIsHealing(j["Player2"]["isHealing"]);
                    pPlayer2->setHealTimer(j["Player2"]["healTimer"]);
                    pPlayer2->setHP(j["Player2"]["hp"]);
                    pPlayer2->setIsDying(j["Player2"]["isDying"]);
                    pPlayer2->setIsHurting(j["Player2"]["isHurting"]);
                    pPlayer2->setIsAttacking(j["Player2"]["isAttacking"]);
                    pPlayer2->setAttackCooldown(j["Player2"]["attackCooldown"]);
                    pPlayer2->setCooldownTimer(j["Player2"]["cooldownTimer"]);
                    pPlayer2->setAttackTimer(j["Player2"]["attackTimer"]);
                    pPlayer2->setDeathTimer(j["Player2"]["deathTimer"]);
                    pPlayer2->setHurtingTimer(j["Player2"]["hurtingTimer"]);
                    pPlayer2->setImpactTimer(j["Player2"]["impactTimer"]);
                    pPlayer2->setIsFacingLeft(j["Player2"]["isFacingLeft"]);
                    pPlayer2->setAttackTimer(j["Player1"]["attackTimer"]);

                    movingEntities.addEntity(pPlayer2);
                }
            }
        }

        if (j.contains("obstacles")) {
            for (const auto& obstacleData : j["obstacles"]) {
                int obstacleid = obstacleData["type"];
     
                if (obstacleid == ID::bush) {
                    Entities::Obstacles::Bush* bush = static_cast<Entities::Obstacles::Bush*>(obstacleFactory.FactoryMethod(Math::CoordF(0, 0), false, false, nullptr, nullptr, ID::bush));
 
                    if (bush) {
                        bush->setPosition(Math::CoordF(obstacleData["position"]["x"], obstacleData["position"]["y"]));
                        bush->setIsActive(obstacleData["isActive"]);

                        staticEntities.addEntity(bush);
                    }
                }

                if (obstacleid == ID::fire) {
                    Entities::Obstacles::Fire* fire = static_cast<Entities::Obstacles::Fire*>(obstacleFactory.FactoryMethod(Math::CoordF(0, 0), false, false, nullptr, nullptr, ID::fire));
                    if (fire) {;
                        fire->setPosition(Math::CoordF(obstacleData["position"]["x"], obstacleData["position"]["y"]));
                        fire->setIsActive(obstacleData["isActive"]);
                        
                        staticEntities.addEntity(fire);
                    }
                }

                if (obstacleid == ID::platform) {
                    Entities::Obstacles::Platform* plat = static_cast<Entities::Obstacles::Platform*>(obstacleFactory.FactoryMethod(Math::CoordF(0, 0), false, false, nullptr, nullptr, ID::platform));

                    if (plat) {
                        plat->setPosition(Math::CoordF(obstacleData["position"]["x"], obstacleData["position"]["y"]));
                        plat->setIsActive(obstacleData["isActive"]);
                        plat->setIsFake(obstacleData["isFake"]);

                        staticEntities.addEntity(plat);
                    }
                }

                // PORTAL
            }
        }

        if (j.contains("enemies")) {
            for (const auto& enemyData : j["enemies"]) {
                int enemyid = enemyData["type"];

                if (enemyid == ID::wolf) {
                    Entities::Characters::Wolf* wolf = static_cast<Entities::Characters::Wolf*>(enemyFactory.FactoryMethod(Math::CoordF(0, 0), false, false, nullptr, nullptr, ID::wolf));     
                    if (wolf) {
                        wolf->setPosition(Math::CoordF(enemyData["position"]["x"], enemyData["position"]["y"]));
                        wolf->setIsActive(enemyData["isActive"]);
                        wolf->setIsFacingLeft(enemyData["isFacingLeft"]);
                        wolf->setIsMoving(enemyData["isMoving"]);
                        wolf->setCounted(enemyData["counted"]);
                        wolf->setHP(enemyData["hp"]);
                        wolf->setIsDying(enemyData["isDying"]);
                        wolf->setIsHurting(enemyData["isHurting"]);
                        wolf->setIsAttacking(enemyData["isAttacking"]);
                        wolf->setAttackCooldown(enemyData["attackCooldown"]);
                        wolf->setCooldownTimer(enemyData["cooldownTimer"]);
                        wolf->setAttackTimer(enemyData["attackTimer"]);
                        wolf->setDeathTimer(enemyData["deathTimer"]);
                        wolf->setHurtingTimer(enemyData["hurtingTimer"]);
                        wolf->setImpactTimer(enemyData["impactTimer"]);
                        wolf->setIsFirstAttack(enemyData["isFirstAttack"]);
                        wolf->setFirstAttackTimer(enemyData["FirstAttackTimer"]);
                        wolf->setAttackTimer(enemyData["attackTimer"]);

                        movingEntities.addEntity(wolf);
                    }
                }

                if (enemyid == ID::archer) {
                    Entities::Characters::Archer* archer = static_cast<Entities::Characters::Archer*>(enemyFactory.FactoryMethod(Math::CoordF(0, 0), false, false, &movingEntities, nullptr, ID::archer));
                    if (archer) {
                        archer->setPosition(Math::CoordF(enemyData["position"]["x"], enemyData["position"]["y"]));
                        archer->setIsActive(enemyData["isActive"]);
                        archer->setIsFacingLeft(enemyData["isFacingLeft"]);
                        archer->setIsMoving(enemyData["isMoving"]);
                        archer->setCounted(enemyData["counted"]);
                        archer->setHP(enemyData["hp"]);
                        archer->setIsDying(enemyData["isDying"]);
                        archer->setIsHurting(enemyData["isHurting"]);
                        archer->setIsAttacking(enemyData["isAttacking"]);
                        archer->setAttackCooldown(enemyData["attackCooldown"]);
                        archer->setCooldownTimer(enemyData["cooldownTimer"]);
                        archer->setAttackTimer(enemyData["attackTimer"]);
                        archer->setDeathTimer(enemyData["deathTimer"]);
                        archer->setHurtingTimer(enemyData["hurtingTimer"]);
                        archer->setImpactTimer(enemyData["impactTimer"]);
                        archer->setArrowDelayTimer(enemyData["arrowDelayTimer"]);
                        archer->setMovingDelayTimer(enemyData["movingDelayTimer"]);
                        archer->setAttackTimer(enemyData["attackTimer"]);

                        movingEntities.addEntity(archer);
                    }
                }

                if (enemyid == ID::demonsamurai) {
                    Entities::Characters::DemonSamurai* demonsamurai = static_cast<Entities::Characters::DemonSamurai*>(enemyFactory.FactoryMethod(Math::CoordF(0, 0), false, false, nullptr, nullptr, ID::demonsamurai));
                    if (demonsamurai) {
                        demonsamurai->setPosition(Math::CoordF(enemyData["position"]["x"], enemyData["position"]["y"]));
                        demonsamurai->setIsActive(enemyData["isActive"]);
                        demonsamurai->setIsFacingLeft(enemyData["isFacingLeft"]);
                        demonsamurai->setIsMoving(enemyData["isMoving"]);
                        demonsamurai->setCounted(enemyData["counted"]);
                        demonsamurai->setHP(enemyData["hp"]);
                        demonsamurai->setIsDying(enemyData["isDying"]);
                        demonsamurai->setIsHurting(enemyData["isHurting"]);
                        demonsamurai->setIsAttacking(enemyData["isAttacking"]);
                        demonsamurai->setAttackCooldown(enemyData["attackCooldown"]);
                        demonsamurai->setCooldownTimer(enemyData["cooldownTimer"]);
                        demonsamurai->setAttackTimer(enemyData["attackTimer"]);
                        demonsamurai->setDeathTimer(enemyData["deathTimer"]);
                        demonsamurai->setHurtingTimer(enemyData["hurtingTimer"]);
                        demonsamurai->setImpactTimer(enemyData["impactTimer"]);
                        demonsamurai->setCont(enemyData["cont"]);
                        demonsamurai->setIsLastBuffed(enemyData["isLastBuffed"]);
                        demonsamurai->setShoutTimer(enemyData["shoutTimer"]);
                        demonsamurai->setIsShouting(enemyData["isShouting"]);
                        demonsamurai->setAttackTimer(enemyData["attackTimer"]);

                        movingEntities.addEntity(demonsamurai);
                    }
                }
            }
        }
        
        if (j.contains("projectiles")) {
            for (const auto& projectileData : j["projectiles"]) {
                
                if (projectileData.is_null()) {
                    continue; 
                }

                Entities::Arrow* arrow = static_cast<Entities::Arrow*>(arrowFactory.FactoryMethod(Math::CoordF(projectileData["position"]["x"], projectileData["position"]["y"]), false, false, nullptr, nullptr, ID::arrow));
                
                if (arrow) {
                    //arrow->setPosition(Math::CoordF(projectileData["position"]["x"], projectileData["position"]["y"]));
                    arrow->setIsActive(projectileData["isActive"]);
                    arrow->setIsFacingLeft(projectileData["isFacingLeft"]);
                    arrow->setInitialX(projectileData["initialX"]);
                    arrow->setDistanceTraveled(projectileData["distanceTraveled"]);

                    movingEntities.addEntity(arrow);
                }
            }
        }

        for (auto itM = (&movingEntities)->begin(); itM != (&movingEntities)->end(); ++itM) {
            if (*itM) {
                if ((*itM)->getID() == ID::wolf || (*itM)->getID() == ID::archer || (*itM)->getID() == ID::demonsamurai) {
                    if (auto* enemy = dynamic_cast<Entities::Characters::Enemy*>(*itM)) {
                        enemy->setPlayers(pPlayer1, pPlayer2);
                    }
                }

            }
        }
    }

    const int Level::getScorePoints() const {
        return pPlayer1->getScorePoints();
    }

}