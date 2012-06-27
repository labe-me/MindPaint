#include "RYBWheel.h"

const float RYBWheel::TABLE[13][3] = {
  {1.00, 0.00, 0.00}, // 000˚ red
  {1.00, 0.45, 0.00}, // 030˚ orange + red
  {1.00, 0.67, 0.00}, // 060˚ orange
  {1.00, 0.83, 0.00}, // 090˚ yellow + orange
  {1.00, 1.00, 0.00}, // 120˚ yellow
  {0.62, 0.93, 0.00}, // 150˚ green + yellow
  {0.00, 0.80, 0.00}, // 180˚ green
  {0.00, 0.60, 0.60}, // 210˚ blue + green
  {0.07, 0.25, 0.67}, // 240˚ blue
  {0.22, 0.08, 0.69}, // 270˚ purple + blue
  {0.44, 0.04, 0.67}, // 300˚ purple
  {0.80, 0.00, 0.45}, // 330˚ purple + red
  {1.00, 0.00, 0.00}  // 360˚ red
};

inline float rotateLimit(float v, float max){
  float q = v/max;
  if (q >= 1.0)
    v = v - floor(q)*max;
  else if (q < 0.)
    v = v + ceil(abs(q))*max;
  return v;
}

ofFloatColor RYBWheel::pickDeg(float degree){
  float degreeNorm = rotateLimit(degree, 360.) / 360.;
  return pick(degreeNorm);
}

ofFloatColor RYBWheel::pickRad(float rad){
  float radNorm = rotateLimit(rad, TWO_PI) / TWO_PI;
  return pick(radNorm);
}

ofFloatColor RYBWheel::pick(float v){
    v = rotateLimit(v, 1.0);
    v *= 12;
    int lowIndex = floor(v);
    int highIndex = ceil(v);
    float ratio = v - lowIndex;
    const float* l = RYBWheel::TABLE[lowIndex];
    const float* h = RYBWheel::TABLE[highIndex];
    return ofFloatColor(
                        round(255. * (l[0] + ratio * (h[0] - l[0]))),
                        round(255. * (l[1] + ratio * (h[1] - l[1]))),
                        round(255. * (l[2] + ratio * (h[2] - l[2])))
                        );
}
