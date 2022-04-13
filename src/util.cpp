#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "./include/util.h"

// https://stackoverflow.com/a/478960
std::string Util::ExecuteCommand(const char *cmd)
{
    char buffer[128];
    std::string result = "";
    auto *pipe = popen(cmd, "r");
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try
    {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
        {
            result += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

char *Util::ShiftArg(int *argc, char ***argv)
{
    assert(*argc > 0);
    char *result = **argv;
    *argv += 1;
    *argc -= 1;
    return result;
}

nlohmann::json Util::LoadJson(const char *path)
{
    if (std::filesystem::exists(path))
    {
        std::ifstream f(path);
        std::stringstream buffer;
        buffer << f.rdbuf();
        return nlohmann::json::parse(buffer.str());
    }
    else
    {
        printf("> File not found in path:\n\t%s\n", path);
        exit(-1);
    }
    return nullptr;
}

std::string Util::TryGet(const nlohmann::json &json, const char *key)
{
    if (json.find(key) != json.end())
    {
        return json[key].get<std::string>();
    }
    else
    {
        printf("> Missing property on jakefile.json. \"%s\"\n", key);
        exit(-1);
    }
    return nullptr;
}

std::string Util::TryGetOr(const nlohmann::json &json, const char *key, const char* fallback)
{
    return json.find(key) != json.end() ? json[key].get<std::string>() : fallback;
}

std::vector<std::string> Util::CollectFilesWithExtOnPath(const char *path, const char *extension)
{
    std::vector<std::string> paths;
    for (const auto &p : std::filesystem::recursive_directory_iterator(path))
        if (!std::filesystem::is_directory(p))
            if (p.path().filename().extension() == extension)
                paths.emplace_back(p.path());
    return paths;
}
