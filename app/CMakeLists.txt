cmake_minimum_required(VERSION 3.16..3.24)

# Project details
project(App	    
    VERSION 1.0.0
    DESCRIPTION "Application description"
    LANGUAGES CXX)

# All .cpp files in App
add_executable(App 
    src/app.cpp)

# Subproject dependencies
find_package(Core REQUIRED)
find_package(Visualizer REQUIRED)

# Link dependencies
target_link_libraries(
    App 
        PUBLIC 
            Core::Core
            Visualizer::Visualizer
        PRIVATE
            sfml-system
            sfml-network 
            sfml-graphics 
            sfml-window)
