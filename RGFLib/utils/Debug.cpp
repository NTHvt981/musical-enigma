#include "Debug.h"
#include <comdef.h>

namespace rgf
{
void DebugOut(wchar_t* fmt, ...)
{
	wchar_t s[4096];
	VA_PRINTS(s);
	OutputDebugString(s);
}

void DebugOutTitle(wchar_t* fmt, ...)
{
	wchar_t s[1024];
	VA_PRINTS(s);
	//SetWindowText(hWnd, s);
}
}