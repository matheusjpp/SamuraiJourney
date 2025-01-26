#include "Menu.h"

namespace Menu {

	Managers::GraphicManager* Menu::pGraphic = Managers::GraphicManager::getInstance();

	Menu::Menu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Menu_ID id) :
		textButtonList(), it(), buttonSize(buttonSize),
		windowSize(sf::Vector2f(pGraphic->getWindowSize().x, pGraphic->getWindowSize().y)),
		title(info, pGraphic->loadFont("alagard.ttf"), fontSize) 
	{
		
	}

	Menu::~Menu() {
		if (!textButtonList.empty()) {
			for (it = textButtonList.begin(); it != textButtonList.end(); it++) {
				delete(*it);
				*it = nullptr;
			}
			textButtonList.clear();
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

	void Menu::addButton(const std::string& info, Math::CoordF pos, const sf::Color selectedColor, Buttons::Button_ID id) {
		Buttons::TextButton* button = new Buttons::TextButton(info, pos, buttonSize, id);
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