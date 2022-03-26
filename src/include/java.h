#ifndef JAVA_FILE
#define JAVA_FILE

#include <string>
#include "./main.h"

void gen_javac_cmd(const JakeProj &);
void gen_extract_cmd(const JakeProj &);
void gen_jar_cmd(const JakeProj &);

#endif //JAVA_FILE