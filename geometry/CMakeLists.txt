set(TARGET_NAME Geometry)

add_library(${TARGET_NAME} primitives/point.cpp primitives/segment.cpp)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE CompilerOptions)