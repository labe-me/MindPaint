#include "MindPaint.h"
#include "Brush.h"
#include "MoverController.h"
#include "Utils.h"
#include "ofFbo.h"
#include "ThinkgearEmu.h"
#include "FlowerBrush.h"
#include "RYBWheel.h"
#include "RYBColorSelector.h"

#define FPS 60

enum ThinkGearState {
    NONE,
    CONNECTING,
    BAD_SIGNAL,
    READY,
};

enum AppState {
    SELECT_BG,
    DRAW,
    PAUSE,
};

EegData eegData;
float backRybAngle = 0.0;
ofFloatColor mood;
ofFloatColor back;
ofFbo buffer;
ofTrueTypeFont smallFont;
int screenshotCount;
int brushN;
int appState;
int tgState;
int frame;
int attBonus = 0;
int attScore;
int medBonus;
int medScore;
int score;
bool useMouse = false;
MoverController* moverControl;
//Mover mover;
//vector<Mover> foes;
ThinkgearEmu tgEmu;

void setMoverController(MoverController* mc){
    if (moverControl == 0){
        moverControl = mc;
        moverControl->mover.pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        moverControl->setup();
        return;
    }
    mc->mover = moverControl->mover;
    mc->setup();
    delete moverControl;
    moverControl = mc;
}

MindPaint::~MindPaint(){
    delete brush;
}

void MindPaint::setup(){
    smallFont.loadFont("Arial.ttf", 10);
    // ofSetBackgroundAuto(false); // disable auto clear, there's a bug there
    ofBackground(230, 220, 220, 255);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetFrameRate(FPS);
    //useMouse = false;
    tgState = NONE;
    appState = SELECT_BG;
    tg.addEventListener(this);
    brush = new EllipseBrush();
    screenshotCount = 0;
    back = RYBWheel::pick(backRybAngle);
    back = ofFloatColor(250, 250, 230);
    mood = RYBWheel::pick(backRybAngle - 0.5);
    mood.a = 0.4;
    attBonus = 0;
    attScore = 0;
    medBonus = 0;
    medScore = 0;
    score = 0;
    //setMoverController(new EvadeController());
    setMoverController(new SpiralController());
    tgEmu.setup();
    Buffer::init(buffer, ofColor(220,220,220,255));
}

void MindPaint::updateFoes(){
}

void MindPaint::update(){
    ofxThinkgearEventArgs& values = (useMouse ? tgEmu.args : tg.values);
    if (false && ++frame % 60 == 0){
        cout
            << " ATT: " << (int)values.attention
            << " MED: " << (int)values.meditation
            << " POO: " << (int)values.poorSignal
            << " RAW: " << (int)values.raw
            << endl;
        if (frame == 6000)
            frame = 0;
    }
    if (useMouse)
        tgEmu.update(*this);
    else
        tg.update();
    switch (tgState){
        case NONE:
        case CONNECTING:
            if (tg.isReady || useMouse)
                tgState = READY;
            break;

        case BAD_SIGNAL:
            if (values.poorSignal == 0)
                tgState = READY;
            else {
                score = 0;
                attBonus = 0;
                attScore = 0;
                medBonus = 0;
                medScore = 0;
            }
            break;

        case READY:
            if (values.poorSignal > 0){
                tgState = BAD_SIGNAL;
                return;
            }
            switch (appState){
                case SELECT_BG:
                    // float h, s, b, cmp;
                    // back.getHsb(h,s,b);
                    // //cout << "h=" << h << " s=" << s << " b=" << b << endl;
                    // h += 0.2;
                    // b = 250.0;
                    // // b += 0.5;
                    // // if (b > 150.0)
                    // //     b = 50.0;
                    // if (h > 255.0) h=0.0;
                    // back.setHsb(h, 255.0, b, 255.0);
                    // cmp = h + 255.0/2;
                    // if (cmp > 255.0)
                    //     cmp -= 255.0;
                    // mood.setHsb(cmp, 255.0, 255.0, 0.9);
                    //backRybAngle += 0.005;
                    // back = RYBWheel::pick(backRybAngle);
                    mood = RYBWheel::pick(backRybAngle - 0.5);
                    mood.a = 0.9;
                    break;

                case PAUSE:
                    appState = DRAW;
                    break;

                case DRAW:
                    if (values.attention < 90) attBonus = 0;
                    if (values.meditation < 90) medBonus = 0;
                    attScore = values.attention + 10*(attBonus/FPS);
                    medScore = values.meditation + 10*(medBonus/FPS);
                    if (attScore > medScore){
                        score = attScore;
                        if (!dynamic_cast<RectBrush*>(brush))
                            setBrush(new RectBrush());
                    }
                    else if (medScore > attScore){
                        score = medScore;
                        if (score > 80 && !dynamic_cast<FlowerBrush*>(brush))
                            setBrush(new FlowerBrush());
                        else if (!dynamic_cast<EllipseBrush*>(brush))
                            setBrush(new EllipseBrush());

                    }
                    else {
                        score = score * 0.98;
                    }
                    updateFoes();
                    updateBrush();
                    if (values.attention > 90) attBonus = min(10*FPS, attBonus++);
                    if (values.meditation > 90) medBonus = min(10*FPS, medBonus++);
                    break;
            }
            break;
    }
}

