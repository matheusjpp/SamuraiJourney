#include "Menu.h"
#include "MenuController.h"

namespace Menu {

	//Managers::GraphicManager* Menu::pGraphic = Managers::GraphicManager::getInstance();

	Menu::Menu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id) :
		textButtonList(), it(), buttonSize(buttonSize),
		windowSize(sf::Vector2f(pGraphic->getWindowSize().x, pGraphic->getWindowSize().y)),
		title(info, pGraphic->loadFont("alagard.ttf"), fontSize),
		Ente(), Managers::States::State(id)
	{
		menuController = new Managers::KeyManagement::MenuController(this);
		//menuController->setIsActive(true);
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

	void Menu::addButton(const std::string& info, Math::CoordF pos, sf::Color selectedColor, Buttons::Button_ID id) {
		float fontSize = 60.0f; // Constante mal feita que deveria ser um atributo do menu (tanto que é passada na construtora) , mas como todos terão o mesmo tamaho, vou deixar assim
		Buttons::TextButton* button = new Buttons::TextButton(info, pos, buttonSize, fontSize, id);
		button->setSelectedColor(selectedColor);
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

	void Menu::saveScore(const char* playerName, int score) {
		json j;
		
		std::ifstream inFile("leaderboard.json");
		if (inFile.is_open()) {
			try {
				inFile >> j;
			}
			catch (const std::exception& e) {
				std::cerr << "Erro ao ler JSON: " << e.what() << std::endl;
			}
			inFile.close();
		}

		json newEntry;
		
		newEntry["name"] = playerName;
		newEntry["score"] = score;

		if (!j.is_array()) {
			j = json::array();
		}
		j.push_back(newEntry);
	
		std::ofstream outFile("leaderboard.json");
		if (outFile.is_open()) {
			outFile << j.dump(4); // formata com indentação de 4 espaços
			outFile.close();
		}
		else {
			std::cerr << "Erro ao abrir o arquivo para escrita!" << std::endl;
		}
	}

	void Menu::setPlayerName(const std::string& name) {
		playerName = name;
	}

	const char* Menu::getPlayerName() const {
		return playerName.c_str();
	}

	void Menu::appendCharacter(char c) {
		if (playerName.size() < 12) // Limite de caracteres
			playerName += c;
	}

	void Menu::removeLastCharacter() {
		if (!playerName.empty())
			playerName.pop_back();
	}

	void Menu::resetLeaderboard() {
		std::ofstream outFile("leaderboard.json", std::ios::trunc);
		if (outFile.is_open()) {
			outFile << "[]";
			outFile.close();
			std::cout << "Leaderboard resetado com sucesso!" << std::endl;
		}
		else {
			std::cerr << "Erro ao resetar o leaderboard." << std::endl;
		}
	}
}