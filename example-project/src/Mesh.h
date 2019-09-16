////
////  Mesh.h
////  example-project
////
////  Created by kkshmzMBP on 9/16/19.
////
//
#pragma once
#ifndef DEVELOPABLEFLOW_MESHSTRUCT_H
#define DEVELOPABLEFLOW_MESHSTRUCT_H

///*
// 
// //
// //  ofxDevelopableMesh.h
// //  example-project
// //
// //  Created by kkshmz on 9/8/19.
// //
// 
// 2018, Oded Stein, Eitan Grinspun and Keenan Crane
// 
// This file is part of the code for "Developability of Triangle Meshes".
// 
// The code for "Developability of Triangle Meshes" is free software: you can
// redistribute it and/or modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation, either version 2 of the
// License, or (at your option) any later version.
// 
// The code for "Developability of Triangle Meshes" is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the code for "Developability of Triangle Meshes". If not,
// see <https://www.gnu.org/licenses/>.
// 
// */
////
//#include "ofxDevelopableFlow.h"
//
//
//
#include <vector>
#include <list>
#include "Types.h"
#include "ofMain.h"

#include <igl/all_edges.h>
#include <igl/triangle_triangle_adjacency.h>
#include <igl/vertex_triangle_adjacency.h>
#include <igl/unique_simplices.h>
#include <igl/is_border_vertex.h>

//
//
namespace Developables {
    
    struct Mesh {
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
        
        void update()
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
                
                std::vector<typename Developables::OMatrixXi::Scalar>& newVF = VF[i];
                std::vector<typename Developables::OMatrixXi::Scalar>& newVFi = VFi[i];
                
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
        
        void draw(ofPolyRenderMode renderType){
            //#ifndef TARGET_OPENGLES
            //            mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
            ////#else
            switch(renderType){
//                case OF_MESH_FILL:
//                    //                    mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
//                    std::cout << "fill" << endl;
//                    break;
                case OF_MESH_WIREFRAME:
                    //note this won't look the same as on non ES renderers.
                    //there is no easy way to convert GL_TRIANGLES to outlines for each triangle
                    //                    mesh.vbo.drawElements(GL_LINES,mesh.indices.size());
                    std::cout << "wire" << endl;
                    break;
//                case OF_MESH_POINTS:
//                    //                    mesh.vbo.drawElements(GL_POINTS,mesh.indices.size());
//                    std::cout << "points" << endl;
//                    break;
//
            }
        }
        void drawWireframe(){
            draw(OF_MESH_WIREFRAME);
        }
        
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



#endif //header guard
//
