#include "TextButton.h"

namespace Menu {

	namespace Buttons {

		TextButton::TextButton(const std::string info, Math::CoordF pos, Math::CoordF size, unsigned int fontSize, Button_ID id) :
			selected(false), selectedColor(sf::Color(255, 255, 255)),
			text(info, pGraphic->loadFont("alagard.ttf"), fontSize),
			Button(pos, size, id)
		{
			Math::CoordF textSize = this->text.getTextSize();
			Math::CoordF textPos = Math::CoordF(
				pos.x + size.x / 2.0f - textSize.x / 2.05f,
				pos.y + size.y / 2.0f - textSize.y * 1.2f
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
			
		}

		const bool TextButton::getSelected() const {
			return selected;
		}

		void TextButton::render() {
			pGraphic->render(text.getText());
		}

	}

}