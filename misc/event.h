#pragma once
#include "esp_system.h"
#include <vector>
#include "action.h"

namespace ESP_Base
{
	template<typename ...Args>
		class Event
		{
			//std::vector<ActionHandler<Args...>*> *actions = NULL;
		public:
			virtual ~Event()
			{
				//if (actions != NULL)
				//{
				//	int size = actions->size();
				//	for (int i = 0;i < size; i++)
				//		delete (*actions)[i];
				//	delete actions;
				//}
			}
		
			template<typename T>
				void Bind(T* instance, void(T::*method)(Args...))
				{
					//if (actions == NULL)
					//	actions = new std::vector<ActionHandler<Args...> *>();
					//actions->push_back(new ActionHandlerMethod<T, Args...>(instance, method));
				}

			void Bind(void(*func)(Args...))
			{
				//if (actions == NULL)
				//	actions = new std::vector<ActionHandler<Args...> *>();
				//actions->push_back(new ActionHandlerFunction<Args...>(func));
			}

			void Invoke(Args... args)
			{
				//if (actions != NULL)
				//{
				//	int size = actions->size();
				//	for (int i = 0;i < size; i++)
				//		(*actions)[i]->Invoke(args...);
				//}
			}
		};
}