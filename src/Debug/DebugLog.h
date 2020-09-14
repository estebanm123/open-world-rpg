#pragma once

#ifdef DEBUG
#define Log(name, message) std::cout << name << ": " << message << std::endl;
#else
#define Log(name, message)
#endif