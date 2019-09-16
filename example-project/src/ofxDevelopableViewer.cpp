//
//  ofxDevelopableViewer.cpp
//  example-project
//
//  Created by kkshmzMBP on 9/16/19.
//

#include "ofxDevelopableViewer.h"
ofxDevelopableViewer::ofxDevelopableViewer(){
    mesh.setMode(OF_PRIMITIVE_POINTS);
    mesh.enableColors();
    
    
    ofVec3f top(100.0, 50.0, 0.0);
    ofVec3f left(50.0, 150.0, 0.0);
    ofVec3f right(150.0, 150.0, 0.0);
    
    mesh.addVertex(top);
    mesh.addColor(ofFloatColor(1.0, 0.0, 0.0)); // Red
    
    mesh.addVertex(left);
    
    mesh.addVertex(right);

    
}



void ofxDevelopableViewer::setmesh(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F, const Eigen::MatrixXi& E){
    assert(V.cols()==3 && "Every vertex must have 3 coordinates.\n");
    m_V = V.cast<float>();
    m_V_mod = m_V;
    
    //Center and scale
    float scale = 1.;
    Eigen::Vector3f transl;
    if(V.rows() != 0) {
        Eigen::MatrixXd barycenters;
        //
        igl::barycenter(V, F, barycenters);
        Eigen::Vector3d minPoint = barycenters.colwise().minCoeff();
        Eigen::Vector3d maxPoint = barycenters.colwise().maxCoeff();
        Eigen::Vector3d center = 0.5*(minPoint + maxPoint);
        transl = -center.cast<float>();
        scale = 2. / (maxPoint-minPoint).array().abs().maxCoeff();
    }
    initialShift = Eigen::Affine3f::Identity();
    initialShift.scale(scale);
    initialShift.translate(transl);
    
    assert(F.cols()==3 && "Every face must have 3 vertices.\n");
    m_F = F.cast<GLuint>();
    m_F_mod = m_F;
    
    igl::per_face_normals(m_V, m_F_mod, m_facedVN_mod);
    igl::per_vertex_normals(m_V, m_F_mod, m_facedVN_mod, m_VN);
    m_VN_mod = m_VN;
    
    assert(E.cols()==2 && "Every edge must have 2 vertices.\n");
    m_E = E.cast<GLuint>();
    m_E_mod = m_E;
    
    cout << m_V << endl;
    meshSet = true;
    
        for(int i=0; i<m_V.rows(); i++){
             for(int j=0; j<m_V.cols(); j++){
                 mesh.addVertex(ofVec3f(m_V.coeff(i,j),m_V.coeff(i,j+1),m_V.coeff(i,j+2)));
                 
        }
    }
       
   
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_F_mod.size(), m_F_mod.data(), GL_STATIC_DRAW);
    
//        update_mesh_data(true);
//        if(defaultColorUsed) {
//            set_colors(defaultColor);
//            defaultColorUsed = true;
//        }
//        linetranspEnabled = false;
//    }
}



//
//
void ofxDevelopableViewer::setmeshCast(const Developables::OMatrixXs& V, const Developables::OMatrixXi& F, const Developables::OMatrixXi& E){
    Developables::doublecast(V);
    Developables::intcast(F);
    Developables::intcast(E);
//    cout << V << endl;
    setmesh(V,F,E);
}

//void ofxDevelopableViewer::updatemeshdata(){
//
//}
//
void ofxDevelopableViewer::draw(){
    
//    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);

//    mesh.drawVertices();
    
    mesh.draw();
}

void ofxDevelopableViewer::modify_V(const Eigen::MatrixXd& V)
{
    m_V_mod = V.cast<float>();
    igl::per_face_normals(m_V_mod, m_F_mod, m_facedVN_mod);
    igl::per_vertex_normals(m_V_mod, m_F_mod, m_facedVN_mod, m_VN_mod);
//    update_mesh_data(false);
//
//    if(defaultColorUsed) {
//        set_colors(defaultColor);
//        defaultColorUsed = true;
//    }
}
