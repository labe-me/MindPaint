#include "RYBColorSelector.h"
#include "RYBWheel.h"

inline float rotateLimit(float v, float max){
  float q = v/max;
  if (q >= 1.0)
    v = v - floor(q)*max;
  else if (q < 0.)
    v = v + ceil(abs(q))*max;
  return v;
}

RYBColor::RYBColor(float angleRad_, float saturation_, float value_)
    : angle(angleRad_), saturation(saturation_), value(value_)
{
    angle = rotateLimit(angle, 1.);
}

// Same hue
//
// Value
//
// A : = this == v
// B : v <= 70 ? 100 + v - 70 : v - 50
// C : 10 + v * 90/100
// D : v  > 70 ? v - 70 : 100 + v - 70
// E : v <= 40 ? 60 + v :  20 + v - 40
//
// Saturation
//
// A : = this = s
// B : s
// C : s > 50 ? max(0, s - 60) : min(100, 60 + s)
// D : s < 24 ? 24 + s : 100 - s
// E : s
vector<RYBColor> RYBColor::getMonochromatic() const {
    vector<RYBColor> result;
    // result[0] = *this;
    // result[1] = RYBColor(angle, (value <= 70 ? 100 + value - 70 : value - 50), saturation);
    // result[2] = RYBColor(angle, (10 + value * 90/100), (saturation > 50 ? max(0, saturation-60) : min(100, 60+saturation)));
    // result[3] = RYBColor(angle, (value > 70 ? value - 70 : 100 + value - 70), (saturation < 24 ? 24 + saturation : 100 - saturation));
    // result[4] = RYBColor(angle, (value <= 40 ? 60 + value : 20 + value - 40), saturation);
    return result;
}

// Saturation:
//
// if saturation == 100 remove 5 to analogous saturations
// if saturation < 100 add 5 to analogous saturations
//
// Value:
//
// L1 = R2 = max(20, v <= 91 ? v+9 : v-8)
// L2 = R1 = max(20, v <= 91 ? v+5 : v + round((100-v)/2))
vector<RYBColor> RYBColor::getAnalogous(float rtotalAngle) const {
    vector<RYBColor> result;
    // float s = saturation == 1.0 ? 0.95 : saturation + 0.05;
    // float v1 = max(20, value <= 91 ? value + 9 : value - 8);
    // float v2 = max(20, value <= 91 ? value + 5 : value + round((100-v)/2));
    // result[0] = RYBColor(angle - 2*rtotalAngle/4, s, v1);
    // result[1] = RYBColor(angle -   rtotalAngle/4, s, v2);
    // result[2] = *this;
    // result[3] = RYBColor(angle +   rtotalAngle/4, s, v1);
    // result[4] = RYBColor(angle + 2*rtotalAngle/4, s, v2);
    return result;
}

vector<RYBColor> RYBColor::getTriad() const {
    vector<RYBColor> result;
    return result;
}

RYBColor RYBColor::getComplementary() const {
    RYBColor result(1,1,1);
    return result;
}

vector<RYBColor> RYBColor::getShades() const {
    vector<RYBColor> result;
    return result;
}

ofFloatColor RYBColor::toColor() const {
    ofFloatColor result = RYBWheel::pickRad(angle);
    float h,s,v;
    result.getHsb(h,s,v);
    result.setHsb(h, saturation, value);
    return result;
}
