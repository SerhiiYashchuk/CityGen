project("Tests")

add_executable(${PROJECT_NAME})

find_package(Catch2 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Catch2::Catch2
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		../include
)

enable_testing()

add_test(NAME All COMMAND ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		../src/GenericTypes.cpp
		GenericTypesTests.cpp
		main.cpp
)
