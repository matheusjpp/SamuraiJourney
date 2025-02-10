#pragma once
#include "Button.h"

// C�digo baseado no reposit�rio "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Reposit�rio: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este reposit�rio n�o possui licen�a expl�cita. O uso, modifica��o e distribui��o
// deste c�digo podem exigir permiss�o do autor original.

namespace Menu {

	class Text {
	private:
		std::string info;
		const sf::Font font; 
		sf::Text text;
		unsigned int fontSize;
		sf::Color textColor;
		sf::Color borderColor;
		Math::CoordF textSize;
		Math::CoordF textPos;

		void initialize();
		void updateTextSize();

	public:
		Text(const std::string info, const sf::Font font, unsigned int fontSize = 50);

		~Text();

		const sf::Text getText() const; 

		Math::CoordF getTextSize();

		Math::CoordF getTextPos() const;
		
		void setTextPos(const Math::CoordF pos);

		void setTextColor(const sf::Color& textColor);

		void setBorderColor(const sf::Color& borderColor);

		void setBorderSize(float borderSize);

		void setSpacing(float spacingSize);

		void setString(const std::string& info);

		void setFontSize(unsigned int fontSize);

		void moveText(float speed);

		void setText(const std::string& newText);
	};

}