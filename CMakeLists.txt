cmake_minimum_required(VERSION 3.7)
project(sdl_2_t)
add_definitions("-Wall" "-g")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/lib)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/lib/*.*)
add_executable(sdl_2_t ${SRC_FILES})

target_link_libraries(sdl_2_t ${SDL2_LIBRARIES})
