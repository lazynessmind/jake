#ifndef FILEUTILS_FILE
#define FILEUTILS_FILE

#include <string>
#include <vector>

namespace FileUtils
{
    enum PathFilter
    {
        ALL_IN_FOLDER,
        ALL_WITH_EXTENSION,
        ALL_IN_FOLDER_WITH_SUBFOLDER,
        ALL_WITH_EXTENSION_WITH_SUBFOLDER,
        SINGLE_FILE,
        SINGLE_FOLDER
    };

    struct FileInfo
    {
        std::string filename;
        std::string fullfilename;
        std::string extension;
        std::string filepath;
        std::string fullpath;
    };

    void CreateDirectoriesAndCopyTo(const FileUtils::FileInfo &, const std::string &);
    PathFilter GetFilter(const std::string &);
    FileInfo GatherFileInfoFromPath(const std::string &);
    const char *FilterToString(PathFilter);
    std::vector<std::string> GatherAllFilesInFolder(const std::string&, const char* ext = "*");
    std::vector<std::string> GatherAllContentsInFolder(const char *, const char * ext = "*");
}

#endif // FILEUTILS_FILE