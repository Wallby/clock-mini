#ifndef CLOCK_MINI_H

#define CLOCK_MINI_VERSION 0.1.2

#include <stdint.h>
#if defined(_WIN32)
//...
#else
#include <stddef.h> //< for NULL
#endif

#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif

#define CM_GET_SECONDS_FROM_MILLISECONDS(a) (a) / 1000.0
#define CM_GET_SECONDS_FROM_MICROSECONDS(a) (a) / 1000000.0
#define CM_GET_SECONDS_FROM_NANOSECONDS(a) (a) / 1000000000.0

#define CM_GET_MILLISECONDS_FROM_SECONDS(a) (a) * 1000.0
#define CM_GET_MICROSECONDS_FROM_SECONDS(a) (a) * 1000000.0
#define CM_GET_NANOSECONDS_FROM_SECONDS(a) (a) * 1000000000.0

#define CM_GET_MILLISECONDS_FROM_MICROSECONDS(a) (a) / 1000.0
#define CM_GET_MILLISECONDS_FROM_NANOSECONDS(a) (a) / 1000000.0

#define CM_GET_MICROSECONDS_FROM_MILLISECONDS(a) (a) * 1000.0
#define CM_GET_MICROSECONDS_FROM_NANOSECONDS(a) (a) / 1000.0

#define CM_GET_NANOSECONDS_FROM_MILLISECONDS(a) (a) * 1000.0
#define CM_GET_NANOSECONDS_FROM_MICROSECONDS(a) (a) * 1000000.0


static double cm_get_nanoseconds()
{	
#if defined(_WIN32)
	FILETIME a;
	GetSystemTimeAsFileTime(&a);
	//ULARGE_INTEGER b = { .u.LowPart = a.dwLowDateTime, .u.HighPart = a.dwHighDateTime };
	// ^
	// designated initializers not allowed in C++
	// TODO: maybe rename this file to clock_mini.hpm?
	ULARGE_INTEGER b;
	b.u.LowPart = a.dwLowDateTime;
	b.u.HighPart = a.dwHighDateTime;
	// ^
	// (b.QuadPart)100nanoseconds
	// ^
	// https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-filetime
	return b.QuadPart * 100ull;
#else //< #elif defined(__linux__)
	struct timeval d;
	gettimeofday(&d, NULL);
	return (((unsigned long long)d.tv_sec) * 1000000ull + ((unsigned long long)d.tv_usec)) * 1000ull;
	//     ^
	//     microseconds
	//     ^
	//     https://man7.org/linux/man-pages/man0/sys_time.h.0p.html
#endif
}
static double cm_get_microseconds()
{
	return CM_GET_MICROSECONDS_FROM_NANOSECONDS(cm_get_nanoseconds());
}
static double cm_get_milliseconds()
{
	return CM_GET_MILLISECONDS_FROM_NANOSECONDS(cm_get_nanoseconds());
}
static double cm_get_seconds()
{
	return CM_GET_SECONDS_FROM_NANOSECONDS(cm_get_nanoseconds());
}

#endif
