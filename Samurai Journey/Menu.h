#pragma once
#include "TextButton.h"

namespace Managers {
	namespace KeyManagement {
		class MenuController;
	}
}

namespace Menu {

	class Menu : public Ente, public Managers::States::State {
	protected:
		Managers::KeyManagement::MenuController* menuController;
		std::list<Buttons::TextButton*> textButtonList;
		std::list<Buttons::TextButton*>::iterator it;

		Math::CoordF buttonSize;
		sf::Vector2f windowSize;

		Text title;
		std::string playerName;

		//virtual void buildMenu() = 0;
		void initializeIterator();

	public:
		Menu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id = Managers::States::State_ID::empty);
		
		virtual ~Menu();

		void addButton(const std::string& info, Math::CoordF pos, sf::Color selectedColor, Buttons::Button_ID id);
		
		void selectAbove();

		void selectBelow();
		
		const Buttons::Button_ID getSelectedButtonID() const;

		void saveScore(const char* playerName, int score);

		void setPlayerName(const std::string& name);

		const char* getPlayerName() const;

		void appendCharacter(char c);

		void removeLastCharacter();

		void resetLeaderboard();

		virtual const int getScore() const = 0;

		virtual void render() = 0;
	};

}