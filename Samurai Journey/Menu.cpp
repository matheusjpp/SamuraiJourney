#include "Menu.h"
#include "MenuController.h"

namespace Menu {

	Managers::GraphicManager* Menu::pGraphic = Managers::GraphicManager::getInstance();

	Menu::Menu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize) :
		textButtonList(), it(), buttonSize(buttonSize),
		windowSize(sf::Vector2f(pGraphic->getWindowSize().x, pGraphic->getWindowSize().y)),
		title(info, pGraphic->loadFont("alagard.ttf"), fontSize) 
	{
		menuController = new Managers::KeyManagement::MenuController(this);
		{
			if (menuController == nullptr) {
				std::cout << "ERROR::Menu::MainMenu:: not possible to create observer to main menu" << std::endl;
				exit(1);
			}
		}
	}

	Menu::~Menu() {
		if (!textButtonList.empty()) {
			for (it = textButtonList.begin(); it != textButtonList.end(); it++) {
				delete(*it);
				*it = nullptr;
			}
			textButtonList.clear();
		}

		if (menuController) {
			menuController->setIsActive(false);
		}
	}

	void Menu::initializeIterator() {
		try {
			it = textButtonList.begin();
			(*it)->setSelected(true);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			exit(1);
		}
	}

	void Menu::addButton(const std::string& info, Math::CoordF pos, Buttons::Button_ID id) {
		float fontSize = 60.0f; // Constante mal feita que deveria ser um atributo do menu (tanto que é passada na construtora) , mas como todos terão o mesmo tamaho, vou deixar assim
		Buttons::TextButton* button = new Buttons::TextButton(info, pos, buttonSize, fontSize, id);
		if (button == nullptr) {
			std::cout << "ERROR::Menu:: not possible to create button" << std::endl;
			exit(1);
		}
		textButtonList.push_back(button);
	}

	void Menu::selectAbove() {
		if (textButtonList.empty())
			return;

		Buttons::TextButton* button = *it;
		button->setSelected(false);
		if (it == textButtonList.begin()) {
			it = textButtonList.end();
		}
		it--;
		button = *it;
		button->setSelected(true);
	}

	void Menu::selectBelow() {
		if (textButtonList.empty())
			return;

		Buttons::TextButton* button = *it;
		button->setSelected(false);
		it++;
		if (it == textButtonList.end()) {
			it = textButtonList.begin();
		}
		button = *it;
		button->setSelected(true);
	}

	const Buttons::Button_ID Menu::getSelectedButtonID() const {
		return (*it)->getButtonID();
	}

}