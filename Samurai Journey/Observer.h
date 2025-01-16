#pragma once
#include "Platform.h"
class Observer
{
private:
    Managers::InputManager* pIm;
public:
    Observer();
    ~Observer();
    virtual void notifyKeyPressed() = 0;
    virtual void notifyKeyReleased() = 0;
};
