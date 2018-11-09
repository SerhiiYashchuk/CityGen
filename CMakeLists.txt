cmake_minimum_required(VERSION 3.8)

project("CityGen")

add_executable(${PROJECT_NAME})

if(MSVC)
	# add_compile_options(/W4) - Old style. Don't use this!
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
		src/Fields/Tensor.cpp
		src/Tracing/Graph.cpp
		src/Tracing/Region.cpp
		src/Tracing/RegionBuilder.cpp
		src/Tracing/Streamline.cpp
		main.cpp
)