void MindPaint::updateBrush(){
    float scoreFactor = max(0.0, min(1.0, (score/150.0))) * (1 - ofRandomuf() * 0.10);
    moverControl->update(scoreFactor);
    brush->update(mood, scoreFactor);
    brush->pos.x = moverControl->mover.pos.x;
    brush->pos.y = moverControl->mover.pos.y;
}

void MindPaint::setBrush(Brush* b){
    delete brush;
    brush = b;
}

void drawMindsetStatus(ofxThinkgearEventArgs& data){
    // ofPushStyle(); // fucking bug
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(ofGetWidth() - 100, 100);
    ofFill();
    ofSetCircleResolution(100);
    ofSetColor(0, 0, 0, 128);
    ofCircle(0, 0, 52);
    // Show connection state
    switch (tgState){
        case NONE:
            ofSetColor(0, 0, 0);
            break;
        case CONNECTING:
            ofSetColor(200, 200, 0);
            break;
        case BAD_SIGNAL:
            ofSetColor(200, 0, 0);
            break;
        case READY:
            ofSetColor(0, 200, 0);
            break;
    }
    ofRect(0, 0, 10, 10);
    if (true || tgState == READY){
        // MindSet info pad
        ofSetColor(200, 200, 200);

        float w = smallFont.stringWidth(ofToString(data.raw));
        smallFont.drawString(ofToString(data.raw), -w/2, -38);

        ofSetColor(200+55*(medScore/200), 200, 200);
        ofCircle(20, -20, min(1.0, data.meditation/100.0) * 16);

        ofSetColor(200+55*(attScore/200), 200, 200);
        ofCircle(-20, -20, min(1.0, data.attention/100.0) * 16);

        ofSetColor(200, 200, 200);
        ofRect(40-15*eegData.midGamma.ratio, 0, 30*eegData.midGamma.ratio, 10);
        ofRotate(25.7, 0, 0, 1);
        ofRect(40-15*eegData.lowGamma.ratio, 0, 30*eegData.lowGamma.ratio, 10);
        ofRotate(25.7, 0, 0, 1);
        ofRect(40-15*eegData.highBeta.ratio, 0, 30*eegData.highBeta.ratio, 10);
        ofRotate(25.7, 0, 0, 1);
        ofRect(40-15*eegData.lowBeta.ratio, 0, 30*eegData.lowBeta.ratio, 10);
        ofRotate(25.7, 0, 0, 1);
        ofRect(40-15*eegData.highAlpha.ratio, 0, 30*eegData.highAlpha.ratio, 10);
        ofRotate(25.7, 0, 0, 1);
        ofRect(40-15*eegData.lowAlpha.ratio, 0, 30*eegData.lowAlpha.ratio, 10);
        ofRotate(25.7, 0, 0, 1);
        ofRect(40-15*eegData.theta.ratio, 0, 30*eegData.theta.ratio, 10);
        ofRotate(25.7, 0, 0, 1);
        ofRect(40-15*eegData.delta.ratio, 0, 30*eegData.delta.ratio, 10);
    }
    ofPopMatrix();
    // ofPopStyle(); // fucking bug
    ofSetRectMode(OF_RECTMODE_CORNER); // fucking bug
}

