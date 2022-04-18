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
    proj.projectName = Util::TryGet(jakefile, "projectName");
    proj.version = Util::TryGet(jakefile, "version");
    proj.srcPath = Util::TryGetOr(jakefile, "srcPath", "./src");
    proj.buildPath = Util::TryGetOr(jakefile, "buildPath", "./build");
    proj.libsPath = Util::TryGetOr(jakefile, "libsPath", "./libs");
    proj.entryPoint = Util::TryGetOr(jakefile, "entryPoint", "");
    proj.fatJar = Util::TryGetOr(jakefile, "fat_jar", "true");
    proj.pwd = std::filesystem::current_path();
    proj.jarName = proj.projectName;
    proj.jarName.append("-").append(proj.version);

    // Prepare directories
    std::filesystem::create_directories(proj.srcPath);
    std::filesystem::create_directories(proj.buildPath);
    std::filesystem::create_directories(proj.libsPath);

    // Generate sources
    std::string sources;
    auto paths = Util::CollectFilesWithExtOnPath(proj.srcPath.c_str(), ".java");
    for (auto path : paths)
        sources.append(path).append(" ");
    proj.sources = sources;

    // Generate file path
    auto libs = Util::CollectFilesWithExtOnPath(proj.libsPath.c_str(), ".jar");
    if (!libs.empty())
    {
        std::string classpath = ".:";
        for (auto lib : libs)
        {
            classpath.append(lib).append(":");
            proj.libs.push_back(lib);
        }
        proj.classpath = classpath;
    }

    // Gather include paths
    if (jakefile.find("include") != jakefile.end())
        proj.includes = jakefile["include"].get<std::vector<std::string>>();

    // Gather exclude paths
    if (jakefile.find("exclude") != jakefile.end())
        proj.excludes = jakefile["exclude"].get<std::vector<std::string>>();

    return proj;
}