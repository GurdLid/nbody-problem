#ifndef SYMPLECTIC_EULER
#define SYMPLECTIC_EULER

#include "NBodyInterface.hpp"

extern double const G;

class SymplecticEuler
{
    public:
        SymplecticEuler(NBodyInterface& NBodyProblem, const double initialTime, const double finalTime, const double stepSize,
                            const std::string outputFileName="output.dat", const int saveGap = 1, const int printGap = 1);
        [[nodiscard("This returns the output positions of the bodies")]] std::vector<double> Solve();

    protected:
        int mSaveGap;
        int mPrintGap;

    private:
        SymplecticEuler();  //Hiding the default constructor

        double mFinalTime;
        double mInitialTime;
        NBodyInterface* mNBody; //pointer for the ODE system
        double mStepSize; //represents h
        std::string mOutputFileName;

};


#endif // SYMPLECTIC_EULER
