//
//  ofxLibiglOBJRead.hpp
//  example-project
//
//  Created by kkshmzMBP on 9/21/19.
//

#ifndef ofxLibiglOBJRead_hpp
#define ofxLibiglOBJRead_hpp

#include "ofxLibigl.h"
#include "ofxEigen.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iterator>

namespace igl
{
    // Read a mesh from an ascii obj file, filling in vertex positions, normals
    // and texture coordinates. Mesh may have faces of any number of degree
    //
    // Templates:
    //   Scalar  type for positions and vectors (will be read as double and cast
    //     to Scalar)
    //   Index  type for indices (will be read as int and cast to Index)
    // Inputs:
    //  str  path to .obj file
    // Outputs:
    //   V  double matrix of vertex positions  #V by 3
    //   TC  double matrix of texture coordinats #TC by 2
    //   N  double matrix of corner normals #N by 3
    //   F  #F list of face indices into vertex positions
    //   FTC  #F list of face indices into vertex texture coordinates
    //   FN  #F list of face indices into vertex normals
    // Returns true on success, false on errors
    template <typename Scalar, typename Index>
    IGL_INLINE bool readOBJ(
                            const std::string obj_file_name,
                            std::vector<std::vector<Scalar > > & V,
                            std::vector<std::vector<Scalar > > & TC,
                            std::vector<std::vector<Scalar > > & N,
                            std::vector<std::vector<Index > > & F,
                            std::vector<std::vector<Index > > & FTC,
                            std::vector<std::vector<Index > > & FN);
    // Inputs:
    //   obj_file  pointer to already opened .obj file
    // Outputs:
    //   obj_file  closed file
    template <typename Scalar, typename Index>
    IGL_INLINE bool readOBJ(
                            FILE * obj_file,
                            std::vector<std::vector<Scalar > > & V,
                            std::vector<std::vector<Scalar > > & TC,
                            std::vector<std::vector<Scalar > > & N,
                            std::vector<std::vector<Index > > & F,
                            std::vector<std::vector<Index > > & FTC,
                            std::vector<std::vector<Index > > & FN);
    // Just V and F
    template <typename Scalar, typename Index>
    IGL_INLINE bool readOBJ(
                            const std::string obj_file_name,
                            std::vector<std::vector<Scalar > > & V,
                            std::vector<std::vector<Index > > & F);
    // Eigen Wrappers. These will return true only if the data is perfectly
    // "rectangular": All faces are the same degree, all have the same number of
    // textures/normals etc.
    template <
    typename DerivedV,
    typename DerivedTC,
    typename DerivedCN,
    typename DerivedF,
    typename DerivedFTC,
    typename DerivedFN>
    IGL_INLINE bool readOBJ(
                            const std::string str,
                            Eigen::PlainObjectBase<DerivedV>& V,
                            Eigen::PlainObjectBase<DerivedTC>& TC,
                            Eigen::PlainObjectBase<DerivedCN>& CN,
                            Eigen::PlainObjectBase<DerivedF>& F,
                            Eigen::PlainObjectBase<DerivedFTC>& FTC,
                            Eigen::PlainObjectBase<DerivedFN>& FN);
    template <typename DerivedV, typename DerivedF>
    IGL_INLINE bool readOBJ(
                            const std::string str,
                            Eigen::PlainObjectBase<DerivedV>& V,
                            Eigen::PlainObjectBase<DerivedF>& F);
    
}


#endif /* ofxLibiglOBJRead_hpp */
