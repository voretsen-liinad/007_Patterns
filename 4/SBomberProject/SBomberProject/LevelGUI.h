#pragma once

#include <stdint.h>

#include "GameObject.h"

class AbstractLevelGUI : public GameObject {
public:
    AbstractLevelGUI() : bombsNumber(0), score(0), passedTime(0), fps(0), height(0) { }
    void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
    void __fastcall SetHeight(uint16_t heightN) { height = heightN; };
    inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

protected:
    uint16_t height;
    uint16_t finishX = 109;

    uint64_t passedTime, fps;
    uint16_t bombsNumber;
    int16_t score;
};




//class LevelGUI : public GameObject 
class LevelGUI : public AbstractLevelGUI
{
public:

    //LevelGUI() : bombsNumber(0), score(0), passedTime(0), fps(0), height(0) { }

    //void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
    
    //void __fastcall SetHeight(uint16_t heightN) { height = heightN; };
    
    //inline uint16_t GetFinishX() const { return finishX; }
    //inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() const override;

/*/private:

    uint16_t height;
    uint16_t finishX = 109;

    uint64_t passedTime, fps;
    uint16_t bombsNumber;
    int16_t score;
*/
};


class LevelGUI1 : public AbstractLevelGUI {
public:

    void Draw() const override;

};

class LevelGUI2 : public AbstractLevelGUI {
public:

    void Draw() const override;

};

