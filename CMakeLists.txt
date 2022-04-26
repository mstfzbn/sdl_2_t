cmake_minimum_required(VERSION 3.7)
project(sdl_2_t)
#warrning levels defines send to GCC
#add_definitions("-Wall" "-g")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#including the custom lib
add_subdirectory(lib)

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES})


target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} sdl_2_primitives_lib)
