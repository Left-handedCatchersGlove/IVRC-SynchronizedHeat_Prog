#include "ofApp.h"

// Current window size
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

// FPS parameter
#define FPS 60

// Serial data buf size
#define BUFSIZE (WINDOW_WIDTH / 2)

// Debug macros
#define FPS_DBG if(debug_fps)
#define SERIAL_DBG if(debug_serial)

static const bool debug_fps = true;
static const bool debug_serial = false;

//--------------------------------------------------------------
void ofApp::setup(){
  // Window shape
  ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
  // Frame rate(aim default 60fps)
  ofSetFrameRate(FPS);
  // Background color
  ofBackground(255, 255, 255);

  /*---- Image ----*/
  heart_img.loadImage("heart.jpg");

  /*---- Serial ----*/
  serial.enumerateDevices();
  serial.setup("COM19", 9600);
  
  /*---- buffer ----*/
  datBuf = new int[BUFSIZE];
}

//--------------------------------------------------------------
void ofApp::update(){
  SERIAL_DBG {
    getParam = serial.readByte();
    printf("%d\n", getParam);
  }
  // Local loop param
  int i = 0;
  // buffer offset
  for( i = 1; i < BUFSIZE; i++ ) {
    datBuf[BUFSIZE - i] = datBuf[BUFSIZE - i - 1];
  }
  getParam = serial.readByte();
  datBuf[0] = getParam;
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

    // FPS•\Ž¦
    sprintf(buf, "%5.2f fps", fps);
    ofDrawBitmapString(buf, 20, 20);

    // F‚ð–ß‚µ‚Ä‚¨‚­
    ofSetColor(255, 255, 255);
  }

  // À•WŒn‚ðÄÝ’è
  // Top 360
  ofTranslate(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3);
  // À•WŒn‚ð”½“]
  ofScale(1, -1);

  // Background Image draw
  //heart_img.draw(-175, 274, 350, -309);
  heart_img.draw(-(heart_img.getHeight() / 2), (heart_img.getHeight() / 2) + WINDOW_HEIGHT / 4,
    heart_img.getWidth(), -heart_img.getHeight());

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
  for( i = -BUFSIZE; i < BUFSIZE; i+=2 )
  {
    // Draw line
    ofLine(preX, preY, i, datBuf[tmpNum]);
    preX = i;
    preY = datBuf[tmpNum];
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
void ofApp::mouseMoved(int x, int y){

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