#ifndef UTIL_FILE
#define UTIL_FILE

#include <string>
#include <vector>
#include <map>

#include "./json.hpp"

std::string exec(const char *);
std::vector<std::string> split_by_delimiter(std::string, std::string);
char *shift(int *, char ***);
std::map<std::string, std::string> parse_properties_file(const char *);
std::string get_prop_or_return(std::map<std::string, std::string>, std::string, std::string);
bool has_prop(std::map<std::string, std::string>, std::string);
nlohmann::json load_json(const char *);
std::string try_get(const nlohmann::json &, const char *);
std::vector<std::string> collect_files_with_ext_on_path(const char *, const char *);

#endif // UTIL_FILE