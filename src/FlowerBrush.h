#ifndef FLOWER_BRUSH_H
#define FLOWER_BRUSH_H
#include "Brush.h"
#include "Flower.h"

class FlowerBrush : public Brush {
public:
    FlowerBrush();
    virtual const char* getName() const;
    virtual void draw();
    virtual void update(const ofFloatColor& mood, const float score);

    Flower flower;
    unsigned long stamp;
    unsigned long delay;
};

#endif //FLOWER_BRUSH_H
