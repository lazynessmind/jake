#include <string>

#include "java.h"
#include "util.h"

void Java::CompileJavaSources(const JakeProj &proj)
{
    if (!proj.sources.empty())
    {
        std::string javacCommand = "javac ";
        if (proj.hasLibs)
        {
            javacCommand
                .append("-cp ")
                .append(proj.classpath)
                .append(" ");
        }
        javacCommand.append("-d ").append(proj.buildPath).append(" ").append(proj.sources);
        printf("> Compile java files with javac:\n");
        printf("  $ %s\n", javacCommand.c_str());
        Util::ExecuteCommand(javacCommand.c_str());
    }
    else
    {
        printf("> Didn't found any .java files in the specified source folder and subfolders.\n\tPath: %s\n", proj.srcPath.c_str());
        printf("Press any key to continue or Ctrl+C to exit.");
        getchar();
    }
}

void Java::ExtractExternalLibraries(const JakeProj &proj)
{
    if (proj.fatJar == "true" && proj.hasLibs)
    {
        printf("> Extracting jar classes:\n");
        std::string extractCommand;
        for (auto lib : proj.libs)
        {
            extractCommand.append("jar xf ").append(proj.pwd).append("/").append(lib);
            printf("  $ %s\n", extractCommand.c_str());
            std::filesystem::current_path(proj.buildPath);
            Util::ExecuteCommand(extractCommand.c_str());
            std::filesystem::current_path(proj.pwd);
            extractCommand = "";
        }
    }
}

void Java::CreateJar(const JakeProj &proj)
{
    if (!proj.includes.empty())
    {
        for (auto include : proj.includes)
        {
            if (std::filesystem::is_directory(include))
            {
                std::string tmp = proj.buildPath;
                std::filesystem::create_directories(tmp.append("/").append(include));
                std::filesystem::copy(include, tmp);
            }
            else
            {
                std::filesystem::copy(include, proj.buildPath);
            }
        }
    }
    std::filesystem::current_path(proj.buildPath);
    std::string createJarCommand = "jar ";
    if (!proj.entryPoint.empty())
    {
        createJarCommand.append("cfe ");
        createJarCommand.append(proj.jarName).append(".jar ");
        createJarCommand.append(proj.entryPoint).append(" ");
    }
    else
    {
        createJarCommand.append("cf ");
        createJarCommand.append(proj.jarName).append(".jar ");
    }
    createJarCommand.append("* ");
    printf("> Creating jar file: %s\n", proj.jarName.c_str());
    printf("  $ %s\n", createJarCommand.c_str());
    Util::ExecuteCommand(createJarCommand.c_str());
    std::filesystem::current_path(proj.pwd);
}