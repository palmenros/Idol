#pragma once
#include <iostream>

#define LOG(x) (std::cout << x << std::endl)
#define ERROR(x) (std::cerr << (x) << std::endl)

#define PROJECT_DIR(path) (__PROJECT_DIR__ path)