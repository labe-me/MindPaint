#ifndef MOVER_CONTROLLER_H
#define MOVER_CONTROLLER_H

#include "Mover.h"

class MoverController {
public:
    Mover mover;

    MoverController();
    virtual void setup() =0;
    virtual void update(float scoreFactor) =0;
    virtual void debugDraw() =0;
};

class WandererController : public MoverController {
    virtual void setup();
    virtual void update(float scoreFactor);
    virtual void debugDraw();
};

class EvadeController : public MoverController {
public:
    vector<Mover> foes;
    virtual void setup();
    virtual void update(float scoreFactor);
    virtual void debugDraw();
};

class SpiralController : public MoverController {
public:
    virtual void setup();
    virtual void update(float scoreFactor);
    virtual void debugDraw();

    float angle;
    ofPoint center;
    float rotation;
    float scaleFactor;
    float speed;
};

class RectSpiralController : public MoverController {
    virtual void setup();
    virtual void update(float scoreFactor);
    virtual void debugDraw();
    ofPoint cursor;
    ofPoint segStart;
    ofPoint segEnd;
    float segLength;
    float rotation;
    float scaleFactor;
    float speed;
    int segCount;
};

#endif //MOVER_CONTROLLER_H
