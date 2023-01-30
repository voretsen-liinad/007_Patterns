#pragma once

#include <stdint.h>

#include "GameObject.h" 
#include "DestroyableGroundObject.h"

class TankAdaptee {
public:
	TankAdaptee() : x(0.0), y(0.0), width(0) { }
	void Paint() const;										     // ~Draw()
	bool __fastcall isInRange(double x1, double x2) const;       // ~isInside()
	inline uint16_t GetScore() const { return score; }
	inline void SetPos(double nx, double ny) { x = nx; y = ny; }
	inline double GetY() const { return y; }
	inline double GetX() const { return x; }
	inline void SetWidth(uint16_t widthN) { width = widthN; }
	inline uint16_t GetWidth() const { return width; }
protected:
	double x, y;
	uint16_t width;
	const uint16_t score = 30;
};


class TankAdapter : public DestroyableGroundObject {
public:
	TankAdapter() {}
	void SetPos(double nx, double ny) { tank.SetPos(nx, ny); }
	double GetY() const { return tank.GetY(); }
	double GetX() const { return tank.GetX(); }
	void SetWidth(uint16_t widthN) { tank.SetWidth(widthN); }
	uint16_t GetWidth() const { return tank.GetWidth(); }
	void Draw() const override { tank.Paint(); };
	bool __fastcall isInside(double x1, double x2) const { return tank.isInRange(x1, x2); }; 
	inline uint16_t GetScore() const override { return tank.GetScore(); }
private:
	TankAdaptee tank;
};