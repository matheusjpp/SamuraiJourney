#pragma once
#include "Coord.h"

// C�digo baseado no reposit�rio "NightZ" de Pedro Ribeiro de Almeida e Matheus Jos� Pereira
// Reposit�rio: https://github.com/pedroribe1r0/NightZ
// Licen�a: MIT
// 
// Conforme a licen�a MIT, este c�digo pode ser usado, modificado e distribu�do,
// desde que a atribui��o aos autores originais seja mantida.

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