#include "Level.h"

namespace Levels {

	Level::Level() {

	}

	Level::~Level() {

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

                switch (value) {
                case 0:

                    break;

                case 1:
                    int posx = 10 * x;
                    int posy = 10 * y;
                    Entities::Obstacles::Platform* tmp = new Entities::Obstacles::Platform(Math::CoordF(posx/*-5*/, posy), Math::CoordF(10.0f, 10.0f), false);
                    if (tmp) {
                        staticEntities.addEntity(tmp);
                    }
                    break;
                }
            }
        }
	}

	List::EntitiesList& Level::getList() {
		return staticEntities;
	}

}