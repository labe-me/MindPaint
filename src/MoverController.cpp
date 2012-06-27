#include "MoverController.h"
#include "ofMain.h"

MoverController::MoverController(){
}

//
// Wanderer implementation
//

void WandererController::setup(){
    mover.maxSpeed = 4.0;
    mover.maxSteeringForce = 5.0;
}

void WandererController::update(float scoreFactor){
    mover.maxSpeed = 4.0 + scoreFactor * 4.0;
    mover.maxSteeringForce = 10.0 + 5.0 * scoreFactor;
    mover.acc.set(0,0,0);
    mover.wander();
    mover.update();
    mover.teleportOffscreenKeepDelta(ofGetWidth(), ofGetHeight());
}

void WandererController::debugDraw(){
}

//
// EvadeController implementation
//

void EvadeController::setup(){
    foes.empty();
    int nFoes = ofRandom(4, 10);
    for (int i=0; i<nFoes; ++i){
        Mover foe;
        foe.pos.set(ofRandom(ofGetWidth()*0.3), ofRandom(ofGetHeight()));
        foe.maxSpeed = 1.0;
        foes.push_back(foe);
    }
    // mover.pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    mover.maxSpeed = 4.0;
    mover.maxSteeringForce = 5.0;
}

void EvadeController::update(float scoreFactor){
    for (vector<Mover>::iterator i = foes.begin(); i != foes.end(); ++i){
        (*i).wander();
        (*i).update();
        (*i).teleportOffscreen(10, ofGetWidth(), ofGetHeight());
    }
    mover.maxSpeed = 4.0 + scoreFactor * 4.0;
    mover.maxSteeringForce = 10.0 + 5.0 * scoreFactor;
    mover.acc.set(0,0,0);
    mover.wander();
    for (vector<Mover>::iterator i = foes.begin(); i != foes.end(); ++i){
        mover.evade(*i);
    }
    mover.update();
    mover.teleportOffscreen(0, ofGetWidth(), ofGetHeight());
}

void EvadeController::debugDraw(){
    for (vector<Mover>::iterator i = foes.begin(); i != foes.end(); ++i){
        ofSetColor(200, 0, 0);
        ofEllipse(i->pos.x, i->pos.y, 5, 5);
    }
}

//
// SpiralController implementation
//

void SpiralController::setup(){
    center = mover.pos;
    float direction = ofRandomuf() >= 0.5f ? 1 : - 1;
    rotation = ofRandomuf() * PI * 2;
    scaleFactor = 1.618 * 3;
    angle = 0.5f * direction;
    speed = 0.5f * direction;
}

void SpiralController::update(float scoreFactor){
    float t = angle;
    mover.pos.x = center.x + cos(t) * scaleFactor * t;
    mover.pos.y = center.y + sin(t) * scaleFactor * t;
    mover.teleportOffscreenKeepDelta(ofGetWidth(), ofGetHeight());
    float sm = (0.7 + scaleFactor * 0.3);
    if (fabs(angle) > 1.0f)
        angle += (speed + sm * speed) * PI / (fabs(angle) * scaleFactor);
    else
        angle += (speed + sm * speed) * (0.7 + scoreFactor * 0.3);
}

void SpiralController::debugDraw(){
    ofPushStyle();
    ofSetHexColor(0xFFAAAA);
    ofFill();
    ofCircle(center.x, center.y, 1);
    ofPopStyle();
}

//
// RectSpiralController implementation
//

void RectSpiralController::setup(){
    segCount = 0;
    scaleFactor = 1.618 * 10;
    segStart.set(mover.pos);
    cursor.set(mover.pos);
    rotation = ofRandomuf() * PI * 2;
    segLength = 1.0;
    segEnd = ofPoint(segLength*scaleFactor, 0);
    segEnd.rotateRad(0, 0, rotation);
    segEnd += segStart;
    mover.maxSpeed = 4.0;
    mover.maxSteeringForce = 40.0;
}

void RectSpiralController::update(float scoreFactor){
    mover.maxSpeed = 4.0;
    mover.maxSteeringForce = mover.maxSpeed;
    mover.pos.set(cursor);
    mover.arrive(segEnd);
    mover.update();
    if (mover.pos.distance(segEnd) <= mover.maxSpeed/2){
        // next seg
        if (++segCount % 2 == 0)
            ++segLength;
        float angle = segEnd.angle(segStart) + 90.0;
        angle = atan2(
                      segStart.y - segEnd.y,
                      segStart.x - segEnd.x
                      );
        angle += PI/2;
        ofPoint t = ofPoint(segLength*scaleFactor, 0);
        t.rotateRad(0.0, 0.0, angle);
        segStart.set(segEnd);
        segEnd += t;
    }
    else {
    }
    cursor.set(mover.pos);
    mover.teleportOffscreenKeepDelta(ofGetWidth(), ofGetHeight());
}

void RectSpiralController::debugDraw(){
    ofPushStyle();
    ofFill();
    ofSetHexColor(0x000000);
    ofCircle(segStart, 5);
    ofSetHexColor(0x0000ff);
    ofCircle(segEnd, 5);
    ofPopStyle();
}
