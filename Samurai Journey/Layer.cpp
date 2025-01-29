#include "Layer.h"

namespace GraphicalElements {

	namespace Parallax {

		Managers::GraphicManager* Layer::pGraphic = Managers::GraphicManager::getInstance();
	
		Layer::Layer(sf::Texture* texture, const float speed) :
			texture(texture), dimension(0.0f, 0.0f, 0.0f, 0.0f), speed(speed),
			Windowsize(sf::Vector2f((float)pGraphic->getWindowSize().x, (float)pGraphic->getWindowSize().y)) 
		{
	
			backgroundSize = sf::Vector2f((float)texture->getSize().x, (float)texture->getSize().y);

			dimension.width = (float)(-fabs(texture->getSize().x));
			dimension.height = texture->getSize().y;
			dimension.left = texture->getSize().x;

			background.setSize(backgroundSize);
			background.setTexture(texture);
			background.setPosition(0.0f, 0.0f);
		

			//auxBackground.setSize(backgroundSize);
			////auxBackground.setTexture(texture);
			//auxBackground.setPosition(backgroundSize.x, 0.0f);
		}

		Layer::~Layer() {
	
		}

		void Layer::switchTexture() {
			sf::RectangleShape aux = background;
			background = auxBackground;
			//auxBackground = aux;
		}

		void Layer::renderLayer() {
			pGraphic->render(&background);
			if (speed != 0.0f) {
				//pGraphic->render(&auxBackground);
			}
		}

		void Layer::update(const sf::Vector2f ds, const sf::Vector2f currentCameraPos) {
			const float y = currentCameraPos.y - backgroundSize.y / 2.0f;
			sf::Vector2f backgroundPosition = background.getPosition();
			sf::Vector2f auxBackgroundPosition = auxBackground.getPosition();
			background.setPosition(sf::Vector2f(backgroundPosition.x, y));
			auxBackground.setPosition(sf::Vector2f(auxBackgroundPosition.x, y));
			if (ds.x != 0.0f) {
				const float rightPos = currentCameraPos.x + backgroundSize.x / 2.0f;
				const float leftPos = currentCameraPos.x - backgroundSize.x / 2.0f;
				if (speed != 0.0f) {
					background.move(ds.x * -speed, 0.0f);
					auxBackground.move(ds.x * -speed, 0.0f);
					if (ds.x > 0.0f) {
						if ((backgroundPosition.x + backgroundSize.x) < leftPos) {
							switchTexture();
							background.setPosition(leftPos, backgroundPosition.y);
							//auxBackground.setPosition(rightPos, auxBackgroundPosition.y);
						}
					}
					else {
						if (backgroundPosition.x > leftPos) {
							switchTexture();
							background.setPosition(leftPos - backgroundSize.x, backgroundPosition.y);
							//auxBackground.setPosition(leftPos, auxBackgroundPosition.y);
						}
					}
				}
				else {
					background.setPosition(leftPos, backgroundPosition.y);
				}
			}
		}

	}

}