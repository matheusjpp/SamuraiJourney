#include "Observer.h"
#include "InputManager.h"

Observer::Observer() {
	pIm = Managers::InputManager::getInstance();
}
Observer::~Observer() {}