cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JWChess)

add_subdirectory(external/SDL)
set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/SDL/include")
set(SDL2_LIBRARY SDL2)

add_subdirectory(external/SDL_image)
include_directories(external/SDL/include)

set(SOURCE_DIR  "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR     "${CMAKE_SOURCE_DIR}/lib")

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.c*")
file(GLOB INCLUDE_FILES "${INCLUDE_DIR}/*.h*")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2_image)
