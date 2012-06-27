#ifndef RYBWHEEL_H
#define RYBWHEEL_H
#include "ofColor.h"

class RYBWheel {
public:
    // 0 to 1
    static ofFloatColor pick(float v);
    // 0 to TWO_PI
    static ofFloatColor pickRad(float rad);
    // 0 to 360
    static ofFloatColor pickDeg(float degree);

private:
    static const float TABLE[13][3];
};

#endif //RYBWHEEL_H
