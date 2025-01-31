#include "Text.h"

namespace Menu {

	Text::Text(const std::string info, const sf::Font font, unsigned int fontSize)
		: info(info), font(font), fontSize(fontSize),
		textColor(sf::Color::White), borderColor(sf::Color::Black)
	{
		initialize();
	}

	Text::~Text() {
	
	}

	void Text::initialize() {
		text.setString(info);
		text.setCharacterSize(fontSize);
		text.setFont(font);
		text.setOutlineThickness(0.0f);
		text.setOutlineColor(borderColor);
		text.setFillColor(textColor);
		updateTextSize();
	}

	void Text::updateTextSize() {
		textSize = Math::CoordF(text.getGlobalBounds().width, text.getGlobalBounds().height);
	}

	const sf::Text Text::getText() const {
		return text;
	}

	Math::CoordF Text::getTextSize() {
		updateTextSize();
		return textSize;
	}

	Math::CoordF Text::getTextPos() const {
		return textPos;
	}

	void Text::setTextPos(const Math::CoordF pos) {
		text.setPosition(sf::Vector2f(pos.x, pos.y));
		textPos = pos;
		updateTextSize();
	}

	void Text::setTextColor(const sf::Color& textColor) {
		this->textColor = textColor;
		text.setFillColor(textColor);
	}

	void Text::setBorderColor(const sf::Color& borderColor) {
		this->borderColor = borderColor;
		text.setOutlineColor(borderColor);
	}

	void Text::setBorderSize(float borderSize) {
		text.setOutlineThickness(borderSize);
		updateTextSize();
	}

	void Text::setSpacing(float spacingSize) {
		text.setLetterSpacing(spacingSize);
		updateTextSize();
	}

	void Text::setString(const std::string& info) {
		text.setString(info);
		updateTextSize();
	}

	void Text::setFontSize(unsigned int fontSize) {
		text.setCharacterSize(fontSize);
		updateTextSize();
	}

	void Text::moveText(float speed) {
		text.move(sf::Vector2f(speed, 0));
	}

	void Text::setText(const std::string& newText) {
		text.setString(newText);
	}

}