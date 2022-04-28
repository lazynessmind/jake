#include <cstdio>
#include <filesystem>
#include <cstring>

#include "jake.h"
#include "util.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        Jake::PrintUsage();
        return 1;
    }
    else
    {
        Util::ShiftArg(&argc, &argv); // Skip program
        const char *arg = Util::ShiftArg(&argc, &argv);
        if (strcmp(arg, "-v") == 0)
        {
            printf("Version: jake-0.0.1\n");
            return 1;
        }
        else if (strcmp(arg, "-b") == 0)
        {
            Jake::BuildProject(argc, argv);
        }
        else if (strcmp(arg, "-br") == 0)
        {
            Jake::BuildProject(argc, argv, true);
        }
        else if (strcmp(arg, "-r") == 0)
        {
            Jake::RunProject();
            return 1;
        }
        else
        {
            Jake::PrintUsage();
            return 1;
        }
    }

    return 0;
}
