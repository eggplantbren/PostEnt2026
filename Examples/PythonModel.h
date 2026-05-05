#ifndef PostEnt2026_Examples_PythonModel_h
#define PostEnt2026_Examples_PythonModel_h

#include "DNest4/code/DNest4.h"
#include <pybind11/embed.h>
#include <filesystem>
#include <pybind11/numpy.h>
#include <ostream>

namespace PostEnt2026
{

namespace Examples
{


class PythonModelParams
{
    private:
        static int size;
        std::vector<double> us, params;

    public:

        PythonModelParams();

        // Generate from the prior
        void from_prior(DNest4::RNG& rng);

        // Perturb in the usual way
        double perturb(DNest4::RNG& rng);

        // Convert us to params (just calls the Python prior_transform)
        void prior_transform();

        // Gaussian kernel
        double log_kernel(const PythonModelParams& other) const;

        // Print
        void print(std::ostream& out) const;

        friend class PythonModelData;

};


class PythonModelData
{
    private:
        pybind11::object data;

    public:

        // Generate given the parameters
        PythonModelData(const PythonModelParams& params, DNest4::RNG& rng);

        // Evaluate log likelihood
        double log_likelihood(const PythonModelParams& params) const;

};




} // namespace PythonModel


inline std::string& model_path_storage() {
    static std::string path;
    return path;
}

inline void set_model_path(const std::string& p) {
    model_path_storage() = p;
}

inline const std::string& get_model_path() {
    return model_path_storage();
}


} // namespace

#endif
