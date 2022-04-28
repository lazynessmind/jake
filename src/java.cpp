#include <string>

#include "java.h"
#include "util.h"
#include "fileutils.h"

void Java::CompileJavaSources(const JakeProj &proj)
{
    if (!proj.sources.empty())
    {
        std::string javacCommand = "javac ";
        if (!proj.libs.empty())
        {
            javacCommand
                .append("-cp ")
                .append(proj.classpath)
                .append(" ");
        }
        javacCommand.append("-d ").append(proj.buildPath).append(" ").append(proj.sources);
        printf("> Compile java files with javac:\n");
        printf("  $ %s\n", javacCommand.length() > 70 ? javacCommand.substr(0, 70).append("...").c_str() : javacCommand.c_str());
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
    if (proj.fatJar == "true" && !proj.libs.empty())
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
    printf("> Collecting files to include:\n");
    if (!proj.includes.empty())
    {
        std::string tmp = proj.buildPath;
        for (auto include : proj.includes)
        {
            if (FileUtils::GetFilter(include) == FileUtils::ALL_IN_FOLDER || FileUtils::GetFilter(include) == FileUtils::SINGLE_FOLDER)
            {
                auto actualPath = include.substr(0, include.length() - 1);
                auto allInPath = FileUtils::GatherAllFilesInFolder(actualPath.c_str());
                for (auto file : allInPath)
                {
                    auto fileInfo = FileUtils::GatherFileInfoFromPath(file);
                    if (std::find(proj.excludes.begin(), proj.excludes.end(), file) != proj.excludes.end())
                    {
                        printf("    > Ignoring file: %s Motive: Found on the exclude list.\n", file.c_str());
                    }
                    else
                    {
                        FileUtils::CreateDirectoriesAndCopyTo(fileInfo, proj.buildPath);
                    }
                }
            }
            else if (!std::filesystem::is_directory(include))
            {

                if (FileUtils::GetFilter(include) == FileUtils::ALL_WITH_EXTENSION)
                {
                    auto fileInfo = FileUtils::GatherFileInfoFromPath(include);
                    auto withExt = FileUtils::GatherAllFilesInFolder(fileInfo.filepath.c_str(), fileInfo.extension.c_str());

                    for (auto file : withExt)
                    {

                        auto fileinfo = FileUtils::GatherFileInfoFromPath(file);

                        if (std::find(proj.excludes.begin(), proj.excludes.end(), file) != proj.excludes.end())
                        {
                            printf("    > Ignoring file: %s Motive: Found on the exclude list.\n", file.c_str());
                        }
                        else
                        {
                            FileUtils::CreateDirectoriesAndCopyTo(fileinfo, proj.buildPath);
                        }
                    }
                }
                else if (FileUtils::GetFilter(include) == FileUtils::ALL_WITH_EXTENSION_WITH_SUBFOLDER)
                {
                    auto fileInfo = FileUtils::GatherFileInfoFromPath(include);

                    std::string filter = "/**/*";
                    filter.append(fileInfo.extension);

                    std::string path = fileInfo.fullpath.substr(0, fileInfo.fullpath.length() - filter.length());

                    auto withExt = FileUtils::GatherAllContentsInFolder(path.c_str(), fileInfo.extension.c_str());

                    for (auto file : withExt)
                    {

                        auto fileinfo = FileUtils::GatherFileInfoFromPath(file);

                        if (std::find(proj.excludes.begin(), proj.excludes.end(), file) != proj.excludes.end())
                        {
                            printf("    > Ignoring file: %s Motive: Found on the exclude list.\n", file.c_str());
                        }
                        else
                        {
                            FileUtils::CreateDirectoriesAndCopyTo(fileinfo, proj.buildPath);
                        }
                    }
                }
                else
                {
                    if (FileUtils::GetFilter(include) == FileUtils::ALL_IN_FOLDER_WITH_SUBFOLDER)
                    {
                        auto fileInfo = FileUtils::GatherFileInfoFromPath(include);

                        std::string filter = "/**/*";

                        std::string path = fileInfo.fullpath.substr(0, fileInfo.fullpath.length() - filter.length());

                        auto withExt = FileUtils::GatherAllContentsInFolder(path.c_str());

                        for (auto file : withExt)
                        {

                            auto fileinfo = FileUtils::GatherFileInfoFromPath(file);

                            if (std::find(proj.excludes.begin(), proj.excludes.end(), file) != proj.excludes.end())
                            {
                                printf("    > Ignoring file: %s Motive: Found on the exclude list.\n", file.c_str());
                            }
                            else
                            {
                                FileUtils::CreateDirectoriesAndCopyTo(fileinfo, proj.buildPath);
                            }
                        }
                    }
                    else if (std::filesystem::is_directory(include))
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