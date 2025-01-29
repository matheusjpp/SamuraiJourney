#pragma once
#include "MainMenu.h"

namespace Managers {
	namespace KeyManagement {
		class MenuController;
	}
}

namespace Menu {

	class PauseMenu : public Menu, public Managers::States::State {
	private:
		sf::RectangleShape* body;
		GraphicalElements::Animation* pauseAnimation;

	public:
		PauseMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id = Managers::States::State_ID::empty);

		~PauseMenu();

		void createButtons();

		void setAnimation();

		void execute(float dt);

		void updateAnimation(float dt);

		void render();
	};

}