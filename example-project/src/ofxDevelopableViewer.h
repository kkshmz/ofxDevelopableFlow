//
//  ofxDevelopableViewer.hpp
//  example-project
//
//  Created by kkshmzMBP on 9/16/19.
//

#ifndef ofxDevelopableViewer_hpp
#define ofxDevelopableViewer_hpp

#include "ofxEigen.h"
#include "ofxLibigl.h"
#include "Types.h"
#include "ofMain.h"
#include "ofxDevelopableUtils.h"


class ofxDevelopableViewer
    {
    public:
        ofxDevelopableViewer();
        ofMesh mesh;
        bool blaunched = true;
        
        
        void setmesh(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F, const Eigen::MatrixXi& E);
        void setmeshCast(const Developables::OMatrixXs& V, const Eigen::MatrixXi& F, const Eigen::MatrixXi& E);
        void updatemeshdata();
        void draw();
        void modify_V(const Eigen::MatrixXd& V);
        
        
//        Eigen::MatrixXi intcast(const Developables::OMatrixXi& A);
//
//        Eigen::MatrixXd doublecast(const Developables::OMatrixXs& A);
//
//        void doublecast(const Developables::OMatrixXs& A, Eigen::MatrixXd& B);
        
        
        
        
        
        
        
        
    private:
        //storage in order of row
        Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> m_V, m_V_mod, m_VN, m_VN_mod, m_facedVN_mod, m_amb, m_spec, m_dif;
        //affine floats
        Eigen::Affine3f initialShift;
        //gluint is a unsigned int from GL libraruy
        Eigen::Matrix<GLuint, Eigen::Dynamic, 3, Eigen::RowMajor> m_F, m_F_mod;
        Eigen::Matrix<GLuint, Eigen::Dynamic, 2, Eigen::RowMajor> m_E, m_E_mod;
        
        Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> pointsCoords;
        Eigen::VectorXi markedPoints;
        
        bool meshSet = false;
    };

#endif /* ofxDevelopableViewer_hpp */
