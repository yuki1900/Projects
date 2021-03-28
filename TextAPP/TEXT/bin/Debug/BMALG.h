#pragma once
/*
生成dll的工程时，vs默认定义宏:DLL_EXPORTS，不是dll工程，没有该宏定义
可以在"属性->预处理器->预处理器定义"里面看见该宏
以下语句的含义：如果定义该宏，则DLL_API是导出.(dll生成工程定义了该宏，所以是导出)
如果未定义该宏，则DLL_API是导入.(调用dll的工程没有定义该宏，所以是导入dll)
*/

#include <string>

namespace BMALGdll  
{
	//extern "C" 作用是编译时用C的编译方式，保证函数名不变
	//C++存在函数重载，所以编译函数时会在函数名后面加上参数类型，如果C++调用C编写的dll库就需要extern "C"
	extern "C" __declspec(dllexport) void setSuffix(std::string pString, int *su);
	extern "C" __declspec(dllexport) void getbChar(std::string pString, int *bc);
	extern "C" __declspec(dllexport) void getgSuff(std::string pString, int *gs, int *su);
	extern "C" __declspec(dllexport) int bm_search(int *bc, int* gs, std::string sString, std::string pString);
};
