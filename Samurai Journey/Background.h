#pragma once
#include"Layer.h"

// C�digo baseado no reposit�rio "JogoPlataforma2D-Jungle" de Giovani Limas Salvi
// Reposit�rio: https://github.com/Giovanenero/JogoPlataforma2D-Jungle
// 
// Este reposit�rio n�o possui licen�a expl�cita. O uso, modifica��o e distribui��o
// deste c�digo podem exigir permiss�o do autor original.

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