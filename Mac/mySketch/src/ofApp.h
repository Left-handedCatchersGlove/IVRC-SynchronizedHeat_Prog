#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"

class CustomWindow : public ofxFenster{
  // Current window size
  #define WINDOW_WIDTH  640
  #define WINDOW_HEIGHT 480
  
  // Serial data buf size
  #define BUFSIZE (WINDOW_WIDTH / 2)

  int rad;
  int preGetParam;
  
  // image class
  ofImage img_body;
  ofImage img_heart;
  
public:
  int * getParam;
  
	void setup(){
    // Window size
		setWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
		setWindowTitle("Heart Beat");
    
    /*---- Image ----*/
    img_body.loadImage("body.jpg");
    img_heart.loadImage("half-heart.jpg");
	}

	void update(){
    
    if( *getParam > 0 )
      rad = *(getParam) * PI / 180;
	}

	void draw(){
    // Set white color
    ofSetColor(255, 255, 255);
    
    // Base Line set
    // Top 360
    ofTranslate(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    // Y roteta
    ofScale(1, -1);
    
    // body img draw
    img_body.draw(-(img_body.getWidth() / 2), (img_body.getHeight() / 2),
                  img_body.getWidth(), -img_body.getHeight());
    
    // Set alpha
    float alpha = 100 * (0.25 * sin(rad) + 0.75);
    // Color set and alpha
    ofSetColor(255, 255, 255, alpha);
    // heart image draw
    img_heart.draw(-(img_heart.getWidth() / 2), (img_heart.getHeight() / 2),
                   img_heart.getWidth() + alpha, -img_heart.getHeight() - alpha);
	}
};

class ofApp : public ofBaseApp{
private:
  // fps param
  int msec;
  // Serial class
  ofSerial serial;
  // All data buffer
  int * datBuf;
  // temp buf
  int * tmp;
  
  // Image class
  ofImage heart_img;
  // Recieve param
  int getParam;

public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  
  CustomWindow window;
};