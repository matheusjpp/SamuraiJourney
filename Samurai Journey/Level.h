#pragma once
#include "ConcreteMenu.h"
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Levels {

	class Level : public Managers::States::State {
	protected:
		static Managers::GraphicManager* pGraphic;

		sf::RectangleShape* mapImage;
		GraphicalElements::Animation* mapSprite;
		GraphicalElements::Parallax::Background background;

		Managers::Collisions::CollisionManager* pCollision;
		List::EntitiesList movingEntities;
		List::EntitiesList staticEntities;

		Entities::Characters::Player* pPlayer1;
		Entities::Characters::Player* pPlayer2;
		bool isMultiplayer;

		Menu::Text* p1life;
		Menu::Text* p2life;

	public:
		Level(bool isMultiplayer = false, Managers::States::State_ID id = Managers::States::State_ID::empty);

		virtual ~Level();

		void createMap(const char* filePath);

		List::EntitiesList* getEntitiesList();

		void setPlayerPoints(int points);

		void updateCamera(float cameraLimit);

		void render();

		virtual void saveLevel(const char* filePath);

		virtual void verifyLevelEnd() = 0;

		virtual void execute(float dt) = 0;
	};

}