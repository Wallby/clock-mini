#ifndef CLOCK_MINI_H

#include <stdint.h>

#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif

#define CM_GET_SECONDS_FROM_MILLISECONDS(a) (a) * 1000
#define CM_GET_SECONDS_FROM_MICROSECONDS(a) (a) * 1000000
#define CM_GET_SECONDS_FROM_NANOSECONDS(a) (a) * 1000000000

#define CM_GET_MILLISECONDS_FROM_SECONDS(a) (a) / 1000
#define CM_GET_MICROSECONDS_FROM_SECONDS(a) (a) / 1000000
#define CM_GET_NANOSECONDS_FROM_SECONDS(a) (a) / 1000000000

#define CM_GET_MILLISECONDS_FROM_MICROSECONDS(a) (a) * 1000
#define CM_GET_MILLISECONDS_FROM_NANOSECONDS(a) (a) / 1000000

#define CM_GET_MICROSECONDS_FROM_MILLISECONDS(a) (a) * 1000
#define CM_GET_MICROSECONDS_FROM_NANOSECONDS(a) (a) / 1000

#define CM_GET_NANOSECONDS_FROM_MILLISECONDS(a) (a) * 1000
#define CM_GET_NANOSECONDS_FROM_MICROSECONDS(a) (a) * 1000000


static uint64_t cm_get_nanoseconds()
{	
#if defined(_WIN32)
	FILETIME a;
	GetSystemTimeAsFileTime(&a);
	ULARGE_INTEGER b = { .u.LowPart = a.dwLowDateTime, .u.HighPart = a.dwHighDateTime };
	// ^
	// (b.QuadPart)100nanoseconds
	// ^
	// https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-filetime
	return b.QuadPart * 100ull;
#else //< #elif defined(__linux__)
	timeval d;
	gettimeofday(&d, NULL);
	return (((unsigned long long)d.tv_sec) * 1000000ull + ((unsigned long long)d.tv_usec)) * 1000ull;
	//     ^
	//     microseconds
	//     ^
	//     https://man7.org/linux/man-pages/man0/sys_time.h.0p.html
#endif
}

#endif
