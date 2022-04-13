#ifndef JAVA_FILE
#define JAVA_FILE

#include <string>

#include "./jake.h"

namespace Java
{
    void CompileJavaSources(const JakeProj &);
    void ExtractExternalLibraries(const JakeProj &);
    void CreateJar(const JakeProj &);
}

#endif // JAVA_FILE