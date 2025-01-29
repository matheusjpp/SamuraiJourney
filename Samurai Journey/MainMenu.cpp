#include "MainMenu.h"

namespace Menu {

	MainMenu::MainMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id) :
		Menu(buttonSize, info, fontSize) , Managers::States::State(id) {

		body = new sf::RectangleShape();
		body->setSize(sf::Vector2f(1920.0f, 1080.0f));

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
		float centerX = windowSize.x / 2.0f;  
		float startY = windowSize.y / 2.0f - ((textButtonList.size() * buttonSize.y) / 2.0f) - 180.0f; 
		float spacing = 100.0f;
		
		addButton("New Game", Math::CoordF(centerX - buttonSize.x / 2.0f, startY), Buttons::Button_ID::newgame);
		addButton("Load Game", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing), Buttons::Button_ID::loadgame);
		addButton("Leaderboard", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 2*spacing), Buttons::Button_ID::leaderboard);
		addButton("Exit", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 3*spacing), Buttons::Button_ID::exit);

		initializeIterator();
	}

	void MainMenu::setAnimation() {
		menuAnimation = new GraphicalElements::Animation(body, Math::CoordF(1, 1));

		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::menubg, "menubg.png", 4);
		body->setOrigin(0, 0);
	}

	void MainMenu::execute(float dt) {
		dt = pGraphic->getDeltaTime();
		updateAnimation(dt);
		render();
	}

	void MainMenu::updateAnimation(float dt) {
		menuAnimation->update(GraphicalElements::Animation_ID::menubg, false, (0,0), dt);
	}

	void MainMenu::render() {
		pGraphic->render(body);
		//pGraphic->render(title.getText());
		std::list<Buttons::TextButton*>::iterator aux;
		for (aux = textButtonList.begin(); aux != textButtonList.end(); aux++) {
			Buttons::TextButton* button = *aux;
			button->render();
			button = nullptr;
		}
	}
}