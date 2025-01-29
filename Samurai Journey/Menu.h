#pragma once
#include "TextButton.h"

namespace Managers {
	namespace KeyManagement {
		class MenuController;
	}
}

namespace Menu {

	class Menu	{
	protected:
		static Managers::GraphicManager* pGraphic;
		Managers::KeyManagement::MenuController* menuController;
		std::list<Buttons::TextButton*> textButtonList;
		std::list<Buttons::TextButton*>::iterator it;

		Math::CoordF buttonSize;
		sf::Vector2f windowSize;

		Text title;

		virtual void createButtons() = 0;
		void initializeIterator();

	public:
		Menu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize);
		
		virtual ~Menu();

		void addButton(const std::string& info, Math::CoordF pos, Buttons::Button_ID id);
		
		void selectAbove();

		void selectBelow();

		const Buttons::Button_ID getSelectedButtonID() const;

		virtual void render() = 0;
	};

}