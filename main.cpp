#include <iostream>
#include "DNest4/code/DNest4.h"
#include "MyModel.h"
#include "Examples/Binomial.h"
#include "Options.h"
#include <iostream>

using namespace PostEnt2026;
using Params = Examples::BinomialParams;
using Data =   Examples::BinomialData;

int main(int argc, char** argv)
{
    // Separate RNG for generating (truth, data) pairs.
    DNest4::RNG rng;

    std::system("rm logzs.txt");

    for(int i=0; i<PostEnt2026::Options::num_runs; ++i)
    {
        Params truth;
        truth.from_prior(rng);
        Data data(truth, rng);

        MyModel<Params, Data>::set_data(&data);
        DNest4::start<PostEnt2026::MyModel<Params, Data>>(argc, argv);
        MyModel<Params, Data>::set_data(nullptr);

        std::system("python3 showresults.py");
    }

    return 0;
}

