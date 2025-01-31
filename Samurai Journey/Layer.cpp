#include "Layer.h"
#include <cmath>

namespace GraphicalElements {
    namespace Parallax {

        Managers::GraphicManager* Layer::pGraphic = Managers::GraphicManager::getInstance();

        Layer::Layer(sf::Texture* texture, const float speed) :
            texture(texture), speed(speed),
            Windowsize(sf::Vector2f((float)pGraphic->getWindowSize().x, (float)pGraphic->getWindowSize().y))
        {
            backgroundSize = sf::Vector2f((float)texture->getSize().x, (float)texture->getSize().y);

            int numRepetitions = std::ceil(Windowsize.x / backgroundSize.x) + 1;

            for (int i = 0; i < numRepetitions; i++) {
                sf::RectangleShape bg(backgroundSize);
                bg.setTexture(texture);
                bg.setPosition(i * backgroundSize.x, 0.0f);
                backgrounds.push_back(bg);
            }
        }

        Layer::~Layer() {}

        void Layer::renderLayer() {
            for (auto& bg : backgrounds) {
                pGraphic->render(&bg);
            }
        }

        void Layer::update(const sf::Vector2f ds, const sf::Vector2f currentCameraPos) {
            if (ds.x != 0.0f) {
                for (auto& bg : backgrounds) {
                    bg.move(ds.x * -speed, 0.0f);
                }
                updatePositions();
            }
        }

        void Layer::updatePositions() {
            float leftBoundary = pGraphic->getCameraPosition().x - Windowsize.x / 2.0f;
            float rightBoundary = pGraphic->getCameraPosition().x + Windowsize.x / 2.0f;

            for (auto& bg : backgrounds) {
                if (bg.getPosition().x + backgroundSize.x < leftBoundary) {
                    bg.setPosition(bg.getPosition().x + backgrounds.size() * backgroundSize.x, bg.getPosition().y);
                }
                else if (bg.getPosition().x > rightBoundary) {
                    bg.setPosition(bg.getPosition().x - backgrounds.size() * backgroundSize.x, bg.getPosition().y);
                }
            }
        }

    }
}
