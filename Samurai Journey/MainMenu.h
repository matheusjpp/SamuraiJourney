#pragma once
#include "Menu.h"

namespace Managers {
	namespace KeyManagement {
		class MenuController;
	}
}

namespace Menu {

	class MainMenu : public Menu, public Managers::States::State {
	private:
		sf::RectangleShape* body;
		GraphicalElements::Animation* menuAnimation;

	public:
		MainMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id = Managers::States::State_ID::empty);

		~MainMenu();

		void createButtons();

		void setAnimation();

		void execute(float dt);

		void updateAnimation(float dt);

		void render();
	};

}