#pragma once
#include"Layer.h"

// Código baseado no repositório "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Repositório: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este repositório não possui licença explícita. O uso, modificação e distribuição
// deste código podem exigir permissão do autor original.

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