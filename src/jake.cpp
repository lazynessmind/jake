#include "jake.h"
#include "java.h"
#include "util.h"

void Jake::PrintUsage()
{
    printf("Usage:\n");
    printf("\tjake [options] [path to jakefile]\n");
    printf("\tOptions:\n");
    printf("\t\t-b: Only build.\n");
    printf("\t\t-v: Print version.\n");
}

void Jake::BuildProject(int argc, char **argv)
{
    std::string jakefile = "";
    const char *arg = Util::ShiftArg(&argc, &argv);
    JakeProj proj = TryCreateProject(Util::LoadJson(jakefile.append(arg).append("/jakefile.json").c_str()));

    // I don't belive this is the best option, but it's the easiest.
    std::filesystem::remove_all(proj.buildPath);

    Java::CompileJavaSources(proj);
    Java::ExtractExternalLibraries(proj);
    Java::CreateJar(proj);

    printf("> Move .jar to root folder:\n");
    std::string jarPath = proj.buildPath;
    jarPath.append("/").append(proj.jarName).append(".jar");
    if (std::filesystem::exists(jarPath))
    {
        printf("  $ mv %s %s\n", jarPath.c_str(), std::filesystem::current_path().string().append("/").append(proj.jarName).append(".jar").c_str());
        std::filesystem::rename(jarPath, std::filesystem::current_path().string().append("/").append(proj.jarName).append(".jar"));
    }
    printf("> Done!\n");
}

JakeProj Jake::TryCreateProject(const nlohmann::json &jakefile)
{
    JakeProj proj;
    proj.projectName = Util::TryGet(jakefile, "project_name");
    proj.version = Util::TryGet(jakefile, "version");
    proj.srcPath = Util::TryGetOr(jakefile, "srcPath", "./src");
    proj.buildPath = Util::TryGetOr(jakefile, "buildPath", "./build");
    proj.entryPoint = Util::TryGetOr(jakefile, "entry_point", "");
    proj.fatJar = Util::TryGetOr(jakefile, "fat_jar", "true");
    proj.pwd = std::filesystem::current_path();
    proj.jarName = proj.projectName;
    proj.jarName.append("-").append(proj.version);

    // Prepare directories
    std::filesystem::create_directories(proj.srcPath);
    std::filesystem::create_directories(proj.buildPath);

    // Generate sources
    std::string sources;
    auto paths = Util::CollectFilesWithExtOnPath(proj.srcPath.c_str(), ".java");
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