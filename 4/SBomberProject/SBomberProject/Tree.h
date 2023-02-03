#pragma once

#include <stdint.h> 

#include "DestroyableGroundObject.h"


class TreeA : public DestroyableGroundObject {
public:
	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }
	
	void Draw() const override;

protected:
	
	const uint16_t score = 8;
};

class TreeB : public DestroyableGroundObject {
public:
	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

protected:

	const uint16_t score = 5;
};

class TreeCreator {
public:
	virtual DestroyableGroundObject* Create() = 0;
	virtual ~TreeCreator() {};
};

class TreeCreatorA : public TreeCreator {
public:
	DestroyableGroundObject* Create() override { return new (std::nothrow) TreeA; }
};

class TreeCreatorB : public TreeCreator {
public:
	DestroyableGroundObject* Create() override { return new (std::nothrow) TreeB; }
};