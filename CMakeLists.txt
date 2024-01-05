cmake_minimum_required(VERSION 3.1)
add_compile_options( -g )
set(CMAKE_CXX_STANDARD 14)
project(sim)

find_package(OpenGL REQUIRED)
find_package(Assimp REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(GLM_INCLUDE_DIRS /opt/homebrew/Cellar/glm/0.9.9.8/include)

add_subdirectory(glad)

add_executable(${PROJECT_NAME} 
    main.cpp
    Simulator.cpp
    ResourceManager.cpp
    Shader.cpp
    Sphere.cpp
    Cloth.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${OpenGL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    ${OpenGL_LIBRARIES}
    GLAD_LIBRARIES
    glfw
)

