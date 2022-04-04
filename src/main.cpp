#include <cstdio>
#include <filesystem>
#include <cstring>

#include "./include/main.h"
#include "./include/java.h"
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
    std::string jakefile2 = "";
    const char *arg = shift(&argc, &argv);
    JakeProj proj = try_create(load_json(jakefile2.append(arg).append("/jakefile.json").c_str()));

    // I don't belive this is the best option, but it's the easiest.
    std::filesystem::remove_all(proj.build_path);

    gen_javac_cmd(proj);
    gen_extract_cmd(proj);
    gen_jar_cmd(proj);

    printf("> Move .jar to root folder:\n");
    std::string jarPath = proj.build_path;
    jarPath.append("/").append(proj.jar_name).append(".jar");
    if (std::filesystem::exists(jarPath))
    {
        printf("  $ mv %s %s\n", jarPath.c_str(), std::filesystem::current_path().string().append("/").append(proj.jar_name).append(".jar").c_str());
        std::filesystem::rename(jarPath, std::filesystem::current_path().string().append("/").append(proj.jar_name).append(".jar"));
    }
    printf("> Done!\n");
}

JakeProj try_create(const nlohmann::json &jakefile)
{
    JakeProj proj;
    proj.proj_name = try_get(jakefile, "project_name");
    proj.version = try_get(jakefile, "version");
    proj.src_path = try_get_or(jakefile, "src_path", "./src");
    proj.build_path = try_get_or(jakefile, "build_path", "./build");
    proj.entry_point = try_get_or(jakefile, "entry_point", "");
    proj.fat_jar = try_get_or(jakefile, "fat_jar", "true");
    proj.pwd = std::filesystem::current_path();
    proj.jar_name = proj.proj_name;
    proj.jar_name.append("-").append(proj.version);

    // Prepare directories
    std::filesystem::create_directories(proj.src_path);
    std::filesystem::create_directories(proj.build_path);

    // Generate sources
    std::string sources;
    auto paths = collect_files_with_ext_on_path(proj.src_path.c_str(), ".java");
    for (auto path : paths)
        sources.append(path).append(" ");
    proj.sources = sources;

    // Generate file path
    if (jakefile.find("libs") != jakefile.end())
    {
        proj.hasLibs = true;
        std::string classpath = ".:";
        proj.libs = jakefile["libs"].get<std::vector<std::string>>();
        for (auto lib : proj.libs)
            classpath.append(lib).append(":");
        proj.classpath = classpath;
    }

    // Gather include paths
    if (jakefile.find("include") != jakefile.end())
        proj.includes = jakefile["include"].get<std::vector<std::string>>();

    return proj;
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
