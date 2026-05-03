#include "Start.h"
#include "Examples/Binomial.h"

using namespace PostEnt2026;

int main(int argc, char** argv)
{
    start<Examples::BinomialParams, Examples::BinomialData>(argc, argv);

    return 0;
}

