#ifndef MindPaint_Utils_h
#define MindPaint_Utils_h

#include <ostream>
#include "ofColor.h"

class ofFbo;

class Buffer {
    public:
    static void init(ofFbo& b, const ofColor& bg = ofColor(200,200,200,255));
    static void draw(ofFbo& b, float x=0, float y=0);
};

std::ostream& operator<<(std::ostream& stream, const ofColor& c);

#endif
