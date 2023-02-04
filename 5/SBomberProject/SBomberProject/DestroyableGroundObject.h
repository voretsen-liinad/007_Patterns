#pragma once

#include <stdint.h>

#include "GameObject.h"

class DestroyableGroundObject : public GameObject
{
public:

    virtual inline uint16_t GetScore() const = 0;

protected:

};


class Observer : public DestroyableGroundObject {
public:
    virtual bool HandleInsideCheck(double x1, double x2) const = 0;
};


class Observable {
public:
    virtual void AddObserver(Observer* o) = 0;
};