void saveCapture(){
    ofPixels pixels;
    buffer.readToPixels(pixels);
    ofImage screenshot(pixels);
    //screenshot.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    // TODO: either put the saveImage action into a separated thread, change the file format for something faster or find some sort of "save a little on each frame method".
    screenshot.saveImage("screenshot-"+ofToString(screenshotCount++)+".png");
}

void MindPaint::draw(){
    // This is for debug purpose, when the headset is not available
    // usually updatebrush is called inside MindPaint::update()
    if (useMouse && tgState != READY && appState == READY){
        updateFoes();
        updateBrush();
    }

    ofBackground(0);
    switch (appState){
        case SELECT_BG:
            buffer.begin();
            ofSetColor((int)back.r, (int)back.g, (int)back.b);
            ofFill();
            ofRect(0, 0, buffer.getWidth(), buffer.getHeight());
            buffer.end();
            Buffer::draw(buffer);

            ofSetColor((int)mood.r, (int)mood.g, (int)mood.b, 255);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2, 50);
            break;

        case DRAW:
            buffer.begin();
            brush->draw();
            buffer.end();
            Buffer::draw(buffer);
            moverControl->debugDraw();
            break;

        case PAUSE:
            Buffer::draw(buffer);
            break;
    }

    drawMindsetStatus(useMouse ? tgEmu.args : tg.values);
    tgEmu.draw();
}

void MindPaint::keyPressed(int key){
}

void MindPaint::keyReleased(int key){
    if (!useMouse && tgState != READY)
        return;
    if (appState == SELECT_BG && key == ' '){
        appState = DRAW;
        return;
    }
    if (appState == SELECT_BG && key == OF_KEY_LEFT){
        backRybAngle -= 0.005;
        return;
    }
    if (appState == SELECT_BG && key == OF_KEY_RIGHT){
        backRybAngle += 0.005;
        return;
    }
    if (key == 's'){
        saveCapture();
    }
    else if (key == ' '){
        if (useMouse)
            tgEmu.toggle();
    }
    else if (key == OF_KEY_BACKSPACE){
        appState = SELECT_BG;
    }
    else if (key == 'm'){
        if (moverControl == 0)
            return;
        if (dynamic_cast<EvadeController*>(moverControl))
            setMoverController(new SpiralController());
        else if (dynamic_cast<SpiralController*>(moverControl))
            setMoverController(new WandererController());
        else if (dynamic_cast<WandererController*>(moverControl))
            setMoverController(new RectSpiralController());
        else if (dynamic_cast<RectSpiralController*>(moverControl))
            setMoverController(new EvadeController());
    }
}

void MindPaint::mouseMoved(int x, int y){
}

void MindPaint::mouseDragged(int x, int y, int button){
}

void MindPaint::mousePressed(int x, int y, int button){
    if (tgState == READY && appState == SELECT_BG)
        appState = DRAW;
}

void MindPaint::mouseReleased(int x, int y, int button){
}

void MindPaint::windowResized(int w, int h){
}

void MindPaint::gotMessage(ofMessage msg){
}

void MindPaint::dragEvent(ofDragInfo dragInfo){
}

//
// ThinkGear event listener implementation
//

void MindPaint::onThinkgearRaw(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearPower(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearPoorSignal(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearAttention(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearMeditation(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearBlinkStrength(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearEeg(ofxThinkgearEventArgs& args){
    eegData.feed(args);
}

void MindPaint::onThinkgearConnecting(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearReady(ofxThinkgearEventArgs& args){
}

void MindPaint::onThinkgearError(ofMessage& err){
}
