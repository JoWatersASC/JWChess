cmake_minimum_required(VERSION 3.22.01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JWChess)

set(SOURCE_DIR  "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR     "${CMAKE_SOURCE_DIR}/lib")
set(SDL_LIB_DIR "${LIB_DIR}/SDL2/x64")

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB INCLUDE_FILES "${INCLUDE_DIR}/*.h*")

link_directories(${SDL_LIB_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main SDL2test SDL2gfx SDL2_image)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_sources(${PROJECT_NAME} PUBLIC ${INCLUDE_FILES})
    