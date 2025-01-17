#include "Player.h"
#include "PlayerController.h"

namespace Entities {
	
	namespace Characters {

		Player::Player(Math::CoordF pos, bool isPlayer1) :
		Character(pos, Math::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), ID::player), isPlayer1(isPlayer1) {
			mudarCor(sf::Color(255, 0, 0));
			pControl = new Managers::KeyManagement::PlayerController(this);
		}

		Player::~Player() {
		
		}

		bool Player::getIsPlayer1() {
			return isPlayer1;
		}

        void Player::update(float dt) {
            // Controle de movimento horizontal
            if (isMoving) {
                if (isFacingLeft) {
                    setVelocityX(PLAYER_SPEED); 
                }
                else {
                    setVelocityX(-PLAYER_SPEED); 
                }
            }
            else {
                setVelocityX(0);
            }

			velocity.y += GRAVITY * dt; // Incrementa velocidade vertical

            position.x += velocity.x * dt;
            position.y += velocity.y * dt;

			setCanJump(false);
            pCollision->notifyCollision(this, dt);

            body->setPosition(sf::Vector2f(position.x, position.y));
        }
		
		void Player::execute() {
			update(pGraphic->getDeltaTime());
			render();
		}
   
		void Player::run() {

		}

		void Player::stopRunning() {

		}

		void Player::attack() {

		}

		void Player::defend() {

		}

		void Player::usePotion() {

		}

		//void Player::initialize() {
			////exit(1);
		//}

	}

}