#include "TextButton.h"

namespace Menu {

	namespace Buttons {

		TextButton::TextButton(const std::string info, Math::CoordF pos, Math::CoordF size, unsigned int fontSize, Button_ID id) :
			selected(false), selectedColor(sf::Color(31, 28, 43)),
			text(info, pGraphic->loadFont("alagard.ttf"), fontSize),
			Button(pos, size, id)
		{
			Math::CoordF textSize = this->text.getTextSize();
			Math::CoordF textPos = Math::CoordF(
				pos.x + size.x / 2.0f - textSize.x / 2.0f,
				pos.y + size.y / 2.0f - textSize.y / 2.0f
			);
			this->text.setTextPos(textPos);

		}

		TextButton::~TextButton() {

		}

		const Math::CoordF TextButton::getTextSize() {
			return (text.getTextSize());
		}

		void TextButton::setSelected(bool selected) {
			this->selected = selected;
			if (selected) {
				text.setTextColor(selectedColor);  
			}
			else {
				text.setTextColor(sf::Color::White);
			}
		}

		const bool TextButton::getSelected() const {
			return selected;
		}

		void TextButton::render() {
			if (selected) { // Sombreamento no botão selecionado
				sf::Text shadow = text.getText(); 
				shadow.setFillColor(sf::Color(255, 255, 255, 100));
				shadow.move(4.f, 4.f); 
				pGraphic->render(shadow);

			}
			pGraphic->render(text.getText());
		}

	}

}