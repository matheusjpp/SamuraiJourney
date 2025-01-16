#pragma once
#include "Coord.h"

namespace Managers {

	#define SCREEN_WIDTH 1920.0f
	#define SCREEN_HEIGHT 1080.0f

	class GraphicManager {
	private:
		sf::RenderWindow* window;
		sf::View camera;
		unordered_map<std::string, sf::Texture*> textures;
		sf::Clock clock;
		static float dt;

		// Singleton
		static Managers::GraphicManager* pGraphic;
		GraphicManager();

	public:
		~GraphicManager();

		static GraphicManager* getInstance();

		void render(sf::RectangleShape* body);

		void display();

		void clear();

		bool isWindowOpen() const;

		void closeWindow();

		Math::CoordUI getWindowSize() const;

		void centerView(Math::CoordF pos);

		sf::Vector2f getCenterView() const;

		sf::Texture* loadTexture(const char* path);

		void updateDeltaTime();

		float getDeltaTime() const;

		bool pollEvent(sf::Event &e);
	};

}