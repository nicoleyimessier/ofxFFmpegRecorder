#pragma once
#include "ofMain.h"
#include "ofxFFmpegRecorder.h"
#include "ofVideoGrabber.h"

class ofApp : public ofBaseApp{ 
public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);

    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
	
private:
    ofxFFmpegRecorder m_Recorder;
    ofVideoGrabber m_Grabber;
    
    ofFbo mCapFbo;
    ofPixels mPix;

	int width = 1920;
	int height = 1080;

	bool useGrabber = true;
};
