#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
	SRCS
		esp_base.cpp
		mtime/datetime.cpp
		mtime/timespan.cpp
		network/Socket.cpp
	INCLUDE_DIRS
		.
		callbacks
		devicemanagement
		helpers
		mtime
		network
		rtos
						REQUIRES json nvs_flash esp_timer)
