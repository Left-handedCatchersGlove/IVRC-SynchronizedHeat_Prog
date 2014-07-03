#include "ofApp.h"

// Graph window
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

// FPS parameter
#define FPS 60

// Graph width
#define GRAPH_WIDTH 2

#define AMP 2

// Serial data buf size
#define BUFSIZE (WINDOW_WIDTH / GRAPH_WIDTH)

// Debug macros
#define FPS_DBG if(debug_fps)
#define SERIAL_DBG if(debug_serial)

static const bool debug_fps = false;
static const bool debug_serial = true;

//--------------------------------------------------------------
void ofApp::setup(){
  /*---- Window setting ----*/
  // Window shape
  ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
  // Frame rate(aim default 60fps)
	ofSetFrameRate(60);
  // Background color
  ofBackground(255, 255, 255);
  // Window title
	ofSetWindowTitle("MAIN WINDOW");
  
  /*---- Image ----*/
  heart_img.loadImage("heart.jpg");
  
  /*---- Serial ----*/
  serial.enumerateDevices();
  serial.setup("/dev/cu.usbmodem1421", 9600);
  
  /*---- buffer ----*/
  datBuf = new int[BUFSIZE];
  tmp = new int[BUFSIZE];
  
	ofxFensterManager::get()->setupWindow(&window);
}

//--------------------------------------------------------------
void ofApp::update(){
  SERIAL_DBG {
    if( getParam > 0 )
      printf("%d\n", getParam);
  }
  
  // Local loop param
  int i = 0;
  // switch buffer
  for( i = 1; i < BUFSIZE; i++ ) {
    datBuf[BUFSIZE - i] = datBuf[BUFSIZE - i - 1];
  }
  
  // Arduino get recieve
  getParam = serial.readByte();
  // Renew first buffer
  if( getParam > 0 ) datBuf[0] = getParam;
  
  for( i = 0; i < BUFSIZE-1; i++ ) {
    tmp[i] = datBuf[i] - datBuf[i+1];
  }
  
  // Write another window parameter
  window.getParam = &getParam;
}

//--------------------------------------------------------------
void ofApp::draw(){
  FPS_DBG {
    // FPS
    int msecNow = ofGetElapsedTimeMillis();
    float fps = 1000.0 / (msecNow - msec);
    msec = msecNow;
    ofSetColor(0, 255, 0);
    char buf[50];
    
    // FPS show
    sprintf(buf, "%5.2f fps", fps);
    ofDrawBitmapString(buf, 20, 20);
    
    // Set white
    ofSetColor(255, 255, 255);
  }
  // Set white
  ofSetColor(255, 255, 255);
  
  // Base point change
  // Top 360
  ofTranslate(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3);
  // y rotate
  ofScale(1, -1);
  
  // Background Image draw
  heart_img.draw(-(heart_img.getHeight() / 2), (heart_img.getHeight() / 2) + WINDOW_HEIGHT / 4, heart_img.getWidth(), -heart_img.getHeight());
  
  // Base Line
  ofSetColor(255, 0, 0);
  ofLine(-320, 0, 320, 0);
  
  ofSetColor(0, 0, 255);
  // Loop param
  int i = 0;
  // Buffer num tmp
  int tmpNum = 0;
  // Pre base point
  int preX = -320, preY = 0;
  // Draw graph
  for( i = -(WINDOW_WIDTH / 2); i < (WINDOW_WIDTH / 2); i+=GRAPH_WIDTH )
  {
    /*
    // Draw line
    if( tmp[tmpNum] > 1 )
    {
      ofLine(preX, preY, i, datBuf[tmpNum] * AMP);
      preY = datBuf[tmpNum] * AMP;
    }
    else
    {
      ofLine(preX, preY, i, datBuf[tmpNum]);
      preY = datBuf[tmpNum];
    }*/
    
    ofLine(preX, preY, i, datBuf[tmpNum]);
    preY = datBuf[tmpNum];
    preX = i;
    tmpNum++;
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
