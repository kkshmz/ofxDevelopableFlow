#pragma once

#include "ofMain.h"
#include "ofxEigen.h"
#include "ofxLibigl.h"
#include "Mesh.h"
#include "Types.h"
//#include "Viewer.h"
#include "ofxDevelopableFlow.h"
#include "ofxDevelopableViewer.h"

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
//    
//    Eigen::MatrixXi intcast(const Developables::OMatrixXi& A){
//        return A;
//    }
//    
//    
//    Eigen::MatrixXd doublecast(const Developables::OMatrixXs& A)
//    {
//        return A;
//    }
    
    ofEasyCam camera;
    Developables::OMatrixXs V;
    Developables::OMatrixXi F;
    Developables::Mesh m;
    std::string path;
    ofxDevelopableViewer viewer;
//    vector<Eigen::VectorXd> lines; //plot lines
//    vector<string> titles; //plot titles
//    
//    ofMesh mesh;
		
};
