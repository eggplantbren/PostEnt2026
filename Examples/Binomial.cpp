#include "Binomial.h"
#include <cmath>
#include "DNest4/code/DNest4.h"
#include "../Options.h"

namespace PostEnt2026
{

namespace Examples
{

void BinomialParams::from_prior(DNest4::RNG& rng)
{
    theta = rng.rand();
}

double BinomialParams::perturb(DNest4::RNG& rng)
{
    theta += rng.randh();
    DNest4::wrap(theta, 0.0, 1.0);
    return 0.0;
}

double BinomialParams::log_kernel(const BinomialParams& other) const
{
    static const double logZ = -0.5*std::log(2.0*M_PI*pow(Options::tolerance, 2));
    double logf = 0.0;
    logf += -0.5*std::pow((theta - other.theta)/Options::tolerance, 2);
    return logf + logZ;
}

void BinomialParams::print(std::ostream& out) const
{
    out << theta;
}

void BinomialParams::csv_header(std::ostream& out)
{
    out << "theta";
}

BinomialData::BinomialData(const BinomialParams& params, DNest4::RNG& rng)
{
    x = 0;
    for(int i=0; i<N; ++i)
    {
        if(rng.rand() <= params.theta)
            ++x;
    }
}

double BinomialData::log_likelihood(const BinomialParams& params) const
{
    double logl = 0.0;
    logl += std::lgamma(N + 1) - std::lgamma(x + 1) - std::lgamma(N + x - 1);
    logl += x*log(params.theta) + (N - x)*log(1.0 - params.theta);
    return logl;
}


} // namespace Examples

} // namespace
