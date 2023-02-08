#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() override; 

    virtual void DrawBody() {};
    virtual void DrawWings() {};
    virtual void DrawTail() {};

    inline void ChangePlaneY(double dy) { yDirection += dy; }

private:

};


class ColorPlane : public Plane {
public:
    virtual void DrawBody() override;
    virtual void DrawWings() override;
    virtual void DrawTail() override;
};


class BigPlane : public Plane {
public:
    virtual void DrawBody() override;
    virtual void DrawWings() override;
    virtual void DrawTail() override;
};