set(TARGET_NAME App)

add_executable(${TARGET_NAME} application.cpp main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE Renderer CompilerOptions)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

#find_package(SFML REQUIRED COMPONENTS Graphics Window)
#target_link_libraries(${TARGET_NAME} PUBLIC SFML::Graphics SFML::Window)