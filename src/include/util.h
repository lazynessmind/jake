#ifndef UTIL_FILE
#define UTIL_FILE

#include <string>
#include <vector>
#include <map>

#include "./json.hpp"

std::string exec(const char *);
char *shift(int *, char ***);
nlohmann::json load_json(const char *);
std::string try_get(const nlohmann::json &, const char *);
std::string try_get_or(const nlohmann::json &, const char *, const char *);
std::vector<std::string> collect_files_with_ext_on_path(const char *, const char *);

#endif // UTIL_FILE