#include "ConcreteMenu.h"
#include "MenuController.h"

namespace Menu {

	ConcreteMenu::ConcreteMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id, Levels::Level* pLevel) : pLevel(pLevel),
		Menu(buttonSize, info, fontSize, id) {

		body->setSize(sf::Vector2f(1920.0f, 1080.0f));

		setAnimation();
		buildMenu();
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

	void ConcreteMenu::buildMenu() {
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

		if (stateID != Managers::States::State_ID::leaderboard_menu) {
			initializeIterator();
		}
	}

	void ConcreteMenu::setAnimation() {
		menuAnimation = new GraphicalElements::Animation(body, Math::CoordF(1, 1));

		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::menubg, "menubg.png", 4);
		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::pausebg, "pausebg.png", 4);
		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::gameoverbg, "gameoverbg.png", 4);
		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::winbg, "winbg.png", 4);
		menuAnimation->addNewAnimation(GraphicalElements::Animation_ID::leaderboardbg, "leaderboardbg.png", 4);

		body->setOrigin(0, 0);
	}

	void ConcreteMenu::execute(float dt) {
		pGraphic->centerView(Math::CoordF(windowSize.x / 2.0f, windowSize.y / 2.0f));
		menuController->setIsActive(true);
		dt = pGraphic->getDeltaTime();
		updateAnimation(dt);
		render();

		if (stateID == Managers::States::State_ID::leaderboard_menu) {
			buildLeaderboard();
		}
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

		else if (stateID == Managers::States::State_ID::leaderboard_menu) {
			body->setSize(sf::Vector2f(1920.0f, 1080.0f));
			menuAnimation->update(GraphicalElements::Animation_ID::leaderboardbg, false, (0, 0), dt);
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

		if (stateID == Managers::States::State_ID::win_menu || stateID == Managers::States::State_ID::gameover_menu) {
			sf::Font font;
			if (!font.loadFromFile("alagard.ttf")) {
				std::cerr << "Erro ao carregar a fonte." << std::endl;
				return;
			}
			/*
			sf::Text nameText;
			nameText.setString("Nome: " + playerName + "_"); // O "_" indica onde o cursor está*/

			float centerX = windowSize.x / 2.0f;
			float startY = 340.0f;

			std::string nameText = playerName + "|";
			Text playerText(nameText, font, 50);

			playerText.setTextPos(Math::CoordF(centerX - playerText.getTextSize().x / 2.0f, startY));
			playerText.setTextColor(sf::Color::White);

			sf::Text shadow = playerText.getText();
			shadow.setFillColor(sf::Color(255, 255, 255, 100));
			shadow.move(3.f, 3.f);
			pGraphic->render(shadow);

			pGraphic->render(playerText.getText());
		}
	}

	const int ConcreteMenu::getScore() const {
		return pLevel->getScorePoints();
	}

	void ConcreteMenu::buildLeaderboard() {
		std::ifstream file("leaderboard.json");
		if (!file.is_open()) {
			std::cerr << "Erro ao abrir o arquivo de leaderboard: " << std::endl;
			return;
		}

		json tmjData;

		try {
			file >> tmjData;
		}
		catch (const std::exception& e) {
			std::cerr << "Erro ao processar JSON: " << e.what() << std::endl;
			return;
		}
		file.close();

		std::vector<std::pair<std::string, int>> scores;
		if (tmjData.is_array()) {
			for (const auto& item : tmjData) {
				std::string name = item.value("name", "");
				int score = item.value("score", 0);
				scores.push_back(std::make_pair(name, score));
			}
		}

		std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
		});

		if (scores.size() > 7) {
			scores.resize(7);
		}

		// Atualiza o JSON apenas se for necessário
		json newJson = json::array();
		for (const auto& s : scores) {
			newJson.push_back({ {"name", s.first}, {"score", s.second} });
		}

		std::ofstream outFile("leaderboard.json");
		if (outFile.is_open()) {
			outFile << newJson.dump(4); // Salva o JSON formatado
			outFile.close();
		}

		renderLeaderboardText(scores);
	}

	void ConcreteMenu::renderLeaderboardText(const std::vector<std::pair<std::string, int>>& scores) {
		sf::Font font;
		if (!font.loadFromFile("alagard.ttf")) {
			std::cerr << "Erro ao carregar a fonte." << std::endl;
			return;
		}

		float centerX = windowSize.x / 2.0f;
		float startY = 535.0f;
		float lineSpacing = 50.0f;
		float maxWidth = 600.0f; // Largura máxima da linha

		for (size_t i = 0; i < scores.size(); i++) {
			std::string name = scores[i].first;
			std::string scoreStr = std::to_string(scores[i].second);

			// Criar textos separados
			Text nameText(name, font, 37);
			Text scoreText(scoreStr, font, 37);

			// Obter tamanhos reais dos textos
			Math::CoordF nameSize = nameText.getTextSize();
			Math::CoordF scoreSize = scoreText.getTextSize();

			// Calcular espaço restante para os pontos
			float dotsWidth = maxWidth - (nameSize.x + scoreSize.x);
			int numDots = dotsWidth / 10.0f; // Aproximando 10px por ponto

			std::string dots(numDots, '.');

			// Criar string final
			std::string formattedText = name + dots + scoreStr;

			// Criar o texto para renderização
			Text leaderboardText(formattedText, font, 37);

			Math::CoordF textSize = leaderboardText.getTextSize();
			leaderboardText.setTextPos(Math::CoordF(centerX - textSize.x / 2.0f, startY + i * lineSpacing));
			leaderboardText.setTextColor(sf::Color(45, 37, 17));

			sf::Text shadow = leaderboardText.getText();
			shadow.setFillColor(sf::Color(171, 143, 73, 220));
			shadow.move(2.f, 2.f);
			pGraphic->render(shadow);

			pGraphic->render(leaderboardText.getText());
		}
	}

}