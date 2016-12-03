project(gmpl)

cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)
aux_source_directory(gmpl SRC_LIST)
aux_source_directory(gmpl/compile SRC_LIST)
aux_source_directory(gmpl/debug SRC_LIST)

include_directories(.)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(
  ${PROJECT_NAME} gmp
)
