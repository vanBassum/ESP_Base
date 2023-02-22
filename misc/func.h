
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
		class FuncHandlerFunction : public FuncHandler<R, Args...>
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
			FuncHandler<R, Args...> *funcHandler = NULL;
			
		public:
			virtual ~Func()
			{
				if (funcHandler != NULL)
					delete funcHandler;
			}
		
			template<typename T>
				void Bind(T* instance, R(T::*method)(Args...))
				{
					if (funcHandler != NULL)
						delete funcHandler;
					
					FuncHandlerMethod<R, T, Args...>* handler = new FuncHandlerMethod<R, T, Args...>();
					handler->Bind(instance, method);
					funcHandler = handler;
				}

			void Bind(R(*func)(Args...))
			{
				if (funcHandler != NULL)
					delete funcHandler;
				FuncHandlerFunction<R, Args...> *handler = new FuncHandlerFunction<R, Args...>();
				handler->Bind(func);
				funcHandler = handler;
			}

			R Invoke(Args... args)
			{
				return funcHandler->Invoke(args...);
			}
			
			bool IsBound()
			{
				return funcHandler != NULL;
			}
		};
}