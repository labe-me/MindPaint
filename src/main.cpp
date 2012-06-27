#include "ofMain.h"
#include "MindPaint.h"
#include "ofAppGlutWindow.h"

int main(int argc, char** argv){
    ofAppGlutWindow window;
    // OF_FULLSCREEN or OF_WINDOW
    //ofSetupOpenGL(&window, 1440, 900, OF_FULLSCREEN);
    ofSetupOpenGL(&window, 1280, 800, OF_WINDOW);
    ofRunApp(new MindPaint());
}
