#pragma once
#include "PauseMenu.h"
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

		~Level();

		void createMap(const char* filePath);

		List::EntitiesList* getEntitiesList();

		void setPlayerPoints(int points);

		virtual void updateCamera() = 0;

		virtual void render() = 0;

		virtual void execute(float dt) = 0;
	};

}