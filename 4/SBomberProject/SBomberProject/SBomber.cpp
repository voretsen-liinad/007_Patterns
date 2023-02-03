
#include <conio.h>
#include <windows.h>
#include <iostream>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "WinterGround.h"
#include "WinterTank.h"
#include "WinterHouse.h"
#include "Tree.h"

using namespace std;
using namespace MyTools;

void CollisionDetector::CheckPlaneAndLevelGUI(Plane* pPlane, AbstractLevelGUI* pLevelGUI) {
    if (pPlane->GetX() > pLevelGUI->GetFinishX())
    {
        sBomber->SetExitFlag(true);
    }
}

void CollisionDetector::CheckBombsAndGround(vector<Bomb*> vecBombs, Ground* pGround, vector<DynamicObject*>& vecDynamicObj, vector<DestroyableGroundObject*> vecDestoyableObjects, vector<GameObject*>& vecStaticObj) {
    //vector<Bomb*> vecBombs = FindAllBombs();
    //Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecDestoyableObjects, vecBombs[i], vecStaticObj);
            //DeleteDynamicObj(vecBombs[i]);
            AbstractCommand<DynamicObject>* pDeleteDynamicObj = new DeleteObjCommand<DynamicObject>;
            pDeleteDynamicObj->SetParams(vecBombs[i], vecDynamicObj);
            sBomber->CommandExecuter(pDeleteDynamicObj);
        }
    }
}

void __fastcall CollisionDetector::CheckDestoyableObjects(vector<DestroyableGroundObject*>& vecDestoyableObjects, Bomb* pBomb, vector<GameObject*>& vecStaticObj) {
    //vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            sBomber->AddScore(vecDestoyableObjects[i]->GetScore());
            //DeleteStaticObj(vecDestoyableObjects[i]);
            AbstractCommand<GameObject>* pDeleteGameObj = new DeleteObjCommand<GameObject>;
            pDeleteGameObj->SetParams(vecDestoyableObjects[i], vecStaticObj);
            sBomber->CommandExecuter(pDeleteGameObj);
        }
    }
}

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0)
{
    char answer = ' ';
    while (answer != 'a' && answer != 'A' && answer != 'b' && answer != 'B') {
        std::cout << "What kind of house would you like to have? Enter A or B: ";
        std::cin >> answer;
    }
    
    //MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    MyTools::LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    //LevelGUI* pGUI = new LevelGUI;
    AbstractLevelGUI* pGUI = new LevelGUI; 
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = MyTools::ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = MyTools::ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    pFactory = new WinterFactory;
    pFactory->CreateLevel1(vecStaticObj);

    HouseDirector HouseDir;
    House* pHouse;
    if (answer == 'a' || answer == 'A') {
        HouseBuilderA HouseA;
        pHouse = HouseDir.Construct(HouseA);
    }
    else {
        HouseBuilderB HouseB;
        pHouse = HouseDir.Construct(HouseB);
    }
    pHouse->SetWidth(13);
    pHouse->SetPos(80, MyTools::ScreenSingleton::getInstance().GetMaxY() - 6);
    vecStaticObj.push_back(pHouse);

    /*
    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    TankAdapter* pTank = new TankAdapter;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    pTank = new TankAdapter;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    House * pHouse = new House;      
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);
    */

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }
    
    delete pFactory;
}

void SBomber::SetLevelGUI(AbstractLevelGUI* pGUI) {
    //LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = MyTools::ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = MyTools::ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);
    AbstractCommand<GameObject>* pDeleteGameObj = new DeleteObjCommand<GameObject>;
    pDeleteGameObj->SetParams(FindLevelGUI(), vecStaticObj);
    CommandExecuter(pDeleteGameObj);
}

void SBomber::MoveObjects()
{
    //MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    MyTools::LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    //MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    MyTools::LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    //CheckPlaneAndLevelGUI();
    CollisionFinder->CheckPlaneAndLevelGUI(FindPlane(), FindLevelGUI());

    //CheckBombsAndGround();
    CollisionFinder->CheckBombsAndGround(FindAllBombs(), FindGround(), vecDynamicObj, FindDestoyableGroundObjects(), vecStaticObj);
};

/*
void SBomber::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}


void SBomber::CheckBombsAndGround() 
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            //DeleteDynamicObj(vecBombs[i]);
            AbstractCommand<DynamicObject>* pDeleteDynamicObj = new DeleteObjCommand<DynamicObject>;
            pDeleteDynamicObj->SetParams(vecBombs[i], vecDynamicObj);
            CommandExecuter(pDeleteDynamicObj);
        }
    }
}
*/
/*
void SBomber::CheckBombsAndGround()
{
    vector<BombDecorator*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            //DeleteDynamicObj(vecBombs[i]);
            AbstractCommand<DynamicObject>* pDeleteDynamicObj = new DeleteObjCommand<DynamicObject>;
            pDeleteDynamicObj->SetParams(vecBombs[i], vecDynamicObj);
            CommandExecuter(pDeleteDynamicObj);
        }
    }
}
*/


