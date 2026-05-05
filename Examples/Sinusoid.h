#ifndef PostEnt2026_Examples_Sinusoid_h
#define PostEnt2026_Examples_Sinusoid_h

#include <ostream>
#include "DNest4/code/DNest4.h"

namespace PostEnt2026
{

namespace Examples
{

class SinusoidParams
{
    private:
        double A, T, phi;

    public:

        SinusoidParams() = default;

        // Generate from the prior
        void from_prior(DNest4::RNG& rng);

        // Perturb in the usual way
        double perturb(DNest4::RNG& rng);

        // Gaussian kernel
        double log_kernel(const SinusoidParams& other) const;

        // Print
        void print(std::ostream& out) const;

        friend class SinusoidData;

};


class SinusoidData
{
    private:
        static constexpr int N = 101;

        std::vector<double> t;
        std::vector<double> y;

    public:

        // Generate given the parameters
        SinusoidData(const SinusoidParams& params, DNest4::RNG& rng);

        // Evaluate log likelihood
        double log_likelihood(const SinusoidParams& params) const;

};



} // namespace Examples

} // namespace

#endif
