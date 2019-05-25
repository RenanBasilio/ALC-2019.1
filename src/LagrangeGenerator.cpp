#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <Generators.hpp>

static void show_usage( std::string name ) {
    std::cerr << "Usage: " << name.substr( name.find_last_of('\\')+1 ) << " <options> [integration points]" << std::endl << std::endl
              << "Options:" << std::endl
              << "-h, --help         Show this help message" << std::endl
              << "-f, --file <name>  Write C++ code to file instead of outputting to stdout" << std::endl;
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }
    std::ofstream file;
    size_t max_points = 0;

    for ( int i = 1; i < argc; i++ ) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        }
        else if (( arg == "-f") || (arg == "--file")) {
            file.open(argv[i+1]);
            i++;
        }
        else max_points = std::atoi(arg.c_str());
    }

    if (max_points == 0) {
        std::cerr << "Number of integration points must be greater than 0." << std::endl;
        return 1;
    }

    std::ostream& out = ( file.is_open() ? file : std::cout );

    out << std::setprecision(std::numeric_limits<real>::max_digits10);

    out << "#include <Definitions.hpp>" << std::endl 
        << "#include <vector>" << std::endl 
        << "extern const std::vector<std::vector<real>> lagrange_weights;" << std::endl;

    out << "const std::vector<std::vector<real>> lagrange_weights = { { 0 }, " << std::endl;

    for (size_t i = 1; i < max_points+1; i++) {
        out << "{ ";
        std::vector<real> weights = generateLagrangeWeights(i);
        for (size_t j = 0; j < weights.size(); j++) {
            out << weights.at(j);
            if ( j != weights.size()-1 ) out << ", ";
        }
        out << " }";
        if ( i != max_points ) out << "," << std::endl;
    }

    out << " };" << std::endl << std::endl;

    file.close();

    return 0;
}
