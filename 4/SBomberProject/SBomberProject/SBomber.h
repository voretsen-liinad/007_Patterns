#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "WinterFactory.h"
#include "MyTools.h"
#include "Tree.h"
#include <memory>

template <typename t>
class AbstractCommand {
public:
    virtual ~AbstractCommand() {}
    virtual void Execute() = 0;
    virtual void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum = 0) = 0;
protected:
    const t* pObj;
    std::vector<t*>* vecObj;
};

template <typename t>
class DeleteObjCommand : public AbstractCommand<t> {
public:
    DeleteObjCommand() {};
    void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum = 0) override { pObj = _pObj; vecObj = &_vecObj; };
    void Execute() override {
        auto it = vecObj->begin();
        for (; it != vecObj->end(); it++)
        {
            if (*it == pObj)
            {
                vecObj->erase(it);
                break;
            }
        }
    };
protected:
    using AbstractCommand<t>::pObj; 
    using AbstractCommand<t>::vecObj;
};

template <typename t>
class DropBombCommand : public AbstractCommand<t> {
public:
    DropBombCommand() {};
    void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum) override { pObj = _pObj; vecObj = &_vecObj; bombsNum = _bombsNum; };
    void Execute() override {
        if (bombsNum > 0)
        {
            //MyTools::FileLoggerSingleton::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");
            MyTools::LoggerSingleton::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");

            //Plane* pPlane = pObj;
            double x = pObj->GetX() + 4;
            double y = pObj->GetY() + 2;

            Bomb* pBomb = new Bomb;
            pBomb->SetDirection(0.3, 1);
            pBomb->SetSpeed(2);
            pBomb->SetPos(x, y);
            pBomb->SetWidth(SMALL_CRATER_SIZE);

            vecObj->push_back(pBomb);
            //bombsNumber--;
            //score -= Bomb::BombCost;
        }
    };
protected:
    using AbstractCommand<t>::pObj;
    using AbstractCommand<t>::vecObj;
    uint16_t bombsNum;
};

/*
template <typename t>
class DropBombDecoratorCommand : public AbstractCommand<t> {
public:
    DropBombDecoratorCommand() {};
    void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum) override { pObj = _pObj; vecObj = &_vecObj; bombsNum = _bombsNum; };
    void Execute() override {
        if (bombsNum > 0)
        {
            //MyTools::FileLoggerSingleton::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");
            MyTools::LoggerSingleton::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");

            //Plane* pPlane = pObj;
            double x = pObj->GetX() + 4;
            double y = pObj->GetY() + 2;

            Bomb* pBomb = new Bomb;
            pBomb->SetDirection(0.3, 1);
            pBomb->SetSpeed(2);
            pBomb->SetPos(x, y);
            pBomb->SetWidth(SMALL_CRATER_SIZE);
            BombDecorator* pBombDecorator = new BombDecorator(pBomb);

            vecObj->push_back(pBombDecorator);
            //bombsNumber--;
            //score -= Bomb::BombCost;
        }
    };
protected:
    using AbstractCommand<t>::pObj;
    using AbstractCommand<t>::vecObj;
    uint16_t bombsNum;
};
*/

class SBomber;

class CollisionDetector {
public:
    CollisionDetector(SBomber* _sBomber) : sBomber(_sBomber) {};
    void CheckPlaneAndLevelGUI(Plane* plane, AbstractLevelGUI* levelGUI); 
    void CheckBombsAndGround(std::vector<Bomb*> vecBombs, Ground* pGround, std::vector<DynamicObject*>& vecDynamicObj, std::vector<DestroyableGroundObject*> vecDestoyableObjects, std::vector<GameObject*>& vecStaticObj);
    void __fastcall CheckDestoyableObjects(std::vector<DestroyableGroundObject*>& vecDestoyableObjects, Bomb* pBomb, std::vector<GameObject*>& vecStaticObj);
protected:
    SBomber* sBomber;
};

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }
    inline void SetExitFlag(const bool& value) { exitFlag = value; } 
    void AddScore(const int16_t& value) { score += value; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects(); 

protected:
    friend class CollisionDetector;

    template<typename t>
    void __fastcall CommandExecuter(AbstractCommand<t>* pCommand) {
        pCommand->Execute();
        delete pCommand;
    };

private:

    //void CheckPlaneAndLevelGUI();
    //void CheckBombsAndGround();
    //void __fastcall CheckDestoyableObjects(Bomb* pBomb); 
    //void __fastcall CheckDestoyableObjects(BombDecorator* pBomb); 

    CollisionDetector* CollisionFinder = new CollisionDetector{ this };

    //void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    //void __fastcall DeleteStaticObj(GameObject* pObj);

    void SetLevelGUI(AbstractLevelGUI* pGUI);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    //LevelGUI * FindLevelGUI() const;
    AbstractLevelGUI* FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;
    //std::vector<BombDecorator*> FindAllBombs() const;

    AbstractFactory* pFactory;
    TreeCreator* pTreeCreator;

    //void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};

