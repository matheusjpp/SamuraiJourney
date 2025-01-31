#include "GraphicManager.h"

namespace Managers {

	GraphicManager* GraphicManager::pGraphic = nullptr;
	float GraphicManager::dt = 0;

	GraphicManager::GraphicManager() : camera(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)) {
		window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Samurai Journey");
		window->setView(camera);
		clock.restart();
		dt = clock.getElapsedTime().asSeconds();
	}

	GraphicManager::~GraphicManager() {
		for (auto& pair : textures) {
			delete pair.second;
		}
		if (window)
			delete window;
	}

	GraphicManager* GraphicManager::getInstance() {
		if (pGraphic == nullptr) {
			pGraphic = new GraphicManager();
		}
		return pGraphic;
	}

	void GraphicManager::render(sf::RectangleShape* body) {
		window->draw(*body);
	}

	void GraphicManager::render(sf::Text text) {
		window->draw(text);
	}

	void GraphicManager::display() {
		if (isWindowOpen()) {
			window->display();
		}
	}

	void GraphicManager::clear() {
		if (isWindowOpen()) {
			window->clear();
		}
	}

	bool GraphicManager::isWindowOpen() const {
		return (window->isOpen());
	}

	void GraphicManager::closeWindow() {
		window->close();
	}

	Math::CoordUI GraphicManager::getWindowSize() const {
		sf::Vector2u size = window->getSize();
		return Math::CoordUI(size.x, size.y);
	}

	void GraphicManager::centerView(Math::CoordF pos) {
		camera.setCenter(sf::Vector2f(pos.x, pos.y));
		window->setView(camera);
	}

	sf::Vector2f GraphicManager::getCenterView() const {
		return camera.getCenter();
	}

	sf::Texture* GraphicManager::loadTexture(const char* path) {
		if (textures.count(path) > 0)
			return textures[path];

		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(path)) {
			std::cout << "Managers::GraphicManager::ERROR: TEXTURE NOT FOUND" << std::endl;
			return nullptr;
		}
		textures.emplace(path, texture);
		return texture;
	}

	void GraphicManager::updateDeltaTime() {
		dt = clock.getElapsedTime().asSeconds();
		clock.restart();
	}

	float GraphicManager::getDeltaTime() const {
		return dt;
	}

	bool GraphicManager::pollEvent(sf::Event &e) {
		return window->pollEvent(e);
	}

	sf::Font GraphicManager::loadFont(const char* fontPath) {
		sf::Font font;
		if (!font.loadFromFile(fontPath)) {
			std::cout << "ERROR:Managers::GraphicManager:: not possible to find font path" << std::endl;
		}
		return font;
	}

	sf::Vector2f GraphicManager::getCameraPosition() const {
		return window->getView().getCenter();
	}
}