// Config.hpp
#pragma once
#include <string>

struct Config {
    std::string inputFile;
    std::string outputFile;
    bool useKalman;
    bool useMadgwick;
    bool showVersion;
    bool showHelp;

    Config()
        : inputFile("")
        , outputFile("")
        , useKalman(false)
        , useMadgwick(true)
        , showVersion(false)
        , showHelp(false)
    {}

    static Config parseCommandLine(int argc, char* argv[]);

    static void printHelp(const char* programName);

    static void printVersion(void);

    static void printSummary(const Config config);
};