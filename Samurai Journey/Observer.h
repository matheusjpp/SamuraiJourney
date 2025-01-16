#pragma once
#include "Platform.h"
namespace Managers {
    class InputManager;
}
class Observer
{
private:
    Managers::InputManager* pIm;
public:
    Observer();
    ~Observer();
    virtual void notifyKeyPressed(sf::Keyboard::Key k) = 0;
    virtual void notifyKeyReleased(sf::Keyboard::Key k) = 0;
  
};
