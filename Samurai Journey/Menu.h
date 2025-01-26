#pragma once
#include "TextButton.h"

namespace Menu {

	enum Menu_ID {
		empty,
		main,
		pause
	};

	class Menu	{
	protected:
		static Managers::GraphicManager* pGraphic;

		std::list<Buttons::TextButton*> textButtonList;
		std::list<Buttons::TextButton*>::iterator it;

		Math::CoordF buttonSize;
		sf::Vector2f windowSize;

		Text title;

		virtual void createButtons() = 0;
		void initializeIterator();

	public:
		Menu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Menu_ID id);
		
		virtual ~Menu();

		void addButton(const std::string& info, Math::CoordF pos, const sf::Color selectedColor, Buttons::Button_ID id);
		
		void selectAbove();

		void selectBelow();

		const Buttons::Button_ID getSelectedButtonID() const;

		virtual void render() = 0;
	};

}