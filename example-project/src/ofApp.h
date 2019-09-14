#pragma once

#include "ofMain.h"
#include "ofxDevelopableFlow.h"
#include "ofxEigen.h"
#include "ofxLibigl.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void keyPressed(int key);
		void keyPressed(int key, int scancode, int action, int modifier);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector<Eigen::VectorXd> lines; //plot lines
    vector<string> titles; //plot titles
    
    ofMesh mesh;
		
};
