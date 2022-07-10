cmake_minimum_required(VERSION 3.0.0)
project(FbxParsing VERSION 0.1.0)

set(EXTERN_ASSIMP_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/ThirdParty/assimp/include" CACHE INTERNAL
    "Include directory for assimp"
)

link_directories("./ThirdParty/assimp/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(FbxParsing ./src/FbxMeshCenter.cpp)

target_include_directories(FbxParsing SYSTEM PUBLIC ${EXTERN_ASSIMP_INCLUDE_DIR})

target_link_libraries(FbxParsing PRIVATE assimp-vc142-mt)

