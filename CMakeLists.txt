cmake_minimum_required(VERSION 3.11)

project("CityGen")

# Hyperstreamline library
set(HYPERSTREAMLINE_LIB_NAME Hyperstreamline)
add_subdirectory(src/Hyperstreamline)

# CityGen
add_executable(${PROJECT_NAME})

# SFML package
find_package(SFML COMPONENTS system window graphics REQUIRED)

# ImGui package
find_package(milerius-sfml-imgui CONFIG REQUIRED)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC
    include
  PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    sfml-graphics
    opengl32
    sfml-imgui::sfml-imgui
  PRIVATE
    ${HYPERSTREAMLINE_LIB_NAME}
)

target_sources(${PROJECT_NAME}
  PUBLIC

  PRIVATE
    # Headers
    include/GraphVisualization.h
	include/UI.h
    # Sources
    src/GraphVisualization.cpp
	src/UI.cpp
    main.cpp
)

add_subdirectory(test)
