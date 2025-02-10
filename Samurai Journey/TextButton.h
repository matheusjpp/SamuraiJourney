#pragma once
#include "Text.h"

// Código baseado no repositório "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Repositório: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este repositório não possui licença explícita. O uso, modificação e distribuição
// deste código podem exigir permissão do autor original.

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