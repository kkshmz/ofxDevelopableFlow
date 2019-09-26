//
//  ofxDevelopableTypes.h
//  example-project
//
//  Created by kkshmzMBP on 9/18/19.
//

#ifndef ofxDevelopableTypes_h
#define ofxDevelopableTypes_h
#pragma once
//#include <Eigen/Core>
#include "ofxEigen.h"


//YOU NEED TO ENABLE CGAL IN THE CMAKELISTS.TXT FOR ANYTHING BUT THE BASIC TYPES TO WORK



#define DOUBLE 1
#define MPFR 2
#define SCALAR_TYPE DOUBLE
#define MPFR_PRECISION 256 //128

//Standard fixed-precision integers
typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> OMatrixXi;
typedef Eigen::Matrix<int, 3, 3> OMatrix3i;
typedef Eigen::Matrix<int, Eigen::Dynamic, 1> OVectorXi;
typedef Eigen::Matrix<int, 3, 1> OVector3i;
typedef Eigen::Matrix<int, 1, Eigen::Dynamic> ORowVectorXi;
typedef Eigen::Matrix<int, 1, 3> ORowVector3i;

static Eigen::MatrixXi intcast(const OMatrixXi& A)
{
    return A;
}


//#if SCALAR_TYPE == DOUBLE

//Standard fixed-precision scalars
typedef double Scalar;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> OMatrixXs;
typedef Eigen::Matrix<double, 3, 3> OMatrix3s;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> OVectorXs;
typedef Eigen::Matrix<double, 3, 1> OVector3s;
typedef Eigen::Matrix<double, 1, Eigen::Dynamic> ORowVectorXs;
typedef Eigen::Matrix<double, 1, 3> ORowVector3s;


void types_startup()
{
}

double toDouble(const Scalar& s) {
    return s;
}

static Eigen::MatrixXd doublecast(const OMatrixXs& A)
{
    return A;
}

void static doublecast(const OMatrixXs& A, Eigen::MatrixXd& B)
{
    B = A;
}
//#endif

//#elif SCALAR_TYPE == MPFR
//
//
//#include <unsupported/Eigen/MPRealSupport>
//typedef mpfr::mpreal Scalar;
//typedef Eigen::Matrix<mpfr::mpreal, Eigen::Dynamic, Eigen::Dynamic> OMatrixXs;
//typedef Eigen::Matrix<mpfr::mpreal, 3, 3> OMatrix3s;
//typedef Eigen::Matrix<mpfr::mpreal, Eigen::Dynamic, 1> OVectorXs;
//typedef Eigen::Matrix<mpfr::mpreal, 3, 1> OVector3s;
//typedef Eigen::Matrix<mpfr::mpreal, 1, Eigen::Dynamic> ORowVectorXs;
//typedef Eigen::Matrix<mpfr::mpreal, 1, 3> ORowVector3s;
//
//void types_startup()
//{
//    mpfr::mpreal::set_default_prec(MPFR_PRECISION);
//}
//
//double toDouble(const Scalar& s) {
//    return s.toDouble();
//}
//
//Eigen::MatrixXd doublecast(const OMatrixXs& A)
//{
//    Eigen::MatrixXd B(A.rows(), A.cols());
//    for(int i=0; i<B.rows(); ++i) {
//        for(int j=0; j<B.cols(); ++j) {
//            B(i,j) = A(i,j).toDouble();
//        }
//    }
//
//    return B;
//}
//
//Eigen::MatrixXd doublecast(const OMatrixXs& A, Eigen::MatrixXd& B)
//{
//    B.resize(A.rows(), A.cols());
//    for(int i=0; i<B.rows(); ++i) {
//        for(int j=0; j<B.cols(); ++j) {
//            B(i,j) = A(i,j).toDouble();
//        }
//    }
//
//    return B;
//}
//
//
//#endif





#endif /* ofxDevelopableTypes_h */
