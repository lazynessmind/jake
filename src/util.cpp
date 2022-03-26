#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "./include/util.h"

// https://stackoverflow.com/a/478960
std::string exec(const char *cmd)
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

// https://stackoverflow.com/a/46931770
std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

char *shift(int *argc, char ***argv)
{
    assert(*argc > 0);
    char *result = **argv;
    *argv += 1;
    *argc -= 1;
    return result;
}

std::map<std::string, std::string> parse_properties_file(const char *path)
{
    std::map<std::string, std::string> config;
    std::ifstream f(path);
    std::stringstream buffer;
    buffer << f.rdbuf();
    std::vector lines = split(buffer.str(), "\n");
    for (std::string line : lines)
    {
        std::vector props = split(line.c_str(), "=");
        config.insert(std::pair(props[0], props[1]));
    }
    return config;
}

std::string get_prop_or_return(std::map<std::string, std::string> map, std::string key, std::string fallback)
{
    return map.find(key) != map.end() ? map[key] : fallback;
}

bool has_prop(std::map<std::string, std::string> map, std::string key)
{
    return map.find(key) != map.end();
}

nlohmann::json load_json(const char *path)
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
