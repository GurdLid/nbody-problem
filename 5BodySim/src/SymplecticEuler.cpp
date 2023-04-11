#include "SymplecticEuler.hpp"

SymplecticEuler::SymplecticEuler(NBodyInterface &NBodyProblem, const double initialTime, const double finalTime, const double stepSize, const std::string outputFileName, const int saveGap, const int printGap)
    : mInitialTime(initialTime), mFinalTime(finalTime), mStepSize(stepSize), mNBody(&NBodyProblem), mOutputFileName(outputFileName), mSaveGap(saveGap), mPrintGap(printGap)
{
}

std::vector<double> SymplecticEuler::Solve()
{
    //Initialising variables and initial conditions
    const double mStepNumber = (mFinalTime - mInitialTime)/mStepSize;
    double t;
    const int noOfBodies = (*mNBody).GetNumberOfBodies();
    std::vector<double> radii(noOfBodies);
    radii = (*mNBody).GetRadii();

    std::vector<double> xOld(noOfBodies);
    xOld = (*mNBody).GetPosition(0);
    std::vector<double> yOld(noOfBodies);
    yOld = (*mNBody).GetPosition(1);
    std::vector<double> zOld(noOfBodies);
    zOld = (*mNBody).GetPosition(2);

    std::vector<double> x(noOfBodies);
    std::vector<double> y(noOfBodies);    
    std::vector<double> z(noOfBodies);

    std::vector<double> vOld_x(noOfBodies);
    vOld_x = (*mNBody).GetVelocity(0);
    std::vector<double> vOld_y(noOfBodies);
    vOld_y = (*mNBody).GetVelocity(1);
    std::vector<double> vOld_z(noOfBodies);
    vOld_z = (*mNBody).GetVelocity(2);

    std::vector<double> v_x(noOfBodies);
    std::vector<double> v_y(noOfBodies);    
    std::vector<double> v_z(noOfBodies);

    std::vector<double> fOld(3);

    bool collision = false;

    int i=1; //Starting from the first non zero time
    while(i<=mStepNumber) //Until N_t + 1 points
    {
        t = mInitialTime + i*mStepSize;

        for(int i=0;i<noOfBodies;i++)
        {
            std::vector<double> x_i(3);
            std::vector<double> x_i_Old(3);
            std::vector<double> v_i(3);
            std::vector<double> v_i_Old(3);
            (x_i_Old)[0] = (xOld)[i];
            (x_i_Old)[1] = (yOld)[i];
            (x_i_Old)[2] = (zOld)[i];     

            (v_i_Old)[0] = (vOld_x)[i];
            (v_i_Old)[1] = (vOld_y)[i];
            (v_i_Old)[2] = (vOld_z)[i];

            (*mNBody).ComputeF(xOld,yOld,zOld,fOld,i);

            //Functions for : v_i = v_i_Old + (fOld)*(mStepSize);
            std::transform(fOld.begin(),fOld.end(),fOld.begin(),[*this](auto& c){return c*mStepSize;});    
            std::transform(v_i_Old.begin(),v_i_Old.end(),fOld.begin(),v_i.begin(),std::plus<double>());

            (v_x)[i] = (v_i)[0];
            (v_y)[i] = (v_i)[1];
            (v_z)[i] = (v_i)[2];

            //Functions for : x_i = x_i_Old + (v_i)*mStepSize;
            std::transform(v_i.begin(),v_i.end(),v_i.begin(),[*this](auto& c){return c*mStepSize;});             
            std::transform(x_i_Old.begin(),x_i_Old.end(),v_i.begin(),x_i.begin(),std::plus<double>());

            (x)[i] = (x_i)[0];
            (y)[i] = (x_i)[1];
            (z)[i] = (x_i)[2];  
        }

        (*mNBody).DetectCollision(x,y,z,radii,t,collision); //Collision testing for the bodies
        if(collision==true) //exiting code if collision is detected
        {
            break;
        }

        xOld = x;
        yOld = y;
        zOld = z;
        vOld_x = v_x;
        vOld_y = v_y;
        vOld_z = v_z;

        i++;
    }

    std::vector<double> OutputPositions(3*noOfBodies); //output positions vector

    if(collision==false)
    {
        for (int i = 0; i< noOfBodies; i++)
        {
            OutputPositions[3 * i] = (x)[i]; //Each body has three position co-ords
            OutputPositions[3 * i + 1] = (y)[i];
            OutputPositions[3 * i + 2] = (z)[i];
        }
    }
    return OutputPositions;
}
