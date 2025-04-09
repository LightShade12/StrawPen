#=========================================================================
# StrawPen
#=========================================================================
cmake_minimum_required(VERSION 3.31)

#--------- Basic Setup -----------
project(StrawPen VERSION 1.0 LANGUAGES C CXX)
add_executable(strawpen)
#--------- Compiler flags -----------
target_compile_features(strawpen PRIVATE cxx_std_17)

# /utf-8 flag for MSVC compiler; character-set dep for spdlog
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(strawpen PRIVATE "/utf-8")
endif()

# Build Config identification -------
# works for both single and multi-config generators
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    # single-config generators (Make, Ninja)
    target_compile_definitions(strawpen PRIVATE DEBUG_BUILD)
    # target_compile_definitions(library_target PRIVATE DEBUG_BUILD)

else()
    # Release, RelWithDebInfo, MinSizeRel, or any other configs
    target_compile_definitions(strawpen PRIVATE NDEBUG)
endif()

# For multi-config generators (like Visual Studio), the above might not be enough
# as CMAKE_BUILD_TYPE is often empty during configuration.
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:Debug>:DEBUG_BUILD>
        $<$<CONFIG:Release>:NDEBUG>
    )
    # target_compile_definitions(library_target PRIVATE
    #   $<$<CONFIG:Debug>:DEBUG_BUILD>
    # )
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
add_subdirectory(thirdparty/StrawPlate)
target_link_libraries(strawpen PRIVATE StrawPlate)
# Dist variant
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include")
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include/imgui")
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include/stbi")
# target_link_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/lib")
# target_link_libraries(strawpen PRIVATE strawplate_rel.lib glad.lib glfw3.lib imgui.lib stbi.lib)
# add_subdirectory(thirdparty/StrawPlate/build/Dist)
# target_link_libraries(strawpen PRIVATE strawplatelib)

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