
#pragma once
#include "esp_system.h"

namespace ESP_Base
{
	template<typename R, typename ...Args>
		class FuncHandler
		{
		public:
			FuncHandler() {}
			virtual ~FuncHandler() {}
			virtual R Invoke(Args... args) = 0;
		};
	
	
	template<typename R, typename T, typename ...Args>
		class FuncHandlerMethod : public FuncHandler<Args...>
		{
		private:
			R(T::*method)(Args...);
			T* methodInstance;
	
		public:
	
			void Bind(T* instance, R(T::*memberFunctionToCall)(Args...))
			{
				method = memberFunctionToCall;
				methodInstance = instance;
			}
	
			R Invoke(Args... args)
			{
				return (methodInstance->*method)(args...);
			}
		};
	
	
	template<typename R, typename ...Args>
		class FuncHandlerFunction : public FuncHandler<Args...>
		{
		private:
			R(*func)(Args...);
	
		public:
			void Bind(R(*functionCall)(Args...))
			{
				func = functionCall;
			}
	
			R Invoke(Args... args)
			{
				return (*func)(args...);
			}
		};
	
	template<typename R, typename ...Args>
		class Func
		{
			FuncHandler<R, Args...> *func = NULL;
			
		public:
			virtual ~Func()
			{
				if (func != NULL)
					delete func;
			}
		
			template<typename T>
				void Bind(T* instance, R(T::*method)(Args...))
				{
					if (func != NULL)
						delete func;
					
					FuncHandlerMethod<R, T, Args...>* handler = new FuncHandlerMethod<R, T, Args...>();
					handler->Bind(instance, method);
					func = handler;
				}

			void Bind(R(*func)(Args...))
			{
				if (func != NULL)
					delete func;
				FuncHandlerFunction<Args...> *handler = new FuncHandlerFunction<Args...>();
				handler->Bind(func);
				func = handler;
			}

			R Invoke(Args... args)
			{
				return func->Invoke(args...);
			}
			
			bool IsBound()
			{
				return func != NULL;
			}
		};
}