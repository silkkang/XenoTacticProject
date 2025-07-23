#include "stdafx.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
   // std::cout << "현재 작업 디렉토리: " << fs::current_path() << std::endl;
    std::cout << std::filesystem::absolute("animations/monsterCol1.csv")
        << " exists? "
        << std::filesystem::exists("animations/monsterCol1.csv")
        << std::endl;

    FRAMEWORK.Init(673 , 503, "TITLE!!");
    //FRAMEWORK.Init(1346, 1006, "TITLE!!");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}