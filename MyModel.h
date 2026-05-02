#ifndef PostEnt2026_MyModel
#define PostEnt2026_MyModel

#include "DNest4/code/DNest4.h"
#include <optional>
#include <memory>
#include "Options.h"

namespace PostEnt2026
{

template<typename Params, typename Data>
class MyModel
{
    private:
        static Params* truth;
        static Data*   data;

        Params params;

    public:
        // Constructor only gives size of params
        MyModel();

        // Generate the point from the prior
        void from_prior(DNest4::RNG& rng);

        // Metropolis-Hastings proposals
        double perturb(DNest4::RNG& rng);

        // Likelihood function
        double log_likelihood() const;

        // Print to stream
        void print(std::ostream& out) const;

        // Return string with column information
        std::string description() const;

        // Global setters
        static void set_data(Data* _data)
        {
            data = _data;
        }
        static void set_truth(Params* _truth)
        {
            truth = _truth;
        }
};



/* IMPLEMENTATIONS FOLLOW */


template<typename Params, typename Data>
Params* MyModel<Params, Data>::truth;

template<typename Params, typename Data>
Data* MyModel<Params, Data>::data;

template<typename Params, typename Data>
MyModel<Params, Data>::MyModel()
{

}

template<typename Params, typename Data>
void MyModel<Params, Data>::from_prior(DNest4::RNG& rng)
{
    params.from_prior(rng);
}

template<typename Params, typename Data>
double MyModel<Params, Data>::perturb(DNest4::RNG& rng)
{
    return params.perturb(rng);
}

template<typename Params, typename Data>
double MyModel<Params, Data>::log_likelihood() const
{
    return data->log_likelihood(params);
}

template<typename Params, typename Data>
void MyModel<Params, Data>::print(std::ostream& out) const
{
    params.print(out);
}

template<typename Params, typename Data>
std::string MyModel<Params, Data>::description() const
{
    return std::string("");
}

} // namespace

#endif

