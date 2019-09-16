//
//  ofxDevelopableUtils.cpp
//  example-project
//
//  Created by kkshmzMBP on 9/16/19.
//

#include "ofxDevelopableUtils.h"
namespace Developable{
Eigen::MatrixXi intcast(const Developables::OMatrixXi& A){
    return A;
}


Eigen::MatrixXd doublecast(const Developables::OMatrixXs& A)
{
    return A;
}
    
void predrawcallback(){
    //Execute instructions
//    execute_instructions(t.totalSteps);
    
    if(animating)
        Developables::animation_step();
    
    if(meshChanged) {
        
        Eigen::MatrixXd V = Developables::doublecast(Developables::m.V);
        Eigen::MatrixXi F = Developables::intcast(Developables::m.F);
        Eigen::MatrixXi E = Developables::intcast(Developables::m.E);
        
        //viewer.modify_V(V);
        //viewer.modify_F(F, E);
       
        Developables::viewer.setmeshCast(V, F, E);
        
        meshChanged = false;
    }
    
    if(meshPosChanged) {
        
        Eigen::MatrixXd V = Developables::doublecast(Developables::m.V);
        Eigen::MatrixXi F = Developables::intcast(Developables::m.F);
        static Eigen::MatrixXd origV = doublecast(Developables::m.origV);
        static Eigen::MatrixXi origF = intcast(Developables::m.origF);
        
        //Update mesh
        Developables::viewer.modify_V(V);
        
        //Dihedral angle coloring
        Eigen::MatrixXd normals;
        igl::per_face_normals(V, F, normals);
        if(dihedralColoring) {
            Eigen::MatrixXd dihedralAngles;
            triangle_cosdihedral_angle(intcast(Developables::m.edgesC), intcast(Developables::m.TT), normals, dihedralAngles);
            Developables::viewer.set_linetransparency(5.*dihedralAngles.array().acos()/M_PI);
        } else {
            viewer.set_linetransparency(Eigen::VectorXd::Ones(Developables::m.E.rows()));
        }
        
        //Color vertices by energy, threshold, or gradient dotted with normal
        if(energyColoring == 0 || t.energy.rows()==0) {
            viewer.set_colors(Eigen::Vector3d(0., 118./255., 189./255.));
        } else if(energyColoring == 1  && t.energy.rows() > 0) {
            Eigen::VectorXd energy = doublecast(t.energy);
            Eigen::VectorXd vertcolors(3*F.rows());
            for(int i=0; i<F.rows(); ++i) {
                for(int j=0; j<3; ++j) {
                    vertcolors(3*i+j) = energy(F(i,j));
                }
            }
            
            Eigen::MatrixXd colors;
            igl::parula(vertcolors, true, colors);
        }
//            viewer.set_colors(colors);
            
//        } else if(energyColoring == 2 && t.energyGrad.rows() > 0) {
//            Eigen::MatrixXd energyGrad = doublecast(t.energyGrad);
//            Eigen::MatrixXd perVertexNormals;
//            igl::per_vertex_normals(V, F, normals, perVertexNormals);
//            Eigen::VectorXd vertcolors(3*F.rows());
//            for(int i=0; i<F.rows(); ++i) {
//                for(int j=0; j<3; ++j) {
//                    vertcolors(3*i+j) = perVertexNormals.row(F(i,j)).dot(energyGrad.row(F(i,j)));
//                }
//            }
//
//            Eigen::MatrixXd colors;
//            igl::parula(vertcolors, true, colors);
//            viewer.set_colors(colors);
//        } else if(energyColoring == 3  && t.energy.rows() > 0) {
//            Eigen::VectorXd energy = doublecast(t.energy);
//            Eigen::MatrixXd colors(3*F.rows(), 3);
//            for(int i=0; i<F.rows(); ++i) {
//                for(int j=0; j<3; ++j) {
//                    if(energy(F(i,j)) > cutThreshold)
//                        colors.row(3*i+j) << 0., 118./255., 189./255.;
//                    else
//                        colors.row(3*i+j) << 0.8, 0.8, 0.8;
//                }
//            }
//            viewer.set_colors(colors);
//        } else if(energyColoring == 4) {
//            Eigen::VectorXd gaussEnergy;
//            curvature_energy(Developables::m.V, Developables::m.F, Developables::m.VF, Developables::m.VFi, Developables::m.isB, gaussEnergy);
//            std::cout << "Total angle defect: " << gaussEnergy.sum() << std::endl;
//
//            Eigen::VectorXd vertcolors(3*F.rows());
//            for(int i=0; i<F.rows(); ++i) {
//                for(int j=0; j<3; ++j) {
//                    vertcolors(3*i+j) = gaussEnergy(F(i,j));
//                }
//            }
//            Eigen::MatrixXd colors;
//            igl::parula(vertcolors, true, colors);
//            viewer.set_colors(colors);
//        } else if(energyColoring == 5) {
//            Eigen::MatrixXd N;
//            igl::per_face_normals(m.V, m.F, N);
//            Eigen::VectorXd A;
//            igl::doublearea(m.V, m.F, A);
//            Eigen::VectorXd err(N.rows());
//            for(int face=0; face<N.rows(); ++face) {
//                double weightSum = 0;
//                Eigen::RowVector3d normalSum(0,0,0);
//                for(int j=0; j<3; ++j) {
//                    int neigh = m.TT(face,j);
//                    if(neigh>=0) {
//                        weightSum += A(neigh);
//                        normalSum += A(neigh)*N.row(neigh);
//                    }
//                }
//                if(weightSum>0)
//                    err(face) = (normalSum/weightSum - N.row(face)).norm();
//                else
//                    err(face) = -1;
//            }
//            Eigen::MatrixXd errorColor;
//            igl::colormap(igl::COLOR_MAP_TYPE_MAGMA, err, 0, err.maxCoeff(), errorColor);
//            viewer.set_colors(errorColor);
//        }
        
        //Statistics about angles
        Eigen::VectorXd doubleareas;
        igl::doublearea(V, F, doubleareas);
        std::stringstream title3;
        title3 << "Smallest triangle area: " << doubleareas.minCoeff();
        Eigen::MatrixXd tipangles;
        igl::internal_angles(V, F, tipangles);
        title3 << ", smallest triangle angle: " << tipangles.minCoeff();
        titles[3] = title3.str();
        
        //Hausdorff distance
//        double dist;
//        igl::hausdorff(V, F, origV, origF, dist);
//        std::stringstream title4;
//        title4 << "Hausdorff dist to original: " << dist;
//        titles[4] = title4.str();
//
//
//        //Update plot
//        viewer.set_plots(titles, lines);
        
        meshPosChanged = false;
    }

}
    void animation_step()
    {
        //Perform a timestep
        const auto oldt = t; const auto oldm = m;
        int success = timestep(Developables::m.V, Developables::m.F, Developables::m.VF, Developables::m.VFi, Developables::m.isB, t.t, t.p, t.energy, t.energyGrad, linesearchMode, stepType, energyMode);
        if(success<0) {
            std::stringstream stream;
            //stream << "energy_at_step_" << t.totalSteps << ".mat";
            //write_energy(oldm.V, oldm.F, oldm.VF, oldm.VFi, oldm.isB, oldt.p, stream.str(), 1e-7, energyMode);
            std::cout << "Line search failed with error code " << success << " at step " << t.totalSteps << std::endl;
            //animating = false;
        }
        t.post_step_processing();
        
        //Do postprocessing
        if(remeshingEnabled) {
            int change = mesh_postprocessing(Developables::m.V, Developables::m.F, Developables::m.E, Developables::m.edgesC, Developables::m.TT, Developables::m.TTi, Developables::m.VF, false);
            if(change==1) { //Structural change happened
                std::cout << "A structural change happened to the mesh." << std::endl;
                m.origF = m.F;
                Developables::OVectorXi _1;
                igl::remove_unreferenced(Developables::OMatrixXs(Developables::m.V), OMatrixXi(m.F), Developables::m.V, Developables::m.F, _1);
                igl::remove_unreferenced(OMatrixXs(m.origV), OMatrixXi(Developables::m.origF), Developables::m.origV, Developables::m.origF, _1);
                Developables::m.update();
                t.invalidate();
                meshChanged = true;
            }
        }
        meshPosChanged = true;
        
        //Update labels
//        double totalEnergy = toDouble(t.energy.sum());
//        lines[0].conservativeResize(lines[0].size()+1);
//        lines[0](lines[0].size()-1) = totalEnergy;
//        std::stringstream title0;
//        title0 << "Energy (" << totalEnergy << ")";
//        titles[0] = title0.str();
//        double energyGradL2 = t.energyGrad.rows()==0 ? 0 : doublecast(t.energyGrad).norm()/sqrt((double) t.energyGrad.rows());
//        lines[1].conservativeResize(lines[1].size()+1);
//        lines[1](lines[1].size()-1) = energyGradL2;
//        std::stringstream title1;
//        title1 << "Scaled L2 gradient norm (" << energyGradL2 << ")";
//        titles[1] = title1.str();
//        std::stringstream title2;
//        title2 << "Timestep: " << toDouble(t.t) << ", total time: " << toDouble(t.totalT) << ", total steps: " << t.totalSteps;
//        titles[2] = title2.str();
        
        //Record video
        if(recordingVideo) {
            if(lastEnergy < 0 || totalEnergy/lastEnergy < 0.99) {
                if(totalEnergy>0)
                    lastEnergy = totalEnergy;
                std::stringstream str;
                str << "./frame_" << std::setw(8) << std::setfill('0') << frameCount++ << ".obj";
                igl::writeOBJ(str.str(), doublecast(m.V), intcast(m.F));
            }
        }
    }
    
    
    
}// end of namespace


