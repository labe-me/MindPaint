#include "Mover.h"
#include "ofMain.h"

inline int intervalCompare(float v, float lower, float high){
    if (v < lower) return -1;
    if (v > high) return 1;
    return 0;
}

Mover::Mover(){
    maxSpeed = 4.0;
    maxSteeringForce = 2.0;
    wanderTheta = 0.0;
}

void Mover::update(){
    vel += acc;
    vel.limit(maxSpeed);
    pos += vel;
}

void Mover::seek(const ofPoint& p){
    acc += computeSteering(p, false);
}

void Mover::arrive(const ofPoint& p){
    acc += computeSteering(p, true);
}

void Mover::wander(){
    float wRadius = 16.0;
    float wDistance = 60.0;
    float change = 0.25;
    wanderTheta += ofRandom(-change, change);
    ofPoint c = vel;
    c.normalize();
    c *= wDistance;
    c += pos;
    ofPoint coff(wRadius*cos(wanderTheta), wRadius*sin(wanderTheta));
    c += coff;
    acc += computeSteering(c, false);
}

ofPoint Mover::predictFuturePosition(const float t) const {
    return pos + (vel * t);
}

void Mover::pursuit(const Mover& o){
    acc += computePursuitSteering(o, 4.0);
}

void Mover::evade(const Mover& o){
    float dist = (o.pos - pos).length();
    float factor = 1 - (dist / 50);
    if (factor <= 0)
        return;
    if (factor > 1)
        factor = 1;
    acc += computeEvadeSteering(o, maxSteeringForce*factor);
}

ofPoint Mover::computeSteering(const ofPoint &target, bool slowDown) const {
    ofPoint result;
    ofPoint desired = target - pos;
    float d = desired.length();
    if (d > 0){
        desired.normalize();
        if (slowDown && d < 100.0)
            desired *= maxSpeed * (d/100.0);
        else
            desired *= maxSpeed;
        result = desired - vel;
        result.limit(maxSteeringForce);
    }
    return result;
}

ofPoint Mover::computeFleeSteering(const ofPoint &target) const {
    return (pos - target) - vel;
}

ofPoint Mover::computePursuitSteering(const Mover &mover, const float maxPredictionTime) const {
    ofPoint offset = mover.pos - pos;
    float dist = offset.length();
    float parallelness = vel.normalized().dot(mover.vel.normalized());
    float quaryForwardness = vel.normalized().dot(offset.normalized());
    float directTravelTime = vel.normalized().dot(offset.normalized());
    int f = intervalCompare(quaryForwardness, -0.707, 0.707);
    int p = intervalCompare(parallelness, -0.707, 0.707);
    float timeFactor = 0;
    switch (f) {
        case 1:
            switch (p) {
                case 1: // ahead, parallel
                    timeFactor = 4;
                    break;
                case 0: // ahead, perpendicular
                    timeFactor = 1.8;
                    break;
                case -1: // ahead, anti-parallel
                    timeFactor = 0.85;
                    break;
            }
            break;
        case 0:
            switch (p){
                case 1: // aside, parallel
                    timeFactor = 1;
                    break;
                case 0: // aside, perpendicular
                    timeFactor = 0.8;
                    break;
                case -1: // aside, anti-parallel
                    timeFactor = 4;
                    break;
            }
        case -1:
            switch (p){
                case 1: // behind, parallel
                    timeFactor = 0.5;
                    break;
                case 0: // behind, perpendicular
                    timeFactor = 2;
                    break;
                case -1: // behind, anti-parallel
                    timeFactor = 2;
                    break;
            }
    }
    float et = directTravelTime * timeFactor;
    float etl = (et > maxPredictionTime) ? maxPredictionTime : et;
    ofPoint target = mover.predictFuturePosition(etl);
    return computeSteering(target, false);
}

ofPoint Mover::computeEvadeSteering(const Mover &mover, const float maxPredictionTime) const {
    ofPoint offset = mover.pos - pos;
    float dist = offset.length();
    float dangerSpeed = mover.vel.length();
    if (dangerSpeed == 0.0f)
        dangerSpeed = 1.0f;
    float time = dist / dangerSpeed;
    if (time > maxPredictionTime)
        time = maxPredictionTime;
    ofPoint target = mover.predictFuturePosition(time);
    return computeFleeSteering(target);
}

void Mover::teleportOffscreen(float r, float w, float h){
    if (pos.x < -r) pos.x = w + r;
    if (pos.x > w + r) pos.x = -r;
    if (pos.y < -r) pos.y = h+ r;
    if (pos.y > h+ r) pos.y = -r;
}

void Mover::teleportOffscreenKeepDelta(float w, float h){
    if (pos.x >= 0.0f && pos.x <= w && pos.y >= 0.0f && pos.y <= h)
        return;
    int ww = (int)w;
    int hh = (int)h;
    int px = (int)pos.x;
    int py = (int)pos.y;
    pos.x = (pos.x - px) + (px % ww);
    pos.y = (pos.y - py) + (py % hh);
    if (pos.x < 0.0f)
        pos.x = (pos.x - px) + w + (px % ww);
    if (pos.y < 0.0f)
        pos.y = (pos.y - py) + h + (py % hh);
}

Mover& Mover::operator=(const Mover& other){
    pos = other.pos;
    acc = other.acc;
    vel = other.vel;
    maxSpeed = other.maxSpeed;
    maxSteeringForce = other.maxSteeringForce;
    wanderTheta = other.wanderTheta;
    return *this;
}
