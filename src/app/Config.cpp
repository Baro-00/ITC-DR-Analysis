// Config.cpp
#include "Config.hpp"
#include <iostream>

const char* VERSION = "1.0.0";

void Config::printHelp(const char* programName) {
    std::cout << "Usage: " << programName << " [options]\n"
              << "Options:\n"
              << "  -f, --file FILE       Input CSV File\n"
              << "  -m, --madgwick        use Madgwick filter (default)\n"
              << "  -k, --kalman          use Kalman filter\n"
              << "  -o, --output FILE     store output into file\n"
              << "  -v, --version         show version\n"
              << "  -h, --help            show this information\n";
}

void Config::printVersion(void) {
    std::cout << "ITC | Dead Reckoning - Analysis | ver. " << VERSION << " | Bartłomiej Szykuła" << std::endl;
}

void Config::printSummary(const Config config) {
    std::cout << "Filter: " 
              << (config.useKalman ? "Kalman" : "Madgwick") << std::endl;
    
    std::cout << "Input  file: " << config.inputFile << std::endl;
    std::cout << "Output file: " << (config.outputFile.empty() ? "None" : config.outputFile) << std::endl;
}

Config Config::parseCommandLine(int argc, char* argv[]) {
    Config config;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            config.showHelp = true;
            return config;
        } else if (arg == "-v" || arg == "--version") {
            config.showVersion = true;
            return config;
        } else if (arg == "-m" || arg == "--madgwick") {
            config.useMadgwick = true;
            config.useKalman = false;
        } else if (arg == "-k" || arg == "--kalman") {
            config.useKalman = true;
            config.useMadgwick = false;
        } else if (arg == "-f" || arg == "--file") {
            if (i + 1 < argc) {
                config.inputFile = argv[++i];
            } else {
                std::cerr << "Error: Option " << arg << " requires an argument.\n";
                config.showHelp = true;
                return config;
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                config.outputFile = argv[++i];
            } else {
                std::cerr << "Error: Option " << arg << " requires an argument.\n";
                config.showHelp = true;
                return config;
            }
        } else {
            std::cerr << "Unknown option: " << arg << "\n";
            config.showHelp = true;
            return config;
        }
    }

    if (config.inputFile.empty() && !config.showHelp && !config.showVersion) {
        std::cerr << "Error: No input file provided.\n";
        config.showHelp = true;
    }

    return config;
}
