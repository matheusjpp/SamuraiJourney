#include "Button.h"

namespace Menu {

	namespace Buttons {

		Managers::GraphicManager* Button::pGraphic = Managers::GraphicManager::getInstance();

		Button::Button(Math::CoordF pos, Math::CoordF size, Button_ID id) : position(pos), size(size), id(id) {
			box.setPosition(pos.x, pos.y);
			box.setSize(sf::Vector2f(size.x, size.y));
		}

		Button::~Button() {
	
		}

		void Button::render() {
			pGraphic->render(&box);
		}

		const Math::CoordF Button::getPos() const {
			return Math::CoordF(box.getPosition().x, box.getPosition().y);
		}

		const Button_ID Button::getButtonID() const {
			return id;
		}

	}

}