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
		include/Gradient.h
		include/GridlineTensorField.h
		include/IEigenField.h
		include/IScalarField.h
		include/ITensorField.h
		include/IVector2Field.h
		include/RadialTensorField.h
		include/ResampleAndRescale.h
		include/ScaledScalarField.h
		include/Tensor.h
	PRIVATE
		main.cpp
)