/*
void SBomber::CheckDestoyableObjects(Bomb * pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            //DeleteStaticObj(vecDestoyableObjects[i]);
            AbstractCommand<GameObject>* pDeleteGameObj = new DeleteObjCommand<GameObject>;
            pDeleteGameObj->SetParams(vecDestoyableObjects[i], vecStaticObj);
            CommandExecuter(pDeleteGameObj);
        }
    }
}
*/
/*
void SBomber::CheckDestoyableObjects(BombDecorator* pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            //DeleteStaticObj(vecDestoyableObjects[i]);
            AbstractCommand<GameObject>* pDeleteGameObj = new DeleteObjCommand<GameObject>;
            pDeleteGameObj->SetParams(vecDestoyableObjects[i], vecStaticObj);
            CommandExecuter(pDeleteGameObj);
        }
    }
}
*/
/*
void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecDynamicObj.erase(it);
            break;
        }
    }
}


void SBomber::DeleteStaticObj(GameObject* pObj)
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }
}
*/

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    //Tank* pTank;
    TankAdapter* pTank;
    House* pHouse;
    DestroyableGroundObject* pTree;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        //pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        pTank = dynamic_cast<TankAdapter*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }

        pTree = dynamic_cast<DestroyableGroundObject*>(vecStaticObj[i]);
        if (pTree != nullptr)
        {
            vec.push_back(pTree);
            continue;
        }
    }

    return vec;
}

Ground* SBomber::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}


vector<Bomb*> SBomber::FindAllBombs() const
{
    vector<Bomb*> vecBombs;
    /*
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }
    */

    Bomb::BombIterator it(vecDynamicObj); 
    while (it != it.end()) {
        if (*it != nullptr) {
            vecBombs.push_back(*it);
            ++it;
        }
    }

    return vecBombs;
}


/*
vector<BombDecorator*> SBomber::FindAllBombs() const
{
    vector<BombDecorator*> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        BombDecorator* pBomb = dynamic_cast<BombDecorator*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}
*/

Plane* SBomber::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

//LevelGUI* SBomber::FindLevelGUI() const
AbstractLevelGUI* SBomber::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        //LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        AbstractLevelGUI* p = dynamic_cast<AbstractLevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b': {
        //DropBomb(); 
        //AbstractCommand<DynamicObject>* pDropBomb = new DropBombCommand<DynamicObject>;
        //pDropBomb->SetParams(FindPlane(), vecDynamicObj, bombsNumber);
        //CommandExecuter(pDropBomb);
        //AbstractCommand<DynamicObject>* pDropBombDecorator = new DropBombDecoratorCommand<DynamicObject>;
        AbstractCommand<DynamicObject>* pDropBomb = new DropBombCommand<DynamicObject>;
        pDropBomb->SetParams(FindPlane(), vecDynamicObj, bombsNumber);
        CommandExecuter(pDropBomb);
        bombsNumber--;
        score -= Bomb::BombCost;
        break;
    }

    case 'B': {
        //DropBomb();
        //AbstractCommand<DynamicObject>* pDropBomb = new DropBombCommand<DynamicObject>;
        //pDropBomb->SetParams(FindPlane(), vecDynamicObj, bombsNumber);
        //CommandExecuter(pDropBomb);
        //AbstractCommand<DynamicObject>* pDropBombDecorator = new DropBombDecoratorCommand<DynamicObject>;
        AbstractCommand<DynamicObject>* pDropBomb = new DropBombCommand<DynamicObject>;
        pDropBomb->SetParams(FindPlane(), vecDynamicObj, bombsNumber);
        CommandExecuter(pDropBomb);
        bombsNumber--;
        score -= Bomb::BombCost;
        break;
    }

    case '0': {
        AbstractLevelGUI* pGUI = new LevelGUI;
        SetLevelGUI(pGUI);
        break;
    }

    case '1': {
        //AbstractLevelGUI* pGUI = new LevelGUI1;
        //SetLevelGUI(pGUI);
        if (pTreeCreator != nullptr) delete pTreeCreator;
        pTreeCreator = new (std::nothrow) TreeCreatorA;
        break;
    }

    case '2': {
        //AbstractLevelGUI* pGUI = new LevelGUI2;
        //SetLevelGUI(pGUI);
        if (pTreeCreator != nullptr) delete pTreeCreator;
        pTreeCreator = new (std::nothrow) TreeCreatorB;
        break;
    }

    case '+': {
        if (pTreeCreator == nullptr) pTreeCreator = new (std::nothrow) TreeCreatorA;
        DestroyableGroundObject* pTree;
        auto it = vecStaticObj.begin();
        for (; it != vecStaticObj.end(); it++)
         {
            pTree = dynamic_cast<TreeA*>(*it); 
            if (pTree == nullptr) pTree = dynamic_cast<TreeB*>(*it);
            if (pTree != nullptr)
            {
                vecStaticObj.erase(it);
                break;
            }
        }
        pTree = pTreeCreator->Create();
        if (dynamic_cast<TreeA*>(pTree) != nullptr) pTree->SetWidth(8);
        else pTree->SetWidth(9);
        pTree->SetPos(15, MyTools::ScreenSingleton::getInstance().GetMaxY() - 6);
        vecStaticObj.push_back(pTree);
    }

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    //MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    MyTools::LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            vecStaticObj[i]->Draw();
        }
    }

    MyTools::ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart()
{
    //MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    MyTools::LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    //MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
    MyTools::LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

/*
void SBomber::DropBomb()
{
    if (bombsNumber > 0)
    {
        //MyTools::FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
        MyTools::LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        Plane* pPlane = FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecDynamicObj.push_back(pBomb);
        bombsNumber--;
        score -= Bomb::BombCost;
    }
}
*/