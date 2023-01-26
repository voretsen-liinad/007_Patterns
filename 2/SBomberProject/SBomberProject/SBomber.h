#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "WinterFactory.h"

template <typename t>
class AbstractCommand {
public:
    virtual ~AbstractCommand() {}
    virtual void Execute() = 0;
    virtual void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum = 0) = 0;
};

template <typename t>
class DeleteObjCommand : public AbstractCommand<t> {
public:
    DeleteObjCommand() {};
    void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum = 0) override { pObj = _pObj; vecObj = &_vecObj; };
    void Execute() override;
protected:
    const t* pObj;
    std::vector<t*>* vecObj;
};

template <typename t>
class DropBombCommand : public AbstractCommand<t> {
public:
    DropBombCommand() {};
    void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum) override { pObj = _pObj; vecObj = &_vecObj; bombsNum = _bombsNum; };
    void Execute() override;
protected:
    const t* pObj;
    std::vector<t*>* vecObj;
    uint16_t bombsNum;
};

template <typename t>
class DropBombDecoratorCommand : public AbstractCommand<t> {
public:
    DropBombDecoratorCommand() {};
    void SetParams(const t* _pObj, std::vector<t*>& _vecObj, const uint16_t& _bombsNum) override { pObj = _pObj; vecObj = &_vecObj; bombsNum = _bombsNum; };
    void Execute() override;
protected:
    const t* pObj;
    std::vector<t*>* vecObj;
    uint16_t bombsNum;
};


class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    //void __fastcall CheckDestoyableObjects(Bomb* pBomb);
    void __fastcall CheckDestoyableObjects(BombDecorator* pBomb);

    //void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    //void __fastcall DeleteStaticObj(GameObject* pObj);

    template<typename t>
    void __fastcall CommandExecuter(AbstractCommand<t>* pCommand);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    //std::vector<Bomb*> FindAllBombs() const;
    std::vector<BombDecorator*> FindAllBombs() const;

    AbstractFactory* pFactory;

    //void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};