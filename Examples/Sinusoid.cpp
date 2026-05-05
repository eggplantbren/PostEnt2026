#include "Sinusoid.h"
#include <cmath>
#include "DNest4/code/DNest4.h"
#include "../Options.h"

namespace PostEnt2026
{

namespace Examples
{

void SinusoidParams::from_prior(DNest4::RNG& rng)
{
    A = exp(0.1*rng.randn());
    T = pow(10.0, -rng.rand());
    phi = 2.0*M_PI*rng.rand();
}

double SinusoidParams::perturb(DNest4::RNG& rng)
{
    int which = rng.rand_int(3);
    double logH = 0.0;

    if(which == 0)
    {
        A = log(A);
        logH -= -0.5*pow(A/0.1, 2);
        A += 0.1*rng.randh();
        logH += -0.5*pow(A/0.1, 2);
        A = exp(A);
    }
    else if(which == 1)
    {
        T = log10(T);
        T += rng.randh();
        DNest4::wrap(T, -1.0, 0.0);
        T = pow(10.0, T);
    }
    else
    {
        phi += 2.0*M_PI*rng.randh();
        DNest4::wrap(phi, 0.0, 2.0*M_PI);
    }

    return logH;
}

double SinusoidParams::log_kernel(const SinusoidParams& other) const
{
    static const double logZ = -0.5*std::log(2.0*M_PI*pow(Options::tolerance, 2));
    double logf = 0.0;
    

    logf += -0.5*std::pow((log10(T) - log10(other.T))/Options::tolerance, 2);
    return logf + logZ;
}

void SinusoidParams::print(std::ostream& out) const
{
    out << A << ' ' << T << ' ' << phi;
}

SinusoidData::SinusoidData(const SinusoidParams& params, DNest4::RNG& rng)
:t(N), y(N)
{
    for(int i=0; i<N; ++i)
    {
        t[i] = 0.01*i;
        y[i] = params.A*sin(2*M_PI*t[i]/params.T + params.phi) + 0.1*rng.randn();
    }
}

double SinusoidData::log_likelihood(const SinusoidParams& params) const
{
    double logl = 0.0;

    for(int i=0; i<N; ++i)
    {
        double mu = params.A*sin(2*M_PI*t[i]/params.T + params.phi);
        logl += -0.5*pow((y[i] - mu)/0.1, 2) - 0.5*log(2.0*M_PI*0.1*0.1);
    }


    return logl;
}


} // namespace Examples

} // namespace
