cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JWChess)

set(SOURCE_DIR  "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR     "${CMAKE_SOURCE_DIR}/lib")

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.c*")
file(GLOB INCLUDE_FILES "${INCLUDE_DIR}/*.h*")

if(WIN32)
    set(SDL_LIB_DIR "${LIB_DIR}/SDL2/x64")
    link_directories(${SDL_LIB_DIR})
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main SDL2test SDL2_image)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_image SDL2_ttf)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_sources(${PROJECT_NAME} PUBLIC ${INCLUDE_FILES})