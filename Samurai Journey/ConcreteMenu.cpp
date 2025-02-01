#include "ConcreteMenu.h"
#include "MenuController.h"

namespace Menu {

	ConcreteMenu::ConcreteMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id) :
		Menu(buttonSize, info, fontSize, id) {

		body->setSize(sf::Vector2f(1920.0f, 1080.0f));

		setAnimation();
		createButtons();
	}

	ConcreteMenu::~ConcreteMenu() {
		if (menuAnimation) {
			delete menuAnimation;
			menuAnimation = nullptr;
		}

		if (body) {
			delete body;
			body = nullptr;
		}
	}

	void ConcreteMenu::createButtons() {
		float centerX = windowSize.x / 2.0f;  
		float startY = windowSize.y / 2.0f - ((textButtonList.size() * buttonSize.y) / 2.0f) - 180.0f; 
		float spacing = 100.0f;
		
		/* Main Menu Buttons */
		if (stateID == Managers::States::State_ID::main_menu) {
			addButton("New Game", Math::CoordF(centerX - buttonSize.x / 2.0f, startY), sf::Color(31, 28, 43), Buttons::Button_ID::newgame);
			addButton("Load Game", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing), sf::Color(31, 28, 43), Buttons::Button_ID::loadgame);
			addButton("Leaderboard", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 2*spacing), sf::Color(31, 28, 43), Buttons::Button_ID::leaderboard);
			addButton("Exit", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 3*spacing), sf::Color(31, 28, 43), Buttons::Button_ID::exit);
		}

		/* New Game Menu Buttons */
		else if (stateID == Managers::States::State_ID::newgame_menu) {
			addButton("Singleplayer", Math::CoordF(centerX - buttonSize.x / 2.0f, startY), sf::Color(31, 28, 43), Buttons::Button_ID::singleplayer);
			addButton("Multiplayer", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing), sf::Color(31, 28, 43), Buttons::Button_ID::multiplayer);
		}

		/* Singleplayer Menu Buttons */
		else if (stateID == Managers::States::State_ID::singleplayer_menu) {
			addButton("Archer Level", Math::CoordF(centerX - buttonSize.x / 2.0f, startY), sf::Color(31, 28, 43), Buttons::Button_ID::archersingle);
			addButton("Boss Level", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing), sf::Color(31, 28, 43), Buttons::Button_ID::bosssingle);
		}

		/* Multiplayer Menu Buttons */
		else if (stateID == Managers::States::State_ID::multiplayer_menu) {
			addButton("Archer Level", Math::CoordF(centerX - buttonSize.x / 2.0f, startY), sf::Color(31, 28, 43), Buttons::Button_ID::archermulti);
			addButton("Boss Level", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing), sf::Color(31, 28, 43), Buttons::Button_ID::bossmulti);
		}

		/* Pause Menu Buttons */
		else if (stateID == Managers::States::State_ID::pause_menu) {
			addButton("Resume Game", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 90.0f), sf::Color(255, 255, 255), Buttons::Button_ID::resumegame);
			addButton("Save Progress", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing + 90.0f), sf::Color(255, 255, 255), Buttons::Button_ID::saveprogress);
			addButton("Exit", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 2 * spacing + 90.0f), sf::Color(255, 255, 255), Buttons::Button_ID::pauseexit);
		}

		/* Game Over Menu Buttons */
		else if (stateID == Managers::States::State_ID::gameover_menu) {
			addButton("Save Score", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 90.0f), sf::Color(255, 255, 255), Buttons::Button_ID::savescore);
			addButton("Exit", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing + 90.0f), sf::Color(255, 255, 255), Buttons::Button_ID::pauseexit);
		}

		/* Win Over Menu Buttons */
		else if (stateID == Managers::States::State_ID::win_menu) {
			addButton("Save Score", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + 90.0f), sf::Color(255, 255, 255), Buttons::Button_ID::savescore);
			addButton("Exit", Math::CoordF(centerX - buttonSize.x / 2.0f, startY + spacing + 90.0f), sf::Color(255, 255, 255), Buttons::Button_ID::pauseexit);
		}

		initializeIterator();
	}

	void ConcreteMenu::setAnimation() {
		menuAnimation = new GraphicalElements::Animation(body, Math::CoordF(1, 1));

		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::menubg, "menubg.png", 4);
		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::pausebg, "pausebg.png", 4);
		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::gameoverbg, "gameoverbg.png", 4);
		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::winbg, "winbg.png", 4);

		body->setOrigin(0, 0);
	}

	void ConcreteMenu::execute(float dt) {
		pGraphic->centerView(Math::CoordF(windowSize.x / 2.0f, windowSize.y / 2.0f));
		menuController->setIsActive(true);
		dt = pGraphic->getDeltaTime();
		updateAnimation(dt);
		render();
	}

	void ConcreteMenu::updateAnimation(float dt) {
		if (stateID == Managers::States::State_ID::pause_menu) {
			body->setSize(sf::Vector2f(1920.0f, 1080.0f));
			menuAnimation->update(GraphicalElements::Animation_ID::pausebg, false, (0, 0), dt);
		}

		else if (stateID == Managers::States::State_ID::gameover_menu) {
			body->setSize(sf::Vector2f(1920.0f, 1080.0f));
			menuAnimation->update(GraphicalElements::Animation_ID::gameoverbg, false, (0, 0), dt);
		}

		else if (stateID == Managers::States::State_ID::win_menu) {
			body->setSize(sf::Vector2f(1920.0f, 1080.0f));
			menuAnimation->update(GraphicalElements::Animation_ID::winbg, false, (0, 0), dt);
		}

		else {
			body->setSize(sf::Vector2f(1920.0f, 1080.0f));
			menuAnimation->update(GraphicalElements::Animation_ID::menubg, false, (0,0), dt);
		}
	}

	void ConcreteMenu::render() {
		pGraphic->render(body);
		std::list<Buttons::TextButton*>::iterator aux;
		for (aux = textButtonList.begin(); aux != textButtonList.end(); aux++) {
			Buttons::TextButton* button = *aux;
			button->render();
			button = nullptr;
		}
	}
}