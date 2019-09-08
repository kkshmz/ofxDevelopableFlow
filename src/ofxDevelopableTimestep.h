//
//  ofxDevelopableTimestep.h
//  example-project
//
//  Created by kkshmzMBP on 9/8/19.
//


#ifndef DEVELOPABLEFLOW_TIMESTEPSTRUCT_H
#define DEVELOPABLEFLOW_TIMESTEPSTRUCT_H

#include "ofxEigen.h"

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


#endif
