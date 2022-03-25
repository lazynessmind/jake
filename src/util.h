#ifndef UTIL_FILE
#define UTIL_FILE

#include <string>
#include <vector>
#include <map>

std::string exec(const char *);
std::vector<std::string> split_by_delimiter(std::string, std::string);
char *shift(int *, char ***);
std::map<std::string, std::string> parse_properties_file(const char *);
std::string get_prop_or_return(std::map<std::string, std::string>, std::string, std::string);
bool has_prop(std::map<std::string, std::string>, std::string);

#endif // UTIL_FILE