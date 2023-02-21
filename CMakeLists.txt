#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
						SRCS "esp_base.cpp" "settings/settings.cpp"
						INCLUDE_DIRS "." "misc" "rtos" "settings" "interfaces"
						REQUIRES json nvs_flash)
