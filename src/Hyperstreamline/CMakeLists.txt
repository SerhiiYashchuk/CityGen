if(NOT DEFINED HYPERSTREAMLINE_LIB_NAME)
	set(HYPERSTREAMLINE_LIB_NAME Hyperstreamline)
endif()

add_library(${HYPERSTREAMLINE_LIB_NAME})

if(MSVC)
	target_compile_options(${HYPERSTREAMLINE_LIB_NAME} PRIVATE /W4)
else()
	target_compile_options(${HYPERSTREAMLINE_LIB_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

find_package(Boost COMPONENTS graph REQUIRED)

target_include_directories(${HYPERSTREAMLINE_LIB_NAME}
	PUBLIC
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${HYPERSTREAMLINE_LIB_NAME}
	PUBLIC
		cxx_std_17
)

target_link_libraries(${HYPERSTREAMLINE_LIB_NAME}
	PUBLIC
		Boost::graph
)

target_sources(${HYPERSTREAMLINE_LIB_NAME}
	PRIVATE
		# Headers
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/GenericTypes.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/GeometricTree.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/Gradient.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/GridlineTensorField.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/IEigenField.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/IScalarField.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/ITensorField.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/IVectorField.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/RadialTensorField.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/ResampleAndRescale.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/ScaledScalarField.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Fields/Tensor.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Tracing/Graph.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Tracing/Region.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Tracing/RegionBuilder.h
		${CMAKE_SOURCE_DIR}/include/Hyperstreamline/Tracing/Streamline.h
		# Sources
		Fields/Tensor.cpp
		Tracing/Graph.cpp
		Tracing/Region.cpp
		Tracing/RegionBuilder.cpp
		Tracing/Streamline.cpp
)