#include <filesystem>

#include <catch2/catch.hpp>

#include <fileutils.h>
#include <util.h>

TEST_CASE("File collectors")
{
    REQUIRE(FileUtils::GatherAllFilesInFolder("./example/assets/").size() == 2);
    REQUIRE(FileUtils::GatherAllContentsInFolder("./example/meta/").size() == 4);
}

TEST_CASE("File path filtering", "[pathfilter]")
{
    REQUIRE(FileUtils::GetFilter("./example/assets/logo.png") == FileUtils::SINGLE_FILE);
    REQUIRE(FileUtils::GetFilter("./example/assets/*") == FileUtils::ALL_IN_FOLDER);
    REQUIRE(FileUtils::GetFilter("./example/assets/") == FileUtils::SINGLE_FOLDER);
    REQUIRE(FileUtils::GetFilter("./example/assets") == FileUtils::SINGLE_FOLDER);
    REQUIRE(FileUtils::GetFilter("./example/assets/**/*") == FileUtils::ALL_IN_FOLDER_WITH_SUBFOLDER);
    REQUIRE(FileUtils::GetFilter("./example/meta/*.txt") == FileUtils::ALL_WITH_EXTENSION);
    REQUIRE(FileUtils::GetFilter("./example/meta/**/*.copy") == FileUtils::ALL_WITH_EXTENSION_WITH_SUBFOLDER);
}

TEST_CASE("File info from path")
{
    SECTION("Folder file info")
    {
        auto info = FileUtils::GatherFileInfoFromPath("./example");
        REQUIRE(info.filename == "");
        REQUIRE(info.extension == "");
        REQUIRE(info.fullfilename == "");
        REQUIRE(info.filepath == "./example");
        REQUIRE(info.fullpath == "./example");
    }

    SECTION("File info")
    {
        auto info = FileUtils::GatherFileInfoFromPath("./example/assets/java.png");
        REQUIRE(info.extension == ".png");
        REQUIRE(info.filename == "java");
        REQUIRE(info.fullfilename == "java.png");
        REQUIRE(info.filepath == "./example/assets/");
        REQUIRE(info.fullpath == "./example/assets/java.png");
    }

    SECTION("Filtered file info")
    {
        auto info = FileUtils::GatherFileInfoFromPath("./example/assets/*");
        REQUIRE(info.extension == "");
        REQUIRE(info.filename == "*");
        REQUIRE(info.fullfilename == "*");
        REQUIRE(info.filepath == "./example/assets/");
        REQUIRE(info.fullpath == "./example/assets/*");
    }
}

TEST_CASE("Create and copy to folder")
{
    auto info = FileUtils::GatherFileInfoFromPath("./example/assets/java.png");
    FileUtils::CreateDirectoriesAndCopyTo(info, "./tests");
    REQUIRE(std::filesystem::exists("./tests/example/assets/java.png"));
    if(std::filesystem::exists("./tests/example/assets/java.png"))
        std::filesystem::remove_all("./tests/example");
}

TEST_CASE("Split String")
{
    auto path = Util::SplitString("example/foo/bar", "/");
    REQUIRE(path.size() == 3);
}