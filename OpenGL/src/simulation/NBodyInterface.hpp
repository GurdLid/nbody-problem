#ifndef NBODY_INTER
#define NBODY_INTER
#include "CelestialBody.hpp"
#include "VectorFunctions.hpp"

#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cassert>
  
extern const double G;

class NBodyInterface
{
    public:
        NBodyInterface(std::vector<std::shared_ptr<CelestialBody>> &CelestialVector); //Constructor

        //Get functions
        std::vector<double> GetPosition(int axis) const;
        std::vector<double> GetVelocity(int axis) const;
        std::vector<double> GetRadii() const {return mRadii;}
        int GetNumberOfBodies() const {return mNumberOfBodies;}

        //Computation functions
        void ComputeF(const std::vector<double>& xStates, const std::vector<double>& yStates, const std::vector<double>& zStates, std::vector<double>& f,int n) const;

        void ComputeAnalyticSolution( double& v0, double& T0, const double fixedMass, const double orbitRadius) const;  //Method to compute true solutions

        void DetectCollision(const std::vector<double>& xStates, const std::vector<double>& yStates, const std::vector<double>& zStates, const std::vector<double>& radii, const double t, bool& collision); //Method to detect collision between bodies



    private:
        NBodyInterface(); //Hiding default constructor

        int mNumberOfBodies;
        std::vector<double> mMasses;
        std::vector<double> mRadii;

        std::vector<double> mXStates;
        std::vector<double> mYStates;
        std::vector<double> mZStates;

        std::vector<double> mXVelocity;
        std::vector<double> mYVelocity;
        std::vector<double> mZVelocity;

        //void singleBodyComputeF(std::vector<double> &xj, std::vector<double> &xj_m_xi, std::vector<double> xi, std::vector<double> &f_single, std::vector<double> &f, double yStates_i, double xStates_i, double zStates_i, double mMasses_i);
};



#endif // NBODY_INTER