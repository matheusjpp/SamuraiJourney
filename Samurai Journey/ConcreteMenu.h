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
		Levels::Level* pLevel;

	public:
		ConcreteMenu(Math::CoordF buttonSize, const std::string info, const unsigned int fontSize, Managers::States::State_ID id = Managers::States::State_ID::empty, Levels::Level* pLevel = nullptr);

		~ConcreteMenu();

		void buildMenu();

		void setAnimation();

		void execute(float dt);

		void updateAnimation(float dt);

		void render();

		const int getScore() const;

		void buildLeaderboard();

		void renderLeaderboardText(const std::vector<std::pair<std::string, int>>& scores);
	};

}