#pragma once
#include "ofMain.h"
#include "Tweener.h"

class Brush;

class BrushTweener {
public:
    BrushTweener(Brush& b);
    void update(unsigned long time);

    Tween scaleX;
    Tween scaleY;
    Tween colorR;
    Tween colorG;
    Tween colorB;
    Tween colorA;
    Tween posX;
    Tween posY;
    Tween rotate;
};

class Brush {
public:
    float scaleX;
    float scaleY;
    ofFloatColor color;
    ofPoint pos;
    float rotate;
    BrushTweener tweener;
    bool initialized;

    Brush() : tweener(*this), initialized(false) {
    }

    virtual const char* getName() const =0;
    virtual void update(const ofFloatColor& mood, const float score) =0;
    virtual void draw() =0;
};

class EllipseBrush : public Brush {
public:
    virtual const char* getName() const;
    virtual void draw();
    virtual void update(const ofFloatColor& mood, const float score);
};

class RectBrush : public Brush {
public:
    virtual const char* getName() const;
    virtual void draw();
    virtual void update(const ofFloatColor& mood, const float score);
};
