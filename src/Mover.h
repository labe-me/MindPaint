#ifndef MindPaint_Mover_h
#define MindPaint_Mover_h

#include "ofPoint.h"

class Mover {
public:
    ofPoint pos;
    ofPoint acc;
    ofPoint vel;
    float maxSpeed;

    Mover();
    void update();
    void seek(const ofPoint& p);
    void arrive(const ofPoint& p);
    void wander();
    void pursuit(const Mover& o);
    void evade(const Mover& o);

    ofPoint predictFuturePosition(const float t) const;

    // Teleport the mover if outside boundaries
    void teleportOffscreen(float r, float w, float h);
    void teleportOffscreenKeepDelta(float w, float h);

    // Boids behaviours
    float maxSteeringForce;
    float wanderTheta;

    Mover& operator=(const Mover&);


private:
    ofPoint computeSteering(const ofPoint& target, const bool slowDown) const;
    ofPoint computeFleeSteering(const ofPoint& target) const;

    ofPoint computePursuitSteering(const Mover& mover, const float maxPredictionTime) const;
    ofPoint computeEvadeSteering(const Mover& mover, const float maxPredictionTime) const;
};

#endif
