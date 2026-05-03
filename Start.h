#ifndef PostEnt2026_Start_h
#define PostEnt2026_Start_h

#include "DNest4/code/DNest4.h"
#include "MyModel.h"
#include "Options.h"
#include <iostream>
#include <iomanip>
#include <fstream>

namespace PostEnt2026
{

template<typename Params, typename Data>
void start(int argc, char** argv);






// Implementation follows

template<typename Params, typename Data>
void start(int argc, char** argv)
{
    // Separate RNG for generating (truth, data) pairs.
    DNest4::RNG rng(time(0));

    std::system("rm logzs.txt logzs2.txt");
    std::fstream fout("truths.txt", std::ios::out);
    fout << std::setprecision(12);

    for(int i=0; i<PostEnt2026::Options::num_runs; ++i)
    {
        // Generate parameters and data.
        Params truth;
        truth.from_prior(rng);
        Data data(truth, rng);
        truth.print(fout); fout << std::endl;

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
    fout.close();
}


} // namespace

#endif
