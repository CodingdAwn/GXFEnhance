// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef STRICT
#define STRICT
#endif

// 如果必须要针对低于以下指定版本的平台，请修改下列定义。
// 有关不同平台对应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用特定于 Windows 95 和 Windows NT 4 或更高版本的功能。
#define WINVER 0x0400		// 将此值更改为适当的值，以适用于 Windows 98 和 Windows 2000 及更高版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows NT 4 或更高版本的功能。
#define _WIN32_WINNT 0x0400	// 将此值更改为适当的值，以适用于 Windows 2000 或更高版本。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将此值更改为适当的值，以适用于 Windows Me 或更高版本。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 4.0 或更高版本的功能。
#define _WIN32_IE 0x0400	// 将此值更改为适当的值，以适用于 IE 5.0 或更新版本。
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的

// 关闭 ATL 对某些常见但经常可放心忽略的警告消息的隐藏
#define _ATL_ALL_WARNINGS


#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>

#pragma warning( disable : 4278 )
#pragma warning( disable : 4146 )
	//下面的 #import 基于其 LIBID 导入 IDTExtensibility2 接口
	#import "libid:AC0714F2-3D04-11D1-AE7D-00A0C90F26F4" version("1.0") lcid("0")  raw_interfaces_only named_guids

	//下面的 #import 基于其 LIBID 导入 VS 命令栏
	#import "libid:1CBA492E-7263-47BB-87FE-639000619B15" version("8.0") lcid("0") raw_interfaces_only named_guids

	//下面的 #import 基于其 LIBID 导入 DTE
	#import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("8.0") lcid("0") raw_interfaces_only named_guids

	//下面的 #import 基于其 LIBID 导入 DTE80
	#import "libid:1A31287A-4D7D-413e-8E32-3B374931BD89" version("8.0") lcid("0") raw_interfaces_only named_guids
#pragma warning( default : 4146 )
#pragma warning( default : 4278 )

#define IfFailGo(x) { hr=(x); if (FAILED(hr)) goto Error; }
#define IfFailGoCheck(x, p) { hr=(x); if (FAILED(hr)) goto Error; if(!p) {hr = E_FAIL; goto Error; } }

class DECLSPEC_UUID("BC8C91F4-8D6B-4FDE-9911-5312FD80EC93") GXFEnhanceLib;

using namespace ATL;

class CAddInModule : public CAtlDllModuleT< CAddInModule >
{
public:
	CAddInModule()
	{
		m_hInstance = NULL;
	}

	DECLARE_LIBID(__uuidof(GXFEnhanceLib))

	inline HINSTANCE GetResourceInstance()
	{
		return m_hInstance;
	}

	inline void SetResourceInstance(HINSTANCE hInstance)
	{
		m_hInstance = hInstance;
	}

private:
	HINSTANCE m_hInstance;
};

extern CAddInModule _AtlModule;