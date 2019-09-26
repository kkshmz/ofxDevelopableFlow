//
//  ofxDevelopableMesh.hpp
//  example-project
//
//  Created by kkshmzMBP on 9/18/19.
//

#ifndef ofxDevelopableMesh_hpp
#define ofxDevelopableMesh_hpp
#pragma once

#include <vector>
#include <list>
#include "ofxDevelopableTypes.h"
#include "ofMain.h"

#include <igl/all_edges.h>
#include <igl/triangle_triangle_adjacency.h>
#include <igl/vertex_triangle_adjacency.h>
#include <igl/unique_simplices.h>
#include <igl/is_border_vertex.h>
#include "ofxDevelopableReader.h"

class ofxDevelopableMesh{
public:
    ofMesh mesh;
    OMatrixXs origV;
    OMatrixXi origF;
    OMatrixXs V;
    OMatrixXi F;
    std::vector<std::vector<float> > tempV;
    std::vector<std::vector<float> > tempF;
    OMatrixXi allE;
    OMatrixXi E;
    OMatrixXi edgesA;
    OMatrixXi edgesC;
    OMatrixXi TT; //triangle-triangle adjacency
    OMatrixXi TTi; //triangle-triangle adjacencyi
    std::vector<std::vector<typename OMatrixXi::Scalar> > VF; //vertex-triangle adjacency
    std::vector<std::vector<typename OMatrixXi::Scalar> > VFi; //vertex-triangle adjacencyi
    std::vector<bool> isB; //is border vertex
    ofxDevelopableMesh();
    ofxDevelopableMesh(const OMatrixXs& iV, const OMatrixXi& iF);
    ofxDevelopableMesh(const char *fileName);
    void update();
    
    void draw(ofPolyRenderMode renderType);
    void drawWireframe();
    void drawFaces();
    void save();
    
    //using reader
    void loadModel(const char *fileName);
//     Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> m_V, m_V_mod, m_VN, m_VN_mod, m_facedVN_mod, m_amb, m_spec, m_dif;
//    Eigen::Matrix<GLuint, Eigen::Dynamic, 3, Eigen::RowMajor> m_F, m_F_mod;
//    Eigen::Matrix<GLuint, Eigen::Dynamic, 2, Eigen::RowMajor> m_E, m_E_mod;
    void set_mesh(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F, const Eigen::MatrixXi& E);
    bool launched;
    
    
    //modified mesh
    ofMesh m_mesh;
//    OMatrixXs m_V, m_origV, m_VN, m_VN_mod, m_facedVN_mod;
//    OMatrixXi m_F, m_origF;
    void predrawcallback();
    
private:
};




#endif /* ofxDevelopableMesh_hpp */
