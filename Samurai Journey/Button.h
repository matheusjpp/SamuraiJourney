#pragma once
#include "EventsManager.h"

namespace Menu {

	namespace Buttons {

		enum Button_ID {
			empty,
			newgame

		};

		class Button {
		protected:
			static Managers::GraphicManager* pGraphic;
			sf::RectangleShape box;
			Math::CoordF position;
			Math::CoordF size;
			Button_ID id;
		
		public:
			Button(Math::CoordF pos = (0, 0), Math::CoordF size = (0, 0), Button_ID id = empty);
			
			virtual ~Button();

			virtual void render();

			const Math::CoordF getPos() const;

			const Button_ID getButtonID() const;
		};

	}

}