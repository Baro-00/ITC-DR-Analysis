// main.cpp
#include "Config.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    Config config = Config::parseCommandLine(argc, argv);

    if (config.showHelp) {
        Config::printHelp(argv[0]);
        return 0;
    }

    if (config.showVersion) {
        Config::printVersion();
        return 0;
    }

    config.printSummary(config);
    
    return 0;
}