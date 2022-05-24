#ifndef MAIN_FILE
#define MAIN_FILE

#include <string>
#include <optional>

#include "./json.hpp"

struct ExternalLibrary
{
    std::string groupId;
    std::string artifact;
    std::string version;
};

struct JakeProj
{
    std::string projectName;
    std::string version;
    std::string srcPath;
    std::string buildPath;
    std::string libsPath;
    std::string entryPoint;
    std::string sources;
    std::string classpath;
    std::string fatJar;
    std::string pwd;
    std::vector<std::string> libs;
    std::vector<std::string> includes;
    std::vector<std::string> excludes;
    std::vector<std::string> repositories;
    std::vector<ExternalLibrary> externalLibraries;
    std::string jarName;
};

namespace Jake
{
    void PrintUsage();
    void PrepareProject(const JakeProj& );
    void BuildProject(int, char **, bool run = false);
    void RunProject();
    JakeProj TryCreateProject(const nlohmann::json &);
}

#endif // MAIN_FILE