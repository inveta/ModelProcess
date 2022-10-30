cmake_minimum_required(VERSION 3.0.0)
project(fbxexport VERSION 0.1.0)

set(EXTERN_FBX_INCLUDE_DIR "D:\\Program Files\\Autodesk\\FBX\\FBX SDK\\2020.3.1\\include")
set(EXTERN_FBX_LIB_DIR "D:\\Program Files\\Autodesk\\FBX\\FBX SDK\\2020.3.1\\lib\\vs2019\\x64\\debug")

link_directories(${EXTERN_FBX_LIB_DIR})

# add_executable(fbxexport main.cpp Common.cpp)
add_executable(fbxexport vertexoffset.cpp Common.cpp)


target_include_directories(fbxexport SYSTEM PUBLIC ${EXTERN_FBX_INCLUDE_DIR})
target_link_libraries(fbxexport libfbxsdk-md.lib libxml2-md.lib zlib-md.lib)
set_target_properties(fbxexport PROPERTIES LINK_FLAGS "/ignore:4099")