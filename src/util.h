#ifndef UTIL_FILE
#define UTIL_FILE

#include <string>
#include <vector>
#include <map>

std::string exec(const char *);
std::vector<std::string> split_by_delimiter(std::string, std::string);
char *shift(int *, char ***);
std::map<std::string, std::string> parse_properties_file(const char *);

#endif //UTIL_FILE