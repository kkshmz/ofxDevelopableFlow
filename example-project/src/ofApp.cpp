#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
// init parallel computing
//    Eigen::initParallel();
//// init precision type of eigen
//    types_startup();
//    
    //read in the mesh
 
    path = "/Users/kkshmzmbp/Documents/of_v0.10.0_osx_release/addons/ofxDevelopableFlow/example-project/bin/data/sphere.obj";
//
    igl::read_triangle_mesh(path, V, F);
    m = Developables::Mesh(V,F);
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);

    ofBackground(255);
    ofSetColor(0);
//    viewer = Developables::Oviewer;
//    
//    viewer.set_mesh
    viewer.setmeshCast(m.V,m.F,m.E);

//    viewer.setmeshcast(doublecast(m.V), intcast(m.F), intcast(m.E));
//    viewer.set_plotting_enabled(true);
//    viewer.set_plots(titles, lines);
//    viewer.set_face_based_coloring(true);
//    viewer.predraw_callback = predraw_callback;
//    viewer.keyboard_callback = keyboard_callback;
//    
//    viewer.launch();
//    viewer.draw();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//    camera.begin();
    
    viewer.draw();
//    camera.end();
//    mesh.drawFaces();
//    viewer.draw();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
