#include "Brush.h"
#include "Tweener.h"

BrushTweener::BrushTweener(Brush& b) :
    scaleX(&b.scaleX),
    scaleY(&b.scaleY),
    colorR(&b.color.r),
    colorG(&b.color.g),
    colorB(&b.color.b),
    colorA(&b.color.a),
    posX(&b.pos.x),
    posY(&b.pos.y),
    rotate(&b.rotate) {
}

void BrushTweener::update(unsigned long time){
    scaleX.update(time);
    scaleY.update(time);
    colorR.update(time);
    colorG.update(time);
    colorB.update(time);
    colorA.update(time);
    posX.update(time);
    posY.update(time);
    rotate.update(time);
}

void startBlending(){
    // BlendMode ADD gives some cool results
    // ofEnableBlendMode(OF_BLENDMODE_ADD);
    // BlendMode ALPHA produces regular expected results, a little bit sad
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    // ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    //ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
}

void endBlending(){
    ofDisableBlendMode();
}

const char* Brush::getName() const {
    return "Brush";
}

void Brush::update(const ofFloatColor& mood, const float score){
    unsigned long now = ofGetSystemTime();
    float duration = initialized ? 1000.0 : 0.0;
    tweener.scaleX.set(score * 5.0, duration, now, Tweener::linear);
    tweener.scaleY.set(score * 5.0, duration, now, Tweener::linear);
    tweener.rotate.set(ofRandomuf() * 2 * PI, duration, now, Tweener::linear);
    tweener.colorR.set(mood.r, duration, now, Tweener::linear);
    tweener.colorB.set(mood.g, duration, now, Tweener::linear);
    tweener.colorB.set(mood.b, duration, now, Tweener::linear);
    tweener.colorA.set(255.0 * score * mood.a, duration, now, Tweener::linear);
    tweener.update(now);

    if (!initialized)
        initialized = true;
}

void Brush::draw(){
    cout << "ERR virtual draw is called" << endl;
}

// --- EllipseBrush implementation ---

const char* EllipseBrush::getName() const {
    return "EllipseBrush";
}

void EllipseBrush::draw(){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(pos);
    ofRotate(ofRadToDeg(rotate));
    ofFill();
    ofSetColor((int)color.r, (int)color.g, (int)color.b, (int)color.a);
    startBlending();
    ofEllipse(0, 0, 10*scaleX/2, 10*scaleY/2);
    endBlending();
    ofPopMatrix();
    ofPopStyle();
}

void EllipseBrush::update(const ofFloatColor& mood, const float score){
    Brush::update(mood, score);
}

// --- RectBrush implementation ---

const char* RectBrush::getName() const {
    return "RectBrush";
}

void RectBrush::draw(){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(pos);
    ofRotate(ofRadToDeg(rotate));
    ofFill();
    ofSetColor((int)color.r, (int)color.g, (int)color.b, (int)color.a);
    startBlending();
    float w = 10*scaleX/2;
    float h = 10*scaleY/2;
    ofRect(-w/2, -h/2, w, h);
    endBlending();
    ofPopMatrix();
    ofPopStyle();
}

void RectBrush::update(const ofFloatColor &mood, const float score){
    Brush::update(mood, score);
}
