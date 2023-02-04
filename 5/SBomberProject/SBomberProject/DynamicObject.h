#pragma once

#include <stdint.h>
#include <utility>
#include <vector>

#include "GameObject.h"
#include "DestroyableGroundObject.h"
#include "MyTools.h"

class Bomb;
class Plane;


class Visitor {
public:
    virtual void log(Bomb* pBomb) const = 0;
    virtual void log(Plane* pPlane) const = 0;
};


class DynamicObject : public GameObject 
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
    
    virtual void Move(uint16_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; }; 

    inline double GetSpeed() { return speed; }
    inline std::pair<double, double> GetDirection() { std::pair<double, double> result(xDirction, yDirection); return result; }

protected:

    double speed;
    double xDirction, yDirection;

};


class Bomb : public DynamicObject, public Observable
{
public:

    static const uint16_t BombCost = 10; // стоимость бомбы в очках

    void Draw() const override; 

    void __fastcall Accept(const Visitor& v) { v.log(this); };

    void AddObserver(Observer* o) override { Observers.push_back(o); }

    DestroyableGroundObject* CheckDestroyableObjects();

private:

    std::vector<Observer*> Observers;
};


class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; } 

    void __fastcall Accept(const Visitor& v) { v.log(this); };;

private:

};

class LogVisitor : public Visitor {
public:
    void log(Bomb* pBomb) const override {
        MyTools::FileLoggerSingleton::getInstance().WriteToLog(" Bomb speed = ", pBomb->GetSpeed());
        MyTools::FileLoggerSingleton::getInstance().WriteToLog(" Bomb xDirection = ", pBomb->GetDirection().first);
        MyTools::FileLoggerSingleton::getInstance().WriteToLog(" Bomb yDirection = ", pBomb->GetDirection().second);
    }

    void log(Plane* pPlane) const override {
        MyTools::FileLoggerSingleton::getInstance().WriteToLog(" Plane speed = ", pPlane->GetSpeed());
        MyTools::FileLoggerSingleton::getInstance().WriteToLog(" Plane xDirection = ", pPlane->GetDirection().first);
        MyTools::FileLoggerSingleton::getInstance().WriteToLog(" Plane yDirection = ", pPlane->GetDirection().second);
    }
};