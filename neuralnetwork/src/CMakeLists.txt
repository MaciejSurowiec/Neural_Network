﻿add_executable(${PROJECT_NAME}
	main.cpp
	gui.h
	gui.cpp
	Network.h
	Network.cpp
	Neuron.h
	Neuron.cpp
	Matrix.h
	Matrix.cpp
	Layer.cpp
	Layer.h
	PictureMatrix.h
	PictureMatrix.cpp
	Input.h
	Input.cpp
)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Config.txt ${PROJECT_BINARY_DIR}/Config.txt
)