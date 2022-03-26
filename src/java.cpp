#include <string>

#include "./include/java.h"
#include "./include/util.h"

void gen_javac_cmd(const JakeProj &proj)
{
    if (!proj.sources.empty())
    {
        std::string compile_command = "javac ";
        if (proj.hasLibs)
        {
            compile_command
                .append("-cp ")
                .append(proj.classpath)
                .append(" ");
        }
        compile_command.append("-d ").append(proj.build_path).append(" ").append(proj.sources);
        printf("> Compile java files with javac:\n");
        printf("  $ %s\n", compile_command.c_str());
        exec(compile_command.c_str());
    }
    else
    {
        printf("> Didn't found any .java files in the specified source folder and subfolders.\n\tPath: %s\n", proj.src_path.c_str());
        printf("Press any key to continue or Ctrl+C to exit.");
        getchar();
    }
}

void gen_extract_cmd(const JakeProj &proj)
{
    if (proj.fat_jar == "true" && proj.hasLibs)
    {
        printf("> Extracting jar classes:\n");
        std::string extract_cmd;
        for (auto lib : proj.libs)
        {
            extract_cmd.append("jar xf ").append(proj.pwd).append("/").append(lib);
            printf("  $ %s\n", extract_cmd.c_str());
            std::filesystem::current_path(proj.build_path);
            exec(extract_cmd.c_str());
            std::filesystem::current_path(proj.pwd);
            extract_cmd = "";
        }
    }
}

void gen_jar_cmd(const JakeProj &proj)
{
    std::filesystem::current_path(proj.build_path);
    std::string jar_command = "jar ";
    if (!proj.entry_point.empty())
    {
        jar_command.append("cfe ");
        jar_command.append(proj.jar_name).append(".jar ");
        jar_command.append(proj.entry_point).append(" ");
    }
    else
    {
        jar_command.append("cf ");
        jar_command.append(proj.jar_name).append(".jar ");
    }
    jar_command.append("*");
    printf("> Creating jar file: %s\n", proj.jar_name.c_str());
    printf("  $ %s\n", jar_command.c_str());
    exec(jar_command.c_str());
    std::filesystem::current_path(proj.pwd);
   

}