#ifndef MAIN_FILE
#define MAIN_FILE

#include <string>
#include <optional>

#include "./json.hpp"

struct JakeProj
{
    std::string projectName;
    std::string version;
    std::string srcPath;
    std::string buildPath;
    std::string entryPoint;
    std::string sources;
    std::string classpath;
    std::string fatJar;
    std::string pwd;
    std::vector<std::string> libs;
    std::vector<std::string> includes;
    bool hasLibs;
    std::string jarName;
};

namespace Jake
{
    void PrintUsage();
    void BuildProject(int, char **);
    JakeProj TryCreateProject(const nlohmann::json &);
}

#endif // MAIN_FILE