#pragma once
#include "Coord.h"

// Código baseado no repositório "NightZ" de Pedro Ribeiro de Almeida e Matheus José Pereira
// Repositório: https://github.com/pedroribe1r0/NightZ
// Licença: MIT
// 
// Conforme a licença MIT, este código pode ser usado, modificado e distribuído,
// desde que a atribuição aos autores originais seja mantida.

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
		
		void render(sf::Text text);

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

		sf::Font loadFont(const char* fontPath);

		sf::Vector2f getCameraPosition() const;
	};

}