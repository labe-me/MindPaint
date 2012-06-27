#ifndef RYB_COLOR_SELECTOR_H
#define RYB_COLOR_SELECTOR_H

#include "ofMain.h"
#include <vector>

class RYBColor {
public:
    RYBColor(float angle, float saturation, float value);

    vector<RYBColor> getMonochromatic() const;

    std::vector<RYBColor> getAnalogous(float rtotalAngle) const;

    // Ryb hue - 1/3, this, hue + 1/3
    //
    //
    vector<RYBColor> getTriad() const;

    // Ryb hue - 0.5
    RYBColor getComplementary() const;

    // same hue
    // same saturation
    // different values (25%, 50%, 75%, 90%)
    vector<RYBColor> getShades() const;

    ofFloatColor toColor() const;


private:
    float angle;
    float saturation;
    float value;
};

#endif//RYB_COLOR_SELECTOR_H
