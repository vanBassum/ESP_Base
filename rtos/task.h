#pragma once

#include <string>

#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../misc/action.h"

namespace ESP_Base
{
	
	class Task
	{
		xTaskHandle taskHandle;
		Action<Task&> callback;
		
		static void TaskFunction(void* parm)
		{
			Task* t = static_cast<Task*>(parm);
			t->callback.Invoke(*t);
			t->taskHandle = NULL;	
			vTaskDelete(NULL);
		}
		
	public:
		
		virtual ~Task()
		{
			if (taskHandle != NULL)
				vTaskDelete(taskHandle);
		}
		
		template<typename T>
		void Bind(T* instance, void(T::* mp)(Task&))
		{
			callback.Bind(instance, mp);
		}

		void Bind(void(*fp)(Task&))
		{
			callback.Bind(fp);
		}
		
		void Run(const std::string name, portBASE_TYPE priority, portSHORT stackDepth)
		{
			if (stackDepth < configMINIMAL_STACK_SIZE)
				stackDepth = configMINIMAL_STACK_SIZE;
			xTaskCreate(&TaskFunction, name.c_str(), stackDepth, this, priority, &taskHandle);
		}
		
		virtual void RunPinned(const std::string name, portBASE_TYPE priority, portSHORT stackDepth, const BaseType_t core)
		{
			if (stackDepth < configMINIMAL_STACK_SIZE)
				stackDepth = configMINIMAL_STACK_SIZE;
			xTaskCreatePinnedToCore(&TaskFunction, name.c_str(), stackDepth, this, priority, &taskHandle, core);
		}
	};
	
	
}