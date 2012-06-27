#pragma once

#include "ofxThinkgear.h"
#include "ofMain.h"
class Brush;

class MindPaint : public ofBaseApp {
public:

    ~MindPaint();
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

public:
    void onThinkgearRaw(ofxThinkgearEventArgs& args);
    void onThinkgearPower(ofxThinkgearEventArgs& args);
    void onThinkgearPoorSignal(ofxThinkgearEventArgs& args);
    void onThinkgearAttention(ofxThinkgearEventArgs& args);
    void onThinkgearMeditation(ofxThinkgearEventArgs& args);
    void onThinkgearBlinkStrength(ofxThinkgearEventArgs& args);
    void onThinkgearEeg(ofxThinkgearEventArgs& args);
    void onThinkgearConnecting(ofxThinkgearEventArgs& args);
    void onThinkgearReady(ofxThinkgearEventArgs& args);
    void onThinkgearError(ofMessage& err);

private:
    void setBrush(Brush* b);
    void updateBrush();
    void updateFoes();
    Brush* brush;
    ofxThinkgear tg;
};
