#ifndef FLOWER_H
#define FLOWER_H

#include "ofMain.h"

class Flower {
public:
    int petalNbr;
    ofFloatColor petalColor;
    int petalSplitNbr;
    float petalSplitAngle;
    float petalWidth;
    float petalWidthPeak;
    int layerNbr;
    float layerScaleDelta;
    float layerColorDelta;
    int stamenNbr;
    float stamenSize;
    float stamenDist;
    ofFloatColor stamenColor;
    float pistilSize;
    ofFloatColor pistilColor;

    bool angular;

    Flower() : petalNbr(1), petalColor(1.0, 0.7, 0.0), petalSplitNbr(1), petalSplitAngle(0.0), petalWidth(0.5), petalWidthPeak(0.5), layerNbr(1), layerScaleDelta(0.8), layerColorDelta(0.618), stamenNbr(0), stamenSize(0), stamenDist(0.3), stamenColor(0.1, 0.0, 0.7), pistilSize(0), pistilColor(1.0, 1.0, 1.0), angular(false) {
    }

    void draw(){
        ofPushMatrix();
        for (int layer=0; layer<layerNbr; ++layer){
            ofPushMatrix();
            ofPushStyle();
            ofFloatColor layerColor = petalColor;
            float cdelta = powf(layerColorDelta, layer);
            layerColor.r *= cdelta;
            layerColor.g *= cdelta;
            layerColor.b *= cdelta;
            layerColor.a *= cdelta;
            ofRotate(layer * 360.0f / layerNbr);
            float scale = powf(layerScaleDelta, layer);
            ofScale(scale, scale);
            //if (layer > 0)
            //    ofScale(0.5f, 0.5f);
            ofFill();
            ofSetColor(layerColor);
            for (int petal=0; petal<petalNbr; ++petal){
                ofRotate(360.0f / petalNbr);
                for (int split=0; split<petalSplitNbr; ++split){
                    ofPushMatrix();
                    ofRotate(split * 360.0f * petalSplitAngle/TWO_PI);
                    if (angular){
                        // Angular star
                        ofBeginShape();
                        ofVertex(0.0, 0.0);
                        ofVertex(-petalWidth/2, petalWidthPeak);
                        ofVertex(0.0, 1.0);
                        ofVertex(petalWidth/2, petalWidthPeak);
                        ofVertex(0.0, 0.0);
                        ofEndShape();
                    }
                    else {
                        ofBeginShape();
                        ofCurveVertex(0.0, 1.0);
                        ofCurveVertex(0.0, 1.0);
                        ofCurveVertex(-petalWidth/2, petalWidthPeak);
                        ofCurveVertex(0.0, 0.0);
                        ofCurveVertex(petalWidth/2, petalWidthPeak);
                        ofCurveVertex(0.0, 1.0);
                        ofCurveVertex(0.0, 1.0);
                        ofEndShape();
                    }
                    ofPopMatrix();
                }
            }
            ofPopStyle();
            ofPopMatrix();
        }
        for (int stamen=0; stamen<stamenNbr; ++stamen){
            ofPushMatrix();
            ofRotate(stamen * 360.0f / stamenNbr);
            ofFill();
            ofSetColor(stamenColor);
            ofBeginShape();
            ofVertex(-stamenSize*0.1, 0);
            ofVertex(-stamenSize*0.1, stamenDist);
            ofVertex(stamenSize*0.1, stamenDist);
            ofVertex(stamenSize*0.1, 0);
            ofEndShape();
            ofCircle(0, stamenDist, stamenSize, stamenSize);
            ofPopMatrix();
        }
        if (pistilSize > 0){
            ofPushStyle();
            ofFill();
            ofSetColor(pistilColor);
            ofCircle(0, 0, pistilSize, pistilSize);
            ofPopStyle();
        }
        ofPopMatrix();
    }
};

#endif // FLOWER_H
