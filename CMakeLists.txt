#=========================================================================
# StrawPen
#=========================================================================
cmake_minimum_required(VERSION 3.31)

#--------- Basic Setup -----------
project(StrawPen VERSION 1.0 LANGUAGES C CXX)
add_executable(strawpen)
#--------- Compiler flags -----------
target_compile_features(strawpen PRIVATE cxx_std_17)

# Add the /utf-8 flag for MSVC compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(strawpen PRIVATE "/utf-8")
endif()

#--------- Includes -----------
target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/src")
#--------- Sources -----------
file(GLOB_RECURSE MYSOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
target_sources(strawpen PRIVATE ${MYSOURCES})

#--------- Icons -----------
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # target_sources(strawpen PRIVATE src/icon.rc)
endif()

#--------- Dependencies -----------
# CMake variant
# add_subdirectory(thirdparty/StrawPlate)
# target_link_libraries(strawpen PRIVATE StrawPlate)
# Dist variant
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include")
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include/imgui")
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include/stbi")
# target_link_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/lib")
# target_link_libraries(strawpen PRIVATE strawplate_rel.lib glad.lib glfw3.lib imgui.lib stbi.lib)
add_subdirectory(thirdparty/StrawPlate/build/Dist)
target_link_libraries(strawpen PRIVATE strawplatelib)

# Assets 
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_BINARY_DIR}
)

# [Desktop Entry]
# Encoding=UTF-8
# Version=1.0
# Type=Application
# Exec= /home/subh01/Dev0/projects/StrawPen/build/strawpen
# Name=Spectral Echo
# Icon =/home/subh01/Dev0/projects/StrawPen/assets/icons/straw_plate_icon.png