cmake_minimum_required(VERSION 3.10)

project(menu CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--strip-all")
add_compile_options(
    -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror
    -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive -lc++-abi
)

include_directories(
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

file(GLOB IMGUI "${CMAKE_SOURCE_DIR}/imgui/*.cpp")
set(BACKEND
"${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_android.cpp"
"${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
)
list(APPEND IMGUI ${BACKEND})
file(GLOB NATIVE_GLUE "${CMAKE_SOURCE_DIR}/src/native_surface/*.c")
file(GLOB NATIVE "${CMAKE_SOURCE_DIR}/src/native_surface/*.cpp")
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
set(ALL_SOURCES ${SOURCES} ${IMGUI} ${NATIVE} ${NATIVE_GLUE})

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

target_link_libraries(${PROJECT_NAME}
    EGL
    GLESv3
    GLESv2
    android
    log
    z
)