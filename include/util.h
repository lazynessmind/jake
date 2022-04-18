#ifndef UTIL_FILE
#define UTIL_FILE

#include <string>
#include <vector>
#include <map>

#include "./json.hpp"

namespace Util
{
    std::string ExecuteCommand(const char *);
    char *ShiftArg(int *, char ***);
    nlohmann::json LoadJson(const char *);
    std::string TryGet(const nlohmann::json &, const char *);
    std::string TryGetOr(const nlohmann::json &, const char *, const char *);
    std::vector<std::string> CollectFilesWithExtOnPath(const char *, const char * = "*");
    std::vector<std::string> SplitString(const std::string&, const std::string&);
}

#endif // UTIL_FILE