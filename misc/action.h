#pragma once
#include "esp_system.h"

namespace ESP_Base
{
	//template<typename ...Args>
	//	class ActionHandler
	//	{
	//	public:
	//		ActionHandler() {}
	//		virtual ~ActionHandler() {}
	//		virtual void Invoke(Args... args) = 0;
	//	};
	//
	//
	//template<typename T, typename ...Args>
	//	class ActionHandlerMethod : public ActionHandler<Args...>
	//	{
	//	private:
	//		void(T::*method)(Args...);
	//		T* methodInstance;
	//
	//	public:
	//
	//		ActionHandlerMethod<T, Args...>(T* instance, void(T::*memberFunctionToCall)(Args...))
	//		{
	//			method = memberFunctionToCall;
	//			methodInstance = instance;
	//		}
	//
	//		void Invoke(Args... args)
	//		{
	//			return (methodInstance->*method)(args...);
	//		}
	//	};
	//
	//
	//template<typename ...Args>
	//	class ActionHandlerFunction : public ActionHandler<Args...>
	//	{
	//	private:
	//		void(*func)(Args...);
	//
	//	public:
	//		ActionHandlerFunction<Args...>(void(*functionCall)(Args...))
	//		{
	//			func = functionCall;
	//		}
	//
	//		void Invoke(Args... args)
	//		{
	//			return (*func)(args...);
	//		}
	//	};
	
	template<typename ...Args>
		class Action
		{
			//ActionHandler<Args...> *action = NULL;
			
		public:
			virtual ~Action()
			{
				//if (action != NULL)
				//	delete action;
			}
		
			template<typename T>
				void Bind(T* instance, void(T::*method)(Args...))
				{
					//if (action != NULL)
					//	delete action;
					//action = new ActionHandlerMethod<T, Args...>(instance, method);
				}

			void Bind(void(*func)(Args...))
			{
				//if (action != NULL)
				//	delete action;
				//action = new ActionHandlerFunction<Args...>(func);
			}

			void Invoke(Args... args)
			{
				//if (action != NULL)
				//	action->Invoke(args...);
			}
		};
}