#include "Utils.h"
#include "ofFbo.h"
#include "ofMain.h"

// std::ostream& operator<<( std::ostream& stream, const ofColor& c){
//     stream << "rgba(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
//     return stream;
// }

void Buffer::init(ofFbo &b, const ofColor &bg){
    b.allocate();
    b.begin();
    ofFill();
    ofSetColor(bg);
    ofRect(0, 0, b.getWidth(), b.getHeight());
    b.end();
}

void Buffer::draw(ofFbo& b, float x, float y){
    ofPushStyle();
    ofSetColor(255, 255, 255);
    b.draw(x, y);
    ofPopStyle();
}
