cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fpermissive")

#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(Protobuf REQUIRED)

# Dependencies and include locations
include_directories(../include ${CONAN_INCLUDE_DIRS_ENET} ${CONAN_INCLUDE_DIRS_PROTOBUF})

file(GLOB SOURCES ../src/*.cpp ../src/*.c ../proto/*.cc)
file(GLOB HEADERS ../include/*.hpp ../include/*.h ../proto/*.h)

# Compile proto files
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../proto/gamestate.proto ../proto/playeraction.proto)


add_executable(server ${SOURCES} ${HEADERS} ${PROTO_SRCS} ${PROTO_HDRS})

#target_link_libraries(server ${CONAN_LIBS} ${Protobuf_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::protobuf)
#target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::enet)
target_link_libraries(server CONAN_PKG::enet CONAN_PKG::protobuf)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})