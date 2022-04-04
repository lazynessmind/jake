#ifndef MAIN_FILE
#define MAIN_FILE

#include <string>
#include <optional>

#include "./json.hpp"

struct JakeProj
{
    std::string proj_name;
    std::string version;
    std::string src_path;
    std::string build_path;
    std::string entry_point;
    std::string sources;
    std::string classpath;
    std::string fat_jar;
    std::string pwd;
    std::vector<std::string> libs;
    std::vector<std::string> includes;
    bool hasLibs;
    std::string jar_name;
};

void print_usage();
void build_project(int, char **);
JakeProj try_create(const nlohmann::json &);

#endif // MAIN_FILE