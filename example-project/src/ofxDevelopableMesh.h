//
//  ofxDevelopableMesh.hpp
//  example-project
//
//  Created by kkshmzMBP on 9/18/19.
//

#ifndef ofxDevelopableMesh_hpp
#define ofxDevelopableMesh_hpp

#include <vector>
#include <list>
#include "Types.h"
#include "ofMain.h"

#include <igl/all_edges.h>
#include <igl/triangle_triangle_adjacency.h>
#include <igl/vertex_triangle_adjacency.h>
#include <igl/unique_simplices.h>
#include <igl/is_border_vertex.h>

class ofxDevelopableMesh{
    Developables::OMatrixXs origV;
    Developables::OMatrixXi origF;
    Developables::OMatrixXs V;
    Developables::OMatrixXi F;
    Developables::OMatrixXi allE;
    Developables::OMatrixXi E;
    Developables::OMatrixXi edgesA;
    Developables::OMatrixXi edgesC;
    Developables::OMatrixXi TT; //triangle-triangle adjacency
    Developables::OMatrixXi TTi; //triangle-triangle adjacencyi
    std::vector<std::vector<typename Developables::OMatrixXi::Scalar> > VF; //vertex-triangle adjacency
    std::vector<std::vector<typename Developables::OMatrixXi::Scalar> > VFi; //vertex-triangle adjacencyi
    std::vector<bool> isB; //is border vertex
    ofxDevelopableMesh();
    ofxDevelopableMesh(const Developables::OMatrixXs& iV, const Developables::OMatrixXi& iF);
    void update();
    
    void draw(ofPolyRenderMode renderType);
    void drawWireframe();
    
    Mesh()
    {}
    
    Mesh(const Developables::OMatrixXs& iV, const Developables::OMatrixXi& iF)
    {
        //typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> OMatrixXs;
        //  OMatrixXs V;
        V = iV;
        F = iF;
        origV = iV;
        origF = iF;
        update();
    }
};
}




#endif /* ofxDevelopableMesh_hpp */
