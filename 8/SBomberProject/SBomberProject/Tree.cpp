#include <iostream>
#include "Tree.h"
#include "MyTools.h"


void SmallTree::Grow(Tree* _currentState, const uint16_t& _deltaTime) {
	time += _deltaTime; 
	if (time >= 4000) _currentState->SetState(new MiddleTree);
}


void MiddleTree::Grow(Tree* _currentState, const uint16_t& _deltaTime) {
	time += _deltaTime;
	if (time >= 4000) _currentState->SetState(new BigTree);
}


void SmallTree::Draw(const Tree* _tree) const
{
	MyTools::SetColor(MyTools::CC_Green);
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 1);
	std::cout << "      #     ";
	MyTools::SetColor(MyTools::CC_Brown);
	MyTools::GotoXY(_tree->GetX(), _tree->GetY());
	std::cout << "      #     ";
}


void MiddleTree::Draw(const Tree* _tree) const
{
	MyTools::SetColor(MyTools::CC_Green);
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 3);
	std::cout << "      #     ";
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 2);
	std::cout << "     ###    ";
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 1);
	std::cout << "    #####   ";
	MyTools::SetColor(MyTools::CC_Brown);
	MyTools::GotoXY(_tree->GetX(), _tree->GetY());
	std::cout << "      #     ";
}


void BigTree::Draw(const Tree* _tree) const
{
	MyTools::SetColor(MyTools::CC_Green);
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 5);
	std::cout << "      #     ";
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 4);
	std::cout << "     ###    ";
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 3);
	std::cout << "    #####   ";
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 2);
	std::cout << "   #######  ";
	MyTools::GotoXY(_tree->GetX(), _tree->GetY() - 1);
	std::cout << "  ######### ";
	MyTools::SetColor(MyTools::CC_Brown);
	MyTools::GotoXY(_tree->GetX(), _tree->GetY());
	std::cout << "      #     ";
}