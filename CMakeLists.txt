cmake_minimum_required(VERSION 3.16)
project(ClayEngineVulkan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)

# find_package(OpenGL REQUIRED)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# add_subdirectory(src/ClayEngine/Manifolds/)

set(HEADERS 
    src/ClayEngineVk/Core/Core.h
)

# set(SOURCES
#     # src/ClayEditorVk/main.cpp
# )

add_library(ClayEngineVk 
        src/ClayEngineVk/Core/Core.h
        src/ClayEngineVk/Window/Window.h
        src/ClayEngineVk/Window/Window.cpp
        src/ClayEngineVk/Pipeline/Pipeline.h
        src/ClayEngineVk/Pipeline/Pipeline.cpp
)

target_include_directories(ClayEngineVk PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(ClayEngineVk PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/ClayEngineVk")

target_link_libraries(ClayEngineVk PUBLIC
        glfw vulkan dl  pthread  X11  Xxf86vm  Xrandr  Xi
)

# if(LOG_DEBUG)
#     target_compile_definitions(ClayEngine PUBLIC -DLOG_DEBUG=1)
# endif()

# if(BUILD_LOCAL)
#     target_compile_definitions(ClayEngine PUBLIC -DASSETS_PATH="../src/ClayEngine/Assets/")
# else()
#     target_compile_definitions(ClayEngine PUBLIC -DASSETS_PATH="/usr/local/include/ClayEngine/Assets/")
# endif()

# message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")


# message(STATUS "SOURCES: ${RENDERER_SOURCES}")

# install(TARGETS ClayEngine DESTINATION lib)
# install(TARGETS glad DESTINATION lib)
# install(TARGETS imgui DESTINATION lib)

# INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/src/ClayEngine DESTINATION include FILES_MATCHING PATTERN "*.h")
# INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/src/ClayEngine DESTINATION include FILES_MATCHING PATTERN "*.hpp")

# INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/Vendor DESTINATION include/ClayEngine FILES_MATCHING PATTERN "*.h")
# INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/Vendor DESTINATION include/ClayEngine FILES_MATCHING PATTERN "*.hpp")
# INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/Vendor DESTINATION include/ClayEngine FILES_MATCHING PATTERN "*.inl")

# INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/src/ClayEngine/Assets DESTINATION include/ClayEngine)

add_executable(ClayEditorVk
        src/ClayEditorVk/main.cpp)
target_link_libraries(ClayEditorVk
        ClayEngineVk)

# SET(CPACK_GENERATOR "DEB")
# SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "BM") #required
# INCLUDE(CPack)