#pragma once

#include "ofxSimpleGuiToo.h"
#include "ofxThinkgear.h"

class ThinkgearEmu {
public:
    ThinkgearEmu();
    void setup();

    template<class T> void update(T& caller){
        args.poorSignal = poorSignal;
        args.attention = attention;
        args.meditation = meditation;
        args.eegDelta = eegDelta;
        args.eegTheta = eegTheta;
        args.eegLowAlpha = eegLowAlpha;
        args.eegHighAlpha = eegHighAlpha;
        args.eegLowBeta = eegLowBeta;
        args.eegHighBeta = eegHighBeta;
        args.eegLowGamma = eegLowGamma;
        args.eegMidGamma = eegMidGamma;
        caller.onThinkgearRaw(args);
        caller.onThinkgearAttention(args);
        caller.onThinkgearMeditation(args);
        caller.onThinkgearEeg(args);
        // caller.onThinkgearBlinkStrength(args);
    }

    void draw();

    inline void toggle(){
        visible = !visible;
        gui.setDraw(visible);
    }

    ofxThinkgearEventArgs args;

protected:
    bool visible;
    ofxSimpleGuiToo gui;
    int raw;
    int blinkStrength;
    int poorSignal;
    int attention;
    int meditation;
    int eegDelta;
    int eegTheta;
    int eegLowAlpha;
    int eegHighAlpha;
    int eegLowBeta;
    int eegHighBeta;
    int eegLowGamma;
    int eegMidGamma;
};
