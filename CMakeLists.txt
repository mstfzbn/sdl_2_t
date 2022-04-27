cmake_minimum_required(VERSION 3.7)
project(sdl_2_t)
#warrning levels defines send to GCC
#add_definitions("-Wall" "-g")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#works for sdl
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#works for other modules
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)


#including the custom lib
add_subdirectory(lib)

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
    
target_link_libraries(${PROJECT_NAME} PRIVATE 
                                      ${SDL2_LIBRARIES}
                                      ${SDL2IMAGE_LIBRARIES} 
                                      ${SDL2TTF_LIBRARIES}
                                      ${SDL2MIXER_LIBRARIES}
                                      sdl_2_primitives_lib 
                                      box2d 
                                      imgui )











