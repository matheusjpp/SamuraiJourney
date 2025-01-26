#include "MainMenu.h"

namespace Menu {

	MainMenu::MainMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Menu_ID id) :
		Menu(buttonSize, info, fontSize, id) {

		body = new sf::RectangleShape();
		body->setSize(sf::Vector2f(1920.0f, 1080.0f));
		
		title.setTextPos(Math::CoordF(windowSize.x / 2.0f - title.getTextSize().x / 2.0f + 200.0f, 220.0f));
		title.setTextColor(sf::Color(92, 116, 191));
		title.setFontSize(170);
		title.setBorderSize(4);

		setAnimation();
		createButtons();
	}

	MainMenu::~MainMenu() {
		if (menuAnimation) {
			delete menuAnimation;
			menuAnimation = nullptr;
		}

		if (body) {
			delete body;
			body = nullptr;
		}
	}

	void MainMenu::createButtons() {
		addButton("New Game", Math::CoordF(windowSize.x / 2.0f, 900), sf::Color(255, 255, 255), Buttons::Button_ID::newgame);
		addButton("New Game", Math::CoordF(windowSize.x / 2.0f, 1050), sf::Color(255, 255, 255), Buttons::Button_ID::newgame);
		addButton("New Game", Math::CoordF(windowSize.x / 2.0f, 1200), sf::Color(255, 255, 255), Buttons::Button_ID::newgame);
		addButton("New Game", Math::CoordF(windowSize.x / 2.0f, 1350), sf::Color(255, 255, 255), Buttons::Button_ID::newgame);
		initializeIterator();
	}

	void MainMenu::setAnimation() {
		menuAnimation = new GraphicalElements::Animation(body, Math::CoordF(1, 1));

		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::menubg, "menubg2.png", 4);
		body->setOrigin(0, 0);
	}

	void MainMenu::execute() {
		updateAnimation(pGraphic->getDeltaTime());
		render();
	}

	void MainMenu::updateAnimation(float dt) {
		menuAnimation->update(GraphicalElements::Animation_ID::menubg, false, (0,0), dt);
	}

	void MainMenu::render() {
		pGraphic->render(body);
		pGraphic->render(title.getText());
		for (auto button : textButtonList) {
			button->render();
		}
	}
}