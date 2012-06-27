#include "FlowerBrush.h"

FlowerBrush::FlowerBrush() : stamp(0), delay(300) {

}

const char* FlowerBrush::getName() const {
    return "FlowerBrush";
}

void FlowerBrush::update(const ofFloatColor& mood, const float score){
    Brush::update(mood, score);
    flower.petalNbr = ofRandom(3, 20);
    flower.petalColor = mood;
    flower.petalSplitAngle = ofRandom(0.01, 0.05);
    flower.petalSplitNbr = ofRandom(0, 3);
    flower.petalWidth = ofRandom(0.1, 1.0);
    flower.petalWidthPeak = ofRandom(0.1, 1.5);
    flower.layerNbr = ofRandom(1, 10);
    flower.layerColorDelta = ofRandom(0.3, 1.7);
    flower.layerScaleDelta = ofRandom(0.3, 1.2);
    flower.stamenNbr = ofRandom(0, 16);
    flower.stamenSize = ofRandom(0.05, 0.1);
    flower.stamenDist = ofRandom(0.05, 0.4);
    flower.stamenColor = mood;
    flower.stamenColor *= 0.6;
    flower.pistilSize = ofRandom(0.05, 0.2);
    flower.pistilColor = mood;
    flower.pistilColor *= 0.5;
}

void FlowerBrush::draw(){
    unsigned long now = ofGetSystemTime();
    if (stamp + delay > now)
        return;
    stamp = now;
    ofPushStyle();
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofTranslate(pos);
    ofRotate(ofRadToDeg(rotate));
    ofScale(scaleX*5.0, scaleY*5.0);
    flower.draw();
    ofDisableBlendMode();
    ofPopMatrix();
    ofPopStyle();
}
