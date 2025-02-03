#pragma once
#include "Menu.h"

namespace Managers {
	namespace KeyManagement {
		class MenuController;
	}
}

namespace Menu {

	class ConcreteMenu : public Menu {
	private:
		GraphicalElements::Animation* menuAnimation;

	public:
		ConcreteMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id = Managers::States::State_ID::empty);

		~ConcreteMenu();

		void createButtons();

		void setAnimation();

		void execute(float dt);

		void updateAnimation(float dt);

		void render();
	};

}