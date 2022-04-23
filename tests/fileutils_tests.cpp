#include <cassert>
#include <string>
#include <vector>

#include "../include/fileutils.h"

int failed;
int pass;
std::vector<FileUtils::PathFilter> passList;
std::vector<FileUtils::PathFilter> failedList;

void TestFilterSingleItem()
{
    printf("> Testing single file filter: ");
    std::string path = "./example/assets/logo.png";
    auto filter = FileUtils::GetFilter(path);
    if (filter != FileUtils::SINGLE_FILE)
    {
        failed++;
        failedList.push_back(FileUtils::SINGLE_FILE);
        printf("FAIL!\n  > Expected %s! Filter was: %s\n", FileUtils::FilterToString(FileUtils::SINGLE_FILE), FileUtils::FilterToString(filter));
    }
    else
    {
        passList.push_back(FileUtils::SINGLE_FILE);
        pass++;
        printf("PASS!\n");
    }
}

void TestFilterSingleFolder()
{
    printf("> Testing single folder filter: ");
    std::string path = "./example/assets";
    auto filter = FileUtils::GetFilter(path);
    if (filter != FileUtils::SINGLE_FOLDER)
    {
        failedList.push_back(FileUtils::SINGLE_FOLDER);
        failed++;
        printf("FAIL!\n  > Expected %s! Filter was: %s\n", FileUtils::FilterToString(FileUtils::SINGLE_FOLDER), FileUtils::FilterToString(filter));
    }
    else
    {
        passList.push_back(FileUtils::SINGLE_FOLDER);
        pass++;
        printf("PASS!\n");
    }
}

void TestFilterAllInFolder()
{
    printf("> Testing single all items in folder filter: ");
    std::string path = "./example/assets/*";
    auto filter = FileUtils::GetFilter(path);
    if (filter != FileUtils::ALL_IN_FOLDER)
    {
        failedList.push_back(FileUtils::ALL_IN_FOLDER);
        failed++;
        printf("FAIL!\n  > Expected %s! Filter was: %s\n", FileUtils::FilterToString(FileUtils::ALL_IN_FOLDER), FileUtils::FilterToString(filter));
    }
    else
    {
        passList.push_back(FileUtils::ALL_IN_FOLDER);
        pass++;
        printf("PASS!\n");
    }
}

void TestFilterAllInFolderWithSubFolders()
{
    printf("> Testing all items in folder and sub folders filter: ");
    std::string path = "./example/assets/**/*";
    auto filter = FileUtils::GetFilter(path);
    if (filter != FileUtils::ALL_IN_FOLDER_WITH_SUBFOLDER)
    {
        failedList.push_back(FileUtils::ALL_IN_FOLDER_WITH_SUBFOLDER);
        failed++;
        printf("FAIL!\n  > Expected %s! Filter was: %s\n", FileUtils::FilterToString(FileUtils::ALL_IN_FOLDER_WITH_SUBFOLDER), FileUtils::FilterToString(filter));
    }
    else
    {
        passList.push_back(FileUtils::ALL_IN_FOLDER_WITH_SUBFOLDER);
        pass++;
        printf("PASS!\n");
    }
}

void TestFilterAllWithExtension()
{
    printf("> Testing all items in folder with extension filter: ");
    std::string path = "./example/meta/*.txt";
    auto filter = FileUtils::GetFilter(path);
    if (filter != FileUtils::ALL_WITH_EXTENSION)
    {
        failedList.push_back(FileUtils::ALL_WITH_EXTENSION);
        failed++;
        printf("FAIL!\n  > Expected %s! Filter was: %s\n", FileUtils::FilterToString(FileUtils::ALL_WITH_EXTENSION), FileUtils::FilterToString(filter));
    }
    else
    {
        passList.push_back(FileUtils::ALL_WITH_EXTENSION);
        pass++;
        printf("PASS!\n");
    }
}

void TestFilterAllWithExtensionWithSubFolders()
{
    printf("> Testing all items in folder and sub folders with extension filter: ");
    std::string path = "./example/meta/**/*.copy";
    auto filter = FileUtils::GetFilter(path);
    if (filter != FileUtils::ALL_WITH_EXTENSION_WITH_SUBFOLDER)
    {
        failedList.push_back(FileUtils::ALL_WITH_EXTENSION_WITH_SUBFOLDER);
        failed++;
        printf("FAIL!\n  > Expected %s! Filter was: %s\n", FileUtils::FilterToString(FileUtils::ALL_WITH_EXTENSION_WITH_SUBFOLDER), FileUtils::FilterToString(filter));
    }
    else
    {
        passList.push_back(FileUtils::ALL_WITH_EXTENSION_WITH_SUBFOLDER);
        pass++;
        printf("PASS!\n");
    }
}

void TestGatherFilesInFolder()
{
    printf("> Testing all items in folder collector: ");
    std::string path = "./example/meta/";
    auto files = FileUtils::GatherAllFilesInFolder(path);
    if (files.size() != 2)
    {
        failed++;
        printf("FAIL!\n  > Expected two files! Found: %li\n", files.size());
               for(auto file : files){
            printf("    > %s\n", file.c_str());
        }
    }
    else
    {
        pass++;
        printf("PASS!\n");
    }
}

int main()
{
    TestFilterSingleItem();
    TestFilterSingleFolder();
    TestFilterAllInFolder();
    TestFilterAllInFolderWithSubFolders();
    TestFilterAllWithExtension();
    TestFilterAllWithExtensionWithSubFolders();
    TestGatherFilesInFolder();
    printf("\nResults:\n");
    printf("  PASS: %i\n", pass);
    for (auto p : passList)
        printf("    > %s\n", FileUtils::FilterToString(p));
    printf("  FAILED: %i\n", failed);
    for (auto f : failedList)
        printf("    > %s\n", FileUtils::FilterToString(f));
    printf("\n");
}