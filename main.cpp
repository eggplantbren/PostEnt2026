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

    std::system("rm logzs.txt logzs2.txt");

    for(int i=0; i<PostEnt2026::Options::num_runs; ++i)
    {
        // Generate parameters and data.
        Params truth;
        truth.from_prior(rng);
        Data data(truth, rng);

        // Do NOT tell DNest4 about the
        // true parameters yet.
        MyModel<Params, Data>::set_data(&data);
        MyModel<Params, Data>::set_truth(nullptr);

        // Do standard DNest4 run
        DNest4::start<PostEnt2026::MyModel<Params, Data>>(argc, argv);
        std::system("python3 _showresults.py");

        // Tell DNest4 about the true parameters.
        MyModel<Params, Data>::set_truth(&truth);

        // Do modified DNest4 run with kernel
        DNest4::start<PostEnt2026::MyModel<Params, Data>>(argc, argv);
        std::system("python3 _showresults2.py");
    }

    return 0;
}

