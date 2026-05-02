#ifndef PostEnt2026_Examples_Binomial_h
#define PostEnt2026_Examples_Binomial_h

#include <ostream>
#include "DNest4/code/DNest4.h"

namespace PostEnt2026
{

namespace Examples
{

class BinomialParams
{
    private:
        double theta;

    public:

        BinomialParams() = default;

        // Generate from the prior
        void from_prior(DNest4::RNG& rng);

        // Perturb in the usual way
        double perturb(DNest4::RNG& rng);

        // Gaussian kernel
        double log_kernel(const BinomialParams& other) const;

        // Print
        void print(std::ostream& out) const;
        static void csv_header(std::ostream& out);

        friend class BinomialData;

};


class BinomialData
{
    private:
        static constexpr int N = 100;
        int x;

    public:

        // Generate given the parameters
        BinomialData(const BinomialParams& params, DNest4::RNG& rng);

        // Evaluate log likelihood
        double log_likelihood(const BinomialParams& params) const;

};



} // namespace Examples

} // namespace

#endif
