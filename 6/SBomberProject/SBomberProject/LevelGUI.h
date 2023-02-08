#pragma once

#include <stdint.h>
#include <deque>

#include "GameObject.h"


class LevelGUI : public GameObject {
public:

    LevelGUI() : bombsNumber(0), score(0), passedTime(0), fps(0), height(0) { }

    void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
    
    void __fastcall SetHeight(uint16_t heightN) { height = heightN; };
    
    inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() override;

    void BeNotified(const std::string& message) override { Messages.push_back(message); } 

    uint64_t GetTime() { return time; }

    void ChangeTime(const uint64_t& _time) { time += int(_time/1000); }

private:

    std::deque<std::string> Messages; 
    uint16_t time = 0;


    uint16_t height;
    uint16_t finishX = 109;

    uint64_t passedTime, fps;
    uint16_t bombsNumber;
    int16_t score;
};



