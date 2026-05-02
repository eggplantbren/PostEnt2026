#ifndef PostEnt2021_Constants_h
#define PostEnt2021_Constants_h

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// From copilot

namespace PostEnt2026
{

namespace Options
{

// --- tiny trim helper -------------------------------------------------------
inline std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    auto end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

// --- class holding all constants --------------------------------------------
class Values {
public:
    // defaults
    static inline int num_runs = 1000;
    static inline double tolerance = 1.0E-3;

private:
    // static initializer
    struct Loader {
        Loader() {
            load_from_file("POSTENT_OPTIONS");
        }

        void load_from_file(const std::string& path) {
            std::ifstream f(path);
            if (!f) return; // file missing → keep defaults

            std::string line;
            while (std::getline(f, line)) {
                // strip comments
                auto hash = line.find('#');
                if (hash != std::string::npos)
                    line = line.substr(0, hash);

                line = trim(line);
                if (line.empty()) continue;

                auto eq = line.find('=');
                if (eq == std::string::npos) continue;

                std::string key = trim(line.substr(0, eq));
                std::string val = trim(line.substr(eq + 1));

                if (key == "num_runs")
                    Values::num_runs = std::stoi(val);
                else if (key == "tolerance")
                    Values::tolerance = std::stod(val);
            }
        }
    };

    // static instance triggers loading at startup
    static inline Loader loader{};
};

// public aliases so old code still works
static inline int& num_runs = Values::num_runs;
static inline double& tolerance = Values::tolerance;

} // namespace Options
} // namespace PostEnt2026

#endif

