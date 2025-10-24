#include <miniros/ros.h>
#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    CLI::App app{"dodo_bridge - Dodobot ROS Bridge Application"};

    // Command line arguments
    int verbosity = 0;

    // Add options
    app.add_option("-v,--verbose", verbosity, "Verbosity level (0-3)")
        ->check(CLI::Range(0, 3));

    // Parse command line
    CLI11_PARSE(app, argc, argv);

    // Display parsed arguments
    std::cout << "Dodo Bridge starting with:" << std::endl;
    std::cout << "  Verbosity: " << verbosity << std::endl;

    return 0;
}
