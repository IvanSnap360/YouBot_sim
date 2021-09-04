cmake_minimum_required(VERSION 3.1.0)



#set project name
project(You_bot C CXX)

find_package(Threads REQUIRED)
find_package(X11 REQUIRED)

# vrep
# include_directories(${PROGECT_NAME} remoteApi)
# include_directories(${PROGECT_NAME} include)
include_directories(You_bot libs)
include_directories(You_bot find_package(X11 REQUIRED))


add_definitions (-DNON_MATLAB_PARSING)
add_definitions (-DMAX_EXT_API_CONNECTIONS=255)
add_definitions (-DDO_NOT_USE_SHARED_MEMORY)




#bild
add_executable (You_bot 
                main.cpp
                libs/sim_lib/extApi.c 
                libs/sim_lib/extApiPlatform.c
                )

target_link_libraries(You_bot Threads::Threads)
target_link_libraries(You_bot X11::X11)