#pragma once
#include"Layer.h"

namespace GraphicalElements {

	namespace Parallax {

		class Background {
		private:
			static Managers::GraphicManager* pGraphic;
			sf::Vector2f prevCameraPos;
			std::vector<Layer*> layers;

		public:
			Background();

			~Background();

			void render();

			void addLayer(const char* texturePath,const float vel);

			void execute(float dt);
		};

	}
}