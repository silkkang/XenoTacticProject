#include "stdafx.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
    std::cout << "���� �۾� ���丮: " << fs::current_path() << std::endl;
    FRAMEWORK.Init(673 , 503, "TITLE!!");
    //FRAMEWORK.Init(1346, 1006, "TITLE!!");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}