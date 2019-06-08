cmake_minimum_required(VERSION 3.11)

project("CityGen")

# ImGui-SFML
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui)
add_subdirectory(ThirdParty/imgui-sfml)

# Hyperstreamline library
set(HYPERSTREAMLINE_LIB_NAME Hyperstreamline)
add_subdirectory(src/Hyperstreamline)

# CityGen
add_executable(${PROJECT_NAME})

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
		ThirdParty
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC

	PRIVATE
		${HYPERSTREAMLINE_LIB_NAME}
		ImGui-SFML::ImGui-SFML
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
