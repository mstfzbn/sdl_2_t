cmake_minimum_required(VERSION 3.7)

project(sdl_2_primitives_lib)

file( GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.*" )

 
#STATIC or SHARED defines the type of libabry .a or .so file
#add_library( ${PROJECT_NAME} STATIC ${SRC_FILES} )
add_library( ${PROJECT_NAME} SHARED ${SRC_FILES} )

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)
