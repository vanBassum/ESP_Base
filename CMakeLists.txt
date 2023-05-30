#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
	SRCS
		esp_base.cpp
	INCLUDE_DIRS
		.
		callbacks
		helpers
		interfaces
		mtime
						REQUIRES json nvs_flash)
