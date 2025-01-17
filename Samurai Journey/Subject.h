#pragma once
#include "Observer.h"

namespace Managers {

	namespace KeyManagement {

		class Subject	{
		protected:
			std::list<Observer*> observers;

		public:

			virtual ~Subject() = default;

			virtual void attachObserver(Observer* observer) = 0;

			virtual void detachObserver(Observer* observer) = 0;

			virtual void notifyKeyPressed(sf::Keyboard::Key key) = 0;

			virtual void notifyKeyReleased(sf::Keyboard::Key key) = 0;
		};

	}

}