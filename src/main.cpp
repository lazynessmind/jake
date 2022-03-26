#include <cstdio>
#include <filesystem>
#include <cstring>

#include "./include/util.h"

void print_usage()
{
    printf("Usage:\n");
    printf("\tjake [options] [path to jakefile]\n");
    printf("\tOptions:\n");
    printf("\t\t-b: Only build.\n");
    printf("\t\t-v: Print version.\n");
}

void build_project(int argc, char **argv)
{
    std::string jakefile = "";
    const char *arg = shift(&argc, &argv);
    auto props = parse_properties_file(jakefile.append(arg).append("/jakefile.properties").c_str());

    const auto build_path = get_prop_or_return(props, "build_path", "./build");

    std::string sources;
    for (const auto &p : std::filesystem::recursive_directory_iterator(get_prop_or_return(props, "src_path", ".")))
        if (!std::filesystem::is_directory(p))
            if (p.path().filename().extension() == ".java")
                sources.append(p.path()).append(" ");

    // Compile the collected sources with the -d option to specify the build folder.
    if (!sources.empty())
    {
        printf("> Compile sources:\n");
        std::string compile_command = "javac -d ";
        compile_command.append(build_path)
            .append(" ")
            .append(sources);
        printf("$ %s\n", compile_command.c_str());
        exec(compile_command.c_str());
        printf("> Done!\n");
    }
    else
    {
        printf("> Didn't found any .java files in the specified source folder and subfolders.\n\tPath: %s\n", props["src_path"].c_str());
        printf("Press any key to continue or Ctrl+C to exit.");
        getchar();
    }

    // Create the .jar file with the classes available in the `build_path` props and includes the `entry_point`.
    printf("> Create .jar file:\n");
    std::string pwd = std::filesystem::current_path().string();
    printf("$ cd %s\n", build_path.c_str());
    std::filesystem::current_path(build_path);
    std::string jar_command = "jar ";
    if (has_prop(props, "entry_point"))
    {
        jar_command.append("cfe ");
        jar_command.append(props["entry_point"]).append(" ");
    }
    else
    {
        jar_command.append("cf ");
    }
    jar_command.append(props["jar_name"]).append(".jar ").append("*");
    printf("$ %s\n", jar_command.c_str());
    exec(jar_command.c_str());
    printf("$ cd %s\n", pwd.c_str());
    std::filesystem::current_path(pwd);
    printf("> Done!\n");

    printf("> Move .jar to root folder:\n");
    std::string jarPath = props["build_path"].append("/").append(props["jar_name"]).append(".jar");
    if (std::filesystem::exists(jarPath))
    {
        printf("$ mv %s %s\n", jarPath.c_str(), std::filesystem::current_path().string().append("/").append(props["jar_name"]).append(".jar").c_str());
        std::filesystem::rename(jarPath, std::filesystem::current_path().string().append("/").append(props["jar_name"]).append(".jar"));
    }
    printf("> Done!\n");
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        print_usage();
        return 1;
    }
    else
    {
        shift(&argc, &argv); // Skip program
        const char *arg = shift(&argc, &argv);
        if (strcmp(arg, "-v") == 0)
        {
            printf("Version: jake-0.0.1\n");
            return 1;
        }
        else if (strcmp(arg, "-b") == 0)
        {
            build_project(argc, argv);
            return 1;
        }
        else
        {
            print_usage();
            return 1;
        }
    }
    return 0;
}
