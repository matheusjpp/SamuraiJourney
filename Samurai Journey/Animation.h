#pragma once
#include "Ente.h"
//Codigo Adaptado do codigo de Matheus Augusto Burda

namespace GraphicalElements {

	enum Animation_ID {
		idle = 0,
		walk = 1,
		run = 2,
		jump = 3,
		fall = 4,
		attack = 5,
		airattack = 6,
		defend = 7,
		heal = 8
	};

	class Animation : public Ente {
	private:
		class SingleAnimation {
		private:
			const unsigned int imageCount;
			unsigned int currentImage;
			sf::Texture* texture;
			float totalTime;
			sf::IntRect rectSize;
			static const float switchTime;
			static const float attackSwitchTime;

		public:
			SingleAnimation(const char* path, const unsigned int imageCount) :
				imageCount(imageCount),
				currentImage(0),
				texture(pGraphic->loadTexture(path)),
				totalTime(0.0f),
				rectSize() {
				if (texture == NULL) {
					std::cout << "ERROR: loading texture failed on SingleAnimation::SingleAnimation()." << std::endl;
					exit(1);
				}
				if (texture) {
					rectSize.width = texture->getSize().x / float(imageCount);
					rectSize.height = texture->getSize().y;
				}
			}

			~SingleAnimation() {}

			void update(float dt, bool isFacingLeft, Animation_ID id) {
				totalTime += dt;
				
				if (totalTime >= switchTime) {
					totalTime -= switchTime;
					currentImage++;

					if (currentImage >= imageCount)
							currentImage = 0;
				}

				if (isFacingLeft) {
					rectSize.left = (currentImage + 1) * abs(rectSize.width);
					rectSize.width = -abs(rectSize.width);
				}

				else {
					rectSize.left = currentImage * rectSize.width;
					rectSize.width = abs(rectSize.width);
				}
			}

			void reset() {
				currentImage = 0;
				totalTime = 0;
			}

			sf::IntRect getSize() const { return rectSize; }
			sf::Texture* getTexture() const { return texture; }
		};

	private:
		sf::RectangleShape* body;
		std::map<Animation_ID, SingleAnimation*> animationMap;
		Animation_ID currentID;

		static Managers::GraphicManager* pGraphic;

	public:
		Animation(sf::RectangleShape* body, Math::CoordF scale);
		~Animation();

		void addNewAnimation(Animation_ID, const char* path, unsigned int imageCount);
		void update(Animation_ID id, bool isFacingLeft, Math::CoordF position, float dt);
		void render();
		Math::CoordF getSize() const;
	};

}