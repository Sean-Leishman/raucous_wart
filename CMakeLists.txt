cmake_minimum_required(VERSION 3.10)

project(raucous_wart LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
message(CMAKE_MODULE_PATH="${CMAKE_MODULE_PATH}")
# find_package(spdlog REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -fopenmp -ffast-math")

add_subdirectory(src)

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
#target_compile_options(main PRIVATE -fno-omit-frame-pointer -fsanitize=address)

target_link_libraries(main PRIVATE raytracer_lib) #-fno-omit-frame-pointer -fsanitize=address)

#target_link_libraries(main PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
