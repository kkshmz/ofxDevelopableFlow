//
//  ofxDevelopableUtils.hpp
//  example-project
//
//  Created by kkshmzMBP on 9/16/19.
//

#ifndef ofxDevelopableUtils_hpp
#define ofxDevelopableUtils_hpp

#include "Types.h"
#include "Mesh.h"
#include "ofxDevelopableViewer.h"

namespace Developables{
    struct Timestep {
        Scalar t = 1e-5; //0.1; //Timestep
        Scalar totalT = 0; //Total time
        int totalSteps = 0;
        OVectorXs energy; //Cached energy
        OMatrixXs energyGrad; //Cached grad
        OMatrixXs p; //Search direction
        
        void post_step_processing() //Increases all relevant counters
        {
            totalT += t;
            ++totalSteps;
        }
        
        void invalidate()
        {
            energy = OVectorXs();
            energyGrad = OMatrixXs();
            p = OMatrixXs();
            t = 1e-8;
        }
    };

    void predrawcallback();
    void animation_step();
    Eigen::MatrixXi intcast(const Developables::OMatrixXi& A);
    Eigen::MatrixXd doublecast(const Developables::OMatrixXs& A);
    
    Developables::Mesh m;
    ofxDevelopableViewer viewer;
    Timestep t;
  
  

    
}

#endif /* ofxDevelopableUtils_hpp */
