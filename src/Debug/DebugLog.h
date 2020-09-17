#pragma once
#include <iostream>
#ifdef DEBUG
#define LOG(name, message) std::cout << name << ": " << message << std::endl;
#else
#define LOG(name, message)
#endif