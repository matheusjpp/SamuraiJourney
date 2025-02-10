#pragma once
#include "Text.h"

// C�digo baseado no reposit�rio "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Reposit�rio: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este reposit�rio n�o possui licen�a expl�cita. O uso, modifica��o e distribui��o
// deste c�digo podem exigir permiss�o do autor original.

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