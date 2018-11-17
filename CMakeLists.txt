cmake_minimum_required(VERSION 3.11)

project("CityGen")

add_executable(${PROJECT_NAME})

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

find_package(Boost COMPONENTS graph REQUIRED)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
	PRIVATE
		src
)

target_compile_features(${PROJECT_NAME}
	PUBLIC
		cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		Boost::graph
)

target_sources(${PROJECT_NAME}
	PUBLIC
		include/GenericTypes.h
		include/Fields/Gradient.h
		include/Fields/GridlineTensorField.h
		include/Fields/IEigenField.h
		include/Fields/IScalarField.h
		include/Fields/ITensorField.h
		include/Fields/IVectorField.h
		include/Fields/RadialTensorField.h
		include/Fields/ResampleAndRescale.h
		include/Fields/ScaledScalarField.h
		include/Fields/Tensor.h
		include/Tracing/Graph.h
		include/Tracing/Region.h
		include/Tracing/RegionBuilder.h
		include/Tracing/Streamline.h
	PRIVATE
		src/GenericTypes.cpp
		src/Fields/Tensor.cpp
		src/Tracing/Graph.cpp
		src/Tracing/Region.cpp
		src/Tracing/RegionBuilder.cpp
		src/Tracing/Streamline.cpp
		main.cpp
)

add_subdirectory(test)
