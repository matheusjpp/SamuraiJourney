#pragma once
#include "Text.h"

namespace Menu {

	namespace Buttons {

		class TextButton : public Button {
		private:
			bool selected;
			sf::Color selectedColor;
			
			Text text;

			const Math::CoordF getTextSize();

		public:
			TextButton(const std::string info, Math::CoordF pos = (0, 0), Math::CoordF size = (0, 0), unsigned int fontSize = 50, Button_ID id = empty);

			~TextButton();

			void setSelected(bool selected);

			void setSelectedColor(sf::Color color);

			const bool getSelected() const;

			void render();
		};

	}

}