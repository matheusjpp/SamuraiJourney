#include "PauseMenu.h"
#include "MenuController.h"

namespace Menu {

	PauseMenu::PauseMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id) :
		Menu(buttonSize, info, fontSize), Managers::States::State(id) {

		body = new sf::RectangleShape();
		body->setSize(sf::Vector2f(1920.0f, 1080.0f));

		setAnimation();
		createButtons();
	}

	PauseMenu::~PauseMenu() {
		if (pauseAnimation) {
			delete pauseAnimation;
			pauseAnimation = nullptr;
		}

		if (body) {
			delete body;
			body = nullptr;
		}
	}

	void PauseMenu::createButtons() {
		float centerX = windowSize.x / 2.0f;
		float startY = windowSize.y / 2.0f - ((textButtonList.size() * buttonSize.y) / 2.0f) - 90.0f;
		float spacing = 100.0f;

		addButton("Resume Game", Math::CoordF(centerX - buttonSize.x / 2.0f, startY), sf::Color(255, 255, 255), Buttons::Button_ID::resumegame);
		addButton("Save Progress", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing), sf::Color(255, 255, 255), Buttons::Button_ID::saveprogress);
		addButton("Exit", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 2 * spacing), sf::Color(255, 255, 255), Buttons::Button_ID::pauseexit);
		
		initializeIterator();
	}

	void PauseMenu::setAnimation() {
		pauseAnimation = new GraphicalElements::Animation(body, Math::CoordF(1, 1));

		pauseAnimation->addNewAnimation(GraphicalElements::Animation_ID::menubg, "pausebg.png", 4);
		body->setOrigin(0, 0);
	}

	void PauseMenu::execute(float dt) {
		pGraphic->centerView(Math::CoordF(windowSize.x / 2.0f, windowSize.y / 2.0f));
		menuController->setIsActive(true);
		dt = pGraphic->getDeltaTime();
		updateAnimation(dt);
		render();
	}

	void PauseMenu::updateAnimation(float dt) {
		pauseAnimation->update(GraphicalElements::Animation_ID::menubg, false, (0, 0), dt);
	}

	void PauseMenu::render() {
		pGraphic->render(body);
		std::list<Buttons::TextButton*>::iterator aux;
		for (aux = textButtonList.begin(); aux != textButtonList.end(); aux++) {
			Buttons::TextButton* button = *aux;
			button->render();
			button = nullptr;
		}
	}
}