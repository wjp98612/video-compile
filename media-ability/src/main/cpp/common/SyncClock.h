//
// Created by 魏魏金鹏 on 2023/12/13.
//

#ifndef LEARNFFMPEG_SYNCCLOCK_H
#define LEARNFFMPEG_SYNCCLOCK_H

#include <LogUtil.h>

class SyncClock {
public:
    SyncClock(){
        curPts = 0;
        lastUpdate = 0;
        lastPts = 0;
        frameTimer = 0;
    }

    ~SyncClock() {
    }

    void SetClock(double pts, double time) {
        this->curPts = pts;
        this->lastUpdate = time;
    }

    double GetClock() {
        double time = GetSysCurrentTime();
        return curPts + time - lastUpdate;
    }

public:
    double lastPts;
    double frameTimer;
    double curPts;

private:
    double lastUpdate;
};


#endif //LEARNFFMPEG_SYNCCLOCK_H
