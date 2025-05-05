#=========================================================================
# StrawPen
#=========================================================================
cmake_minimum_required(VERSION 3.31)

#--------- Basic Setup -----------
project(StrawPen VERSION 1.1.0.0 LANGUAGES C CXX)

add_executable(strawpen)
#--------- Compiler flags -----------
target_compile_features(strawpen PRIVATE cxx_std_17)

# /utf-8 flag for MSVC compiler; character-set dep for spdlog
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(strawpen PRIVATE "/utf-8")
endif()

# -----------Build Config identification -------
# works for both single and multi-config generators
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    # single-config generators (Make, Ninja)
    target_compile_definitions(strawpen PRIVATE DEBUG_BUILD)
    # target_compile_definitions(library_target PRIVATE DEBUG_BUILD)

else()
    # Release, RelWithDebInfo, MinSizeRel, or any other configs
    target_compile_definitions(strawpen PRIVATE NDEBUG)
endif()

target_compile_definitions(strawpen PRIVATE VERSION_STRING="v${PROJECT_VERSION}")

# For multi-config generators (like Visual Studio), the above might not be enough
# as CMAKE_BUILD_TYPE is often empty during configuration.
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    target_compile_definitions(strawpen
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
    target_sources(strawpen PRIVATE src/icon.rc)
endif()

#--------- Dependencies -----------
# CMake variant
add_subdirectory(thirdparty/StrawPlate)
target_link_libraries(strawpen PRIVATE StrawPlate)
# Dist variant
# add_subdirectory(thirdparty/StrawPlate/build/Dist)
# target_link_libraries(strawpen PRIVATE strawplatelib)
# more manual ----------------
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include")
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include/imgui")
# target_include_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/include/stbi")
# target_link_directories(strawpen PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/StrawPlate/build/Dist/lib")
# target_link_libraries(strawpen PRIVATE strawplate_rel.lib glad.lib glfw3.lib imgui.lib stbi.lib)
# add_subdirectory(thirdparty/StrawPlate/build/Dist)
# target_link_libraries(strawpen PRIVATE strawplatelib)

# -------------Outputs--------------
set_target_properties(strawpen PROPERTIES
    RUNTIME_OUTPUT_NAME "strawpen"
    RUNTIME_OUTPUT_NAME_RELEASE "strawpen_rel"
    RUNTIME_OUTPUT_NAME_DEBUG "strawpen_dbg"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Assets 
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    DESTINATION "${CMAKE_BINARY_DIR}/bin"
)
# ImGui config
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/config/imgui.ini"
    DESTINATION "${CMAKE_BINARY_DIR}/bin"
)
# kde .desktop
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/linux/strawpen_editor.desktop"
    DESTINATION "${CMAKE_BINARY_DIR}/bin"
)
