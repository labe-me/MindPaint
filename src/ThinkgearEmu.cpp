#include "ThinkgearEmu.h"

ThinkgearEmu::ThinkgearEmu() : visible(false), raw(0), blinkStrength(0), attention(0), meditation(0), eegDelta(0), eegTheta(0), eegLowAlpha(0), eegHighAlpha(0), eegLowBeta(0), eegHighBeta(0), eegLowGamma(0), eegMidGamma(0) {
}

void ThinkgearEmu::setup(){
    gui.setup();
    gui.addSlider("Poor signal", poorSignal, 0, 255);
    gui.addSlider("Attention", attention, 0, 100);
    gui.addSlider("Meditation", meditation, 0, 100);
    gui.addTitle("EEG");
    gui.addSlider("Delta", eegDelta, 0, 100000);
    gui.addSlider("Theta", eegTheta, 0, 100000);
    gui.addSlider("Low Alpha", eegLowAlpha, 0, 100000);
    gui.addSlider("High Alpha", eegHighAlpha, 0, 100000);
    gui.addSlider("Low Beta", eegLowBeta, 0, 100000);
    gui.addSlider("High Beta", eegHighBeta, 0, 100000);
    gui.addSlider("Low Gamma", eegLowGamma, 0, 100000);
    gui.addSlider("Mid Gamma", eegMidGamma, 0, 100000);
    gui.loadFromXML();
}

void ThinkgearEmu::draw(){
    gui.draw();
}

