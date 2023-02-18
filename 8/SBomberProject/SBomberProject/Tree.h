#pragma once

#include "DynamicObject.h"

class Tree;


enum class States { Small = 1, Middle = 2, Big = 3 };


class TreeState {
public:
	TreeState(const States& _treeState) : treeState(_treeState) {};
	virtual void Grow(Tree* _currentState, const uint16_t& _deltaTime) = 0;
	virtual void Draw(const Tree* _tree) const = 0;
protected:
	uint16_t time = 0;
private:
	States treeState;
};


class Tree : public DynamicObject {
public:
	Tree(TreeState* _state) : state(_state) {};
	~Tree() { delete state; };
	void SetState(TreeState* _state) { delete state; state = _state; };
	virtual void Move(uint16_t time) override { state->Grow(this, time); };
	void Draw() const override { state->Draw(this); };
private:
	TreeState* state;
};


class SmallTree : public TreeState {
public:
	SmallTree() : TreeState(States::Small) {};
	void Grow(Tree* _currentState, const uint16_t& _deltaTime) override;
	void Draw(const Tree* _tree) const override;
};


class MiddleTree : public TreeState {
public:
	MiddleTree() : TreeState(States::Middle) {};
	void Grow(Tree* _currentState, const uint16_t& _deltaTime) override;
	void Draw(const Tree* _tree) const override;
};


class BigTree : public TreeState {
public:
	BigTree() : TreeState(States::Big) {};
	void Grow(Tree* _currentState, const uint16_t& _deltaTime) override {};
	void Draw(const Tree* _tree) const override;
};
