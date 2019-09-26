//
//  ofxDevelopableMesh.cpp
//  example-project
//
//  Created by kkshmzMBP on 9/18/19.
//

#include "ofxDevelopableMesh.h"
ofxDevelopableMesh::ofxDevelopableMesh(){
   
}
ofxDevelopableMesh::ofxDevelopableMesh(const OMatrixXs& iV, const OMatrixXi& iF){
    //typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> OMatrixXs;
    //  OMatrixXs V;
    V = iV;
    F = iF;
    origV = iV;
    origF = iF;
    update();
}
ofxDevelopableMesh::ofxDevelopableMesh(const char *fileName){
    
    
}

void ofxDevelopableMesh::update()
{
    igl::all_edges(F, allE);
    igl::unique_simplices(allE, E, edgesA, edgesC);
    igl::triangle_triangle_adjacency(F, TT, TTi);
    isB = igl::is_border_vertex(V, F);
    
    //Build sorted vertex triangle adjacency matrix
    igl::vertex_triangle_adjacency(V.rows(), F, VF, VFi);
    for(int i=0; i<VF.size(); ++i) {
        if(isB[i])
            continue;
        
        std::vector<typename OMatrixXi::Scalar>& newVF = VF[i];
        std::vector<typename OMatrixXi::Scalar>& newVFi = VFi[i];
        
        //We keep the first face intact, then we rotate over the others
        for(int ind=1; ind < newVF.size(); ++ind) {
            int nextface = TT(newVF[ind-1], (newVFi[ind-1]+2)%3);
            newVF[ind] = nextface;
            for(int j=0; j<3; ++j) {
                if(F(nextface,j)==i) {
                    newVFi[ind] = j;
                    break;
                }
            }
            
        }
        
    }
    
    //Redo isB
    //for(int i=0; i<V.rows(); ++i) {
    //    if(i!=230)
    //        isB[i]=true;
    //}
}
void ofxDevelopableMesh::draw(ofPolyRenderMode renderType){
    switch(renderType){
        case OF_MESH_POINTS:
            std::cout << "points" << endl;
            break;
        case OF_MESH_WIREFRAME:
            //note this won't look the same as on non ES renderers.
            //there is no easy way to convert GL_TRIANGLES to outlines for each triangle
            std::cout << "wire" << endl;
            break;
    
        case OF_MESH_FILL:
            std::cout << "fill" << endl;
            break;
    }
}

void ofxDevelopableMesh::drawWireframe(){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.drawWireframe();
}
void ofxDevelopableMesh::drawFaces(){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.draw(OF_MESH_FILL);
}
void ofxDevelopableMesh::save(){
    ofxDevelopableReader reader;
    reader.exportOBJ(mesh, "hey.obj");
 
}


void ofxDevelopableMesh::loadModel(const char *fileName){
    ofxDevelopableReader reader;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    string modelpath = ofToDataPath(fileName);
    igl::read_triangle_mesh(modelpath,V,F);
    igl::read_triangle_mesh(modelpath,tempV,tempF);

    for(auto & v : tempV){
        for (int i=0; i<1; i++){
            ofVec3f temp(v.at(i),v.at(i+1),v.at(i+2));
            mesh.addVertex(glm::vec3(v.at(i),v.at(i+1),v.at(i+2)));
            m_mesh.addVertex(glm::vec3(v.at(i),v.at(i+1),v.at(i+2)));
 
        }
    }
    for(auto & v : tempF){
        for (int i=0; i<1; i++){
            ofVec3f temp(v.at(i),v.at(i+1),v.at(i+2));
            mesh.addIndex(v.at(i));
            mesh.addIndex(v.at(i+1));
            mesh.addIndex(v.at(i+2));
            m_mesh.addIndex(v.at(i));
            m_mesh.addIndex(v.at(i+1));
            m_mesh.addIndex(v.at(i+2));
        }
    }
    //same as constructor
    origV = V;
    origF = F;
    
    //for modified
//    m_V = V;
//    m_F = F;
//    
//    m_origV = V;
//    m_origF = F;
   
    
    update();
}



void ofxDevelopableMesh::predrawcallback(){
//    //this is predraw callback
//    //Callback, called once per frame. The bool signifies if any modification to the mesh is happening.
//    if(meshChanged) {
//        
//        Eigen::MatrixXd V = doublecast(dmesh.V);
//        Eigen::MatrixXi F = intcast(dmesh.F);
//        Eigen::MatrixXi E = intcast(dmesh.E);
//        
//        //what to do about this
//        //        viewer.set_mesh(V, F, E);
//        
//        //inside set_mesh
//        assert(V.cols()==3 && "Every vertex must have 3 coordinates.\n");
//        m_V = d
//        m_V_mod = m_V;
//        
//        //
//        assert(F.cols()==3 && "Every face must have 3 vertices.\n");
//        m_F = F.cast<GLuint>();
//        m_F_mod = m_F;
//        //
//        igl::per_face_normals(m_V, m_F_mod, m_facedVN_mod);
//        igl::per_vertex_normals(m_V, m_F_mod, m_facedVN_mod, m_VN);
//        m_VN_mod = m_VN;
//        //
//        assert(E.cols()==2 && "Every edge must have 2 vertices.\n");
//        //        m_E = E.cast<GLuint>();
//        //        m_E_mod = m_E;
//        
//        
//        meshChanged = false;
//    }
//    if(meshPosChanged) {
//        
//        Eigen::MatrixXd V = doublecast(dmesh.V);
//        Eigen::MatrixXi F = intcast(dmesh.F);
//        static Eigen::MatrixXd origV = doublecast(dmesh.origV);
//        static Eigen::MatrixXi origF = intcast(dmesh.origF);
//        
//        //Update mesh
//        //
//        //        viewer.modify_V(V);
//        
//        //inside modify_V
//        //void OViewer::modify_V(const Eigen::MatrixXd& V)
//        m_V_mod = V.cast<float>();
//        //basically makes m_facedVN
//        igl::per_face_normals(m_V_mod, m_F_mod, m_facedVN_mod);
//        //makes VN_mod
//        igl::per_vertex_normals(m_V_mod, m_F_mod, m_facedVN_mod, m_VN_mod);
//        //update_mesh_data(false);
//        
//        
//        
//        //end::predrawcallback there is more but it is about coloring
//        
//    }
    
}
