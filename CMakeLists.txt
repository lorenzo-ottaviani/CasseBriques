cmake_minimum_required(VERSION 3.15)
project(Breakout CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Compiler Configuration (MSYS2) ---
if (WIN32)
    set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# --- SFML 2.6.2 Configuration ---
if (WIN32)
    set(SFML_INCLUDE_DIR "C:/msys64/SFML-2.6.2/include")
    set(SFML_LIBRARY_DIR "C:/msys64/SFML-2.6.2/lib")
    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_LIBRARY_DIR})
endif()

# --- Sources and Headers ---
# Include the 'include' directory so C++ can find our .hpp files
include_directories(include)

# Explicitly list files
add_executable(Breakout
        src/main.cpp
        src/InputManager.cpp
        src/GameObject.cpp
)

# --- Library Linking ---
if(WIN32)
    target_link_libraries(Breakout PRIVATE
            sfml-graphics
            sfml-window
            sfml-system
            sfml-audio
            # Windows system dependencies required by static SFML/MinGW
            gdi32
            opengl32
            winmm
    )
endif()

# Enable detailed build output
set(CMAKE_VERBOSE_MAKEFILE ON)
