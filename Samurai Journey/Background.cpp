#include "Background.h"

namespace GraphicalElements {

	namespace Parallax {

		Managers::GraphicManager* Background::pGraphic = Managers::GraphicManager::getInstance();

		Background::Background() :
			prevCameraPos(0.0f, 0.0f), layers() {
	
		}

		Background :: ~Background() {
			int i = 0;
			while (i != layers.size()) {
				Layer* layer = layers.at(i);
				if (layer) {
					delete layer;
					layer = nullptr;
				}
				i++;
			}
			layers.clear();
		}

		void Background :: render() {
			for (int i = 0; i < layers.size(); i++) {
				Layer* layer = layers.at(i);
				layer->renderLayer();
			}
		}

		void Background ::addLayer(const char* texturePath, const float vel) {
			Layer* layer = new Layer(pGraphic->loadTexture(texturePath), vel);
			if (layer == nullptr) {
				cout << "NO layer!" << endl;
			}
			layers.push_back(layer);
		}

		void Background :: execute(float dt) {
			sf::Vector2f cameraPos = pGraphic->getCameraPosition();
			sf::Vector2f ds = cameraPos - prevCameraPos;
			prevCameraPos = cameraPos;
			for (int i = 0; i < layers.size(); i++) {
				layers.at(i)->update(ds, cameraPos);
			}
			render();
		}

	}

}