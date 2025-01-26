#pragma once
#include "Menu.h"

namespace Menu {

	class MainMenu : public Menu {
	private:
		sf::RectangleShape* body;
		GraphicalElements::Animation* menuAnimation;

	public:
		MainMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Menu_ID id);

		~MainMenu();

		void createButtons();

		void setAnimation();

		void execute();

		void updateAnimation(float dt);

		void render();
	};

}