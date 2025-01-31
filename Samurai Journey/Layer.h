#include"Animation.h"

namespace GraphicalElements {

	namespace Parallax {

		class Background;

		class Layer {
		private:
			const sf::Vector2f Windowsize;
			sf::Vector2f backgroundSize;
			sf::IntRect dimension;
			static Managers::GraphicManager* pGraphic;
			const float speed;

			sf::Texture* texture;
			std::vector<sf::RectangleShape> backgrounds;
		
			void updatePositions();

		public:
			Layer(sf::Texture* texture,const float speed);

			~Layer();

			void renderLayer();

			void update(const sf::Vector2f ds,const sf::Vector2f currentCamerapos);
		};

	}

}