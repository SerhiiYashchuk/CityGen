project("Tests")

if(NOT DEFINED HYPERSTREAMLINE_LIB_NAME)
	set(HYPERSTREAMLINE_LIB_NAME Hyperstreamline)
endif()

add_executable(${PROJECT_NAME})

find_package(Catch2 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Catch2::Catch2
		${HYPERSTREAMLINE_LIB_NAME}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${CMAKE_SOURCE_DIR}/include
)

enable_testing()

add_test(NAME All COMMAND ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		Fields/RegionTests.cpp
		GenericTypesTests.cpp
		main.cpp
)
