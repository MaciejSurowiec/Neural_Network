add_executable(${PROJECT_NAME}
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
	PictureMatrix.h
	PictureMatrix.cpp
	Input.h
	Input.cpp
)


target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

#set taget

#add config to copy to target

# add qt 

