#include <iostream>
#include "terminal_colors.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

#define INFO_PRINT(x) std::cout << Bold << White  << "[INFO] " << Reset << x << std::endl;
#define DEBUG_PRINT(x) std::cout << Bold << Green  << "[DEBUG] "<< Reset << x << std::endl;
#define WARN_PRINT(x) std::cout << Bold << Yellow << "[WARN] " << Reset << x << std::endl;
#define ERROR_PRINT(x) std::cout << Bold << Red    << "[ERROR] "<< Reset << x << std::endl;
