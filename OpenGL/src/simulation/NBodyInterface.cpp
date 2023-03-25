#include "NBodyInterface.hpp"

NBodyInterface::NBodyInterface(std::vector<std::shared_ptr<CelestialBody>> &CelestialVector)
{
    for(const auto &elem : CelestialVector)
    {
        mMasses.emplace_back(elem->GetMass());
        mRadii.emplace_back(elem->GetRadius());
        mXStates.emplace_back(elem->GetPosition()[0]);
        mYStates.emplace_back(elem->GetPosition()[1]);
        mZStates.emplace_back(elem->GetPosition()[2]);
        mXVelocity.emplace_back(elem->GetVelocity()[0]);
        mYVelocity.emplace_back(elem->GetVelocity()[1]);
        mZVelocity.emplace_back(elem->GetVelocity()[2]);
    }
    mNumberOfBodies = (int)CelestialVector.size();
}

void NBodyInterface::ComputeAnalyticSolution( double& v0, double& T0, const double fixedMass, const double orbitRadius) const
{
    v0 = pow(((G*fixedMass)/orbitRadius),0.5);
    T0 = pow(((4.0*pow(M_PI,2.0)*pow(orbitRadius,3.0))/(G*fixedMass)),0.5);
}

void NBodyInterface::ComputeF( const std::vector<double>& xStates, const std::vector<double>& yStates, const std::vector<double>& zStates, std::vector<double>& f, int n) const
{
    std::vector<double> f_single(3);
    f[0] = 0.0;
    f[1] = 0.0;
    f[2] = 0.0;
    std::vector<double> xj_m_xi(3);
    std::vector<double> xj(3);
    std::vector<double> xi(3);
    xi[0] = xStates[n];
    xi[1] = yStates[n];
    xi[2] = zStates[n];
    if(n==0)
    {
        for(int i=1;i<mNumberOfBodies;i++)
        {
            xj[0] = xStates[i];
            xj[1] = yStates[i];
            xj[2] = zStates[i];
            std::transform(xj.begin(),xj.end(),xi.begin(),xj_m_xi.begin(),std::minus<double>());
            double mass = mMasses[i];
            std::transform(xj_m_xi.begin(),xj_m_xi.end(),f_single.begin(),[&mass](auto& c){return c*(G*mass);});
            double denom = VectorFunctions::CalculateNorm(2,xj_m_xi);
            denom = pow(denom,3.0);

            std::transform(f_single.begin(),f_single.end(),f_single.begin(),[&denom](auto& c){return c*(1.0/denom);});
            std::transform(f.begin(),f.end(),f_single.begin(),f.begin(),std::plus<double>()); 
        }
    }
    else
    {
        for(int i=0;i<mNumberOfBodies;i++)
        {
            if(i!=n)
            {
                xj[0] = xStates[i];
                xj[1] = yStates[i];
                xj[2] = zStates[i];
                std::transform(xj.begin(),xj.end(),xi.begin(),xj_m_xi.begin(),std::minus<double>());
                double mass = mMasses[i];
                std::transform(xj_m_xi.begin(),xj_m_xi.end(),f_single.begin(),[&mass](auto& c){return c*(G*mass);});
                double denom = VectorFunctions::CalculateNorm(2,xj_m_xi);
                denom = pow(denom,3.0);

                std::transform(f_single.begin(),f_single.end(),f_single.begin(),[&denom](auto& c){return c*(1.0/denom);});
                std::transform(f.begin(),f.end(),f_single.begin(),f.begin(),std::plus<double>());
            }
        }
    }
}


void NBodyInterface::DetectCollision(const std::vector<double>& xStates, const std::vector<double>& yStates, const std::vector<double>& zStates, const std::vector<double>& radii, const double t, bool& collision)
{
    std::vector<double> distance_between_centres(3);
    for(int i=0;i<mNumberOfBodies-1;i++)
    {
        for(int j=i;j<mNumberOfBodies-1;j++)
        {
            (distance_between_centres)[0] = xStates[i]-xStates[j+1];
            (distance_between_centres)[1] = yStates[i]-yStates[j+1];
            (distance_between_centres)[2] = zStates[i]-zStates[j+1];
            double distance = VectorFunctions::CalculateNorm(2,distance_between_centres);
            double radius1 = radii[i];
            double radius2 = radii[j+1];
            try
            {
                if(distance<radius1+radius2)
                {
                    throw "Computation stopped" ;
                }
            }
            catch (const char msg)
            {
                std::cout << "\n" << "######## Collision has occurred between: ########" << std::endl;
                std::cout << "Body number "<< i+1 << " at position: \n"<< xStates[i] <<" "<< yStates[i] <<" " << zStates[i] <<  std::endl;
                std::cout << "Body number "<< (int)(j+2) << " at position: \n"<< xStates[j+1] <<" "<< yStates[j+1] <<" " <<zStates[j+1] <<  std::endl;
                std::cout << "Time of collision was: " << t << " seconds after t0." << std::endl;
                std::cout << msg << std::endl;
                collision = true;
            }
        }
    }
} 


std::vector<double> NBodyInterface::GetPosition(int axis) const
{
    switch(axis)
    {
        case 0:
        {
            return mXStates;
        }
        case 1:
        {
            return mYStates;
        }
        case 2:
        {
            return mZStates;
        }
        default:
        {
            std::vector<double> Zeros(3);
            return Zeros;
        }
    }
}


std::vector<double> NBodyInterface::GetVelocity(int axis) const
{
    switch(axis)
    {
        case 0:
        {
            return mXVelocity;
        }
        case 1:
        {
            return mYVelocity;
        }
        case 2:
        {
            return mZVelocity;
        }
        default:
        {
            std::vector<double> Zeros(3);
            return Zeros;
        }
    }
}

/* void singleBodyComputeF(std::vector<double> &xj, std::vector<double> &xj_m_xi, std::vector<double> xi, std::vector<double> &f_single, std::vector<double> &f, double yStates_i, double xStates_i, double zStates_i, double mMasses_i)
{
    xj[0] = xStates_i;
    xj[1] = yStates_i;
    xj[2] = zStates_i;
    std::transform(xj.begin(),xj.end(),xi.begin(),xj_m_xi.begin(),std::minus<double>());
    double mass = mMasses_i;
    std::transform(xj_m_xi.begin(),xj_m_xi.end(),f_single.begin(),[&mass](auto& c){return c*(G*mass);});
    double denom = VectorFunctions::CalculateNorm(2,xj_m_xi);
    denom = pow(denom,3.0);

    std::transform(f_single.begin(),f_single.end(),f_single.begin(),[&denom](auto& c){return c*(1.0/denom);});
    std::transform(f.begin(),f.end(),f_single.begin(),f.begin(),std::plus<double>()); 
} */
