#pragma once

#include <string>


class GameObject {
public:

    GameObject() : x(0.0), y(0.0), width(0) { }

    virtual void Draw() = 0;

    inline void SetPos(double nx, double ny) { x = nx; y = ny; }

    inline double GetY() const { return y; }
    inline double GetX() const { return x; }

    inline void SetWidth(uint16_t widthN) { width = widthN; }
    inline uint16_t GetWidth() const { return width; }

    virtual void BeNotified(const std::string& message) {};

protected:

    double x, y;
    uint16_t width;
};