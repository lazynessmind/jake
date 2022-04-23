#include <filesystem>

#include "fileutils.h"
#include "util.h"

using Filter = FileUtils::PathFilter;
using FileInfo = FileUtils::FileInfo;

Filter FileUtils::GetFilter(const std::string &path)
{

    auto fileInfo = GatherFileInfoFromPath(path);
    auto pathParts = Util::SplitString(path, "/");

    if (path.ends_with("/*"))
    {
        if (pathParts[pathParts.size() - 2] == "**")
        {
            return Filter::ALL_IN_FOLDER_WITH_SUBFOLDER;
        }
        else
        {
            return Filter::ALL_IN_FOLDER;
        }
    }
    else if (path.ends_with("/") || std::filesystem::is_directory(path))
    {
        return Filter::SINGLE_FOLDER;
    }
    else if (fileInfo.fullfilename.starts_with("*."))
    {
        if (pathParts[pathParts.size() - 2] == "**")
        {
            return Filter::ALL_WITH_EXTENSION_WITH_SUBFOLDER;
        }
        else
        {
            return Filter::ALL_WITH_EXTENSION;
        }
    }
    else if (!std::filesystem::is_directory(path))
    {
        return Filter::SINGLE_FILE;
    }
    else
    {
        printf("Unreachable state for: %s\n", path.c_str());
        exit(-1);
    }
}

FileInfo FileUtils::GatherFileInfoFromPath(const std::string &path)
{
    auto finalPathPart = Util::SplitString(path, "/").back();
    std::string extension = ".";
    extension.append(Util::SplitString(finalPathPart, ".").back());
    auto fileName = finalPathPart.substr(0, finalPathPart.length() - (extension.length() + 1));
    auto filePath = path.substr(0, path.length() - finalPathPart.length());

    if (filePath.empty())
        filePath = "./";

    return {fileName, finalPathPart, extension, filePath, path};
}

const char *FileUtils::FilterToString(FileUtils::PathFilter filter)
{
    switch (filter)
    {
    case PathFilter::ALL_IN_FOLDER:
        return "PathFilter::ALL_IN_FOLDER";
    case PathFilter::ALL_IN_FOLDER_WITH_SUBFOLDER:
        return "PathFilter::ALL_IN_FOLDER_WITH_SUBFOLDER";
    case PathFilter::ALL_WITH_EXTENSION:
        return "PathFilter::ALL_WITH_EXTENSION";
    case PathFilter::ALL_WITH_EXTENSION_WITH_SUBFOLDER:
        return "PathFilter::ALL_WITH_EXTENSION_WITH_SUBFOLDER";
    case PathFilter::SINGLE_FILE:
        return "PathFilter::SINGLE_FILE";
    case PathFilter::SINGLE_FOLDER:
        return "PathFilter::SINGLE_FOLDER";

    default:
        printf("Unreachable state!!");
        exit(-1);
    }
}
void FileUtils::CreateDirectoriesAndCopyTo(const FileInfo &fileinfo, const std::string &to)
{
    std::string tmp = to;
    tmp.append("/").append(fileinfo.filepath);
    if (!std::filesystem::exists(tmp))
    {
        std::filesystem::create_directories(tmp);
    }
    std::filesystem::copy(fileinfo.fullpath, tmp);
}

std::vector<std::string> FileUtils::GatherAllFilesInFolder(const std::string &path, const char* ext)
{
    std::vector<std::string> files;
    if (!std::filesystem::is_directory(path))
    {
        printf("Given path isn't a directory! Abort.");
        exit(1);
    }
    for (const auto &dirPath : std::filesystem::directory_iterator(path))
    {
        if (!dirPath.is_directory())
            if (dirPath.path().filename().extension() == ext || strcmp(ext, "*") == 0)
                files.emplace_back(dirPath.path());
    }
    return files;
}

std::vector<std::string> FileUtils::GatherAllContentsInFolder(const char *path, const char *extension)
{
    std::vector<std::string> paths;
    for (const auto &p : std::filesystem::recursive_directory_iterator(path))
        if (!std::filesystem::is_directory(p))
            if (p.path().filename().extension() == extension || strcmp(extension, "*") == 0)
                paths.emplace_back(p.path());
    return paths;
}