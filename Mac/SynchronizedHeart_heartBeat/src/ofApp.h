#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
  private:
    // fps�p�ϐ�
    int msec;
    // Serial class
    ofSerial serial;
    // Recieve data buffer tmp param
    int getParam;

    int deg;
    int rad;
    
    // image class
    ofImage img_body;
    ofImage img_heart;

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
