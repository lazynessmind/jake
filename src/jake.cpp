#include "jake.h"
#include "java.h"
#include "util.h"
#include "fileutils.h"
#include "algorithm"

void Jake::PrintUsage()
{
    printf("Usage:\n");
    printf("\tjake [options]\n");
    printf("\tOptions:\n");
    printf("\t\t-b: Only build.\n");
    printf("\t\t-r: Run jar program.\n");
    printf("\t\t-br: Build and run the jar program.\n");
    printf("\t\t-v: Print version.\n");
}

void Jake::PrepareProject(const JakeProj &proj)
{
    if (!std::filesystem::exists("./.cache/"))
        std::filesystem::create_directory("./.cache/");

    printf("%s> Preparing:%s\n", Util::GetAnsiColorStr(Util::ANSIColors::GREEN), Util::GetAnsiColorStr(Util::ANSIColors::RESET));
    if (!proj.externalLibraries.empty())
    {
        if (proj.repositories.empty())
        {
            printf("%s> Using external libraries without any repositories.%s\n", Util::GetAnsiColorStr(Util::ANSIColors::RED), Util::GetAnsiColorStr(Util::ANSIColors::RESET));
            exit(1);
        }
        for (const auto &lib : proj.externalLibraries)
        {
            std::string libUrlPath;
            libUrlPath.append(lib.groupId);
            std::replace(libUrlPath.begin(), libUrlPath.end(), '.', '/');
            libUrlPath.append("/").append(lib.artifact).append("/").append(lib.version).append("/");
            std::string libName = lib.artifact;
            libName.append("-").append(lib.version).append(".jar");
            libUrlPath.append(libName);

            if (std::filesystem::exists("./.cache/" + libName))
            {
                printf("  > Cached: %s\n", libUrlPath.c_str());
                continue;
            }

            bool found = false;

            for (auto &repo : proj.repositories)
            {
                std::string fullPath = repo;
                if (!repo.ends_with("/"))
                    fullPath.append("/");
                fullPath.append(libUrlPath);
                std::string curlCmd = "curl ";
                curlCmd.append(fullPath).append(" -o ./.cache/").append(libName);
                Util::ExecuteCommand(curlCmd.c_str());

                if (std::filesystem::exists("./.cache/" + libName))
                {
                    found = true;
                    printf("  > Found: %s\n", libUrlPath.c_str());
                    break;
                }
            }

            if (!found)
                printf("Couldnt found %s in any of the given repositories.\n", libUrlPath.c_str());
        }
    }
}

void Jake::BuildProject(int argc, char **argv, bool run)
{
    JakeProj proj = TryCreateProject(Util::LoadJson("./jakefile.json"));
    PrepareProject(proj);

    // I don't belive this is the best option, but it's the easiest.
    std::filesystem::remove_all(proj.buildPath);

    Java::CompileJavaSources(proj);
    Java::ExtractExternalLibraries(proj);
    Java::CreateJar(proj);

    std::string jarPath = proj.buildPath;
    jarPath.append("/").append(proj.jarName).append(".jar");
    if (std::filesystem::exists(jarPath))
    {
        std::filesystem::rename(jarPath, std::filesystem::current_path().string().append("/").append(proj.jarName).append(".jar"));
    }
    printf("%s> Done!%s\n", Util::GetAnsiColorStr(Util::GREEN), Util::GetAnsiColorStr(Util::RESET));

    if (run)
    {
        std::string runCmd = "java -jar ";
        runCmd.append(proj.jarName).append(".jar");
        printf("=========================================\n%s", Util::ExecuteCommand(runCmd.c_str()).c_str());
    }
}

void Jake::RunProject()
{
    JakeProj proj = TryCreateProject(Util::LoadJson("./jakefile.json"));
    std::string jarName = proj.jarName;
    if (std::filesystem::exists(jarName.append(".jar")))
    {
        std::string runCmd = "java -jar ";
        runCmd.append(proj.jarName).append(".jar");
        printf("%s", Util::ExecuteCommand(runCmd.c_str()).c_str());
    }
    else
    {
        printf("Error: Couldn't found %s in this path: %s\n", jarName.c_str(), proj.pwd.c_str());
    }
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
    auto paths = FileUtils::GatherAllContentsInFolder(proj.srcPath.c_str(), ".java");
    for (auto path : paths)
        sources.append(path).append(" ");
    proj.sources = sources;

    // Get all repositories
    if (jakefile.find("repositories") != jakefile.end())
        proj.repositories = jakefile["repositories"].get<std::vector<std::string>>();

    // Gather all external libs
    if (jakefile.find("externalLibs") != jakefile.end())
    {
        for (const auto &json : jakefile["externalLibs"])
        {
            // TODO: Implement json types
            ExternalLibrary lib;
            lib.groupId = json["groupId"].get<std::string>();
            lib.artifact = json["artifact"].get<std::string>();
            lib.version = json["version"].get<std::string>();
            proj.externalLibraries.push_back(lib);
        }
    }

    // Gather exclude paths
    if (jakefile.find("exclude") != jakefile.end())
        proj.excludes = jakefile["exclude"].get<std::vector<std::string>>();

    // Generate file path
    auto libs = FileUtils::GatherAllContentsInFolder(proj.libsPath.c_str(), ".jar");
    if (!libs.empty())
    {
        std::string classpath = ".:";
        for (auto lib : libs)
        {
            if (std::find(proj.excludes.begin(), proj.excludes.end(), lib) != proj.excludes.end())
            {
                // TODO: Find better way to display this.
                // printf("> WARN! Ignoring file: %s Motive: Found on the exclude list.\n", lib.c_str());
            }
            else
            {
                classpath.append(lib).append(":");
                proj.libs.push_back(lib);
            }
        }
        proj.classpath = classpath;
    }

    // Generate file path
    auto repoLibs = FileUtils::GatherAllContentsInFolder("./.cache/", ".jar");
    if (!repoLibs.empty())
    {
        std::string classpath = proj.classpath;
        for (auto lib : repoLibs)
        {
            if (std::find(proj.excludes.begin(), proj.excludes.end(), lib) != proj.excludes.end())
            {
                // TODO: Find better way to display this.
                // printf("> WARN! Ignoring file: %s Motive: Found on the exclude list.\n", lib.c_str());
            }
            else
            {
                classpath.append(lib).append(":");
            }
        }
        proj.classpath = classpath;
    }

    // Gather include paths
    if (jakefile.find("include") != jakefile.end())
        proj.includes = jakefile["include"].get<std::vector<std::string>>();

    return proj;
}